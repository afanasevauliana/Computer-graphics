#include "glut.h"

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

void RenderScene(void)
{
    const GLfloat colors[10][3] = {
        {1.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f},
        {1.0f, 1.0f, 0.0f},
        {0.0f, 1.0f, 1.0f},
        {1.0f, 0.0f, 1.0f},
        {1.0f, 0.5f, 0.0f},
        {0.5f, 1.0f, 0.0f},
        {0.0f, 0.5f, 1.0f},
        {1.0f, 1.0f, 1.0f}
    };
    const GLushort patterns[10] = {
        0xFFFF, 0x5555, 0x00FF, 0x0F0F, 0x3333,
        0x3F07, 0xAAAA, 0xF0F0, 0xFF00, 0x1111
    };

    glClear(GL_COLOR_BUFFER_BIT);

    // одинаковые индексы связывают цвет и шаблон с одной из десяти линий
    glPushMatrix();
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);

    glEnable(GL_LINE_STIPPLE);

    for (int i = 0; i < 10; ++i)
    {
        GLfloat y = -90.0f + i * 20.0f;
        GLfloat z = -45.0f + i * 10.0f;

        // ширина и фактура задаются до glBegin, потому что внутри пары glBegin/glEnd это недопустимо
        glLineWidth(1.0f + i);
        glColor3f(colors[i][0], colors[i][1], colors[i][2]);

        // единичный бит шаблона рисует участок линии, а нулевой оставляет пропуск
        glLineStipple(1, patterns[i]);
        glBegin(GL_LINES);
        glVertex3f(-80.0f, y, z);
        glVertex3f(80.0f, y, z);
        glEnd();
    }

    // восстановление матрицы не позволяет повороту накапливаться при перерисовке
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

    // более длинная ось объема расширяется, поэтому изменение окна не искажает линии
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
    glutCreateWindow("Lines with Different Parameters");
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(RenderScene);
    SetupRC();
    glutMainLoop();

    return 0;
}
