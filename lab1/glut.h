#pragma once

#include <GL/gl.h>

#ifdef __cplusplus
extern "C" {
#endif

#define GLUT_RGB    0
#define GLUT_SINGLE 0
#define GLUT_DOUBLE 2
#define GLUT_WINDOW_WIDTH  102
#define GLUT_WINDOW_HEIGHT 103

void __cdecl glutInit(int* argc, char** argv);
void __cdecl glutInitDisplayMode(unsigned int mode);
int  __cdecl glutCreateWindow(const char* title);
void __cdecl glutInitWindowSize(int width, int height);
void __cdecl glutDisplayFunc(void (__cdecl *func)(void));
void __cdecl glutReshapeFunc(void (__cdecl *func)(int width, int height));
void __cdecl glutKeyboardFunc(void (__cdecl *func)(unsigned char key, int x, int y));
void __cdecl glutTimerFunc(unsigned int milliseconds,
                          void (__cdecl *func)(int value), int value);
void __cdecl glutPostRedisplay(void);
void __cdecl glutSwapBuffers(void);
int  __cdecl glutGet(int state);
void __cdecl glutMainLoop(void);

#ifdef __cplusplus
}
#endif
