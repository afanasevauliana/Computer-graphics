#include "glut.h"

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

void RenderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    // сохранение матрицы не позволяет повороту накапливаться при повторной отрисовке
    glPushMatrix();
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);

    glPointSize(2.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POINTS);
    glVertex3f(-75.0f, -50.0f, -50.0f);
    glEnd();

    // выбранные размер и цвет действуют на следующие точки до очередного изменения состояния
    glPointSize(4.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_POINTS);
    glVertex3f(-45.0f, 30.0f, -30.0f);
    glEnd();

    glPointSize(6.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_POINTS);
    glVertex3f(-15.0f, -20.0f, -10.0f);
    glEnd();

    glPointSize(8.0f);
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_POINTS);
    glVertex3f(15.0f, 50.0f, 10.0f);
    glEnd();

    glPointSize(9.0f);
    glColor3f(0.0f, 1.0f, 1.0f);
    glBegin(GL_POINTS);
    glVertex3f(45.0f, -40.0f, 30.0f);
    glEnd();

    // разные значения z задают точки в трехмерном пространстве, хотя проекция остается ортографической
    glPointSize(10.0f);
    glColor3f(1.0f, 0.0f, 1.0f);
    glBegin(GL_POINTS);
    glVertex3f(75.0f, 20.0f, 50.0f);
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

    // нулевая высота заменяется единицей, чтобы исключить деление на ноль
    if (h == 0)
        h = 1;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // более длинная ось объема расширяется для сохранения пропорций при изменении окна
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
    glutCreateWindow("Points of Different Sizes and Colors");
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(RenderScene);
    SetupRC();
    glutMainLoop();

    return 0;
}
