#include <glut.h>
#include <math.h>

// Параметры поворотов
static GLfloat xRot = 10.0f;
static GLfloat yRot = -20.0f;

typedef GLfloat GLTVector3[3];
typedef GLfloat GLTVector4[4];
typedef GLfloat GLTMatrix[16];

// Коды и координаты источников света
GLfloat lightPos0[] = {-80.0f, 120.0f, 60.0f, 1.0f};
GLfloat lightPos1[] = {90.0f, 130.0f, 50.0f, 1.0f};
GLfloat lightPos2[] = {0.0f, 110.0f, -100.0f, 1.0f};

// Матрицы преобразования, дающие проекции теней
GLTMatrix shadowMat0;
GLTMatrix shadowMat1;
GLTMatrix shadowMat2;

// Вычитание одного вектора из другого
void gltSubtractVectors(const GLTVector3 vFirst,
                        const GLTVector3 vSecond,
                        GLTVector3 vResult)
{
    vResult[0] = vFirst[0] - vSecond[0];
    vResult[1] = vFirst[1] - vSecond[1];
    vResult[2] = vFirst[2] - vSecond[2];
}

// Вычислить векторное произведение двух векторов
void gltVectorCrossProduct(const GLTVector3 vU,
                           const GLTVector3 vV,
                           GLTVector3 vResult)
{
    vResult[0] = vU[1] * vV[2] - vV[1] * vU[2];
    vResult[1] = -vU[0] * vV[2] + vV[0] * vU[2];
    vResult[2] = vU[0] * vV[1] - vV[0] * vU[1];
}

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

// Три точки на плоскости расположены против часовой стрелки, вычисление
// нормали
void gltGetNormalVector(const GLTVector3 vP1,
                        const GLTVector3 vP2,
                        const GLTVector3 vP3,
                        GLTVector3 vNormal)
{
    GLTVector3 vV1, vV2;
    gltSubtractVectors(vP2, vP1, vV1);
    gltSubtractVectors(vP3, vP1, vV2);
    gltVectorCrossProduct(vV1, vV2, vNormal);
    gltNormalizeVector(vNormal);
}

// Полученные три коэффициента уравнения плоскости
// дают три точки на поверхности
void gltGetPlaneEquation(const GLTVector3 vPoint1,
                         const GLTVector3 vPoint2,
                         const GLTVector3 vPoint3,
                         GLTVector4 vPlane)
{
    gltGetNormalVector(vPoint1, vPoint2, vPoint3, vPlane);
    vPlane[3] = -(vPlane[0] * vPoint3[0] +
                  vPlane[1] * vPoint3[1] +
                  vPlane[2] * vPoint3[2]);
}

// Создание матрицы теневой проекции из коэффициентов
// уравнения плоскости и положения света
void gltMakeShadowMatrix(GLTVector3 vPoints[3],
                         GLTVector4 vLightPos,
                         GLTMatrix destMat)
{
    GLTVector4 vPlaneEquation;
    GLfloat dot;

    gltGetPlaneEquation(vPoints[0], vPoints[1], vPoints[2],
                        vPlaneEquation);

    // Скалярное произведение направляющего вектора
    // плоскости и положения источника света
    dot = vPlaneEquation[0] * vLightPos[0] +
          vPlaneEquation[1] * vLightPos[1] +
          vPlaneEquation[2] * vLightPos[2] +
          vPlaneEquation[3] * vLightPos[3];

    // Выполняется проектирование
    // Первый столбец
    destMat[0] = dot - vLightPos[0] * vPlaneEquation[0];
    destMat[4] = 0.0f - vLightPos[0] * vPlaneEquation[1];
    destMat[8] = 0.0f - vLightPos[0] * vPlaneEquation[2];
    destMat[12] = 0.0f - vLightPos[0] * vPlaneEquation[3];

    // Второй столбец
    destMat[1] = 0.0f - vLightPos[1] * vPlaneEquation[0];
    destMat[5] = dot - vLightPos[1] * vPlaneEquation[1];
    destMat[9] = 0.0f - vLightPos[1] * vPlaneEquation[2];
    destMat[13] = 0.0f - vLightPos[1] * vPlaneEquation[3];

    // Третий столбец
    destMat[2] = 0.0f - vLightPos[2] * vPlaneEquation[0];
    destMat[6] = 0.0f - vLightPos[2] * vPlaneEquation[1];
    destMat[10] = dot - vLightPos[2] * vPlaneEquation[2];
    destMat[14] = 0.0f - vLightPos[2] * vPlaneEquation[3];

    // Четвертый столбец
    destMat[3] = 0.0f - vLightPos[3] * vPlaneEquation[0];
    destMat[7] = 0.0f - vLightPos[3] * vPlaneEquation[1];
    destMat[11] = 0.0f - vLightPos[3] * vPlaneEquation[2];
    destMat[15] = dot - vLightPos[3] * vPlaneEquation[3];
}

