//---------------------------------------------------------------------------
//Кольцо
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
  q = gluNewQuadric();
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);
  glGetIntegerv(GL_VIEWPORT, vp);
  glMatrixMode(GL_PROJECTION);
    gluPerspective(45, (GLfloat)vp[3]/vp[2], 1, 10);
    glTranslatef(0, 0, -4);
  glMatrixMode(GL_MODELVIEW);
}
//---------------------------------------------------------------------------
ExportStdcall(int) NumVariants(void)
{
  return 2;
}
//---------------------------------------------------------------------------
ExportStdcall(int) Correct(void)
{
  return 0;
}
//---------------------------------------------------------------------------
char *variants[] = {"Внешняя", "Внутренняя" };
ExportStdcall(char *) AnsVariant(int Number)
{
  return variants[Number];
}
//---------------------------------------------------------------------------
char *task =
  "Какая сторона кольца имеет большую протяжённость в пространстве?";
ExportStdcall(char *) Task(void)
{
  return task;
}
//---------------------------------------------------------------------------
ExportStdcall(void) OnTimerEvent(void)
{
  static int angle = 0;
  glColor4f(1, 1, 0, 1);
  const float R = 0.95, r = 0.9, h = 0.03;
  static float rx = 1, ry = 1, rz = 1;
  glLoadIdentity();
  glRotatef(angle, rz, ry, rx);
  gluCylinder(q, R, R, h, 100, 100);
  gluCylinder(q, r, r, h, 100, 100);
  gluDisk(q, r, R, 100, 100);
    glTranslatef(0, 0, h);
  gluDisk(q, r, R, 100, 100);
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
