//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <GL/glu.h>
#include <vector>
#include "Level3Routines.h"
#include "SrtFile.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

using std::vector;

const float xscale = 0.12, yscale = 0.15;
const AnsiString Hint = "Расположите слова по группам";
const unsigned NoWord = 0xFFFF;
AnsiString problempath;
GLuint SelectBuf[160];
unsigned SelWord;
vector<TMovingWord> words;
GLUquadricObj *box;
TStringList *Prb20;
//---------------------------------------------------------------------------
void LoadSort(void)
{
  glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
  SelWord = NoWord;  
  glDisable(GL_SCISSOR_TEST);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_NORMALIZE);
  GLfloat lcoord[] = { 0, 0, -100, 1};
  glLightfv(GL_LIGHT0, GL_POSITION, lcoord);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  box = gluNewQuadric();
  glViewport(0, 0, width, height);
  SortFile.LoadFromFile(problempath + Prb20->Strings[0]);
  Prb20->Delete(0);
  words.clear();
  for (int i = 0; i < 3; i++)
    for (int j = SortFile.GroupWords[i]->Count - 1; j >= 0; j--)
      words.push_back(TMovingWord(SortFile.GroupWords[i]->Strings[j], i));
  glSelectBuffer(sizeof SelectBuf, SelectBuf);
}
//---------------------------------------------------------------------------
void DrawFrame(void)
{
  for (unsigned i = 0; i < words.size(); i++)
    if (i != SelWord)
    {
      glLoadName(i);
      glColor3fv(words[i].color);
      glLoadIdentity();
      glTranslatef(words[i].x, words[i].y, 0);
      glRotatef(words[i].angle, 0, 1, 0);
      glScalef(xscale, yscale, 0.2);
      glCallLists(words[i].word.Length(), GL_UNSIGNED_BYTE,
        words[i].word.c_str());
    }
  const float colors[3][3] = { {1, 0, 0}, {0, 1, 0 }, {0, 0, 1} };
  const float r = 0.8 / 3, d = 0.2 / 3, w = 0.55;
  glLoadIdentity();
  glTranslatef(-1, -0.65, -0.8);
  glPushMatrix();
    glTranslatef(d + r, 0 , 0);
    glEnable(GL_DEPTH_TEST);
    glRotatef(30, 1, 0, 0);
    glScalef(1, 0.1, 1);
    for (int i = 0; i < 3; i++)
    {
      glLoadName(words.size() + i);
      glColor3fv(colors[i]);
      gluCylinder(box, r, r, w, 100, 40);
      glTranslatef((r + d) * 2, 0, 0);
    }
    glDisable(GL_DEPTH_TEST);
  glPopMatrix();

  glTranslatef(1 / 3.0 - SortFile.GroupNames[0].Length() / 31.0, 0.05, 0);
  glScalef(xscale, yscale, 1);
  for (int i = 0; i < 3; i++)
  {
    if (i > 0)
      glTranslatef((2 / 3.0 - (SortFile.GroupNames[i - 1].Length() +
        SortFile.GroupNames[i].Length()) / 31.0) / xscale , 0, 0);
    glLoadName(words.size() + i);
    glColor3fv(colors[i]);
    glCallLists(SortFile.GroupNames[i].Length(), GL_UNSIGNED_BYTE,
      SortFile.GroupNames[i].c_str());
  }
}
//---------------------------------------------------------------------------
void OnSortTimer(void)
{
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(-0.9, 0.85, 0);
    glScalef(xscale, yscale, 1);
  glColor3f(0.8, 0.2, 0.3);
  glCallLists(Hint.Length(), GL_UNSIGNED_BYTE, Hint.c_str());
  DrawFrame();
  if (SelWord != NoWord)
  {
    glLoadIdentity();
    glTranslatef(-words[SelWord].word.Length() / 31.0, -0.4, 0);
    glScalef(xscale, yscale, 1);
    glColor3f(1, 0, 0);
    glCallLists(words[SelWord].word.Length(), GL_UNSIGNED_BYTE,
      words[SelWord].word.c_str());
  }
  for (unsigned i = 0; i < words.size(); i++)
    words[i].ModifyMove();
}
//---------------------------------------------------------------------------
void CleanupSort(void)
{
  gluDeleteQuadric(box);
  glDisable(GL_COLOR_MATERIAL);
  glDisable(GL_NORMALIZE);
  glDisable(GL_LIGHTING);
  glDisable(GL_LIGHT0);
}
//---------------------------------------------------------------------------
int OnSortMouseDown(int X, int Y)
{
  glRenderMode(GL_SELECT);
  glInitNames();
  glPushName(0);
  GLint vp[4];
  glGetIntegerv(GL_VIEWPORT, vp);
  glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPickMatrix(X, vp[3] - Y, 4, 4, vp);
  glMatrixMode(GL_MODELVIEW);
  DrawFrame();          
  GLint hits = glRenderMode(GL_RENDER);
  glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
  if (hits)
  {
    unsigned i = SelectBuf[(hits - 1) * 4 + 3];
    if (i < words.size()) SelWord = i;
    else
      if (SelWord != NoWord)
      {
        if (words[SelWord].group != i - words.size())
        {
          CleanupSort();
          return 2;
        }
        words.erase(&words[SelWord]);
        SelWord = NoWord;
        if (words.size() == 0)
        {
          CleanupSort();
          return 1;
        }
      }
  }
  return 0;
}
//---------------------------------------------------------------------------
TMovingWord::TMovingWord(AnsiString Word, int Group)
{
  word = Word;
  group = Group;
  const COLORREF MIN_LIGHT = 0x60;
  color[0] = (random(0xFF - MIN_LIGHT) + MIN_LIGHT) / 255.0;
  color[1] = (random(0xFF - MIN_LIGHT) + MIN_LIGHT) / 255.0;
  color[2] = (random(0xFF - MIN_LIGHT) + MIN_LIGHT) / 255.0;
  x = (random((MAXX - MINX) * 100) + MINX * 100) / 100.0;
  y = (random((MAXY - MINY) * 100) + MINY * 100) / 100.0;
  angle = random(360);
  More = random(2);
  switch (random(2))
  {
    case 0:
      xtransfer = true;
      maxval = MAXX;
      minval = MINX;
      break;
    case 1:
      xtransfer = false;
      maxval = MAXY;
      minval = MINY;
      break;
  }
}
//---------------------------------------------------------------------------
void TMovingWord::ModifyMove(void)
{
  float d = random(21) / 5000.0;
  angle = (angle + 1) % 360;
  changing = xtransfer ? &x : &y;
  if (More)
    if (*changing < maxval) *changing += d;
    else
    {
      *changing = maxval;
      More = false;
    }
  else
    if (*changing > minval) *changing -= d;
    else
    {
      *changing = minval;
      More = true;
    }
}
//---------------------------------------------------------------------------
char *task;
typedef char *__stdcall (*TAnsVariantProc)(int Number);
typedef char *__stdcall (*TTaskProc)(void);
typedef void __stdcall (*TVoidReturnProc)(void);
typedef int __stdcall (*TIntReturnProc)(void);
extern int points;
HMODULE DllInstance;
int NumVariants, Correct;
TVoidReturnProc OnTimerEvent;
TAnsVariantProc AnsVariant;
TStringList *Prb5, *Prb10;
//---------------------------------------------------------------------------
void LoadSelect(void)
{
  if (points == 5)
  {
    DllInstance = LoadLibrary((problempath + Prb5->Strings[0]).c_str());
    Prb5->Delete(0);
  }
  else
  {
    DllInstance = LoadLibrary((problempath + Prb10->Strings[0]).c_str());
    Prb10->Delete(0);
  }
  NumVariants = reinterpret_cast<TIntReturnProc>
    (GetProcAddress(DllInstance, "NumVariants"))();
  Correct = reinterpret_cast<TIntReturnProc>
    (GetProcAddress(DllInstance, "Correct"))();
  task = reinterpret_cast<TTaskProc>
    (GetProcAddress(DllInstance, "Task"))();
  OnTimerEvent = reinterpret_cast<TVoidReturnProc>
    (GetProcAddress(DllInstance, "OnTimerEvent"));
  AnsVariant = reinterpret_cast<TAnsVariantProc>
    (GetProcAddress(DllInstance, "AnsVariant"));

  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
  glEnable(GL_SCISSOR_TEST);
  glViewport(0, 0, width, height * 0.2);
  glScissor(0, 0, width, height * 0.2);
  glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
  const GLfloat scalex = 0.08, scaley = 0.5, xstart = -1;
  glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(xstart, 0.5, 0);
    glScalef(scalex, scaley, 1);
  glColor3f(1, 0.1, 0.1);
  int len1 = StrLen(task), len2 = 0;
  if (len1 > 45)
  {
    len1 = 45;
    while (task[len1] != ' ') len1--;
    len2 = StrLen(task) - len1 - 1;
  }
  glCallLists(len1, GL_UNSIGNED_BYTE, task);
  if (len2)
  {
    glLoadIdentity();
    glTranslatef(xstart, -0.1, 0);
    glScalef(scalex, scaley, 1);
    glCallLists(len2, GL_UNSIGNED_BYTE, &task[len1 + 1]);
  }
  glLoadIdentity();
    glTranslatef(xstart, -0.75, 0);
    glScalef(scalex, scaley, 1);
  const GLfloat colors[4][3] =
    {{1, 0, 0.5}, {1, 1, 0}, {0.3, 1, 0}, {0, 0, 1}};
  for (int i = 0; i < NumVariants; i++)
  {
    glPushMatrix();
      glColor3fv(colors[i]);
      glCallLists(StrLen(AnsVariant(i)), GL_UNSIGNED_BYTE, AnsVariant(i));
    glPopMatrix();
    glTranslatef(2 / scalex / NumVariants, 0, 0);
  }
  glViewport(0, height * 0.2, width, height - height * 0.2);
  glScissor(0, height * 0.2, width, height - height * 0.2);
  glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
  glPushAttrib(GL_ALL_ATTRIB_BITS);
  reinterpret_cast<TVoidReturnProc>(GetProcAddress(DllInstance,
    "InitGL"))();
}
//---------------------------------------------------------------------------
void OnSelectTimer(void)
{
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
  (*OnTimerEvent)();
}
//---------------------------------------------------------------------------
bool OnSelectMouseDown(int X)
{
  FreeLibrary(DllInstance);
  glPopAttrib();
  glDisable(GL_SCISSOR_TEST);
  if (Correct == X / (width / NumVariants)) return true;
  else return false;
}
//---------------------------------------------------------------------------
void InitLists(void)
{
  problempath = ExtractFilePath(ParamStr(0)) + "Problems\\";
  Prb5 = new TStringList;
  WIN32_FIND_DATAA fdata;
  HANDLE HFind = FindFirstFileA((problempath + "*.5pn").c_str(), &fdata);
  do
    Prb5->Insert(random(Prb5->Count), fdata.cFileName);
  while (FindNextFileA(HFind, &fdata));
  FindClose(HFind);
  while (Prb5->Count > 4) Prb5->Delete(4);

  Prb10 = new TStringList;
  HFind = FindFirstFileA((problempath + "*.10pn").c_str(), &fdata);
  do
    Prb10->Insert(random(Prb10->Count), fdata.cFileName);
  while (FindNextFileA(HFind, &fdata));
  FindClose(HFind);
  while (Prb10->Count > 4) Prb10->Delete(4);

  Prb20 = new TStringList;
  HFind = FindFirstFileA((problempath + "*.srt").c_str(), &fdata);
  do
    Prb20->Insert(random(Prb20->Count), fdata.cFileName);
  while (FindNextFileA(HFind, &fdata));
  FindClose(HFind);
  while (Prb20->Count > 4) Prb20->Delete(4);
}
//---------------------------------------------------------------------------
void FreeLists(void)
{
  delete Prb5;
  delete Prb10;
  delete Prb20;
}
//---------------------------------------------------------------------------
#pragma startup InitLists
#pragma exit FreeLists
//---------------------------------------------------------------------------
