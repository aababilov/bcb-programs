//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Game1.h"
#include "Utils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

const TResImage ChessImgs = "CHESS";
const TCursor crHandOpen = 0x4, crHandClose = 0x5;
const int SIDE = 32;

TGame1Form *Game1Form;
bool field[8][8];
POINT White = {7, 7}, Black;
int Number = 13;
enum {CleanCell, Pawn, WRook, BRook};
//---------------------------------------------------------------------------
#define CheckOrder(a, b)  if (a > b) \
  {                                  \
    int tmp = a;                     \
    a = b;                           \
    b = tmp;                         \
  }
bool See(int x1, int y1, int x2, int y2)
{
  if (x1 == x2 && y1 == y2) return false;
  if (x1 == x2)
  {
    CheckOrder(y1, y2);
    for (int i = y1 + 1; i < y2; i++)
      if (field[x1][i]) return false;
  }
  else if (y1 == y2)
  {
    CheckOrder(x1, x2);
    for (int i = x1 + 1; i < x2; i++)
      if (field[i][y1]) return false;
  }
  else return false;
  return true;
}
//---------------------------------------------------------------------------
__fastcall TGame1Form::TGame1Form(TComponent* Owner)
  : TForm(Owner)
{
  Screen->Cursors[crHandOpen] = LoadCursorA(HInstance, "HANDOPEN");
  Screen->Cursors[crHandClose] = LoadCursorA(HInstance, "HANDCLOSE");

  randomize();
  field[0][0] = field[7][7] = true;
  for (int i = 0, r, c; i < 13; i++)
  {
    do
    {
      r = random(8);
      c = random(8);
    }
    while (field[r][c]);
    field[r][c] = true;
  }
  field[0][0] = field[7][7] = false;
}
//---------------------------------------------------------------------------
#define ProcessFound(i, j) if (!See(White.x, White.y, i, j))   \
{                                                              \
  Black.x = i; Black.y = j;                                    \
  ChessImgs.DrawSqr(FieldView->Canvas->Handle, i * SIDE,       \
    j * SIDE, BRook);                                          \
  if (field[i][j])                                             \
  {                                                            \
    lblScBlack->Caption = StrToInt(lblScBlack->Caption) + 1;   \
    field[i][j] = false;                                       \
    if (--Number == 0) FinishGame();                           \
  }                                                            \
  if (lblLead->Caption == "20") FinishGame();                  \
  return;                                                      \
}
void __fastcall TGame1Form::FieldImageMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  if (!See(White.x, White.y, X /= SIDE, Y /= SIDE)) return;
  ChessImgs.DrawSqr(FieldView->Canvas->Handle, White.x * SIDE,
    White.y * SIDE, CleanCell);
  White.x = X;
  White.y = Y;
  ChessImgs.DrawSqr(FieldView->Canvas->Handle, White.x * SIDE,
    White.y * SIDE, WRook);
  if (field[X][Y])
  {
    field[X][Y] = false;
    lblScWhite->Caption = StrToInt(lblScWhite->Caption) + 1;
    Number--;
    if (Number == 0)
    {
      FinishGame();
      return;
    }
  }
  lblLead->Caption = StrToInt(lblLead->Caption) + 1;
  double Start = Now();
  do
    Application->ProcessMessages();
  while (TimeToSecs(Start - Now()) > -0.5);
  ChessImgs.DrawSqr(FieldView->Canvas->Handle, Black.x * SIDE,
    Black.y * SIDE, CleanCell);
  if (See(White.x, White.y, Black.x, Black.y))
  {
    ChessImgs.DrawSqr(FieldView->Canvas->Handle, White.x * SIDE,
      White.y * SIDE, BRook);
    lblScWhite->Caption = "0";
    FinishGame();
    return;
  }
  int i, j, k;
  for (k = 0; k < 8; k++)
  {
    if (field[Black.x][k] && See(Black.x, Black.y, Black.x, k))
      ProcessFound(Black.x, k);
    if (field[k][Black.y] && See(Black.x, Black.y, k, Black.y))
      ProcessFound(k, Black.y);
  }
  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
      if (field[i][j])
      {
        if (See(Black.x, Black.y, i, Black.y)) ProcessFound(i, Black.y);
        if (See(Black.x, Black.y, Black.x, j)) ProcessFound(Black.x, j);
      }
  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
      if (field[i][j])
        for (k = 0; k < 8; k++)
        {
          if (See(Black.x, Black.y, i, k)) ProcessFound(i, k);
          if (See(Black.x, Black.y, k, j)) ProcessFound(k, j);
        }
}
//---------------------------------------------------------------------------
void __fastcall TGame1Form::FieldViewPaint(TObject *Sender)
{
  FieldView->Canvas->MoveTo(0, 8 * SIDE);
  FieldView->Canvas->LineTo(8 * SIDE, 8 * SIDE);
  FieldView->Canvas->LineTo(8 * SIDE, 0);
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++)
      ChessImgs.DrawSqr(FieldView->Canvas->Handle,
        i * SIDE, j * SIDE, field[i][j]);
  ChessImgs.DrawSqr(FieldView->Canvas->Handle, Black.x * SIDE,
    Black.y * SIDE, BRook);
  ChessImgs.DrawSqr(FieldView->Canvas->Handle, White.x * SIDE,
    White.y * SIDE, WRook);
}
//---------------------------------------------------------------------------
void __fastcall TGame1Form::FieldViewMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
  FieldView->Cursor = See(White.x, White.y, X / SIDE, Y / SIDE) ?
    crHandClose : crHandOpen;
}
//---------------------------------------------------------------------------
void __fastcall TGame1Form::FinishGame(void)
{
  OnClose = NULL;
  Tag = StrToInt(lblScWhite->Caption) > StrToInt(lblScBlack->Caption);
  Close();
}
//---------------------------------------------------------------------------
void __fastcall TGame1Form::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  Application->Terminate();
}
//---------------------------------------------------------------------------
