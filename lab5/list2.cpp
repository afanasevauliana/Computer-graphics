#include "glut.h"
#include <GL/glext.h>
#include <GL/glu.h>

#include <math.h>

static GLfloat rotationAngle = 0.0f;

typedef GLfloat Vector3[3];

struct Face
{
    GLint first;
    GLint second;
    GLint third;
};

static const Vector3 vertices[4] = {
    {1.0f, 1.0f, 1.0f},
    {-1.0f, -1.0f, 1.0f},
    {-1.0f, 1.0f, -1.0f},
    {1.0f, -1.0f, -1.0f}
};

static const Face faces[4] = {
    {0, 2, 1},
    {0, 1, 3},
    {0, 3, 2},
    {1, 2, 3}
};

void Normalize(Vector3 vector)
{
    GLfloat length = (GLfloat)sqrt(
        vector[0] * vector[0] +
        vector[1] * vector[1] +
        vector[2] * vector[2]);

    if (length == 0.0f)
    {
        return;
    }

    vector[0] /= length;
    vector[1] /= length;
    vector[2] /= length;
}

void CalculateNormal(const Face &face, Vector3 normal)
{
    Vector3 firstEdge = {
        vertices[face.second][0] - vertices[face.first][0],
        vertices[face.second][1] - vertices[face.first][1],
        vertices[face.second][2] - vertices[face.first][2]
    };
    Vector3 secondEdge = {
        vertices[face.third][0] - vertices[face.first][0],
        vertices[face.third][1] - vertices[face.first][1],
        vertices[face.third][2] - vertices[face.first][2]
    };

    normal[0] = firstEdge[1] * secondEdge[2] - firstEdge[2] * secondEdge[1];
    normal[1] = firstEdge[2] * secondEdge[0] - firstEdge[0] * secondEdge[2];
    normal[2] = firstEdge[0] * secondEdge[1] - firstEdge[1] * secondEdge[0];
    Normalize(normal);
}

// Преобразование нормали в том же порядке, что и тетраэдра
void TransformNormal(const Vector3 normal, Vector3 transformedNormal)
{
    const GLfloat angleY = rotationAngle * 3.14159265f / 180.0f;
    const GLfloat angleX = -20.0f * 3.14159265f / 180.0f;

    Vector3 rotatedY = {
        normal[0] * (GLfloat)cos(angleY) + normal[2] * (GLfloat)sin(angleY),
        normal[1],
        -normal[0] * (GLfloat)sin(angleY) + normal[2] * (GLfloat)cos(angleY)
    };

    transformedNormal[0] = rotatedY[0];
    transformedNormal[1] =
        rotatedY[1] * (GLfloat)cos(angleX) - rotatedY[2] * (GLfloat)sin(angleX);
    transformedNormal[2] =
        rotatedY[1] * (GLfloat)sin(angleX) + rotatedY[2] * (GLfloat)cos(angleX);
}

GLfloat CalculateTextureCoordinate(const Vector3 normal)
{
    Vector3 lightDirection = {-0.4f, 0.7f, 1.0f};
    Vector3 transformedNormal;

    Normalize(lightDirection);
    TransformNormal(normal, transformedNormal);

    GLfloat intensity =
        transformedNormal[0] * lightDirection[0] +
        transformedNormal[1] * lightDirection[1] +
        transformedNormal[2] * lightDirection[2];

    if (intensity < 0.0f)
    {
        intensity = 0.0f;
    }

    // Небольшая фоновая составляющая сохраняет видимость неосвещённых граней
    return 0.15f + intensity * 0.85f;
}

void SetupRC()
{
    const GLint gradientCount = 16;
    GLubyte yellowGradient[gradientCount][3];

    // Создание не менее 12 оттенков жёлтого цвета от тёмного к светлому
    for (GLint i = 0; i < gradientCount; ++i)
    {
        GLfloat intensity = (GLfloat)i / (GLfloat)(gradientCount - 1);
        yellowGradient[i][0] = (GLubyte)(255.0f * intensity);
        yellowGradient[i][1] = (GLubyte)(220.0f * intensity);
        yellowGradient[i][2] = 0;
    }

    glClearColor(0.05f, 0.06f, 0.09f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage1D(
        GL_TEXTURE_1D,
        0,
        GL_RGB,
        gradientCount,
        0,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        yellowGradient);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glEnable(GL_TEXTURE_1D);
}

void ChangeSize(int width, int height)
{
    if (height == 0)
    {
        height = 1;
    }

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, (GLfloat)width / (GLfloat)height, 1.0, 20.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void RenderScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -6.0f);
    glRotatef(-20.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);

    glBegin(GL_TRIANGLES);
    for (GLint i = 0; i < 4; ++i)
    {
        Vector3 normal;
        CalculateNormal(faces[i], normal);

        // Одна координата выбирает оттенок из одномерной текстуры
        glNormal3fv(normal);
        glTexCoord1f(CalculateTextureCoordinate(normal));
        glVertex3fv(vertices[faces[i].first]);
        glVertex3fv(vertices[faces[i].second]);
        glVertex3fv(vertices[faces[i].third]);
    }
    glEnd();

    glPopMatrix();
    glutSwapBuffers();
}

void TimerFunction(int value)
{
    rotationAngle += 0.7f;
    if (rotationAngle >= 360.0f)
    {
        rotationAngle -= 360.0f;
    }

    glutPostRedisplay();
    glutTimerFunc(16, TimerFunction, 1);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("One-dimensional texture - Variant 3");
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);

    SetupRC();
    glutTimerFunc(16, TimerFunction, 1);
    glutMainLoop();

    return 0;
}
