//---------------------------------------------------------------------------

#include <vcl.h>
#include <cmath>
#include <gl/glu.h>
#pragma hdrstop

#include "main.h"

using namespace std;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
HANDLE viewDC, viewRC;
GLdouble aspect, angle, height = 4.1;
//---------------------------------------------------------------------------
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
const int N_SIDES = 8;
typedef float side_arr[N_SIDES][2];
side_arr gen =
 {{0.2, 0.2},
 {0.1, 0.5},
 {-0.1, 0.6},
 {-0.3, 0.3},
 {-0.3, -0.2},
 {-0.1, -0.4},
 {0.2, -0.4},
 {0.3, -0.2}},
 sides[2];
float t = 0, centerx, centerz;
const double side = 3, iceH = 0.7;
int iceAngle, sTop = 1,  sBtm = 0;
bool rotating = false;
void RedrawPicture(void)
{
	glClearColor(0.4, 0.7, 1, 1);
	glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0, 0.4, 0);
		glScalef(0.7, 1, 0.7);

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1, 1, 1, 0.1);

	float waterH = (1 - t) * 0.1;
	glBegin(GL_QUADS);
		glVertex3f(side, waterH, side);
		glVertex3f(side, waterH, -side);
		glVertex3f(-side, waterH, -side);
		glVertex3f(-side, waterH, side);
	glEnd();

#define ICETOP glVertex3f( \
	sides[sTop][i][0], 0.5 * iceH * (1 - t), sides[sTop][i][1])
#define ICEBOTTOM glVertex3f( \
	sides[sBtm][i][0], -0.5 * iceH * (1 - t), sides[sBtm][i][1])
	glRotatef(iceAngle, 1, 0, 0);

 /*	glColor4f(1, 0, 0, 1);
	glBegin(GL_LINES);
		glVertex3f(100, 0, 0);
		glVertex3f(-100, 0, 0);
		glVertex3f(0, 100, 0);
		glVertex3f(0, -100, 0);
		glVertex3f(0, 0, 100);
		glVertex3f(0, 0, -100);
	glEnd();
 */
	glColor4f(1, 1, 1, 0.5);
	glBegin(GL_POLYGON);
		for (int i = 0; i < N_SIDES; i++)
			ICETOP;
	glEnd();
	glColor4f(0.6, 0.9, 1, 0.7);
	glBegin(GL_POLYGON);
		for (int i = 0; i < N_SIDES; i++)
			ICEBOTTOM;
	glEnd();
	glColor4f(0.6, 0.8, 0.9, 0.5);
	glBegin(GL_QUAD_STRIP);
		for (int i = 0; i < N_SIDES; i++)
		{
			ICETOP;
			ICEBOTTOM;
		}
		int i = 0;
		ICETOP;
		ICEBOTTOM;
	glEnd();

	glDisable(GL_BLEND);
	SwapBuffers(viewDC);
}
//---------------------------------------------------------------------------
void SetView(void)
{
	glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0, aspect, 0.1, 15.0);
		gluLookAt(cos(angle) * 2, height - 4.09, sin(angle) * 1.5,
			0, 0.4, 0, 0, 1, 0);
	RedrawPicture();
}
//------------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
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
//  glEnable(GL_DEPTH_TEST);
	aspect = static_cast<double>(ViewPanel->Width) / ViewPanel->Height;
	glClearColor(0.2, 0.2, 1, 1);
	SetView();

	memcpy(sides[0], gen, sizeof gen);
	memcpy(sides[1], gen, sizeof gen);
	for (int i = 0; i < N_SIDES; i++) {
		centerx += gen[i][0];
		centerz += gen[i][1];
	}
	centerx /= N_SIDES;
	centerz /= N_SIDES;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormDestroy(TObject *Sender)
{
  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(viewRC);
  ReleaseDC(ViewPanel->Handle, viewDC);
}
//---------------------------------------------------------------------------
int oldX, oldY;
void __fastcall TForm1::ViewPanelMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  oldX = X;
  oldY = Y;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ViewPanelMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
  if (Shift.Contains(ssLeft))
  {
    angle += (X - oldX) / 100.0;
    height += (Y - oldY) / 100.0;
    if (height < 0.0) height = 0.0;
    else if (height > 7) height = 7;
    SetView();
    oldX = X;
    oldY = Y;
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
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
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
	if (iceAngle % 180)
	{
		iceAngle += 5;
		if (!iceAngle % 180) {
			sTop = !sTop;
			sBtm = !sBtm;
		}
	}
	else
	{
		const float topSpeed = 0.005, btmSpeed = 0.007;
		for (int i = 0; i < N_SIDES; i++) {
			sides[sTop][i][0] += (centerx - sides[sTop][i][0]) * topSpeed;
			sides[sTop][i][1] += (centerz - sides[sTop][i][1]) * topSpeed;
			sides[sBtm][i][0] += (centerx - sides[sBtm][i][0]) * btmSpeed;
			sides[sBtm][i][1] += (centerz - sides[sBtm][i][1]) * btmSpeed;
		}
		if (random(100) == 0)
			iceAngle += 5;
		t += 5e-3;
		if (t > 0.9) Timer1->Enabled = false;
	}
	RedrawPicture();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::StartClick(TObject *Sender)
{
	memcpy(sides[0], gen, sizeof gen);
	memcpy(sides[1], gen, sizeof gen);

  Timer1->Enabled = true;
	t = 0;
	iceAngle = 0;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::btnChangeTimerClick(TObject *Sender)
{
	Timer1->Enabled = !Timer1->Enabled;
	btnChangeTimer->Caption = Timer1->Enabled ?
		"Pause" : "Continue";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Repainting(TObject *Sender)
{
	aspect = static_cast<double>(ViewPanel->Width) / ViewPanel->Height;
	SetView();
}
//---------------------------------------------------------------------------
