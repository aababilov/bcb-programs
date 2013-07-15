//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <gl/gl.h>
#include <gl/glu.h>
#include <algorithm>
#include <cmath>
using std::atan;
using std::cos;
using std::sin;
using std::sqrt;
using std::acos;
using std::fabs;
using std::asin;
using std::max;
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSettingsForm *SettingsForm;
HANDLE viewDC, viewRC;
//---------------------------------------------------------------------------
struct TDice
{
  double Angle, Omega, L_Moment, K_Energy;
};
//------------------------------------------------------------------------------
// length = 0.206;        // в м.
// dthickness = 0.028;      // в м.
// dwidth = 0.133;         // в м.
// step = 0.10;            // в м.
// mass = 200;           // в гр.
const double M_g = 9.813;
//------------------------------------------------------------------------------
long double Str2Float(AnsiString s)
{
  for (int i = 1; i <= s.Length(); i++)
    if (s[i] < '0' || s[i] > '9')
      if (s[i] == '.' || s[i] == ',')
        s[i] = DecimalSeparator;
      else
      {
        s.Delete(i, 1);
        i--;
      }
  return s.Length() ? StrToFloat(s) : 0;
}
template<class T>
inline T sqr(const T &x)
{
  return x * x;
}
//------------------------------------------------------------------------------// в м/с2.
// Dom_Count = 3;
// Delta_T = 0.01; // в с.
// Tollerance = 0.001;

TDice Domins[28];
int CurFirst, Dom_Count, TaktCount;
double dlength, dthickness, dwidth, step, Delta_T, Tollerance, atan_cnv,
  I_Moment, Omega, Epsilon, StartTime;// epsilon - rad/s2 ;  omega - rad/s
