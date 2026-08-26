#include "glut.h"

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

struct Point3
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

void DrawQuad(const Point3 &a, const Point3 &b, const Point3 &c, const Point3 &d)
{
    GLfloat ux = b.x - a.x;
    GLfloat uy = b.y - a.y;
    GLfloat uz = b.z - a.z;
    GLfloat vx = c.x - a.x;
    GLfloat vy = c.y - a.y;
    GLfloat vz = c.z - a.z;

    glNormal3f(uy * vz - uz * vy,
               uz * vx - ux * vz,
               ux * vy - uy * vx);

    glVertex3f(a.x, a.y, a.z);
    glVertex3f(b.x, b.y, b.z);
    glVertex3f(c.x, c.y, c.z);
    glVertex3f(d.x, d.y, d.z);
}

void DrawFigure()
{
    const GLfloat frontZ = 45.0f;
    const GLfloat backZ = -45.0f;

    const Point3 outerFront[6] = {
        {-110.0f, 0.0f, frontZ},
        {-80.0f, -40.0f, frontZ},
        {80.0f, -40.0f, frontZ},
        {110.0f, 0.0f, frontZ},
        {80.0f, 40.0f, frontZ},
        {-80.0f, 40.0f, frontZ}};

    const Point3 outerBack[6] = {
        {-110.0f, 0.0f, backZ},
        {-80.0f, -40.0f, backZ},
        {80.0f, -40.0f, backZ},
        {110.0f, 0.0f, backZ},
        {80.0f, 40.0f, backZ},
        {-80.0f, 40.0f, backZ}};

    const Point3 innerFront[6] = {
        {-82.0f, 0.0f, frontZ},
        {-60.0f, -22.0f, frontZ},
        {60.0f, -22.0f, frontZ},
        {82.0f, 0.0f, frontZ},
        {60.0f, 22.0f, frontZ},
        {-60.0f, 22.0f, frontZ}};

    const Point3 innerBack[6] = {
        {-82.0f, 0.0f, backZ},
        {-60.0f, -22.0f, backZ},
        {60.0f, -22.0f, backZ},
        {82.0f, 0.0f, backZ},
        {60.0f, 22.0f, backZ},
        {-60.0f, 22.0f, backZ}};

    glBegin(GL_QUADS);

    // Внешние грани
    glColor3f(0.15f, 0.45f, 0.90f);
    for (int i = 0; i < 6; ++i)
    {
        int next = (i + 1) % 6;

        // Передняя и задняя части рамки
        DrawQuad(outerFront[i], outerFront[next], innerFront[next], innerFront[i]);
        DrawQuad(outerBack[next], outerBack[i], innerBack[i], innerBack[next]);

        // Наружная боковая поверхность
        DrawQuad(outerFront[next], outerFront[i], outerBack[i], outerBack[next]);
    }

    // Внутренние грани
    glColor3f(1.0f, 0.45f, 0.10f);
    for (int i = 0; i < 6; ++i)
    {
        int next = (i + 1) % 6;
        DrawQuad(innerFront[i], innerFront[next], innerBack[next], innerBack[i]);
    }

    glEnd();
}

void ChangeSize(GLsizei w, GLsizei h)
{
    GLfloat nRange = 150.0f;

    if (h == 0)
        h = 1;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (w <= h)
        glOrtho(-nRange, nRange, -nRange * h / w, nRange * h / w,
                -nRange * 2.0f, nRange * 2.0f);
    else
        glOrtho(-nRange * w / h, nRange * w / h, -nRange, nRange,
                -nRange * 2.0f, nRange * 2.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void SetupRC()
{
    glEnable(GL_DEPTH_TEST);

    // Новый цвет фона
    glClearColor(0.82f, 0.86f, 0.90f, 1.0f);
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

    xRot = static_cast<GLfloat>(static_cast<int>(xRot) % 360);
    yRot = static_cast<GLfloat>(static_cast<int>(yRot) % 360);
    glutPostRedisplay();
}

void RenderScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    DrawFigure();
    glPopMatrix();

    glutSwapBuffers();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Variant 3 - Orthographic Projection");
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(RenderScene);
    SetupRC();
    glutMainLoop();

    return 0;
}
