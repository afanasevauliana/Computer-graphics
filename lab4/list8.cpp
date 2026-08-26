#include <glut.h>
#include <math.h>

#define GLT_PI 3.14159265358979323846
#define NUM_SPHERES 40

typedef GLfloat GLTVector3[3];

struct SphereData
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
    GLubyte red;
    GLubyte green;
    GLubyte blue;
};

SphereData spheres[NUM_SPHERES];
static GLfloat yRot = 0.0f;
static GLfloat viewRot = 20.0f;

GLfloat fogGray[] = {0.35f, 0.35f, 0.35f, 1.0f};
GLfloat fogBlue[] = {0.15f, 0.25f, 0.45f, 1.0f};
GLfloat fogWhite[] = {0.8f, 0.8f, 0.8f, 1.0f};

// Масштабирование вектора по длине - создание единичного вектора
void gltNormalizeVector(GLTVector3 vNormal)
{
    GLfloat length = (GLfloat)sqrt(vNormal[0] * vNormal[0] +
                                   vNormal[1] * vNormal[1] +
                                   vNormal[2] * vNormal[2]);
    vNormal[0] /= length;
    vNormal[1] /= length;
    vNormal[2] /= length;
}

void gltDrawTorus(GLfloat majorRadius, GLfloat minorRadius,
                  GLint numMajor, GLint numMinor)
{
    GLTVector3 vNormal;
    double majorStep = 2.0 * GLT_PI / numMajor;
    double minorStep = 2.0 * GLT_PI / numMinor;

    for (int i = 0; i < numMajor; ++i)
    {
        double a0 = i * majorStep;
        double a1 = a0 + majorStep;
        GLfloat x0 = (GLfloat)cos(a0);
        GLfloat y0 = (GLfloat)sin(a0);
        GLfloat x1 = (GLfloat)cos(a1);
        GLfloat y1 = (GLfloat)sin(a1);

        glBegin(GL_TRIANGLE_STRIP);
        for (int j = 0; j <= numMinor; ++j)
        {
            double b = j * minorStep;
            GLfloat c = (GLfloat)cos(b);
            GLfloat r = minorRadius * c + majorRadius;
            GLfloat z = minorRadius * (GLfloat)sin(b);

            vNormal[0] = x0 * c;
            vNormal[1] = y0 * c;
            vNormal[2] = z / minorRadius;
            gltNormalizeVector(vNormal);
            glNormal3fv(vNormal);
            glVertex3f(x0 * r, y0 * r, z);

            vNormal[0] = x1 * c;
            vNormal[1] = y1 * c;
            vNormal[2] = z / minorRadius;
            gltNormalizeVector(vNormal);
            glNormal3fv(vNormal);
            glVertex3f(x1 * r, y1 * r, z);
        }
        glEnd();
    }
}

// Рисуется земля с координатной сеткой
void DrawGround(void)
{
    GLfloat fExtent = 10.0f;
    GLfloat fStep = 1.0f;
    GLfloat y = 0.0f;

    glDisable(GL_LIGHTING);
    glColor3ub(100, 100, 100);
    glBegin(GL_LINES);
    for (GLfloat iLine = -fExtent; iLine <= fExtent; iLine += fStep)
    {
        glVertex3f(iLine, y, fExtent);
        glVertex3f(iLine, y, -fExtent);
        glVertex3f(fExtent, y, iLine);
        glVertex3f(-fExtent, y, iLine);
    }
    glEnd();
    glEnable(GL_LIGHTING);
}