int oldX, oldY;
float dist = 2., angle, height = 0.5, aspect;
//------------------------------------------------------------------------------
long double MyCos(long double A)
{
  long double Result;
  Result = cos(A * M_PI / 180) * 180 / M_PI;
  return Result;
}
//------------------------------------------------------------------------------
void RedrawPicture(void)
{
  static const float xp[] = {1, 0, 0}, xn[] = {-1, 0, 0},
    yp[] = {0, 1, 0}, yn[] = {0, -1, 0},
    zp[] = {0, 0, 1}, zn[] = {0, 0, -1},
    diceDiff[] = {0.5, 0.5, 0.0, 1};
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diceDiff);
  const float tblY = 0, tblX = 1, tblZ = 0.5, tblThick = 0.05;
  glColor3f(0.4, 0.7, 0);
  glBegin(GL_QUADS);
    glNormal3fv(yp);
    glVertex3f(-tblX, tblY, tblZ);
    glVertex3f(tblX, tblY, tblZ);
    glVertex3f(tblX, tblY, -tblZ);
    glVertex3f(-tblX, tblY, -tblZ);
  glEnd();
  glBegin(GL_QUAD_STRIP);
    glNormal3fv(zp);
    glVertex3f(-tblX, tblY, tblZ);
    glVertex3f(-tblX, tblY - tblThick, tblZ);
    glVertex3f(tblX, tblY, tblZ);
    glVertex3f(tblX, tblY - tblThick, tblZ);
    glNormal3fv(xp);
    glVertex3f(tblX, tblY, -tblZ);
    glVertex3f(tblX, tblY - tblThick, -tblZ);
    glNormal3fv(zn);
    glVertex3f(-tblX, tblY, -tblZ);
    glVertex3f(-tblX, tblY - tblThick, -tblZ);
    glNormal3fv(xn);
    glVertex3f(-tblX, tblY, tblZ);
    glVertex3f(-tblX, tblY - tblThick, tblZ);
  glEnd();

  glColor3f(1, 0.9, 1);
  for (int i = 0; i < Dom_Count; i++)
  {
    glLoadIdentity();
    glTranslatef(step * tblX * (Dom_Count / 2 - i), 0, 0);
    glRotatef(90 - Domins[i].Angle, 0, 0, 1);
    glBegin(GL_QUAD_STRIP);
      glNormal3fv(zn);
      glVertex3f(0, 0, 0);
      glVertex3f(dthickness, 0, 0);
      glVertex3f(0, dlength, 0);
      glVertex3f(dthickness, dlength, 0);
      glNormal3fv(yp);
      glVertex3f(0, dlength, dwidth);
      glVertex3f(dthickness, dlength, dwidth);
      glNormal3fv(zp);
      glVertex3f(0, 0, dwidth);
      glVertex3f(dthickness, 0, dwidth);
      glNormal3fv(yn);
      glVertex3f(0, 0, 0);
      glVertex3f(dthickness, 0, 0);
    glEnd();
    glBegin(GL_QUADS);
      glNormal3fv(xn);
      glVertex3f(0, 0, dwidth);
      glVertex3f(0, dlength, dwidth);
      glVertex3f(0, dlength, 0);
      glVertex3f(0, 0, 0);
      glNormal3fv(xp);
      glVertex3f(dthickness, 0, 0);
      glVertex3f(dthickness, dlength, 0);
      glVertex3f(dthickness, dlength, dwidth);
      glVertex3f(dthickness, 0, dwidth);
    glEnd();
  }
  SwapBuffers(viewDC);
}
//------------------------------------------------------------------------------
void SetView(void)
{
  glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, aspect, 0.1, 15.0);
    gluLookAt(cos(angle) * 2, height, sin(angle) * 1.5,
      0, 0.4, 0, 0, 1, 0);
  glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
  const float lPos[] = {0, 1, 0, 1}, lDir[] = {0, 0, 0, 1};
  glLightfv(GL_LIGHT0, GL_POSITION, lPos);
  glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lDir);
  RedrawPicture();
}
//------------------------------------------------------------------------------
long double GetBeta(long double alpha, bool rad)
{
  long double Result;
  double A, B, D1, x2, x1, angle;
  if (~rad)
    angle = alpha * M_PI / 180;
  else
    angle = alpha;
  A = dlength * sin(angle) / dthickness;
  B = (dlength * cos(angle) - step) / dthickness;
  D1 = B * B * (B * B - 1 + A * A);
  if ((D1 < 0))
  {
    Result = -1;
    return Result;
  }
  D1 = sqrt(D1);
  x2 = (-A + D1) / (B * B - 1);
  x1 = (-A - D1) / (B * B - 1);
  if ((A - x2) / B < 0)
    if ((A - x1) / B < 0)
    {
      Result = -1;
      return Result;
    }
    else
      x2 = x1;
  Result = acos(1 / x2);
  if (~rad)
    Result = Result * 180 / M_PI;
  return Result;
}
//------------------------------------------------------------------------------
long double GetAlpha(long double beta, bool rad)
{
  long double Result;
  double angle, A, B;
  if (~rad)
    angle = beta * M_PI / 180;
  else
    angle = beta;
  A = (sin(angle) * step - dthickness) / dlength;
  B = cos(angle) / (step / dthickness - sin(angle));
  if (((A >= -1) && (A <= 1)))
    Result = max(fabs(asin(A) - angle), atan(B));
  else
  {
    Result = -1;
    return Result;
  }
  if (~rad)
    Result = Result * 180 / M_PI;
  return Result;
}
//------------------------------------------------------------------------------
double FindMoment(double deltaOmega)
{
  double Result;
  int i;
  double CurAngle, delta;
  delta = deltaOmega;
  CurAngle = Domins[CurFirst].Angle - deltaOmega * Delta_T;
  Result = delta * I_Moment;
  if (CurFirst != 0)
    for (i = CurFirst - 1; i >= 0; i--)
    {
      CurAngle = GetAlpha(CurAngle, false);
      delta = Domins[i].Angle - CurAngle;
      Result = Result + delta * I_Moment;
    }
  return Result;
}
//------------------------------------------------------------------------------
double FindFirstMoment(double Omega)
{
  double Result;
  int i;
  double CurAngle, delta;
  CurAngle = Domins[CurFirst + 1].Angle - Omega * Delta_T;
  Result = Omega * I_Moment;
  CurAngle = GetAlpha(CurAngle, false);
  delta = (Domins[CurFirst].Angle - CurAngle);
  Result = Result + delta * I_Moment;
  return Result;
}
//------------------------------------------------------------------------------
double FindFirstOmega(void)
{
  double Result;
  double iLo, iHi, iT;
  double lLo, lHi, lT;
  int i;
  double L_Moment1;
  L_Moment1 = Domins[CurFirst].Omega * I_Moment;
  iLo = 0;
  iHi = Domins[CurFirst].Omega;
  iT = iLo;
  lLo = FindFirstMoment(iLo) - L_Moment1;
  lHi = FindFirstMoment(iHi) - L_Moment1;
  if (lLo * lHi < 1)
    do
    {
      iT = (iLo + iHi) / 2;
      lT = FindFirstMoment(iT) - L_Moment1;
      if (lT == 0)
        break;
      if (lHi * lT < 1)
      {
        iLo = iT;
        lLo = lT;
      }
      else
      {
        iHi = iT;
        lHi = lT;
      }
    }
    while (!(iHi - iLo < Tollerance));
  Result = iT;
  return Result;
}
//------------------------------------------------------------------------------
double FindDeltaOmega(void)
{
  double Result;
  double iLo, iHi, iT;
  double lLo, lHi, lT;
  double Summary_LmgMoment, fm;
  int i;
  Result = 0;
  if (CurFirst == 0)
    return Result;
  Summary_LmgMoment = 0;
  {
    int Main__2 = Dom_Count - 1;
    for (i = 0; i <= Main__2; i++)
      Summary_LmgMoment += M_g * 2 / dlength * MyCos(Domins[i].Angle) * Delta_T * I_Moment;
  }
  iLo = 0;
  iHi = Domins[CurFirst].Angle;
  iT = iLo;
  fm = FindMoment(iLo);
  lLo = fm - Summary_LmgMoment;
  fm = FindMoment(iHi);
  lHi = fm - Summary_LmgMoment;
  if (lLo * lHi < 1)
    do
    {
      iT = (iLo + iHi) / 2;
      lT = FindMoment(iT) - Summary_LmgMoment;
      if (lT == 0)
        break;
      if (lHi * lT < 1)
      {
        iLo = iT;
        lLo = lT;
      }
      else
      {
        iHi = iT;
        lHi = lT;
      }
    }
    while (!(iHi - iLo < Tollerance));
  return iT;
}
//------------------------------------------------------------------------------
__fastcall TSettingsForm::TSettingsForm(TComponent* Owner)
  : TForm(Owner)
{
  viewDC = GetDC(ViewPanel->Handle);
  PIXELFORMATDESCRIPTOR pfd = { sizeof(PIXELFORMATDESCRIPTOR) };
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL
    | PFD_DOUBLEBUFFER;
  pfd.dwLayerMask = PFD_MAIN_PLANE;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.cColorBits = 24;
  pfd.cDepthBits = 32;
  SetPixelFormat(viewDC, ChoosePixelFormat(viewDC, &pfd), &pfd);
  viewRC = wglCreateContext(viewDC);
  wglMakeCurrent(viewDC, viewRC);
  glEnable(GL_DEPTH_TEST);
  aspect = static_cast<double>(ViewPanel->Width) / ViewPanel->Height;
  const float lAmb[] = {0.3, 0.3, 0, 1};
  glLightfv(GL_LIGHT0, GL_AMBIENT, lAmb);
  glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 1);
  SetView();
