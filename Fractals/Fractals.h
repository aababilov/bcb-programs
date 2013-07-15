//---------------------------------------------------------------------------

#ifndef FractalsH
#define FractalsH
//---------------------------------------------------------------------------
#include <windows.h>
//---------------------------------------------------------------------------
typedef double TFloat;

const TFloat
 MPLeft = -0.135,
 MPWidth = 0.0007,
 MPTop = 0.85,

 NPLeft = -0.2,
 NPWidth = 0.4,
 NPTop = 0.2,
 NBail = 0.7;

typedef void (*SetupBitsProc)(COLORREF *bits,
  int CWidth, int CHeight, int MaxIter, int colCoeff,
  TFloat px, TFloat py, TFloat stepx, TFloat stepy, TFloat BailOut);

void DrawFractal(HDC DC, SetupBitsProc FracProc,
  TFloat PLeft, TFloat PTop, TFloat PWidth, TFloat PHeight,
  int MaxIter, TFloat BailOut, int colCoeff);
    
void Mandelbrot(COLORREF *bits,
  int CWidth, int CHeight, int MaxIter, int colCoeff,
  TFloat startx, TFloat starty, TFloat stepx, TFloat stepy, TFloat BailOut);

void Julia(COLORREF *bits,
  int CWidth, int CHeight, int MaxIter, int colCoeff,
  TFloat startx, TFloat starty, TFloat stepx, TFloat stepy, TFloat BailOut);

void Newton(COLORREF *bits,
  int CWidth, int CHeight, int MaxIter, int colCoeff,
  TFloat startx, TFloat starty, TFloat stepx, TFloat stepy, TFloat BailOut);

#endif
