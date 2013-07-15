//---------------------------------------------------------------------------
//Сжимание жидкости и газа
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
    lightpos[] = {0, 7, -10, 1};
  q = gluNewQuadric();
  glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
  return 1;
}
//---------------------------------------------------------------------------
char *variants[] = {"Жидкость", "Газ" };
ExportStdcall(char *) AnsVariant(int Number)
{
  return variants[Number];
}
//---------------------------------------------------------------------------
char *task =
  "В каком состоянии у вещества большее расстояние между молекулами?";
ExportStdcall(char *) Task(void)
{
  return task;
}
//---------------------------------------------------------------------------
const float cylh = 0.8, r = 0.15, rl = r - 0.005, pistonh = 0.6;
void DrawCylPist(float low, GLfloat color[4])
{
  glTranslatef(0, 0, low-0.7);
  glColor3f(0.6, 0.8, 0.4);
  glLineWidth(2);
  glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, pistonh);
  glEnd();
  glLineWidth(4);
  glBegin(GL_LINES);
    glVertex3f(-r, 0, pistonh);
    glVertex3f(r, 0, pistonh);
  glEnd();
  glColor3f(0.1, 0.1, 0.2);
  gluDisk(q, 0, r, 30, 1);
  glTranslatef(0, 0, -low);
  glDisable(GL_LIGHTING);
    glColor4fv(color);
    gluCylinder(q, rl, rl, low, 30, 40);
  glEnable(GL_LIGHTING);
  glColor4f(1, 1, 1, 0.2);
  gluCylinder(q, r, r, cylh, 30, 40);
}
//---------------------------------------------------------------------------
ExportStdcall(void) OnTimerEvent(void)
{
  GLfloat gas_color[] = {0.6, 0.6, 0.6, 0.3},
    liquid_color[] = {0.1, 0.2, 0.2, 0.9};
  static float down = cylh;
  const float MIN_LIQUID = 0.7, MIN_GAS = 0.3;
  glLoadIdentity();
    glTranslatef(-0.5, 0, 0);
    glPushMatrix();
      glTranslatef(-0.1, -0.8, 0);
      glScalef(0.1, 0.1, 1);
      glCallLists(4, GL_UNSIGNED_BYTE, "Вода");
    glPopMatrix();
    glRotatef(-120, 1, 0, 0);
    DrawCylPist(down > MIN_LIQUID ? down : MIN_LIQUID, liquid_color);

  glLoadIdentity();
    glTranslatef(0.5, 0, 0);
    glPushMatrix();
      glTranslatef(-0.08, -0.8, 0);
      glScalef(0.1, 0.1, 1);
      glCallLists(3, GL_UNSIGNED_BYTE, "Пар");
    glPopMatrix();
    glRotatef(-120, 1, 0, 0);
    DrawCylPist(down > MIN_GAS ? down : MIN_GAS, gas_color);
  down -= 0.01;
}
//---------------------------------------------------------------------------
