#include <glut.h>
#include <math.h>

#define GL_PI 3.1415f

// Значения углов
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
static int currentListing = 2;

void DrawListing2(void)
{
    GLfloat x, y, z, angle;

    // Вызываем один раз для всех оставшихся точек
    glPointSize(5.0f);
    glBegin(GL_POINTS);

    z = -50.0f;
    for (angle = 0.0f; angle <= (2.0f * GL_PI) * 3.0f; angle += 0.1f)
    {
        x = 50.0f * (GLfloat)sin(angle);
        y = 50.0f * (GLfloat)cos(angle);

        // Задаем точку и немного смещаем значение z
        glVertex3f(x, y, z);
        z += 0.5f;
    }

    // Рисуем точки
    glEnd();
}

void DrawListing3(void)
{
    GLfloat x, y, z, angle;
    GLfloat sizes[2];
    GLfloat step;
    GLfloat curSize;

    // Получаем диапазон размеров поддерживаемых точек и размер шага
    glGetFloatv(GL_POINT_SIZE_RANGE, sizes);
    glGetFloatv(GL_POINT_SIZE_GRANULARITY, &step);

    // Задаем исходный размер точки
    curSize = sizes[0];

    // Задаем начальную координату z
    z = -50.0f;

    // Циклический проход по окружности три раза
    for (angle = 0.0f; angle <= (2.0f * GL_PI) * 3.0f; angle += 0.1f)
    {
        // Расчет значений x и у точек окружности
        x = 50.0f * (GLfloat)sin(angle);
        y = 50.0f * (GLfloat)cos(angle);

        // Задаем размер точки перед указанием примитива
        glPointSize(curSize);

        // Рисуем точку
        glBegin(GL_POINTS);
        glVertex3f(x, y, z);
        glEnd();

        // Увеличиваем значение z и размер точки
        z += 0.5f;
        curSize += step;
    }
}

void DrawListing4(void)
{
    GLfloat x, y, z, angle;

    glLineWidth(2.0f);
    glBegin(GL_LINES);

    // Все линии принадлежат плоскости ху
    z = 0.0f;
    for (angle = 0.0f; angle <= GL_PI; angle += GL_PI / 20.0f)
    {
        // Верхняя половина окружности
        x = 50.0f * (GLfloat)sin(angle);
        y = 50.0f * (GLfloat)cos(angle);
        glVertex3f(x, y, z);

        // Нижняя половина окружности
        x = 50.0f * (GLfloat)sin(angle + GL_PI);
        y = 50.0f * (GLfloat)cos(angle + GL_PI);
        glVertex3f(x, y, z);
    }

    // Рисуются точки
    glEnd();
}

void DrawListing5(void)
{
    GLfloat x, y, z, angle;

    glLineWidth(3.0f);

    // Вызывается один раз для всех точек
    glBegin(GL_LINE_STRIP);
    z = -50.0f;
    for (angle = 0.0f; angle <= (2.0f * GL_PI) * 3.0f; angle += 0.1f)
    {
        x = 50.0f * (GLfloat)sin(angle);
        y = 50.0f * (GLfloat)cos(angle);

        // Задаем точку и немного смещаем значение z
        glVertex3f(x, y, z);
        z += 0.5f;
    }

    // Рисует точки
    glEnd();
}

// В ответ на выбор позиции меню устанавливаются
// соответствующие метки
void ProcessMenu(int value)
{
    switch (value)
    {
        case 1:
            // Включается сглаживание и дается подсказка
            // обеспечить наивысшее качество
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_BLEND);
            glEnable(GL_POINT_SMOOTH);
            glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
            glEnable(GL_LINE_SMOOTH);
            glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
            break;

        case 2:
            // Выключается смешивание и сглаживание
            glDisable(GL_BLEND);
            glDisable(GL_LINE_SMOOTH);
            glDisable(GL_POINT_SMOOTH);
            break;

        case 3:
            currentListing = 2;
            break;

        case 4:
            currentListing = 3;
            break;

        case 5:
            currentListing = 4;
            break;

        case 6:
            currentListing = 5;
            break;
    }

    // Активизируем перерисовывание изображения
    glutPostRedisplay();
}

// Вызывается для рисования сцены
void RenderScene(void)
{
    // Окно очищается текущим цветом очистки
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Записываем состояние матрицы и выполняем поворот
    glPushMatrix();
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);

    if (currentListing == 2)
        DrawListing2();
    else if (currentListing == 3)
        DrawListing3();
    else if (currentListing == 4)
        DrawListing4();
    else
        DrawListing5();

    // Восстанавливаем преобразования
    glPopMatrix();

    // Очищаем стек команд рисования
    glutSwapBuffers();
}

// Функция выполняет необходимую инициализацию
// в контексте визуализации
void SetupRC(void)
{
    // Черный фон
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Цвет рисования выбирается зеленым
    glColor3f(0.0f, 1.0f, 0.0f);

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

    // Обновляем окно
    glutPostRedisplay();
}

void ChangeSize(int w, int h)
{
    GLfloat nRange = 100.0f;

    // Предотвращает деление на нуль
    if (h == 0)
        h = 1;

    // Устанавливаем размеры поля просмотра равными размерам окна
    glViewport(0, 0, w, h);

    // Устанавливаем перспективную систему координат
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Устанавливает объем отсечения с помощью отсекающих
    // плоскостей (левая, правая, нижняя, верхняя, ближняя, дальняя)
    if (w <= h)
        glOrtho(-nRange, nRange, -nRange * h / w,
                nRange * h / w, -nRange, nRange);
    else
        glOrtho(-nRange * w / h, nRange * w / h,
                -nRange, nRange, -nRange, nRange);

    // Обновляется стек матриц проекции модели
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Point and Line Smoothing");
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(RenderScene);
    SetupRC();

    // Создаем меню
    glutCreateMenu(ProcessMenu);
    glutAddMenuEntry("Antialiased Rendering", 1);
    glutAddMenuEntry("Normal Rendering", 2);
    glutAddMenuEntry("Listing 2: points", 3);
    glutAddMenuEntry("Listing 3: point sizes", 4);
    glutAddMenuEntry("Listing 4: lines", 5);
    glutAddMenuEntry("Listing 5: line strip", 6);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
}