void DrawBox(GLfloat x1, GLfloat y1, GLfloat z1,
             GLfloat x2, GLfloat y2, GLfloat z2)
{
    glBegin(GL_QUADS);
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(x1, y1, z2); glVertex3f(x2, y1, z2);
        glVertex3f(x2, y2, z2); glVertex3f(x1, y2, z2);

        glNormal3f(0.0f, 0.0f, -1.0f);
        glVertex3f(x2, y1, z1); glVertex3f(x1, y1, z1);
        glVertex3f(x1, y2, z1); glVertex3f(x2, y2, z1);

        glNormal3f(-1.0f, 0.0f, 0.0f);
        glVertex3f(x1, y1, z1); glVertex3f(x1, y1, z2);
        glVertex3f(x1, y2, z2); glVertex3f(x1, y2, z1);

        glNormal3f(1.0f, 0.0f, 0.0f);
        glVertex3f(x2, y1, z2); glVertex3f(x2, y1, z1);
        glVertex3f(x2, y2, z1); glVertex3f(x2, y2, z2);

        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(x1, y2, z2); glVertex3f(x2, y2, z2);
        glVertex3f(x2, y2, z1); glVertex3f(x1, y2, z1);

        glNormal3f(0.0f, -1.0f, 0.0f);
        glVertex3f(x1, y1, z1); glVertex3f(x2, y1, z1);
        glVertex3f(x2, y1, z2); glVertex3f(x1, y1, z2);
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

// Функция, специально прорисовывающая автомобиль
void DrawCar(int nShadow)
{
    // Черный цвет используется только для тени
    if (nShadow == 0)
        glColor3ub(128, 128, 128);
    else
        glColor3ub(0, 0, 0);

    DrawBox(-35.0f, -8.0f, -14.0f, 35.0f, 7.0f, 14.0f);
    DrawBox(-17.0f, 7.0f, -12.0f, 18.0f, 23.0f, 12.0f);

    if (nShadow == 0)
        glColor3ub(70, 70, 70);
    DrawBox(-14.0f, 10.0f, -12.5f, 15.0f, 20.0f, 12.5f);

    if (nShadow == 0)
        glColor3ub(35, 35, 35);
    DrawWheel(-23.0f, 14.0f);
    DrawWheel(23.0f, 14.0f);
    DrawWheel(-23.0f, -14.0f);
    DrawWheel(23.0f, -14.0f);
}

void DrawShadow(GLTMatrix shadowMat)
{
    glPushMatrix();
    // Текущая матрица множится на матрицу проекции тени
    glMultMatrixf(shadowMat);
    glTranslatef(0.0f, 30.0f, 0.0f);
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    DrawCar(1);
    glPopMatrix();
}

// Вызывается окно для рисования
void RenderScene(void)
{
    // Очищает окно текущим цветом очистки
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Рисуется земля
    glDisable(GL_LIGHTING);
    glColor3ub(0, 120, 0);
    glBegin(GL_QUADS);
        glVertex3f(-140.0f, -45.0f, -110.0f);
        glVertex3f(-140.0f, -25.0f, 110.0f);
        glVertex3f(140.0f, 15.0f, 110.0f);
        glVertex3f(140.0f, -5.0f, -110.0f);
    glEnd();

    // Рисуется автомобиль с новой ориентацией
    glEnable(GL_LIGHTING);
    glPushMatrix();
    glTranslatef(0.0f, 30.0f, 0.0f);
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    DrawCar(0);
    glPopMatrix();

    // Мы готовы рисовать тени и землю
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    DrawShadow(shadowMat0);
    DrawShadow(shadowMat1);
    DrawShadow(shadowMat2);

    // Рисуются источники света
    glColor3ub(255, 255, 0);
    glPushMatrix();
    glTranslatef(lightPos0[0], lightPos0[1], lightPos0[2]);
    glutSolidSphere(4.0f, 10, 10);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(lightPos1[0], lightPos1[1], lightPos1[2]);
    glutSolidSphere(4.0f, 10, 10);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(lightPos2[0], lightPos2[1], lightPos2[2]);
    glutSolidSphere(4.0f, 10, 10);
    glPopMatrix();

    // Восстанавливаются переменные состояния освещения
    glEnable(GL_DEPTH_TEST);

    // Отображаются результаты
    glutSwapBuffers();
}

// Эта функция выполняет необходимую инициализацию
// в контексте визуализации
void SetupRC()
{
    GLfloat ambientLight[] = {0.1f, 0.1f, 0.1f, 1.0f};
    GLfloat diffuseLight[] = {0.35f, 0.35f, 0.35f, 1.0f};
    GLfloat specref[] = {1.0f, 1.0f, 1.0f, 1.0f};

    // Любые три точки на поверхности
    GLTVector3 points[3] = {
        {-140.0f, -45.0f, -110.0f},
        {-140.0f, -25.0f, 110.0f},
        {140.0f, 15.0f, 110.0f}
    };

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);

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

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
    glMateriali(GL_FRONT, GL_SHININESS, 128);

    // Расчет матриц проекции для рисования теней на земле
    gltMakeShadowMatrix(points, lightPos0, shadowMat0);
    gltMakeShadowMatrix(points, lightPos1, shadowMat1);
    gltMakeShadowMatrix(points, lightPos2, shadowMat2);

    // Светло-синий фон
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}

void SpecialKeys(int key, int x, int y)
{
    if (key == GLUT_KEY_UP) xRot -= 5.0f;
    if (key == GLUT_KEY_DOWN) xRot += 5.0f;
    if (key == GLUT_KEY_LEFT) yRot -= 5.0f;
    if (key == GLUT_KEY_RIGHT) yRot += 5.0f;

    if (xRot > 356.0f) xRot = 0.0f;
    if (xRot < -1.0f) xRot = 355.0f;
    if (yRot > 356.0f) yRot = 0.0f;
    if (yRot < -1.0f) yRot = 355.0f;

    // Перерисовка окна
    glutPostRedisplay();
}

void ChangeSize(int w, int h)
{
    GLfloat nRange = 150.0f;

    // Предотвращает деление на ноль
    if (h == 0) h = 1;

    // Размер поля просмотра устанавливается равным размеру окна
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

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
    glutCreateWindow("Three Shadows on Inclined Ground");
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(RenderScene);
    SetupRC();
    glutMainLoop();

    return 0;
}
