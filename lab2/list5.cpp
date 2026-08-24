#include "glut.h"
#include <math.h>

#define GL_PI 3.1415f

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

void RenderScene(void)
{
    const int pointCount = 20;
    GLfloat angle;

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 1.0f, 0.0f);

    // сохранение матрицы не позволяет повороту накапливаться при повторной отрисовке
    glPushMatrix();
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);

    // GL_LINE_LOOP сам соединяет последнюю вершину с первой, поэтому повторять первую точку не нужно
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < pointCount; ++i)
    {
        angle = 2.0f * GL_PI * i / pointCount;
        glVertex3f(50.0f * cos(angle), 50.0f * sin(angle), -60.0f);
    }
    glEnd();

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < pointCount; ++i)
    {
        angle = 2.0f * GL_PI * i / pointCount;
        glVertex3f(50.0f * cos(angle), 50.0f * sin(angle), 60.0f);
    }
    glEnd();

    // GL_LINE_STRIP последовательно соединяет вершины, но не замыкает ломаную автоматически
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= pointCount * 2; ++i)
    {
        angle = 4.0f * GL_PI * i / (pointCount * 2);
        glVertex3f(50.0f * cos(angle), 50.0f * sin(angle),
                   -60.0f + 120.0f * i / (pointCount * 2));
    }
    // две окружности содержат по 20 точек, а соединяющая их спираль — 41 точку
    glEnd();

    glPopMatrix();
    glutSwapBuffers();
}

void SetupRC(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void SpecialKeys(int key, int x, int y)
{
    if (key == GLUT_KEY_UP)
        xRot -= 5.0f;
    if (key == GLUT_KEY_DOWN)
        xRot += 5.0f;
    if (key == GLUT_KEY_LEFT)
        yRot -= 5.0f;
    if (key == GLUT_KEY_RIGHT)
        yRot += 5.0f;

    if (xRot > 355.0f)
        xRot = 0.0f;
    if (xRot < 0.0f)
        xRot = 355.0f;
    if (yRot > 355.0f)
        yRot = 0.0f;
    if (yRot < 0.0f)
        yRot = 355.0f;

    glutPostRedisplay();
}

void ChangeSize(int w, int h)
{
    GLfloat nRange = 100.0f;

    if (h == 0)
        h = 1;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // расширение более длинной оси наблюдаемого объема сохраняет пропорции объекта
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
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Line Strip and Line Loop Object");
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(RenderScene);
    SetupRC();
    glutMainLoop();

    return 0;
}
