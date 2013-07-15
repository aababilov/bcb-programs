//---------------------------------------------------------------------------
//Шар
//---------------------------------------------------------------------------
#include <windows.h>
#include <GL\gl.h>
#include <GL\glu.h>
#pragma hdrstop

#pragma argsused

#define ExportStdcall(type) extern "C" type __export __stdcall

GLUquadricObj *q;

int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
{
  if (reason == DLL_PROCESS_DETACH) gluDeleteQuadric(q);
  return 1;
}
//---------------------------------------------------------------------------
ExportStdcall(void) InitGL(void)
{
  const GLfloat diff[] = {1.0, 1.0, 1.0, 1.0},
    lightpos[] = {10, 7, -10, 1};
  GLint vp[4];
  q = gluNewQuadric();
  glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_DEPTH_TEST);
  glGetIntegerv(GL_VIEWPORT, vp);
  glMatrixMode(GL_PROJECTION);
    glScalef((GLfloat)vp[3] / vp[2], 1, 1);
    glRotatef(-120, 1, 0, 0);
    glTranslatef(0, 0, -0.4);
  glMatrixMode(GL_MODELVIEW);
  glColor3f(1, 0.1, 0);
}
//---------------------------------------------------------------------------
ExportStdcall(int) NumVariants(void)
{
  return 3;
}
//---------------------------------------------------------------------------
ExportStdcall(int) Correct(void)
{
  return 0;
}
//---------------------------------------------------------------------------
char *variants[] = {"Конус", "Пирамида" , "Колпак"};
ExportStdcall(char *) AnsVariant(int Number)
{
  return variants[Number];
}
//---------------------------------------------------------------------------
char *task =
  "Как называется это геометрическое тело?";
ExportStdcall(char *) Task(void)
{
  return task;
}
//---------------------------------------------------------------------------
const float cylh = 0.8, r = 0.15, rl = r - 0.005, pistonh = 0.6;
ExportStdcall(void) OnTimerEvent(void)
{
  glLoadIdentity();
    gluCylinder(q, 0.8, 0, 1.2, 100, 100);
}
//--------------------------------------------------------------------------- 
