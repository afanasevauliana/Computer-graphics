#include "glew.h"
#include "glut.h"
#include <stdlib.h>

// Растровый образ размером 24x24
GLubyte image[72] = {
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00,
    0x00, 0x18, 0x00,
    0x00, 0x3c, 0x00,
    0x00, 0x7e, 0x00,
    0x00, 0xe7, 0x00,
    0x01, 0xc3, 0x80,
    0x03, 0xff, 0xc0,
    0x07, 0x00, 0xe0,
    0x0e, 0x00, 0x70,
    0x1c, 0x00, 0x38,
    0x38, 0x00, 0x1c,
    0x39, 0x81, 0x9c,
    0x1d, 0x81, 0xb8,
    0x0f, 0x81, 0xf0,
    0x07, 0x00, 0xe0,
    0x03, 0x81, 0xc0,
    0x01, 0xc3, 0x80,
    0x00, 0xe7, 0x00,
    0x00, 0x7e, 0x00,
    0x00, 0x3c, 0x00,
    0x00, 0x18, 0x00,
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00
};

int windowWidth = 512;
int windowHeight = 512;

// Функция выполняет всю необходимую инициализацию в контексте визуализации
void SetupRC() {
    // Черный фон
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Строки битового образа выровнены по одному байту
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

// Устанавливается система координат, согласованная с координатами окна
void ChangeSize(int w, int h) {
    // Предотвращает деление на нуль, когда окно слишком маленькое
    // (нельзя сделать окно нулевой ширины)
    if (h == 0)
        h = 1;

    windowWidth = w;
    windowHeight = h;

    glViewport(0, 0, w, h);

    // Система координат обновляется перед модификацией
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Псевдокоординаты окна
    gluOrtho2D(0.0, (GLfloat)w, 0.0f, (GLfloat)h);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


// Вызывается для рисования сцены
void RenderScene(void) {
    int x, y;
    const int imageSize = 24;
    const int imagesPerSide = 6;
    const int squareSize = imageSize * imagesPerSide;
    const int startX = (windowWidth - squareSize) / 2;
    const int startY = (windowHeight - squareSize) / 2;

    // Очищаем окно текущим цветом очистки
    glClear(GL_COLOR_BUFFER_BIT);

    // Цикл из 6 строк и столбцов
    for (y = 0; y < imagesPerSide; y++) {
        for (x = 0; x < imagesPerSide; x++) {
            // Цвет каждого изображения задается случайно
            glColor3f((GLfloat)rand() / RAND_MAX,
                      (GLfloat)rand() / RAND_MAX,
                      (GLfloat)rand() / RAND_MAX);

            // Устанавливается растровое положение данного образа
            glRasterPos2i(startX + x * imageSize, startY + y * imageSize);

            // Рисуется битовый образ размером 24x24
            glBitmap(imageSize, imageSize, 0.0, 0.0, 0.0, 0.0, image);
        }
    }

    // Переключает буферы
    glutSwapBuffers();
}


// Точка входа основной программы
int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(512, 512);
    glutCreateWindow("OpenGL Bitmaps");
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    SetupRC();
    glutMainLoop();
    return 0;
}
