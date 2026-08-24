#include "glut.h"

GLfloat angle = 0.0f;

GLfloat windowWidth;
GLfloat windowHeight;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);
	glPushMatrix();
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
	glRectf(-40.0f, 20.0f, 40.0f, -20.0f);
	glPopMatrix();
	glutSwapBuffers();
}

void TimerFunction(int value)
{
	angle += 1.0f;
	if (angle > 360.0f)
		angle -= 360.0f;
	glutPostRedisplay();
	glutTimerFunc(33, TimerFunction, 1);
}

void SetupRC(void)
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}

void ChangeSize(GLsizei w, GLsizei h)
{
	GLfloat aspectRatio;
	if (h == 0)
		h = 1;

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	aspectRatio = (GLfloat)w / (GLfloat)h;
	if (w <= h)
	{
		windowWidth = 100;
		windowHeight = 100 / aspectRatio;
		glOrtho(-100.0, 100.0, -windowHeight, windowHeight, 1.0, -1.0);
	}
	else
	{
		windowWidth = 100 * aspectRatio;
		windowHeight = 100;
		glOrtho(-windowWidth, windowWidth, -100.0, 100.0, 1.0, -1.0);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("Rotation rectangle");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(33, TimerFunction, 1);
	SetupRC();
	glutMainLoop();
	return 0;
}
