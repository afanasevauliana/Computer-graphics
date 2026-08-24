#include "glut.h"

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

void RenderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);

    // каждая последовательная тройка вершин GL_TRIANGLES образует независимую грань
    glBegin(GL_TRIANGLES);

    // четыре верхние грани обходятся против часовой стрелки при наблюдении снаружи
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 60.0f);
    glVertex3f(60.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 60.0f, 0.0f);

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 60.0f);
    glVertex3f(0.0f, 60.0f, 0.0f);
    glVertex3f(-60.0f, 0.0f, 0.0f);

    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 60.0f);
    glVertex3f(-60.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, -60.0f, 0.0f);

    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 60.0f);
    glVertex3f(0.0f, -60.0f, 0.0f);
    glVertex3f(60.0f, 0.0f, 0.0f);

    // у нижних граней порядок экваториальных вершин меняется для сохранения внешнего обхода
    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -60.0f);
    glVertex3f(0.0f, 60.0f, 0.0f);
    glVertex3f(60.0f, 0.0f, 0.0f);

    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -60.0f);
    glVertex3f(-60.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 60.0f, 0.0f);

    glColor3f(1.0f, 0.5f, 0.0f);
    glVertex3f(0.0f, 0.0f, -60.0f);
    glVertex3f(0.0f, -60.0f, 0.0f);
    glVertex3f(-60.0f, 0.0f, 0.0f);

    glColor3f(0.5f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, -60.0f);
    glVertex3f(60.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, -60.0f, 0.0f);

    glEnd();
    glPopMatrix();
    glutSwapBuffers();
}

void SetupRC(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glShadeModel(GL_FLAT);

    // проверка глубины не позволяет дальним граням перекрывать ближние из-за порядка рисования
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
    GLfloat nRange = 100.0f;

    if (h == 0)
        h = 1;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // расширение более длинной оси наблюдаемого объема сохраняет пропорции октаэдра
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
    glutCreateWindow("Octahedron from Triangles");
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(RenderScene);
    SetupRC();
    glutMainLoop();

    return 0;
}
