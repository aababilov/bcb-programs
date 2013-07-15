//---------------------------------------------------------------------------
#include <vcl.h>

#pragma hdrstop

#include <math.h>
#include <jpeg.hpp>
#include <GL/glu.h>
#include "Utils.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------
struct TWall
{
  GLfloat xmin, xmax, zmin, zmax, length;
};
struct TFloatPoint
{
  float x, y;
};
//---------------------------------------------------------------------------
const float deviation = 0;
const GLfloat CHAR_EXT = 0.2;
const int TEXT_D = 16, WallCount = 46;
const GLfloat top = 4, EyeY = 1;
const GLdouble RSphere = 0.5;
const GLuint BACKGROUNDLIST = 1, WALLSLIST = 2, SPACECRAFTLIST = 3,
  STARSLIST = 4;
const double MIN_BOT_T = -0.8;
const int MAX_GAME_NAME = 50;
const char Prologue[] =
"Физон с планеты Физма может\r\n\
взять Вас с собой в космический\r\n\
полёт, если Вы покажете быстро-\r\n\
ту реакции, способности к физике\r\n\
и математике. Для этого Вам не-\r\n\
обходимо пройти три уровня про-\r\n\
верки и суперигру, набрав соот-\r\n\
ветствующее количество баллов:\r\n\
  140 баллов и выше - Вы помощ-\r\n\
ник командира корабля, \r\n\
  от 60 до 139 баллов - Вы член\r\n\
экипажа,  \r\n\
  от 40 до 59 баллов - Вы пасса-\r\n\
жир, \r\n\
  а меньше 40 баллов - Вас не бе-\r\n\
рут в полёт.\r\n\r\n\
Дополнительные сведения.\r\n\
Физма - планета, где обитают\r\n\
существа с развитыми способ-\r\n\
ностями к физике и математике.\r\n\
Экстренный выход из игры - Esc \r\n\
или Alt+F4. Приступить к выпол-\r\n\
нению заданий уровня или супер-\r\n\
игры - пробел";

TWall Walls[WallCount];
TFloatPoint *WallPoints;
GLUquadricObj *q;
HDC MainDC, PanelDC;
HGLRC MainRC, PanelRC;
GLuint textures[3];
GLfloat EyeX = 75, EyeZ = 64,
  Spheres[2][2] = {{72, 67}, {29, 53}};
