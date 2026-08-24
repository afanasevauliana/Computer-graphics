#include "glut.h"
#include <math.h>

#define GL_PI 3.1415f

static int segmentCount = 8;

void RenderScene(void)
{
    GLfloat angle;

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 1.0f, 0.0f);

    // меньшее угловое расстояние между вершинами дает более короткие отрезки и более точную кривую
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= segmentCount; ++i)
    {
        angle = 2.0f * GL_PI * i / segmentCount;
        glVertex3f(70.0f * cos(angle), 70.0f * sin(angle), 0.0f);
    }
    glEnd();

    glutSwapBuffers();
}

void SetupRC(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void ProcessMenu(int value)
{
    // значение пункта меню сразу задает число отрезков в одном из трех примеров
    segmentCount = value;
    glutPostRedisplay();
}

void ChangeSize(int w, int h)
{
    GLfloat nRange = 100.0f;

    // замена нулевой высоты исключает деление на ноль при изменении размеров окна
    if (h == 0)
        h = 1;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // расширение более длинной оси наблюдаемого объема сохраняет форму окружности
    if (w <= h)
        glOrtho(-nRange, nRange, -nRange * h / w, nRange * h / w,
                -nRange, nRange);
    else
        glOrtho(-nRange * w / h, nRange * w / h, -nRange, nRange,
                -nRange, nRange);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Curve Approximation");
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    SetupRC();

    glutCreateMenu(ProcessMenu);
    glutAddMenuEntry("8 segments", 8);
    glutAddMenuEntry("24 segments", 24);
    glutAddMenuEntry("72 segments", 72);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();

    return 0;
}
