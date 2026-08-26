#pragma once

#include <GL/gl.h>

#ifdef __cplusplus
extern "C" {
#endif

#define GLUT_RGB    0
#define GLUT_DOUBLE 2
#define GLUT_DEPTH  16

#define GLUT_KEY_LEFT  100
#define GLUT_KEY_UP    101
#define GLUT_KEY_RIGHT 102
#define GLUT_KEY_DOWN  103

void __stdcall glutInit(int* argc, char** argv);
void __stdcall glutInitDisplayMode(unsigned int mode);
void __stdcall glutInitWindowSize(int width, int height);
int  __stdcall glutCreateWindow(const char* title);
void __stdcall glutDisplayFunc(void (__cdecl *func)(void));
void __stdcall glutReshapeFunc(void (__cdecl *func)(int width, int height));
void __stdcall glutSpecialFunc(void (__cdecl *func)(int key, int x, int y));
void __stdcall glutTimerFunc(unsigned int millis, void (__cdecl *func)(int value), int value);
void __stdcall glutPostRedisplay(void);
void __stdcall glutSwapBuffers(void);
void __stdcall glutSolidSphere(GLdouble radius, GLint slices, GLint stacks);
void __stdcall glutMainLoop(void);

#ifdef __cplusplus
}
#endif
