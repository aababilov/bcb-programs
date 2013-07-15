//---------------------------------------------------------------------------
//Диффузия
//---------------------------------------------------------------------------
#include <windows.h>
#include <GL\gl.h>
#include <GL\glu.h>
#pragma hdrstop

#pragma argsused

#define ExportStdcall(type) extern "C" type __export __stdcall

GLUquadricObj *q;
const int NUM_VERT = 200;
GLfloat vt1[NUM_VERT][3], vt2[NUM_VERT][3];

int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
{
  if (reason == DLL_PROCESS_DETACH) gluDeleteQuadric(q);
  return 1;
}
//---------------------------------------------------------------------------
ExportStdcall(void) InitGL(void)
{
  const GLfloat White[] = {1.0, 1.0, 1.0, 1.0},
    lightpos[4] = {0, 7, -10, 1};
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);
  glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, White);

  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_DEPTH_TEST);
  q = gluNewQuadric();
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glClearColor(0.2, 0.3, 0.4, 1);
  glMatrixMode(GL_PROJECTION);
    glRotatef(-120, 1, 0, 0);
    glTranslatef(0, 0, -0.5);
  glMatrixMode(GL_MODELVIEW);
  glEnableClientState(GL_VERTEX_ARRAY);
  for (int i = 0; i < NUM_VERT; i++)
    for (int j = 0; j < 3; j++)
      vt1[i][j] = 0.05 - random(100) / 1000.0;
}
//---------------------------------------------------------------------------
ExportStdcall(int) NumVariants(void)
{
  return 2;
}
//---------------------------------------------------------------------------
ExportStdcall(int) Correct(void)
{
  return 1;
}
//---------------------------------------------------------------------------
char *variants[] = {"В левом", "В правом" };
ExportStdcall(char *) AnsVariant(int Number)
{
  return variants[Number];
}
//---------------------------------------------------------------------------
char *task =
  "Вы видите диффузию порошка в воде. В каком стакане температура жидкости выше?";
ExportStdcall(char *) Task(void)
{
  return task;
}
//---------------------------------------------------------------------------
const float h = 0.85, r = 0.18, R = 0.23;
void DrawGlass(void)
{
  glColor4f(1, 1, 1, 0.5);
  gluCylinder(q, r, R, h, 10, 50);
  glPushMatrix();
    glTranslatef(0, 0, h - 0.02);
    gluCylinder(q, R, R, 0.1, 50, 50);
  glPopMatrix();
}
//---------------------------------------------------------------------------
ExportStdcall(void) OnTimerEvent(void)
{
  for (int i = 0; i < NUM_VERT / 2; i++)
    if (vt1[i][0] > -0.1)
      vt1[i][0] -= i / 100000.0;
  for (int i = NUM_VERT / 2; i < NUM_VERT; i++)
    if (vt1[i][0] < 0.1)
      vt1[i][0] += i / 100000.0;
  for (int i = 0; i < NUM_VERT; i++)
  {
    if (vt1[i][2] < 0.5)
      vt1[i][2] += 0.003;
    vt2[i][2] = vt1[i][2] / 1.5;
    vt2[i][0] = vt1[i][0] / 1.5;
  }
  glLoadIdentity();
    glTranslatef(0.5, 0, 0);
    glColor3f(1, 1, 1);
    glVertexPointer(3, GL_FLOAT, 0, vt1);
    glDrawArrays(GL_POINTS, 0, NUM_VERT);
    DrawGlass();
  glLoadIdentity();
    glTranslatef(-0.5, 0, 0);
    glColor3f(1, 1, 1);
    glVertexPointer(3, GL_FLOAT, 0, vt2);
    glDrawArrays(GL_POINTS, 0, NUM_VERT);
    DrawGlass();
}
//---------------------------------------------------------------------------
