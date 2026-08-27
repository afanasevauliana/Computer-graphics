#include "glew.h"
#include "glut.h"
#include <stdio.h>
#include <stdlib.h>

// Определение заголовка Targa.
#pragma pack(1)
typedef struct {
    GLbyte identsize; // Размер поля ID, следующего за заголовком (0)
    GLbyte colorMapType; // 0 = нет цветовой карты, 1 = есть цветовая карта
    GLbyte imageType; // 0 = нет, 1 = индексированное, 2 = RGB, 3 = серое, +8 = RLE
    unsigned short colorMapStart;  // Первая позиция цветовой карты
    unsigned short colorMapLength; // Количество цветов
    unsigned char colorMapBits;    // Количество битов
    unsigned short xstart;         // Начальная координата X
    unsigned short ystart;         // Начальная координата Y
    unsigned short width;          // Ширина в пикселях
    unsigned short height;         // Высота в пикселях
    GLbyte bits;       // Количество битов на пиксель (8, 16, 24 или 32)
    GLbyte descriptor; // Дескриптор изображения
} TGAHEADER;
#pragma pack(8)

// Распределяет память и загружает данные файла Targa. Возвращает указатель
// на новый буфер, высоту и ширину текстуры, а также формат данных OpenGL.
// После завершения работы буфер необходимо освободить функцией free().
// Поддерживаются простые файлы Targa с 8-, 24- или 32-битовым цветом,
// без палитры и группового кодирования.
GLbyte *gltLoadTGA(const char *szFileName, GLint *iWidth, GLint *iHeight, GLint *iComponents,
                   GLenum *eFormat) {
    FILE *pFile;              // Указатель на файл
    TGAHEADER tgaHeader;      // Заголовок файла TGA
    unsigned long lImageSize; // Размер изображения в байтах
    short sDepth;             // Размер пикселя
    GLbyte *pBits = NULL;     // Указатель на данные изображения

    // Значения по умолчанию на случай ошибки.
    *iWidth = 0;
    *iHeight = 0;
    *eFormat = GL_BGR_EXT;
    *iComponents = GL_RGB8;

    pFile = fopen(szFileName, "rb");
    if (pFile == NULL)
        return NULL;

    // Считываем двоичный заголовок.
    fread(&tgaHeader, 18 /* sizeof(TGAHEADER) */, 1, pFile);

    // Изменяем порядок байтов на платформах с обратным порядком.
#ifdef __APPLE__
    BYTE_SWAP(tgaHeader.colorMapStart);
    BYTE_SWAP(tgaHeader.colorMapLength);
    BYTE_SWAP(tgaHeader.xstart);
    BYTE_SWAP(tgaHeader.ystart);
    BYTE_SWAP(tgaHeader.width);
    BYTE_SWAP(tgaHeader.height);
#endif

    *iWidth = tgaHeader.width;
    *iHeight = tgaHeader.height;
    sDepth = tgaHeader.bits / 8;

    // Поддерживаются только 8-, 24- и 32-битовые файлы Targa.
    if (tgaHeader.bits != 8 && tgaHeader.bits != 24 && tgaHeader.bits != 32) {
        fclose(pFile);
        return NULL;
    }

    lImageSize = tgaHeader.width * tgaHeader.height * sDepth;
    pBits = (GLbyte *)malloc(lImageSize * sizeof(GLbyte));
    if (pBits == NULL) {
        fclose(pFile);
        return NULL;
    }

    // Ошибка здесь может означать неподдерживаемое групповое кодирование
    // или другой формат, который функция не умеет распознавать.
    if (fread(pBits, lImageSize, 1, pFile) != 1) {
        free(pBits);
        fclose(pFile);
        return NULL;
    }

    // Устанавливаем формат, ожидаемый OpenGL.
    switch (sDepth) {
    case 3:
        *eFormat = GL_BGR_EXT;
        *iComponents = GL_RGB8;
        break;
    case 4:
        *eFormat = GL_BGRA_EXT;
        *iComponents = GL_RGBA8;
        break;
    case 1:
        *eFormat = GL_LUMINANCE;
        *iComponents = GL_LUMINANCE8;
        break;
    }

    fclose(pFile);
    return pBits;
}
