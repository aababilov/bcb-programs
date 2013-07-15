//---------------------------------------------------------------------------
//Изумруд
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
  GLint vp[4];
  GLfloat pos[] = {-0.4, 5.6, 10, 1};
  q = gluNewQuadric();
  glEnable(GL_DEPTH_TEST);
  glLightfv(GL_LIGHT0, GL_POSITION, pos);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);
  glEnable(GL_COLOR_MATERIAL);
  glGetIntegerv(GL_VIEWPORT, vp);
  glMatrixMode(GL_PROJECTION);
    gluPerspective(45, (GLfloat)vp[3]/vp[2], 1, 10);
    glTranslatef(0, 0, -4);
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
char *variants[] = {"Изумруд", "Рубин", "Сапфир" };
ExportStdcall(char *) AnsVariant(int Number)
{
  return variants[Number];
}
//---------------------------------------------------------------------------
char *task = "Что это?";
ExportStdcall(char *) Task(void)
{
  return task;
}
//---------------------------------------------------------------------------
ExportStdcall(void) OnTimerEvent(void)
{
  static int angle = 0;
  glColor4f(0.1, 0.8, 0.3, 0.7);
  const float R = 0.5, h = 2.2;
  glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, 1.1, 0);
    glRotatef(120, 1, 0, 0);
    glRotatef(angle += 2, 0, 0, 1);
  gluCylinder(q, R, R, h, 6, 100);
  gluDisk(q, 0, R, 6, 100);
  glTranslatef(0, 0, h);
  gluDisk(q, 0, R, 6, 100);
  angle %= 360;
}
//---------------------------------------------------------------------------
