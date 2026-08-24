#include "glut.h"
#include <math.h>

#define GL_PI 3.1415f

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
static bool bDepth = false;
static bool bCull = false;

void RenderScene(void)
{
    GLfloat angle;

    // буфер глубины необходимо очищать перед построением каждого нового кадра
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // отбор прекращает обработку граней, которые определены как обратные
    if (bCull)
        glEnable(GL_CULL_FACE);
    else
        glDisable(GL_CULL_FACE);

    // проверка глубины оставляет в каждом пикселе фрагмент ближайшей грани
    if (bDepth)
        glEnable(GL_DEPTH_TEST);
    else
        glDisable(GL_DEPTH_TEST);

    glPushMatrix();
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);

    // первая вершина веера является общей вершиной всех боковых граней конуса
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 70.0f);

    for (int i = 0; i <= 16; ++i)
    {
        angle = 2.0f * GL_PI * i / 16.0f;

        // при GL_FLAT каждая грань получает цвет последней заданной вершины
        if (i % 2 == 0)
            glColor3f(1.0f, 0.0f, 0.0f);
        else
            glColor3f(0.0f, 1.0f, 0.0f);

        glVertex3f(50.0f * sin(angle), 50.0f * cos(angle), -40.0f);
    }
    // повторение первой точки окружности замыкает боковую поверхность
    glEnd();

    // основание строится отдельным веером с центром в качестве общей вершины
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -40.0f);

    for (int i = 0; i <= 16; ++i)
    {
        // обратный проход окружности направляет лицевую сторону основания наружу
        angle = 2.0f * GL_PI * (16 - i) / 16.0f;
        glVertex3f(50.0f * sin(angle), 50.0f * cos(angle), -40.0f);
    }
    glEnd();

    glPopMatrix();
    glutSwapBuffers();
}

void SetupRC(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glShadeModel(GL_FLAT);

    // по аналогии с примером методички лицевыми считаются грани с обходом по часовой стрелке
    glFrontFace(GL_CW);
}

void ProcessMenu(int value)
{
    // пункты меню изменяют только состояния проверки глубины и отбора граней
    if (value == 1)
        bDepth = true;
    else if (value == 2)
        bDepth = false;
    else if (value == 3)
        bCull = true;
    else if (value == 4)
        bCull = false;

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

    // изменение границ glOrtho компенсирует пропорции окна без искажения конуса
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
    glutCreateWindow("Depth Test and Back-Face Culling");
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(RenderScene);
    SetupRC();

    glutCreateMenu(ProcessMenu);
    glutAddMenuEntry("Depth test ON", 1);
    glutAddMenuEntry("Depth test OFF", 2);
    glutAddMenuEntry("Back-face culling ON", 3);
    glutAddMenuEntry("Back-face culling OFF", 4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();

    return 0;
}
