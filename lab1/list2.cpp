#include "glut.h"

void RenderScene(void)
{
	// Окно очищается текущим цветом очистки
	glClear(GL_COLOR_BUFFER_BIT);
	// В буфер вводятся команды рисования
	glFlush();
}
// Устанавливается состояние визуализации
void SetupRC(void)
{
	glClearColor(0.98f, 0.625f, 0.12f, 1.0f);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("Listing 2");
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();
	return 0;
}
