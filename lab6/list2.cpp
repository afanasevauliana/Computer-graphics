#include "glew.h"
#include "glut.h"
#include <stdlib.h>

GLbyte *gltLoadTGA(const char *szFileName, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat);

// Функция выполняет всю необходимую инициализацию в контексте визуализации
void SetupRC() {
    // Черный фон
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

// Устанавливается система координат, согласованная с координатами окна
void ChangeSize(int w, int h) {
    if (h == 0)
        h = 1;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLfloat)w, 0.0, (GLfloat)h);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void RenderScene(void) {
    GLubyte *pImage = NULL;
    GLint iWidth, iHeight, iComponents;
    GLint iViewport[4];
    GLenum eFormat;
    // Очищаем окно текущим цветом очистки
    glClear(GL_COLOR_BUFFER_BIT);
    // Информация в файле Targa выравнена по одному байту
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Загружает файл TGA и получает ширину, высоту, компоненты и формат
    pImage = (GLubyte *)gltLoadTGA("image.tga", &iWidth, &iHeight, &iComponents, &eFormat);

    if (pImage != NULL) {
        glGetIntegerv(GL_VIEWPORT, iViewport);

        // Рисуется исходное изображение в правом верхнем углу
        glRasterPos2i(iViewport[2] - iWidth, iViewport[3] - iHeight);
        glDrawPixels(iWidth, iHeight, eFormat, GL_UNSIGNED_BYTE, pImage);

        // Рисуется красная компонента изображения
        glPixelTransferf(GL_RED_SCALE, 1.0f);
        glPixelTransferf(GL_GREEN_SCALE, 0.0f);
        glPixelTransferf(GL_BLUE_SCALE, 0.0f);
        glRasterPos2i(2 * (iViewport[2] - iWidth) / 3, 2 * (iViewport[3] - iHeight) / 3);
        glDrawPixels(iWidth, iHeight, eFormat, GL_UNSIGNED_BYTE, pImage);

        // Рисуется зеленая компонента изображения
        glPixelTransferf(GL_RED_SCALE, 0.0f);
        glPixelTransferf(GL_GREEN_SCALE, 1.0f);
        glPixelTransferf(GL_BLUE_SCALE, 0.0f);
        glRasterPos2i((iViewport[2] - iWidth) / 3, (iViewport[3] - iHeight) / 3);
        glDrawPixels(iWidth, iHeight, eFormat, GL_UNSIGNED_BYTE, pImage);

        // Рисуется синяя компонента изображения в левом нижнем углу
        glPixelTransferf(GL_RED_SCALE, 0.0f);
        glPixelTransferf(GL_GREEN_SCALE, 0.0f);
        glPixelTransferf(GL_BLUE_SCALE, 1.0f);
        glRasterPos2i(0, 0);
        glDrawPixels(iWidth, iHeight, eFormat, GL_UNSIGNED_BYTE, pImage);

        // Возвращаются исходные значения цветовых компонент
        glPixelTransferf(GL_RED_SCALE, 1.0f);
        glPixelTransferf(GL_GREEN_SCALE, 1.0f);
        glPixelTransferf(GL_BLUE_SCALE, 1.0f);
    }

    // Данные изображения уже не нужны
    free(pImage);
    // Переключает буферы
    glutSwapBuffers();
}

// Точка входа основной программы
int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL TGA Image");
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    SetupRC();
    glutMainLoop();
    return 0;
}
