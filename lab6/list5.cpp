#include "glew.h"
#include "glut.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
// Глобальные переменные модуля для хранения исходных данных изображения
static GLubyte *pImage = NULL;
static GLint iWidth, iHeight, iComponents;
static GLenum eFormat;

// Глобальная переменная для хранения режима рисования
static GLint iRenderMode = 1;
// Определение заголовка targa
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
    GLbyte bits;                   // Количество битов на пиксель
    GLbyte descriptor;             // Дескриптор изображения
} TGAHEADER;

#pragma pack(8)

// Эта функция определена в листинге 3
GLbyte *gltLoadTGA(const char *szFileName, GLint *iWidth, GLint *iHeight, GLint *iComponents,
                   GLenum *eFormat);

// Выполняет необходимую инициализацию в контексте визуализации
void SetupRC(void) {
    // Черный фон
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Загружаем изображение
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    pImage = (GLubyte *)gltLoadTGA("image.tga", &iWidth, &iHeight, &iComponents, &eFormat);
}

void ShutdownRC(void) {
    // Освобождаем исходные данные изображения
    free(pImage);
}

// Должным образом обновляем флаги в ответ на выбор позиции из меню
void ProcessMenu(int value) {
    // Меняем индекс режима визуализации на индекс,
    // соответствующий позиции меню
    iRenderMode = value;

    // Активизируем перерисовывание изображения
    glutPostRedisplay();
}

// Вызывается для рисования сцены
void RenderScene(void) {
    GLfloat invertMap[256];
    GLint i;

    // Очищаем окно текущим цветом очистки
    glClear(GL_COLOR_BUFFER_BIT);

    // Текущее растровое положение соответствует левому нижнему углу окна
    glRasterPos2i(0, 0);

    // В зависимости от индекса режима визуализации выполняются
    // необходимые операции с изображением
    switch (iRenderMode) {
    case 2: // Масштабирование и инверсия цветов согласно варианту 3
        glPixelZoom(2.0f, 0.7f);

        for (i = 0; i < 256; i++)
            invertMap[i] = 1.0f - (GLfloat)i / 255.0f;

        glPixelMapfv(GL_PIXEL_MAP_R_TO_R, 256, invertMap);
        glPixelMapfv(GL_PIXEL_MAP_G_TO_G, 256, invertMap);
        glPixelMapfv(GL_PIXEL_MAP_B_TO_B, 256, invertMap);
        glPixelTransferi(GL_MAP_COLOR, GL_TRUE);
        break;

    case 1: // Просто копия старого изображения
    default:
        break;
    }

    // Рисуются пиксели
    if (pImage != NULL)
        glDrawPixels(iWidth, iHeight, eFormat, GL_UNSIGNED_BYTE, pImage);

    // Обновление всего до настроек по умолчанию
    glPixelTransferi(GL_MAP_COLOR, GL_FALSE);
    glPixelTransferf(GL_RED_SCALE, 1.0f);
    glPixelTransferf(GL_GREEN_SCALE, 1.0f);
    glPixelTransferf(GL_BLUE_SCALE, 1.0f);
    glPixelZoom(1.0f, 1.0f); // Без увеличения пикселей

    // Переключает буферы
    glutSwapBuffers();
}

void ChangeSize(int w, int h) {
    // Предотвращает деление на нуль, когда окно слишком маленькое
    // (нельзя сделать окно нулевой ширины)
    if (h == 0)
        h = 1;

    glViewport(0, 0, w, h);

    // Система координат обновляется перед модификацией
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Устанавливается объем отсечения
    gluOrtho2D(0.0f, (GLfloat)w, 0.0, (GLfloat)h);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Точка входа основной программы

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GL_DOUBLE);
    glutInitWindowSize(400, 300);
    glutCreateWindow("OpenGL Image Operations");
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);

    // Создается меню и добавляются опции выбора
    glutCreateMenu(ProcessMenu);
    glutAddMenuEntry("Original Image", 1);
    glutAddMenuEntry("Zoom and Invert", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    SetupRC(); // Настройка

    glutMainLoop(); // Основной программный цикл

    ShutdownRC(); // Выключение
    return 0;
}
