#include "glut.h"
#include <GL/glu.h>

// Параметры освещения
GLfloat whiteLight[] = {0.2f, 0.2f, 0.2f, 1.0f};
GLfloat sourceLight[] = {0.8f, 0.8f, 0.8f, 1.0f};
GLfloat lightPos[] = {0.0f, 0.0f, 0.0f, 1.0f};

// Вызывается для рисования сцены
void RenderScene()
{
    // Углы поворота системы Земля–Луна
    static GLfloat fMoonRot = 0.0f;
    static GLfloat fEarthRot = 0.0f;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    // Перемещаем всю сцену в поле зрения
    glTranslatef(0.0f, 0.0f, -300.0f);

    // Солнце
    glDisable(GL_LIGHTING);
    glColor3ub(255, 255, 0);
    glutSolidSphere(15.0f, 30, 17);
    glEnable(GL_LIGHTING);

    // Источник света находится в центре Солнца
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    // Земля и Луна
    glPushMatrix();
    glRotatef(fEarthRot, 0.0f, 1.0f, 0.0f);
    glTranslatef(105.0f, 0.0f, 0.0f);

    // Земля
    glColor3ub(0, 0, 255);
    glutSolidSphere(15.0f, 30, 17);

    // Луна вращается относительно Земли
    glRotatef(fMoonRot, 0.0f, 1.0f, 0.0f);
    glTranslatef(30.0f, 0.0f, 0.0f);
    glColor3ub(200, 200, 200);
    glutSolidSphere(6.0f, 30, 17);
    glPopMatrix();

    // Дополнительная планета без спутника
    // Она движется в плоскости и по траектории системы Земля–Луна
    glPushMatrix();
    glRotatef(fEarthRot + 180.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(105.0f, 0.0f, 0.0f);
    glColor3ub(0, 200, 100);
    glutSolidSphere(12.0f, 30, 17);
    glPopMatrix();

    glPopMatrix();

    // Изменяем углы поворота
    fMoonRot += 15.0f;
    if (fMoonRot > 360.0f)
        fMoonRot = 0.0f;

    fEarthRot += 5.0f;
    if (fEarthRot > 360.0f)
        fEarthRot = 0.0f;

    glutSwapBuffers();
}

// Выполняет необходимую инициализацию визуализации
void SetupRC()
{
    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);

    glEnable(GL_LIGHTING);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, whiteLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, sourceLight);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glEnable(GL_LIGHT0);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void TimerFunc(int value)
{
    glutPostRedisplay();
    glutTimerFunc(100, TimerFunc, 1);
}

void ChangeSize(int w, int h)
{
    if (h == 0)
        h = 1;

    GLfloat fAspect = static_cast<GLfloat>(w) / static_cast<GLfloat>(h);

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, fAspect, 1.0f, 425.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Earth/Moon/Sun System - Variant 3");
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    glutTimerFunc(250, TimerFunc, 1);
    SetupRC();
    glutMainLoop();

    return 0;
}
