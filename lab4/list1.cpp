#include <glut.h>

// Параметры поворота
static GLfloat xRot = 25.0f;
static GLfloat yRot = -35.0f;

// Вызывается для рисования сцены
void RenderScene(void)
{
    // Очистка окна текущим цветом очистки
    // Очистка буфера глубины
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Восстанавливаем нормальное состояние рисования
    glShadeModel(GL_SMOOTH);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);

    // Боковые грани пирамиды с квадратным основанием
    glBegin(GL_TRIANGLES);
        // Передняя грань
        glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)0);
        glVertex3f(0.0f, 180.0f, 0.0f);
        glColor3ub((GLubyte)0, (GLubyte)255, (GLubyte)0);
        glVertex3f(-140.0f, -100.0f, 140.0f);
        glColor3ub((GLubyte)0, (GLubyte)0, (GLubyte)255);
        glVertex3f(140.0f, -100.0f, 140.0f);

        // Правая грань
        glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)0);
        glVertex3f(0.0f, 180.0f, 0.0f);
        glColor3ub((GLubyte)0, (GLubyte)0, (GLubyte)255);
        glVertex3f(140.0f, -100.0f, 140.0f);
        glColor3ub((GLubyte)255, (GLubyte)255, (GLubyte)0);
        glVertex3f(140.0f, -100.0f, -140.0f);

        // Задняя грань
        glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)0);
        glVertex3f(0.0f, 180.0f, 0.0f);
        glColor3ub((GLubyte)255, (GLubyte)255, (GLubyte)0);
        glVertex3f(140.0f, -100.0f, -140.0f);
        glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)255);
        glVertex3f(-140.0f, -100.0f, -140.0f);

        // Левая грань
        glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)0);
        glVertex3f(0.0f, 180.0f, 0.0f);
        glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)255);
        glVertex3f(-140.0f, -100.0f, -140.0f);
        glColor3ub((GLubyte)0, (GLubyte)255, (GLubyte)0);
        glVertex3f(-140.0f, -100.0f, 140.0f);
    glEnd();

    // Квадратное основание
    glBegin(GL_QUADS);
        glColor3ub((GLubyte)0, (GLubyte)255, (GLubyte)0);
        glVertex3f(-140.0f, -100.0f, 140.0f);
        glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)255);
        glVertex3f(-140.0f, -100.0f, -140.0f);
        glColor3ub((GLubyte)255, (GLubyte)255, (GLubyte)0);
        glVertex3f(140.0f, -100.0f, -140.0f);
        glColor3ub((GLubyte)0, (GLubyte)0, (GLubyte)255);
        glVertex3f(140.0f, -100.0f, 140.0f);
    glEnd();

    // Очищает очередь текущих команд
    glutSwapBuffers();
}

// Эта функция выполняет необходимую инициализацию в контексте
// визуализации
void SetupRC()
{
    // Черный фон
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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

    if (xRot > 356.0f)
        xRot = 0.0f;

    if (xRot < -1.0f)
        xRot = 355.0f;

    if (yRot > 356.0f)
        yRot = 0.0f;

    if (yRot < -1.0f)
        yRot = 355.0f;

    // Обновляется окно
    glutPostRedisplay();
}

void ChangeSize(int w, int h)
{
    GLfloat windowHeight, windowWidth;

    // Предотвращает деление на нуль, когда окно слишком маленькое
    if (h == 0)
        h = 1;

    // Размер поля просмотра устанавливается равным размеру окна
    glViewport(0, 0, w, h);

    // Обновление системы координат перед модификациями
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (w <= h)
    {
        windowHeight = 250.0f * h / w;
        windowWidth = 250.0f;
    }
    else
    {
        windowWidth = 250.0f * w / h;
        windowHeight = 250.0f;
    }

    // Установить объем отсечения
    glOrtho(-windowWidth, windowWidth,
            -windowHeight, windowHeight,
            -500.0f, 500.0f);

    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Smooth shaded square pyramid");
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(RenderScene);
    SetupRC();
    glutMainLoop();
    return 0;
}
