//---------------------------------------------------------------------------
//Тор
//---------------------------------------------------------------------------
#include <math.h>
#include <windows.h>
#include <GL\gl.h>
#include <GL\glu.h>
#pragma hdrstop

#pragma argsused

#define ExportStdcall(type) extern "C" type __export __stdcall

GLUquadricObj *q;
const float r = 0.15, R = 0.7, r1 = r + 0.05, R1 = R + 0.02;
GLuint List;

int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
{
  if (reason == DLL_PROCESS_DETACH) gluDeleteQuadric(q);
  return 1;
}
//---------------------------------------------------------------------------
ExportStdcall(void) InitGL(void)
{
  GLfloat lightpos[4] = {0, 6, 0, 1};
  glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_DEPTH_TEST);
  q = gluNewQuadric();
  List = glGenLists(1);
  glNewList(List, GL_COMPILE);
  for (int density = 0; density < 285; density++)
  {
    glPushMatrix();
    glTranslatef(R, 0, 0);
      gluCylinder(q, r, r, 0.02, 10, 10);
    glPopMatrix();
    glRotatef(1.3, 0, 1, 0);
  }
  glEndList();
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
char *variants[] = {"Геоид", "Тор", "Бублик" };
ExportStdcall(char *) AnsVariant(int Number)
{
  return variants[Number];
}
//---------------------------------------------------------------------------
char *task =
  "Как называется геометрическое тело, изображённое синим цветом?";
ExportStdcall(char *) Task(void)
{
  return task;
}
//---------------------------------------------------------------------------
ExportStdcall(void) OnTimerEvent(void)
{
  glLoadIdentity();
  glRotatef(60, -1, 0.5, 0);
  glColor3f(0.5, 0.3, 0.9);
  glCallList(List);
  glColor3f(1, 0, 0);
  glLoadIdentity();
  glRotatef(60, -1, 0.5, 0);

  static float ba = 0, sta = 0;
  float alpha = ba;
  glRotatef(sta, 0, 1, 0);
  ba += 0.3;
  if (ba > M_PI * 2) ba -= M_PI * 2;
  sta -= 2;
  if (sta < 0) sta += 360;
  for (int density = 0; density < 90; density++)
  {
    glRotatef(3, 0, 1, 0);
    glPushMatrix();
      glTranslatef(cos(alpha) * r1 + R1, sin(alpha) * r1, 0);
      gluSphere(q, 0.02, 4, 4);
    glPopMatrix();
    alpha += 0.2;
  }
}
//---------------------------------------------------------------------------
