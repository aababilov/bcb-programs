//---------------------------------------------------------------------------
//Цилиндр
//---------------------------------------------------------------------------
#include <windows.h>
#include <GL\gl.h>
#include <GL\glu.h>
#pragma hdrstop

#pragma argsused

#define ExportStdcall(type) extern "C" type __export __stdcall

GLUquadricObj *q;
int count;
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
{
  if (reason == DLL_PROCESS_DETACH) gluDeleteQuadric(q);
  return 1;
}
//---------------------------------------------------------------------------
ExportStdcall(void) InitGL(void)
{
  GLfloat pos[] = { 0, 0, -2, 1 };
  GLint vp[4];
  q = gluNewQuadric();
  glEnable(GL_DEPTH_TEST);
  glLightfv(GL_LIGHT0, GL_POSITION, pos);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);
  glEnable(GL_COLOR_MATERIAL);
  glGetIntegerv(GL_VIEWPORT, vp);
  glColor3f(1, 1, 0);
  glMatrixMode(GL_PROJECTION);
    gluPerspective(45, (GLfloat)vp[2]/vp[3], 1, 10);
}
//---------------------------------------------------------------------------
ExportStdcall(int) NumVariants(void)
{
  return 3;
}
//---------------------------------------------------------------------------
ExportStdcall(int) Correct(void)
{
  return 1;
}
//---------------------------------------------------------------------------
char *variants[] = {"На 1 мм", "На 2 мм", "На 4 мм" };
ExportStdcall(char *) AnsVariant(int Number)
{
  return variants[Number];
}
//---------------------------------------------------------------------------
char *task = "Толщина стенок цилиндра 2 мм.\
 Насколько внешний радиус больше внутреннего?";
ExportStdcall(char *) Task(void)
{
  return task;
}
//---------------------------------------------------------------------------
ExportStdcall(void) OnTimerEvent(void)
{
  const float R = 1, r = 0.9, h = 2;
  static int rx = 1, ry = 1, rz = 1, angle = 0;
  glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, 0, -5);
    glRotatef(angle, rz, ry, rx);
    glTranslatef(0, 0, -h/2);
  gluCylinder(q, R, R, h, 100, 100);
  gluCylinder(q, r, r, h, 100, 100);
  gluDisk(q, r, R, 100, 10);
    glTranslatef(0, 0, h);
  gluDisk(q, r, R, 100, 10);
  angle = (angle + random(4) + 6) % 360;
  if (angle < 10)
  do
    switch (random(3))
    {
      case 0:rx = random(3) - 1;break;
      case 1:ry = random(3) - 1;break;
      case 2:rz = random(3) - 1;break;
    }
  while (rx == 0 && ry == 0);
}
//---------------------------------------------------------------------------
