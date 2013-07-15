//---------------------------------------------------------------------------


#pragma hdrstop

#include "Fractals.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------
void DrawFractal(HDC DC, SetupBitsProc FracProc,
  TFloat PLeft, TFloat PTop, TFloat PWidth, TFloat PHeight,
  int MaxIter, TFloat BailOut, int colCoeff)
{
  long x, y;
  int count, CWidth, CHeight;
  RECT Rect;
  GetClipBox(DC, &Rect);
  CWidth = (Rect.right - Rect.left) & 0xFFFFFFF8;
  CHeight = (Rect.bottom - Rect.top) & 0xFFFFFFF8;
  COLORREF *bits = new COLORREF[CWidth * CHeight];

  (*FracProc)(bits, CWidth, CHeight, MaxIter, colCoeff, PLeft, PTop,
    PWidth / CWidth, PHeight / CHeight, BailOut);

  HDC bmpdc = CreateCompatibleDC(DC);
  HBITMAP bmp = CreateBitmap(CWidth, CHeight, 1, 32, bits);
  SelectObject(bmpdc, bmp);
  BitBlt(DC, 0, 0, CWidth, CHeight, bmpdc,
    0,0, SRCCOPY);
  SelectObject(bmpdc, NULL);
  DeleteObject(bmp);
  DeleteDC(bmpdc);
  delete bits;
}
//---------------------------------------------------------------------------
void Mandelbrot(COLORREF *bits,
  int CWidth, int CHeight, int MaxIter, int colCoeff,
  TFloat startx, TFloat starty, TFloat stepx, TFloat stepy, TFloat BailOut)
{
  long x, y, count;
  TFloat px, py;
  double Worr, Wori, Wor2r, BackUpi, BackUpr;
  for (y = 0, py = starty; y < CHeight; y++, py -= stepy)
    for (x = 0, px = startx; x < CWidth; x++, px += stepx)
    {
      Worr = BackUpr = px;
      Wori = BackUpi = py;
      for (count = 0; count <= MaxIter; count++)
      {
        Wor2r = Worr;
        Worr = Worr * Worr - Wori * Wori + BackUpr;
        Wori = 2 * Wor2r * Wori + BackUpi;
        if (Worr * Worr + Wori * Wori > BailOut)
        {
          bits[y * CWidth + x] = colCoeff * count;
          goto ExCycle;
        }
      }
      bits[y * CWidth + x] = 0;
      ExCycle:
    }
}
//---------------------------------------------------------------------------
void Julia(COLORREF *bits,
  int CWidth, int CHeight, int MaxIter, int colCoeff,
  TFloat startx, TFloat starty, TFloat stepx, TFloat stepy, TFloat BailOut)
{
  double Worr, Wori, Wor2r, BackUpi, BackUpr;
  long x, y;
  int count;
  TFloat px, py;

  for (y = 0, py = starty; y < CHeight; y++, py -= stepy)
    for (x = 0, px = startx; x < CWidth; x++, px += stepx)
    {
      BackUpr = 0.36;
      BackUpi = 0.36;
      Worr = px;
      Wori = py;
      for (count = 0; count <= MaxIter; count++)
      {
        Wor2r = Worr;
        Worr = Worr * Worr - Wori * Wori + BackUpr;
        Wori = 2 * Wor2r * Wori + BackUpi;
        if (Worr * Worr + Wori * Wori > BailOut)
        {
          bits[y * CWidth + x] = colCoeff * count;
          goto ExCycle;
        }
      }
      bits[y * CWidth + x] = 0;
      ExCycle:
    }
}
//---------------------------------------------------------------------------
void Newton(COLORREF *bits,
  int CWidth, int CHeight, int MaxIter, int colCoeff,
  TFloat startx, TFloat starty, TFloat stepx, TFloat stepy, TFloat BailOut)
{
  double zr, zi, z3r, z3i, z4min1r, z4min1i, z3norm;
  long x, y;
  int count;
  TFloat px, py;
  for (y = 0, py = starty; y < CHeight; y++, py -= stepy)
    for (x = 0, px = startx; x < CWidth; x++, px += stepx)
    {
      zr = px;
      zi = py;
      for (count = 0; count <= MaxIter; count++)
      {
        z3r = zr * (zr * zr - 3 * zi * zi);
        z3i = zi * (3 * zr * zr - zi * zi);
        z4min1r = z3r * zr - z3i * zi - 1;
        z4min1i = z3i * zr + z3r * zi;

        z3norm = z3r * z3r + z3i * z3i;
        if (!z3norm) break;
        zr = (3 * zr + z3r / z3norm) / 4;
        zr = (3 * zr - z3i / z3norm) / 4;
        if (z4min1r * z4min1r + z4min1i * z4min1i < BailOut)
        {
          bits[y * CWidth + x] = colCoeff * count;
          goto ExCycle;
        }

      }
      bits[y * CWidth + x] = 0;
      ExCycle:
    }
}
//---------------------------------------------------------------------------
