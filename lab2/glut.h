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
#define GLUT_RIGHT_BUTTON 2

void __cdecl glutInit(int* argc, char** argv);
void __cdecl glutInitDisplayMode(unsigned int mode);
int  __cdecl glutCreateWindow(const char* title);
void __cdecl glutDisplayFunc(void (__cdecl *func)(void));
void __cdecl glutReshapeFunc(void (__cdecl *func)(int width, int height));
void __cdecl glutSpecialFunc(void (__cdecl *func)(int key, int x, int y));
int  __cdecl glutCreateMenu(void (__cdecl *func)(int value));
void __cdecl glutAddMenuEntry(const char* label, int value);
void __cdecl glutAttachMenu(int button);
void __cdecl glutPostRedisplay(void);
void __cdecl glutSwapBuffers(void);
void __cdecl glutMainLoop(void);

#ifdef __cplusplus
}
#endif
