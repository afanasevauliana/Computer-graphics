#include "glut.h"
#include <GL/glext.h>
#include <GL/glu.h>

#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

enum TextureIndex
{
    TEXTURE_BRICK,
    TEXTURE_WOOD,
    TEXTURE_STONE,
    TEXTURE_TILES,
    TEXTURE_METAL,
    TEXTURE_COUNT
};

static const char *textureFiles[TEXTURE_COUNT] = {
    "brick.tga",
    "wood.tga",
    "stone.tga",
    "tiles.tga",
    "metal.tga"
};

static GLuint textures[TEXTURE_COUNT];
static GLfloat corridorPosition = 0.0f;
static GLfloat viewRotation = 0.0f;

struct Point2D
{
    GLfloat x;
    GLfloat y;
};

// Пятиугольное сечение коридора для варианта 3
static const Point2D corridorPoints[5] = {
    {-3.0f, 0.0f},
    {-1.5f, 2.0f},
    {2.5f, 2.0f},
    {2.5f, -2.0f},
    {-1.5f, -2.0f}
};

bool LoadTexture(const char *fileName, GLuint texture)
{
    int width;
    int height;
    int channelCount;

    unsigned char *image = stbi_load(fileName, &width, &height, &channelCount, 3);
    if (image == NULL)
    {
        fprintf(stderr, "Не удалось загрузить текстуру %s\n", fileName);
        return false;
    }

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGB,
        width,
        height,
        0,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        image);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    stbi_image_free(image);
    return true;
}

void SetupRC()
{
    glClearColor(0.02f, 0.02f, 0.03f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    stbi_set_flip_vertically_on_load(1);
    glGenTextures(TEXTURE_COUNT, textures);

    for (GLint i = 0; i < TEXTURE_COUNT; ++i)
    {
        LoadTexture(textureFiles[i], textures[i]);
    }
}

void ShutdownRC()
{
    glDeleteTextures(TEXTURE_COUNT, textures);
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
    gluPerspective(60.0, (GLfloat)width / (GLfloat)height, 0.5, 180.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void DrawSurface(
    const Point2D &first,
    const Point2D &second,
    GLfloat nearZ,
    GLfloat farZ,
    GLuint texture)
{
    glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(first.x, first.y, nearZ);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(second.x, second.y, nearZ);
    glTexCoord2f(1.0f, 20.0f);
    glVertex3f(second.x, second.y, farZ);
    glTexCoord2f(0.0f, 20.0f);
    glVertex3f(first.x, first.y, farZ);
    glEnd();
}

void DrawCorridor(GLfloat nearZ, GLfloat farZ)
{
    // Для каждой поверхности используется отдельный текстурный объект
    for (GLint i = 0; i < 5; ++i)
    {
        DrawSurface(
            corridorPoints[i],
            corridorPoints[(i + 1) % 5],
            nearZ,
            farZ,
            textures[i]);
    }
}

void RenderScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glRotatef(viewRotation, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, corridorPosition);

    // Два последовательных участка скрывают переход при движении
    DrawCorridor(2.0f, -78.0f);
    DrawCorridor(-78.0f, -158.0f);

    glPopMatrix();
    glutSwapBuffers();
}

void SpecialKeys(int key, int x, int y)
{
    if (key == GLUT_KEY_UP)
    {
        corridorPosition += 1.0f;
    }

    if (key == GLUT_KEY_DOWN)
    {
        corridorPosition -= 1.0f;
    }

    if (key == GLUT_KEY_LEFT)
    {
        viewRotation += 2.0f;
    }

    if (key == GLUT_KEY_RIGHT)
    {
        viewRotation -= 2.0f;
    }

    if (corridorPosition >= 80.0f)
    {
        corridorPosition -= 80.0f;
    }
    else if (corridorPosition < 0.0f)
    {
        corridorPosition += 80.0f;
    }

    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(900, 650);
    glutCreateWindow("Textured Corridor - Variant 3");
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    glutSpecialFunc(SpecialKeys);

    SetupRC();
    glutMainLoop();
    ShutdownRC();

    return 0;
}
