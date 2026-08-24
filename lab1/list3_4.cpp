#include "glut.h"
#include <stdio.h>

int currentVariant = 1;
GLfloat bgColor[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
GLfloat objColor[3] = { 1.0f, 0.0f, 0.0f };
GLfloat rectCoords[4] = { -25.0f, 25.0f, 25.0f, -25.0f };
int numObjects = 1;
GLsizei windowWidth = 800;
GLsizei windowHeight = 600;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 0; i < numObjects; i++)
	{
		GLfloat offset = i * 30.0f;
		glColor3f(objColor[0], objColor[1], objColor[2]);
		glRectf(rectCoords[0] + offset, rectCoords[1] + offset,
			rectCoords[2] + offset, rectCoords[3] + offset);
	}
	glFlush();
}


void SetupRC(void)
{
	glClearColor(bgColor[0], bgColor[1], bgColor[2], bgColor[3]);
}

void ChangeSize(GLsizei w, GLsizei h)
{
	GLfloat aspectRatio;
	if (h == 0) h = 1;
	windowWidth = w;
	windowHeight = h;

	if (currentVariant == 1)
	{
		glViewport(0, 0, w, h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		aspectRatio = (GLfloat)w / (GLfloat)h;
		if (w <= h)
			glOrtho(-100.0, 100.0, -100.0 / aspectRatio, 100.0 / aspectRatio, 1.0, -1.0);
		else
			glOrtho(-100.0 * aspectRatio, 100.0 * aspectRatio, -100.0, 100.0, 1.0, -1.0);
	}
	else if (currentVariant == 2)
	{
		glViewport(w / 2, 0, w / 2, h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-100.0, 100.0, -100.0, 100.0, 1.0, -1.0);
	}
	else if (currentVariant == 3)
	{
		glViewport(0, 0, w / 2, h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-50.0, 50.0, -50.0, 50.0, 1.0, -1.0);
	}
	else if (currentVariant == 4)
	{
		glViewport(w / 4, h / 4, w / 2, h / 2);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-200.0, 200.0, -200.0, 200.0, 1.0, -1.0);
	}
	else
	{
		glViewport(w / 3, 0, w / 3, h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-150.0, 150.0, -150.0, 150.0, 1.0, -1.0);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':
		currentVariant = 1;
		bgColor[0] = 0.0f; bgColor[1] = 0.0f; bgColor[2] = 1.0f;
		objColor[0] = 1.0f; objColor[1] = 0.0f; objColor[2] = 0.0f;
		rectCoords[0] = -25.0f; rectCoords[1] = 25.0f; rectCoords[2] = 25.0f; rectCoords[3] = -25.0f;
		numObjects = 1;
		break;
	case '2':
		currentVariant = 2;
		bgColor[0] = 1.0f; bgColor[1] = 0.4f; bgColor[2] = 0.7f;
		objColor[0] = 1.0f; objColor[1] = 1.0f; objColor[2] = 0.0f;
		rectCoords[0] = -50.0f; rectCoords[1] = 50.0f; rectCoords[2] = 50.0f; rectCoords[3] = -50.0f;
		numObjects = 2;
		break;
	case '3':
		currentVariant = 3;
		bgColor[0] = 1.0f; bgColor[1] = 0.0f; bgColor[2] = 0.0f;
		objColor[0] = 1.0f; objColor[1] = 1.0f; objColor[2] = 0.0f;
		rectCoords[0] = -75.0f; rectCoords[1] = 75.0f; rectCoords[2] = 75.0f; rectCoords[3] = -75.0f;
		numObjects = 3;
		break;
	case '4':
		currentVariant = 4;
		bgColor[0] = 1.0f; bgColor[1] = 1.0f; bgColor[2] = 0.0f;
		objColor[0] = 1.0f; objColor[1] = 0.5f; objColor[2] = 0.0f;
		rectCoords[0] = -30.0f; rectCoords[1] = 30.0f; rectCoords[2] = 30.0f; rectCoords[3] = -30.0f;
		numObjects = 4;
		break;
	case '5':
		currentVariant = 5;
		bgColor[0] = 1.0f; bgColor[1] = 0.5f; bgColor[2] = 0.0f;
		objColor[0] = 0.0f; objColor[1] = 0.75f; objColor[2] = 1.0f;
		rectCoords[0] = -20.0f; rectCoords[1] = 20.0f; rectCoords[2] = 20.0f; rectCoords[3] = -20.0f;
		numObjects = 5;
		break;
	default:
		return;
	}
	SetupRC();
	ChangeSize(windowWidth, windowHeight);
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Listings 3 and 4");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutKeyboardFunc(Keyboard);
	SetupRC();
	glutMainLoop();
	return 0;
}