double Angle;
unsigned WhSpheres = 3;
//---------------------------------------------------------------------------
inline float Distance(float dx, float dy)
{
  return sqrt(dx * dx + dy * dy);
}
//---------------------------------------------------------------------------
void SetupGLDC(HWND Wnd, HDC &DC, HGLRC &RC)
{
  DC = GetDC(Wnd);
  PIXELFORMATDESCRIPTOR pfd = { sizeof(PIXELFORMATDESCRIPTOR) };
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL
    | PFD_DOUBLEBUFFER;
  pfd.dwLayerMask = PFD_MAIN_PLANE;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.cColorBits = 24;
  pfd.cDepthBits = 32;
  SetPixelFormat(DC, ChoosePixelFormat(DC, &pfd), &pfd);
  RC = wglCreateContext(DC);
  wglMakeCurrent(DC, RC);
  glListBase(CHARS_START - FIRST_SYMB);
}
//---------------------------------------------------------------------------
void BmpTexImage(HDC dc, HBITMAP bitmap, bool SetAlpha = false)
{
  BITMAP sz;
  GetObjectA(bitmap, sizeof sz, &sz);
  BITMAPINFO bmi = {{sizeof(BITMAPINFO), sz.bmWidth, sz.bmHeight, 1, 32},
    {{255, 255, 255}}};
  GLubyte *bits = new GLubyte[sz.bmWidth * sz.bmHeight * 4], tmp;
  GetDIBits(dc, bitmap, 0, sz.bmHeight, bits, &bmi, DIB_RGB_COLORS);
  if (SetAlpha)
    for (int i = sz.bmWidth * sz.bmHeight - 1; i >= 0; i--)
      bits[i * 4 + 3] = bits[i * 4];
  else
    for (int i = sz.bmWidth * sz.bmHeight - 1; i >= 0; i--)
    {
      tmp = bits[i * 4];
      bits[i * 4] = bits[i * 4 + 2];
      bits[i * 4 + 2] = tmp;
    }
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sz.bmWidth, sz.bmHeight, 0,
    GL_RGBA, GL_UNSIGNED_BYTE, bits);
  delete bits;
}
//---------------------------------------------------------------------------
void InitListsAndTextures(HWND HForm, HWND HPanel)
{
  SetupGLDC(HPanel, PanelDC, PanelRC);
  LOGFONT lf = {10, -10, 0, 0, 700, 0, 0, 0,
    DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
    DEFAULT_QUALITY, FF_DONTCARE | DEFAULT_PITCH, "Courier New"};
  HFONT hfNew = CreateFontIndirect(&lf),
    hfOld = SelectObject(PanelDC, hfNew);
  wglUseFontOutlines(PanelDC, FIRST_SYMB, LAST_SYMB, CHARS_START, deviation,
    CHAR_EXT, WGL_FONT_POLYGONS, NULL);
  DeleteObject(SelectObject(PanelDC, hfOld));
  DeleteObject(SelectObject(PanelDC, hfNew));
  SetupGLDC(HForm, MainDC, MainRC);
  wglShareLists(PanelRC, MainRC);
  q = gluNewQuadric();
  glEnable(GL_TEXTURE_2D);

  glGenTextures(3, textures);
  glBindTexture(GL_TEXTURE_2D, textures[0]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  TJPEGImage *JPEGImg = new TJPEGImage;
  TResourceStream *Stream = new TResourceStream(
    reinterpret_cast<UINT>(HInstance), "SPACE", RT_RCDATA);
  Graphics::TBitmap *BmpImg = new Graphics::TBitmap;
  JPEGImg->LoadFromStream(Stream);
  BmpImg->Assign(JPEGImg);
  BmpTexImage(BmpImg->Canvas->Handle, BmpImg->Handle);
  delete BmpImg;
  delete Stream;
  delete JPEGImg;

  glBindTexture(GL_TEXTURE_2D, textures[2]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  Graphics::TBitmap *bmp = new Graphics::TBitmap;
  bmp->Width = 512;
  bmp->Height = 1024;
  RECT r = {0, 4, 508, 1024};
  bmp->Canvas->Font->Name = "Arial";
  bmp->Canvas->Font->Size = 24;
  bmp->Canvas->Font->Color = clWhite;
  bmp->Canvas->Brush->Color = clBlack;
  bmp->Canvas->FillRect(bmp->Canvas->ClipRect);
  DrawText(bmp->Canvas->Handle, Prologue, strlen(Prologue),
    &r, DT_WORDBREAK);
  BmpTexImage(bmp->Canvas->Handle, bmp->Handle, true);
  delete bmp;

  glNewList(BACKGROUNDLIST, GL_COMPILE);
    glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
    const float corner = 1.001, zcoord = 0.98;
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
      glTexCoord2f(0, 0);
      glVertex3f(-corner, -corner, zcoord);
      glTexCoord2f(0, 1);
      glVertex3f(-corner, corner, zcoord);
      glTexCoord2f(1, 1);
      glVertex3f(corner, corner, zcoord);
      glTexCoord2f(1, 0);
      glVertex3f(corner, -corner, zcoord);
    glEnd();
  glEndList();

  WallPoints = static_cast<TFloatPoint*>(LockResource(LoadResource
    (HInstance, FindResource(HInstance, "MAZE", RT_RCDATA))));
  TFloatPoint plate = *WallPoints++;
  for (int i = 0; i < WallCount; i++)
  {
    SetMinMax(WallPoints[i].x, WallPoints[i + 1].x,
      Walls[i].xmin, Walls[i].xmax);
    SetMinMax(WallPoints[i].y, WallPoints[i + 1].y,
      Walls[i].zmin, Walls[i].zmax);
    Walls[i].length = Distance(WallPoints[i].x - WallPoints[i + 1].x,
      WallPoints[i].y - WallPoints[i + 1].y);
  }
  glBindTexture(GL_TEXTURE_2D, textures[3]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  TResImage stone("STONE");
  BmpTexImage(stone.DevCtxt, stone.Bitmap);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

  glNewList(WALLSLIST, GL_COMPILE);
    glBegin(GL_QUADS);
      glColor3f(0.1, 0.1, 0.2);
      glVertex3f(0, -1, 0);
      glVertex3f(0, -1, plate.y);
      glVertex3f(plate.x, -1, plate.y);
      glVertex3f(plate.x, -1, 0);
      glColor3f(0.3, 0.7, 0.7);
      glVertex3f(0, top,  plate.y);
      glVertex3f(0, top, 0);
      glVertex3f(plate.x, top, 0);
      glVertex3f(plate.x, top,  plate.y);
    glEnd();
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUAD_STRIP);
      float k = 0;
      for (int i = 0; i <= WallCount; i++)
      {
        glTexCoord2f(k * 2, 0);
        glVertex3f(WallPoints[i].x,  -1, WallPoints[i].y);
        glTexCoord2f(k * 2, top * 2);
        glVertex3f(WallPoints[i].x, top, WallPoints[i].y);
        k += Walls[i].length;
      }
    glEnd();
    glDisable(GL_TEXTURE_2D);
  glEndList();

  GLfloat *Material = static_cast<GLfloat*>(LockResource(LoadResource
    (HInstance, FindResource(HInstance, "SPACECRAFT", RT_RCDATA))));
  GLuint *Index = reinterpret_cast<GLuint*>(Material + 72);
  glInterleavedArrays(GL_N3F_V3F, 0, reinterpret_cast<GLfloat*>
    (Index + 1734));
  glNewList(SPACECRAFTLIST, GL_COMPILE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glMaterialfv(GL_FRONT, GL_AMBIENT, Material + 0);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, Material + 4);
    glMaterialfv(GL_FRONT, GL_SPECULAR, Material + 8);
    glDrawElements(GL_TRIANGLES, 996, GL_UNSIGNED_INT, Index + 0);
    glMaterialfv(GL_FRONT, GL_AMBIENT, Material + 12);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, Material + 16);
    glMaterialfv(GL_FRONT, GL_SPECULAR, Material + 20);
    glDrawElements(GL_TRIANGLES, 276, GL_UNSIGNED_INT, Index + 996);
    glMaterialfv(GL_FRONT, GL_AMBIENT, Material + 24);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, Material + 28);
    glMaterialfv(GL_FRONT, GL_SPECULAR, Material + 32);
    glDrawElements(GL_TRIANGLES, 228, GL_UNSIGNED_INT, Index + 1272);
    glMaterialfv(GL_FRONT, GL_AMBIENT, Material + 36);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, Material + 40);
    glMaterialfv(GL_FRONT, GL_SPECULAR, Material + 44);
    glDrawElements(GL_TRIANGLES, 192, GL_UNSIGNED_INT, Index + 1500);
    glMaterialfv(GL_FRONT, GL_AMBIENT, Material + 48);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, Material + 52);
    glMaterialfv(GL_FRONT, GL_SPECULAR, Material + 56);
    glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, Index + 1692);
    glMaterialfv(GL_FRONT, GL_AMBIENT, Material + 60);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, Material + 64);
    glMaterialfv(GL_FRONT, GL_SPECULAR, Material + 68);
    glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, Index + 1716);
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
  glEndList();

  glNewList(STARSLIST, GL_COMPILE);
    glDisable(GL_DEPTH_TEST);
    glColor3f(1, 1, 0);
    glBegin(GL_POINTS);
    for (int i = 0; i < 100; i++)
      glVertex2f(random(1000) / 500.0 - 1, random(1000) / 500.0 - 1);
    glEnd();
  glEndList();
}
//---------------------------------------------------------------------------
void CleanupGL(const HWND HForm, const HWND HPanel)
{
  gluDeleteQuadric(q);
  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(MainDC);
  wglDeleteContext(PanelDC);
  ReleaseDC(HForm, MainDC);
  ReleaseDC(HPanel, PanelDC);
}
//---------------------------------------------------------------------------
void SetupSuperGame(void)
{
  wglMakeCurrent(MainDC, MainRC);
  glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
  glEnable(GL_DEPTH_TEST);
  glFrontFace(GL_CCW);
  glBindTexture(GL_TEXTURE_2D, textures[3]);
}
//---------------------------------------------------------------------------
bool DrawGameName(void)
{
  const char GameName[] = "Физон";
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glCallList(BACKGROUNDLIST); //Cleans matrices
  glDisable(GL_TEXTURE_2D);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_COLOR_MATERIAL);
  glDisable(GL_CULL_FACE);
  glMatrixMode(GL_PROJECTION);
    glFrustum(-1, 1, -1.4, 1, 0.1, 2);
  static float zt = -1.8;
  static int frame = 0;
  glMatrixMode(GL_MODELVIEW);
    glTranslatef(-1.1, 0.2, zt);
    if (zt < -0.133) zt *= 0.93;
    glScalef(0.8, 0.8, 6);
  glColor3f(0, 1, 0);
  glCallLists(strlen(GameName), GL_UNSIGNED_BYTE, GameName);
  glEnable(GL_CULL_FACE);
  glDisable(GL_COLOR_MATERIAL);
  glDisable(GL_LIGHTING);
  glDisable(GL_LIGHT0);
  glDisable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
  SwapBuffers(MainDC);
  return ++frame > MAX_GAME_NAME;
}
//---------------------------------------------------------------------------
bool DrawRules(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glCallList(BACKGROUNDLIST); //Cleans matrices
  static float bot_t = 0.49;
  float top_t = bot_t + 3;
  const float zNear = 0.1, zFar = -1.1, yc1 = -2, yc2 = yc1 + 0.35,
      left = -1, right = 1.1;
  glMatrixMode(GL_PROJECTION);
    glFrustum(left, right, yc1, 1, zNear, 4);
  glBindTexture(GL_TEXTURE_2D, textures[2]);
  glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBegin(GL_QUADS);
      glTexCoord2f(0, bot_t);
      glVertex3f(left, yc1, zNear);
      glTexCoord2f(0, top_t);
      glVertex3f(left, yc2, zFar);
      glTexCoord2f(1, top_t);
      glVertex3f(right, yc2, zFar);
      glTexCoord2f(1, bot_t);
      glVertex3f(right, yc1, zNear);
    glEnd();
  glDisable(GL_BLEND);

  bot_t -= 0.004;
  SwapBuffers(MainDC);
  return bot_t < MIN_BOT_T;
}
//---------------------------------------------------------------------------
bool DrawFly(void)
{
  static GLfloat y = -6;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
  glCallList(STARSLIST);
  glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40, 1.0, 0.1, 200);
  glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 30.0, 10.0, 0, 0, -5.0, 0, 1, 0);
    glRotatef (234, 1, 0, 0);
    glTranslatef (0.0, y, 0.0);
    glScalef(0.6, 1, 1);
    glCallList(SPACECRAFTLIST);
    glColor3f(1, 1, 0);
    glBegin(GL_LINES);
    for (int i = 0; i < 6; i++)
    {
      glVertex3f(1.3 + i / 12.0, -5, 0);
      glVertex3f(1.3 + i / 12.0, 0, 0);
      glVertex3f(-1.3 - i / 12.0, -5, 0);
      glVertex3f(-1.3 - i / 12.0, 0, 0);
    }
  glEnd();
  SwapBuffers(MainDC);
  return (y += 0.2) > 60;
}
//---------------------------------------------------------------------------
bool CrossWall(GLfloat EndX, GLfloat EndZ)
{
  GLfloat xmin, zmin, xmax, zmax, vx, vz, x1, x2, z1, z2;
  SetMinMax(EyeX, EndX, xmin, xmax);
  SetMinMax(EyeZ, EndZ, zmin, zmax);
  for (int i = 0; i < WallCount; i++)
  {
    x1 = WallPoints[i].x;
    z1 = WallPoints[i].y;
    x2 = WallPoints[i + 1].x;
    z2 = WallPoints[i + 1].y;
    vx = x2 - x1;
    vz = z2 - z1;
    if (xmax < Walls[i].xmin || Walls[i].xmax < xmin ||
        zmax < Walls[i].zmin || Walls[i].zmax < zmin) continue;
    if ((vx * (EyeZ - z2) - vz * (EyeX - x2)) *
        (vx * (EndZ - z2) - vz * (EndX - x2)) > 0) continue;
    vx = EndX - EyeX;
    vz = EndZ - EyeZ;
    if ((vx * (z2 - EyeZ) - vz * (x2 - EyeX)) *
        (vx * (z1 - EyeZ) - vz * (x1 - EyeX)) <= 0) return true;
  }
  return false;
}
//---------------------------------------------------------------------------
bool CannotGo(GLfloat EndX, GLfloat EndZ)
{
  GLfloat vx, vz, x1, x2, z1, z2;
  for (int i = 0; i < WallCount; i++)
    if (Distance(WallPoints[i].x - EndX, WallPoints[i].y - EndZ) < 0.5)
      return true;
  for (int i = 0; i < WallCount; i++)
  {
    x1 = WallPoints[i].x;
    z1 = WallPoints[i].y;
    x2 = WallPoints[i + 1].x;
    z2 = WallPoints[i + 1].y;
    vx = x2 - x1;
    vz = z2 - z1;
    if (fabs((x1 - EndX) * (z2 - EndZ) -
             (z1 - EndZ) * (x2 - EndX))
        < Walls[i].length * 1.5 &&
        (EndX - x1) * vx + (EndZ - z1) * vz >= 0 &&
        (EndX - x2) * vx + (EndZ - z2) * vz <= 0)
      return true;
  }
  if (CrossWall(EndX, EndZ)) return true;
  EyeX = EndX;
  EyeZ = EndZ;
  return false;
}
//---------------------------------------------------------------------------
void DrawMaze(void)
{
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 640.0 / 480.0, 0.05, 100.0);
    gluLookAt(EyeX, EyeY, EyeZ,
      EyeX + cos(Angle), EyeY, EyeZ + sin(Angle), 0, 1, 0);
  glMatrixMode(GL_MODELVIEW);
  glCallList(WALLSLIST);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);
  const GLfloat pos[] = {50, 100, 50, 0};
  glLightfv(GL_LIGHT0, GL_POSITION, pos);
  if (WhSpheres & 1)
  {
    glColor3f(1, 0, 0);
    glTranslatef(Spheres[0][0], EyeY, Spheres[0][1]);
    gluSphere(q, RSphere, 20, 20);
    glLoadIdentity();
  }
  if (WhSpheres & 2)
  {
    glColor3f(0, 1, 0);
    glTranslatef(Spheres[1][0], EyeY, Spheres[1][1]);
    gluSphere(q, RSphere, 20, 20);
    glLoadIdentity();
  }
  glDisable(GL_LIGHTING);
  glDisable(GL_LIGHT0);
  glDisable(GL_COLOR_MATERIAL);

  SwapBuffers(MainDC);
}
//---------------------------------------------------------------------------
bool KeyCheckAndProcess(const WORD Key)
{
  const GLfloat STEP = 2;
  switch (Key)
  {
    case 'W': case VK_UP:
    if (CannotGo(EyeX + STEP * cos(Angle), EyeZ + STEP * sin(Angle)))
      return false;
    else return true;

    case 'S': case VK_DOWN:
    if (CannotGo(EyeX - STEP * cos(Angle), EyeZ - STEP * sin(Angle)))
      return false;
    else return true;

    case 'A': case VK_LEFT:
    if (CannotGo(EyeX - STEP * cos(Angle + M_PI_2),
      EyeZ - STEP * sin(Angle + M_PI_2)))
      return false;
    else return true;

    case 'D': case VK_RIGHT:
    if (CannotGo(EyeX + STEP * cos(Angle + M_PI_2),
      EyeZ + STEP * sin(Angle + M_PI_2)))
      return false;
    else return true;

    default:
    return false;
  }
}
//---------------------------------------------------------------------------
int ClickProcess(void)
{       
  GLdouble modelMatrix[16], projMatrix[16], wx, wy, wz;
  glGetDoublev(GL_MODELVIEW_MATRIX, modelMatrix);
  glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
  GLint viewport[] = {0, 0, 640, 480};
  for (unsigned Sph = 1; Sph <= 2; Sph <<= 1)
    if (WhSpheres & Sph)
      if (!CrossWall(Spheres[Sph - 1][0], Spheres[Sph - 1][1]))
      {
        gluProject(Spheres[Sph - 1][0], EyeY + RSphere,
          Spheres[Sph - 1][1], modelMatrix, projMatrix, viewport,
          &wx, &wy, &wz);
        if (fabs(320 - wx) <= wy - 240)
        {
          WhSpheres &= ~Sph;
          return Sph;
        }
      }
  return 0;
}
//---------------------------------------------------------------------------
void ChangeAngle(int Delta)
{
  Angle += Delta / 500.0;
  if (Angle > M_PI * 2) Angle -= M_PI * 2;
  else if (Angle < 0) Angle += M_PI * 2;
}
//---------------------------------------------------------------------------
TResImage::TResImage(const char *Name)
{
  Bitmap = LoadBitmap(HInstance, Name);
  DevCtxt = CreateCompatibleDC(NULL);
  SelectObject(DevCtxt, Bitmap);
  GetObjectA(Bitmap, sizeof prop, &prop);
}
//---------------------------------------------------------------------------
TResImage::~TResImage()
{
  SelectObject(DevCtxt, NULL);
  DeleteObject(Bitmap);
  DeleteObject(DevCtxt);
}
//---------------------------------------------------------------------------
void TResImage::DrawSqr(HDC DC, int X, int Y, int Index) const
{
  BitBlt(DC, X, Y, prop.bmHeight, prop.bmHeight, DevCtxt,
    prop.bmHeight * Index, 0, SRCCOPY);
}
//---------------------------------------------------------------------------
void TResImage::Draw(HDC DC, int X, int Y) const
{
  BitBlt(DC, X, Y, prop.bmWidth, prop.bmHeight, DevCtxt, 0, 0, SRCCOPY);
}
//---------------------------------------------------------------------------
HDC TMeteorite::DevCtxt;
TCanvas *TMeteorite::BmpCanvas;
//---------------------------------------------------------------------------
TMeteorite::TMeteorite(void)
{
  X = random(600);
  Y = -32;
  speed = (Picture = random(6)) * 0.5 + 3;
}
//---------------------------------------------------------------------------
bool TMeteorite::DrawSelf(TMeteorite *from)
{
  static const TResImage MeteoPics("METEORITES");
  bool crash = false;
  for (; from < this; from++)
    if (abs(from->X - X) < 40 && abs(from->Y - Y) < 40)
    {
      crash = true;
      break;
    }
  Clean();
  if (crash) return true;
  if (Y > 356)
  {
    lost++;
    return true;
  }  
  MeteoPics.DrawSqr(DevCtxt, X, Y += speed, Picture);
  return false;
}
//---------------------------------------------------------------------------
void TMeteorite::Clean(void)
{
  BitBlt(DevCtxt, X, Y, 32, 32, BmpCanvas->Handle, X, Y, SRCCOPY);
}
//---------------------------------------------------------------------------
