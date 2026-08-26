#include <glut.h>

// Величина поворота
static GLfloat xRot = 20.0f;
static GLfloat yRot = -25.0f;

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
    glColor3ub(128, 128, 128);
    DrawBox(-35.0f, -8.0f, -14.0f, 35.0f, 7.0f, 14.0f);
    DrawBox(-17.0f, 7.0f, -12.0f, 18.0f, 23.0f, 12.0f);

    glColor3ub(70, 70, 70);
    DrawBox(-14.0f, 10.0f, -12.5f, 15.0f, 20.0f, 12.5f);

    glColor3ub(35, 35, 35);
    DrawWheel(-23.0f, 14.0f);
    DrawWheel(23.0f, 14.0f);
    DrawWheel(-23.0f, -14.0f);
    DrawWheel(23.0f, -14.0f);
}

// Вызывается для рисования сцены
void RenderScene(void)
{
    // Очистка окна текущим цветом очистки
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Записываем состояние матрицы и выполняем поворот
    glPushMatrix();
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    glScalef(1.5f, 1.5f, 1.5f);
    DrawCar();
    glPopMatrix();

    // Отобразить результаты
    glutSwapBuffers();
}

// Эта функция выполняет необходимую инициализацию в контексте
// визуализации
void SetupRC()
{
    // Коды и координаты источников света
    GLfloat ambientLight[] = {0.075f, 0.075f, 0.075f, 1.0f};
    GLfloat diffuseLight[] = {0.175f, 0.175f, 0.175f, 1.0f};

    GLfloat lightPos0[] = {20.0f, 70.0f, 20.0f, 1.0f};
    GLfloat lightPos1[] = {28.0f, 75.0f, 25.0f, 1.0f};
    GLfloat lightPos2[] = {-80.0f, 50.0f, -80.0f, 1.0f};
    GLfloat lightPos3[] = {80.0f, -50.0f, 80.0f, 1.0f};

    glEnable(GL_DEPTH_TEST);

    // Активизируется освещение
    glEnable(GL_LIGHTING);

    // Устанавливаются и активизируются источники света
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
    glEnable(GL_LIGHT1);

    glLightfv(GL_LIGHT2, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT2, GL_POSITION, lightPos2);
    glEnable(GL_LIGHT2);

    glLightfv(GL_LIGHT3, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT3, GL_POSITION, lightPos3);
    glEnable(GL_LIGHT3);

    // Активизирует согласование цветов
    glEnable(GL_COLOR_MATERIAL);

    // Свойства материалов соответствуют кодам glColor
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    // Светло-голубой фон
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}

// Управление стрелками
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

// Обновляется проекция и положение источника света
void ChangeSize(int w, int h)
{
    GLfloat nRange = 100.0f;

    // Предотвращает деление на нуль
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
    glutCreateWindow("Four Light Sources Car");
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(RenderScene);
    SetupRC();
    glutMainLoop();

    return 0;
}