void DrawWorld(void)
{
    DrawGround();

    // Рисуются сферы на разном уровне по оси z
    for (int i = 0; i < NUM_SPHERES; ++i)
    {
        glPushMatrix();
        glTranslatef(spheres[i].x, spheres[i].y, spheres[i].z);
        glColor3ub(spheres[i].red, spheres[i].green, spheres[i].blue);
        glutSolidSphere(0.45f, 13, 13);
        glPopMatrix();
    }

    glPushMatrix();
    glTranslatef(0.0f, 1.1f, 0.0f);

    glPushMatrix();
    glRotatef(-yRot * 2.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(2.0f, 0.0f, 0.0f);
    glColor3ub(255, 220, 0);
    glutSolidSphere(0.45f, 13, 26);
    glPopMatrix();

    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    glColor3ub(220, 60, 40);
    gltDrawTorus(1.2f, 0.45f, 40, 20);
    glPopMatrix();
}

// В ответ на выбор позиции меню устанавливаются
// соответствующие метки
void ProcessMenu(int value)
{
    switch (value)
    {
        case 1:
            glEnable(GL_FOG);
            break;
        case 2:
            glDisable(GL_FOG);
            break;
        case 3:
            glFogfv(GL_FOG_COLOR, fogGray);
            glClearColor(fogGray[0], fogGray[1], fogGray[2], fogGray[3]);
            break;
        case 4:
            glFogfv(GL_FOG_COLOR, fogBlue);
            glClearColor(fogBlue[0], fogBlue[1], fogBlue[2], fogBlue[3]);
            break;
        case 5:
            glFogfv(GL_FOG_COLOR, fogWhite);
            glClearColor(fogWhite[0], fogWhite[1], fogWhite[2], fogWhite[3]);
            break;
        case 6:
            glFogi(GL_FOG_MODE, GL_LINEAR);
            break;
        case 7:
            glFogi(GL_FOG_MODE, GL_EXP);
            break;
        case 8:
            glFogi(GL_FOG_MODE, GL_EXP2);
            break;
    }

    // Активизируем перерисовывание изображения
    glutPostRedisplay();
}

// Вызывается для рисования сцены
void RenderScene(void)
{
    // Очищаем окно текущим цветом очистки
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(viewRot, 1.0f, 0.0f, 0.0f);
    DrawWorld();

    // Переключение буферов
    glutSwapBuffers();
}

// Эта функция выполняет необходимую инициализацию в контексте
// визуализации
void SetupRC()
{
    GLfloat ambientLight[] = {0.3f, 0.3f, 0.3f, 1.0f};
    GLfloat diffuseLight[] = {0.7f, 0.7f, 0.7f, 1.0f};
    GLfloat lightPos[] = {-5.0f, 10.0f, 5.0f, 1.0f};

    // Сферы размещаются в уменьшенном пространстве
    for (int i = 0; i < NUM_SPHERES; ++i)
    {
        spheres[i].x = (GLfloat)((i * 37) % 180 - 90) * 0.1f;
        spheres[i].y = 0.45f;
        spheres[i].z = (GLfloat)((i * 67) % 180 - 90) * 0.1f;
        spheres[i].red = (GLubyte)(55 + (i * 47) % 200);
        spheres[i].green = (GLubyte)(55 + (i * 83) % 200);
        spheres[i].blue = (GLubyte)(55 + (i * 29) % 200);
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glEnable(GL_LIGHT0);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    // Установка параметров тумана
    glEnable(GL_FOG);
    glFogfv(GL_FOG_COLOR, fogGray);
    // Насколько далеко начинается туман
    glFogf(GL_FOG_START, 2.0f);
    // Насколько далеко заканчивается туман
    glFogf(GL_FOG_END, 12.0f);
    glFogf(GL_FOG_DENSITY, 0.18f);
    // Какое уравнение тумана используется
    glFogi(GL_FOG_MODE, GL_LINEAR);

    // Цвет тумана соответствует фону
    glClearColor(fogGray[0], fogGray[1], fogGray[2], fogGray[3]);
}

void SpecialKeys(int key, int x, int y)
{
    if (key == GLUT_KEY_UP)
        viewRot -= 5.0f;
    if (key == GLUT_KEY_DOWN)
        viewRot += 5.0f;

    // Обновление окна
    glutPostRedisplay();
}

// Вызывается библиотекой GLUT в холостом состоянии
void TimerFunction(int value)
{
    yRot += 1.0f;
    if (yRot > 360.0f)
        yRot = 0.0f;

    // Перерисовывает сцену с новыми координатами
    glutPostRedisplay();
    glutTimerFunc(33, TimerFunction, 1);
}

void ChangeSize(int w, int h)
{
    GLfloat nRange = 13.0f;

    // Предотвращает деление на нуль, когда окно слишком маленькое
    if (h == 0)
        h = 1;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Устанавливается объём сечения
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
    glutCreateWindow("Fogged Sphere World");
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    glutSpecialFunc(SpecialKeys);
    glutTimerFunc(33, TimerFunction, 1);

    SetupRC();

    // Создаем меню
    glutCreateMenu(ProcessMenu);
    glutAddMenuEntry("Fog ON", 1);
    glutAddMenuEntry("Fog OFF", 2);
    glutAddMenuEntry("Fog color: gray", 3);
    glutAddMenuEntry("Fog color: blue", 4);
    glutAddMenuEntry("Fog color: white", 5);
    glutAddMenuEntry("Fog equation: GL_LINEAR", 6);
    glutAddMenuEntry("Fog equation: GL_EXP", 7);
    glutAddMenuEntry("Fog equation: GL_EXP2", 8);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
}
