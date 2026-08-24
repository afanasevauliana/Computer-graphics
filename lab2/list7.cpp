#include "glut.h"
#include <math.h>

#define GL_PI 3.1415f

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

void RenderScene(void)
{
    GLfloat angle;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);

    // после первых двух вершин каждая новая вершина GL_TRIANGLE_STRIP создает следующий треугольник
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i < 5; ++i)
    {
        GLfloat x = -90.0f + i * 20.0f;
        GLfloat z = -20.0f + i * 10.0f;

        // попарное задание нижней и верхней вершин образует непрерывную ленту без разрывов
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(x, -30.0f, z);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(x, 30.0f, z);
    }
    glEnd();

    // первая вершина GL_TRIANGLE_FAN становится общей вершиной всех треугольников веера
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(45.0f, 0.0f, 50.0f);

    for (int i = 0; i <= 12; ++i)
    {
        angle = 2.0f * GL_PI * i / 12.0f;
        if (i % 2 == 0)
            glColor3f(0.0f, 0.0f, 1.0f);
        else
            glColor3f(1.0f, 1.0f, 0.0f);
        glVertex3f(45.0f + 30.0f * cos(angle),
                   30.0f * sin(angle), -30.0f);
    }
    // повторение первой точки окружности в конце цикла замыкает боковую поверхность конуса
    glEnd();

    glPopMatrix();
    glutSwapBuffers();
}

void SetupRC(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glShadeModel(GL_FLAT);

    // проверка глубины оставляет видимыми только ближайшие части треугольников
    glEnable(GL_DEPTH_TEST);
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
    GLfloat nRange = 120.0f;

    if (h == 0)
        h = 1;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

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
    glutCreateWindow("Triangle Strip and Triangle Fan");
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(RenderScene);
    SetupRC();
    glutMainLoop();

    return 0;
}
