#include <glut.h>

// Параметры поворота
static GLfloat xRot = 20.0f;
static GLfloat yRot = -25.0f;
static int currentExample = 1;

void DrawBox(GLfloat x1, GLfloat y1, GLfloat z1,
             GLfloat x2, GLfloat y2, GLfloat z2)
{
    glBegin(GL_QUADS);
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(x1, y1, z2);
        glVertex3f(x2, y1, z2);
        glVertex3f(x2, y2, z2);
        glVertex3f(x1, y2, z2);

        glNormal3f(0.0f, 0.0f, -1.0f);
        glVertex3f(x2, y1, z1);
        glVertex3f(x1, y1, z1);
        glVertex3f(x1, y2, z1);
        glVertex3f(x2, y2, z1);

        glNormal3f(-1.0f, 0.0f, 0.0f);
        glVertex3f(x1, y1, z1);
        glVertex3f(x1, y1, z2);
        glVertex3f(x1, y2, z2);
        glVertex3f(x1, y2, z1);

        glNormal3f(1.0f, 0.0f, 0.0f);
        glVertex3f(x2, y1, z2);
        glVertex3f(x2, y1, z1);
        glVertex3f(x2, y2, z1);
        glVertex3f(x2, y2, z2);

        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(x1, y2, z2);
        glVertex3f(x2, y2, z2);
        glVertex3f(x2, y2, z1);
        glVertex3f(x1, y2, z1);

        glNormal3f(0.0f, -1.0f, 0.0f);
        glVertex3f(x1, y1, z1);
        glVertex3f(x2, y1, z1);
        glVertex3f(x2, y1, z2);
        glVertex3f(x1, y1, z2);
    glEnd();
}

void DrawWheel(GLfloat x, GLfloat z)
{
    glPushMatrix();
    glTranslatef(x, -9.0f, z);
    glScalef(1.0f, 1.0f, 0.45f);
    glutSolidSphere(7.0, 20, 12);
    glPopMatrix();
}

void DrawCar()
{
    // Устанавливается цвет материала
    glColor3ub(190, 30, 30);
    DrawBox(-35.0f, -8.0f, -14.0f, 35.0f, 7.0f, 14.0f);

    glColor3ub(210, 45, 45);
    DrawBox(-17.0f, 7.0f, -12.0f, 18.0f, 23.0f, 12.0f);

    glColor3ub(40, 70, 100);
    DrawBox(-14.0f, 10.0f, -12.5f, 15.0f, 20.0f, 12.5f);

    glColor3ub(35, 35, 35);
    DrawWheel(-23.0f, 14.0f);
    DrawWheel(23.0f, 14.0f);
    DrawWheel(-23.0f, -14.0f);
    DrawWheel(23.0f, -14.0f);
}

void DrawExample(GLfloat x, GLfloat y, const GLfloat light[4], GLenum materialMode)
{
    const GLfloat material[] = {0.2f, 0.2f, 0.2f, 1.0f};

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light);

    glDisable(GL_COLOR_MATERIAL);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material);

    // Активизируется согласование цветов
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, materialMode);

    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    glScalef(1.5f, 1.5f, 1.5f);
    DrawCar();
    glPopMatrix();
}

// Вызывается для рисования сцены
void RenderScene(void)
{
    const GLfloat brightLight[] = {1.0f, 1.0f, 1.0f, 1.0f};
    const GLfloat halfLight[] = {0.5f, 0.5f, 0.5f, 1.0f};
    const GLenum materialModes[] = {
        GL_AMBIENT,
        GL_DIFFUSE,
        GL_AMBIENT_AND_DIFFUSE
    };

    // Очищаем окно текущим цветом очистки
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (currentExample <= 3)
        DrawExample(0.0f, 0.0f, brightLight,
                    materialModes[currentExample - 1]);
    else
        DrawExample(0.0f, 0.0f, halfLight,
                    materialModes[currentExample - 4]);

    // Отобразить результаты
    glutSwapBuffers();
}

void ProcessMenu(int value)
{
    currentExample = value;
    glutPostRedisplay();
}

// Функция выполняет необходимую инициализацию
// в контексте визуализации
void SetupRC()
{
    glEnable(GL_DEPTH_TEST);

    // Освещение материала
    glEnable(GL_LIGHTING);

    // Светло-синий цвет
    glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
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
    GLfloat nRange = 100.0f;

    // Предотвращение деления на ноль
    if (h == 0)
        h = 1;

    // Устанавливает поле просмотра по размерам окна
    glViewport(0, 0, w, h);

    // Обновляет стек матрицы проектирования
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Устанавливает объем отсечения с помощью отсекающих
    // плоскостей (левая, правая, нижняя, верхняя,
    // ближняя, дальняя)
    if (w <= h)
        glOrtho(-nRange, nRange, -nRange * h / w,
                nRange * h / w, -nRange, nRange);
    else
        glOrtho(-nRange * w / h, nRange * w / h,
                -nRange, nRange, -nRange, nRange);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Light Model and Color Material Cars");
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(RenderScene);
    SetupRC();

    glutCreateMenu(ProcessMenu);
    glutAddMenuEntry("1: bright, GL_AMBIENT", 1);
    glutAddMenuEntry("2: bright, GL_DIFFUSE", 2);
    glutAddMenuEntry("3: bright, GL_AMBIENT_AND_DIFFUSE", 3);
    glutAddMenuEntry("4: half, GL_AMBIENT", 4);
    glutAddMenuEntry("5: half, GL_DIFFUSE", 5);
    glutAddMenuEntry("6: half, GL_AMBIENT_AND_DIFFUSE", 6);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();

    return 0;
}
