#include "glew.h"
#include "glut.h"
#include <stdio.h>
#include <stdlib.h>

// Определение заголовка Targa.
#pragma pack(1)
typedef struct {
    GLbyte identsize;
    GLbyte colorMapType;
    GLbyte imageType;
    unsigned short colorMapStart;
    unsigned short colorMapLength;
    unsigned char colorMapBits;
    unsigned short xstart;
    unsigned short ystart;
    unsigned short width;
    unsigned short height;
    GLbyte bits;
    GLbyte descriptor;
} TGAHEADER;
#pragma pack(8)

// Записывает текущее поле просмотра в файл Targa. Перед вызовом этой функции
// при двойной буферизации следует вызвать SwapBuffers, а при одинарной — glFinish.
// Возвращает 0 при ошибке и 1 при успешном завершении.
GLint gltWriteTGA(const char *szFileName) {
    FILE *pFile;              // Указатель на файл
    TGAHEADER tgaHeader;      // Заголовок файла TGA
    unsigned long lImageSize; // Размер изображения в байтах
    GLbyte *pBits = NULL;     // Указатель на данные изображения
    GLint iViewport[4];       // Размер поля просмотра в пикселях
    GLenum lastBuffer;        // Предыдущее значение буфера чтения

    glGetIntegerv(GL_VIEWPORT, iViewport);

    // Файлы Targa плотно упакованы и содержат по три байта на пиксель.
    lImageSize = iViewport[2] * 3 * iViewport[3];

    pBits = (GLbyte *)malloc(lImageSize);
    if (pBits == NULL)
        return 0;

    // Настраиваем плотную упаковку данных из буфера цвета.
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glPixelStorei(GL_PACK_ROW_LENGTH, 0);
    glPixelStorei(GL_PACK_SKIP_ROWS, 0);
    glPixelStorei(GL_PACK_SKIP_PIXELS, 0);

    // Сохраняем текущий буфер чтения, читаем передний буфер и восстанавливаем настройку.
    glGetIntegerv(GL_READ_BUFFER, (GLint *)&lastBuffer);
    glReadBuffer(GL_FRONT);
    glReadPixels(0, 0, iViewport[2], iViewport[3], GL_BGR_EXT, GL_UNSIGNED_BYTE, pBits);
    glReadBuffer(lastBuffer);

    // Инициализируем заголовок файла Targa.
    tgaHeader.identsize = 0;
    tgaHeader.colorMapType = 0;
    tgaHeader.imageType = 2;
    tgaHeader.colorMapStart = 0;
    tgaHeader.colorMapLength = 0;
    tgaHeader.colorMapBits = 0;
    tgaHeader.xstart = 0;
    tgaHeader.ystart = 0;
    tgaHeader.width = iViewport[2];
    tgaHeader.height = iViewport[3];
    tgaHeader.bits = 24;
    tgaHeader.descriptor = 0;

#ifdef __APPLE__
    BYTE_SWAP(tgaHeader.colorMapStart);
    BYTE_SWAP(tgaHeader.colorMapLength);
    BYTE_SWAP(tgaHeader.xstart);
    BYTE_SWAP(tgaHeader.ystart);
    BYTE_SWAP(tgaHeader.width);
    BYTE_SWAP(tgaHeader.height);
#endif

    pFile = fopen(szFileName, "wb");
    if (pFile == NULL) {
        free(pBits);
        return 0;
    }

    fwrite(&tgaHeader, sizeof(TGAHEADER), 1, pFile);
    fwrite(pBits, lImageSize, 1, pFile);

    free(pBits);
    fclose(pFile);
    return 1;
}
