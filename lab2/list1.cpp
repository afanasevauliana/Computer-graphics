#include "glut.h"
#include <math.h>
#define GL_PI 3.1415f

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

void RenderScene(void)
{
    GLfloat x, y, z, angle;
    glClear(GL_COLOR_BUFFER_BIT);
    // сохраняем матрицу, чтобы поворот не накапливался при каждой перерисовке
    glPushMatrix();
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    // sin и cos получают радианы; четыре оборота с шагом 0,1 дают около 252 точек
    glBegin(GL_POINTS);

    z = -50.0f;
    for (angle = 0.0f; angle <= (2.0f * GL_PI) * 4.0f; angle += 0.1f)
    {
        x = 50.0f * sin(angle);
        y = 50.0f * cos(angle);
        glVertex3f(x, y, z);
        z += 0.4f;
    }

    glEnd();
    glPopMatrix();
    glutSwapBuffers();
}

void SetupRC(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
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

    // после полного оборота возвращаем угол в диапазон от 0 до 355 градусов
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

void ProcessMenu(int value)
{
    if (value == 1)
    {
        xRot = 0.0f;
        yRot = 0.0f;
        glutPostRedisplay();
    }
}

void ChangeSize(int w, int h)
{
    GLfloat nRange = 100.0f;

    if (h == 0)
        h = 1;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // расширяем более длинную ось объема, чтобы фигура не растягивалась вместе с окном
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
    glutCreateWindow("Points Example");
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(RenderScene);
    SetupRC();

    glutCreateMenu(ProcessMenu);
    glutAddMenuEntry("Reset rotation", 1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();

    return 0;
}