//  glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 90);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
}
//---------------------------------------------------------------------------
void __fastcall TSettingsForm::ViewPanelMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  oldX = X;
  oldY = Y;
}
//---------------------------------------------------------------------------
void __fastcall TSettingsForm::ViewPanelMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
  if (Shift.Contains(ssLeft))
  {
    angle += (X - oldX) / 100.0;
    height += (Y - oldY) / 100.0;
    if (height < 0.0) height = 0.0;
    else if (height > 5) height = 5;
    SetView();
    oldX = X;
    oldY = Y;
    RedrawPicture();
  }
}
//---------------------------------------------------------------------------
void __fastcall TSettingsForm::TimerTimer(TObject *Sender)
{
  int i;
  double d_O;
  TaktCount++;
  RedrawPicture();
  Epsilon = M_g * sqrt(dlength * dlength + dthickness * dthickness)
    * MyCos(Domins[CurFirst].Angle + atan_cnv)
    / (2 * I_Moment);
  Domins[CurFirst].Omega = Domins[CurFirst].Omega + Epsilon * Delta_T;
  d_O = FindDeltaOmega();

  Domins[CurFirst].Omega = Domins[CurFirst].Omega + d_O;
  Caption = FloatToStr(Domins[CurFirst].Omega);
  Domins[CurFirst].Angle = Domins[CurFirst].Angle - Domins[CurFirst].Omega * Delta_T;
  if (Domins[CurFirst].Angle < 0)
  {
    Domins[CurFirst].Omega = 0;
    Domins[CurFirst].Angle = 0;
    Timer->Enabled = false;
    AnsiString s;
    s.printf("Takts: %d; seconds: %.2lf", TaktCount, TaktCount * Delta_T);
    lblInfo->Caption = s;
  }
  if (CurFirst != Dom_Count - 1)
  {
    Domins[CurFirst + 1].Angle = GetBeta(Domins[CurFirst].Angle, false);
    if (Domins[CurFirst + 1].Angle < 0)
      Domins[CurFirst + 1].Angle = 90;
    if (Domins[CurFirst + 1].Angle < 90 - atan_cnv)
    {
      Domins[CurFirst + 1].Omega = FindFirstOmega();
      CurFirst++;
    }
    else
    {
      d_O = FindDeltaOmega();
      Domins[CurFirst].Omega = Domins[CurFirst].Omega - d_O;
    }
  }

  if (CurFirst != 0)
    for (i = CurFirst; i >= 1; i--)
    {
      Domins[i - 1].Angle = GetAlpha(Domins[i].Angle, false);
      if (Domins[i - 1].Angle < 0)
        Domins[i - 1].Angle = 90;
    }

}
//------------------------------------------------------------------------------
void __fastcall TSettingsForm::Button2Click(TObject *Sender)
{
  int i;
  TaktCount = 0;
  dlength = Str2Float(leLength->Text);
  dwidth = Str2Float(leWidth->Text);
  dthickness = Str2Float(leThickness->Text);
  step = Str2Float(leStep->Text);
  Dom_Count = StrToInt(leDomCount->Text);
  Tollerance = Str2Float(leTollerance->Text);
  Delta_T = Str2Float(leDelta_T->Text);
  Timer->Interval = StrToInt(leInterval->Text) / 2;
  I_Moment = (sqr(dlength) + sqr(dthickness)) / 3;
  atan_cnv = atan(dthickness / dlength) * 180 / M_PI;
  StartTime = Now();
  CurFirst = 0;
  Omega = 0;
  Epsilon = 0;
  Domins[0].Angle = 90 - atan_cnv - 4.5;
  Domins[0].Omega = 0;
  for (i = 1; i < Dom_Count; i++)
  {
    Domins[i].Angle = 90;
    Domins[i].Omega = 0;
  }
  Timer->Enabled = step < dlength;
}
//------------------------------------------------------------------------------
void __fastcall TSettingsForm::ApplicationEvents1Message(tagMSG &Msg, bool &Handled)
{
  if (((Msg.message == WM_KEYDOWN) && (Msg.wParam == VK_F1)))
    Timer->Enabled = !Timer->Enabled;
}
//------------------------------------------------------------------------------
void __fastcall TSettingsForm::FormDestroy(TObject *Sender)
{
  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(viewRC);
  ReleaseDC(ViewPanel->Handle, viewDC);
}
//---------------------------------------------------------------------------

void __fastcall TSettingsForm::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  const double dH = 0.1, dA = M_PI / 20;
  switch (Key)
  {
		case 'W':
		if (height < 7)
		{
			height += dH;
			SetView();
		}
		break;
		case 'S':
		if (height > 0)
		{
			height -= dH;
			SetView();
		}
		break;
		case 'D':
		angle -= dA;
		SetView();
		break;
		case 'A':
		angle += dA;
		SetView();
		break;
		default:
		return;
	}
	Key = 0;
}


