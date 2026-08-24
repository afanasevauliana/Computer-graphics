#include "glut.h"
#include <math.h>

#define GL_PI 3.1415f

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
static GLenum shadeModel = GL_FLAT;

void RenderScene(void)
{
    GLfloat angle;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // режим затенения задается до glBegin и действует на все последующие многоугольники
    glShadeModel(shadeModel);

    glPushMatrix();
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);

    // первая вершина веера является общей вершиной всех восьми треугольников конуса
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 70.0f);

    for (int i = 0; i <= 8; ++i)
    {
        angle = 2.0f * GL_PI * i / 8.0f;

        // условие i <= 8 повторяет начальную точку окружности при последней итерации
        // цвет задается вершине, а способ его распространения по грани определяет glShadeModel
        if (i % 3 == 0)
            glColor3f(1.0f, 0.0f, 0.0f);
        else if (i % 3 == 1)
            glColor3f(0.0f, 1.0f, 0.0f);
        else
            glColor3f(0.0f, 0.0f, 1.0f);

        glVertex3f(55.0f * cos(angle), 55.0f * sin(angle), -50.0f);
    }
    // повторенная точка окружности замыкает веер, поэтому девять точек контура дают восемь граней
    glEnd();

    glPopMatrix();
    glutSwapBuffers();
}

void SetupRC(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // проверка глубины обеспечивает правильное перекрытие граней при вращении конуса
    glEnable(GL_DEPTH_TEST);
}

void ProcessMenu(int value)
{
    // режим GL_FLAT использует цвет последней вершины грани, а GL_SMOOTH интерполирует цвета вершин
    if (value == 1)
        shadeModel = GL_FLAT;
    else
        shadeModel = GL_SMOOTH;

    // выбранный режим сохраняется в shadeModel и применяется при следующей перерисовке
    glutPostRedisplay();
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
    glutCreateWindow("Flat and Smooth Shading");
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(RenderScene);
    SetupRC();

    glutCreateMenu(ProcessMenu);
    glutAddMenuEntry("GL_FLAT", 1);
    glutAddMenuEntry("GL_SMOOTH", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();

    return 0;
}
