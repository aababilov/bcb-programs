//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainGame.h"
#include "GermanMsg.h"
#include "NewGameDlg.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TAdjGameForm *AdjGameForm;
namespace
{
  const TCursor crHand = 1;
  const int dist = 4;
  char buf[1024];
  enum { csWhite, csBlack, csGray };
  int len, curr, score[2], topind[2], w, h, TextHeight;
  char words[6][6], states[6][6], cards[2][18];
  const char *LEADHINTS[] = { "Ход белых", "Ход чёрных" };
}
//---------------------------------------------------------------------------
/*char * __fastcall German(unsigned Code)
{
  LoadStringA(HInstance, Code, buf, sizeof buf);
  return buf;
} */
//---------------------------------------------------------------------------
__fastcall TAdjGameForm::TAdjGameForm(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TAdjGameForm::FormShow(TObject *Sender)
{
  randomize();
  Screen->Cursors[crHand] = LoadCursorA(HInstance, "HAND");
  TTextMetric tm;
  GetTextMetrics(Canvas->Handle, &tm);
  TextHeight = tm.tmHeight + tm.tmInternalLeading;
  BoundsRect = Screen->WorkAreaRect;
  w = ClientWidth / 6;
  h = ClientHeight / 7;
  Field->Height = h * 6;
  FieldCanvas = Field->Canvas;
  FieldCanvas->Brush->Color = clBtnFace;
  FieldCanvas->Pen->Color = clBtnFace;
  FieldCanvas->Rectangle(FieldCanvas->ClipRect);
  FieldCanvas->Font->Assign(Font);

  plLeadCard->SetBounds(dist * 2, Field->BoundsRect.Bottom, Width - dist * 4,
    h);
  CrdWhite->SetBounds(dist * 2, dist * 2, w - dist * 4, h / 2 - dist * 2);
  CrdWhite->Canvas->Brush->Color = clBtnFace;
  CrdWhite->Canvas->Pen->Color = clBtnFace;
  CrdWhite->Canvas->Rectangle(CrdWhite->Canvas->ClipRect);
  CrdWhite->Canvas->Font->Assign(Font);
  CrdWhite->Canvas->Brush->Color = clWhite;
  CrdWhite->Canvas->Font->Color = clBlack;
  CrdBlack->BoundsRect = CrdWhite->BoundsRect;
  CrdBlack->Left = plLeadCard->Width - CrdBlack->Width - dist * 2;
  CrdBlack->Canvas->Brush->Color = clBtnFace;
  CrdBlack->Canvas->Pen->Color = clBtnFace;
  CrdBlack->Canvas->Rectangle(CrdBlack->Canvas->ClipRect);
  CrdBlack->Canvas->Font->Assign(Font);
  CrdBlack->Canvas->Brush->Color = clBlack;
  CrdBlack->Canvas->Font->Color = clWhite;

  roots = new TStringList;
  suffixes = new TStringList;
  TMemoryStream *dat = new TMemoryStream;
  AnsiString DatFile = ExtractFilePath(ParamStr(0)) + "game.dat";
  if (!FileExists(DatFile)) Application->Terminate();
  dat->LoadFromFile(DatFile);
  for (register char *i = static_cast<char *>(dat->Memory) +
    dat->Size - 1; i >= static_cast<char *>(dat->Memory); i--)
    *i = ~ *i;
  dat->Position = 16;
  dat->Read(&len, sizeof len);
  if (len)
  {
    dat->Read(buf, len);
    buf[len] = 0;
    roots->SetText(buf);
  }
  dat->Read(&len, sizeof len);
  if (len)
  {
    dat->Read(buf, len);
    buf[len] = 0;
    suffixes->SetText(buf);
  }
  delete dat;
  NewGame();
}
//---------------------------------------------------------------------------
void __fastcall TAdjGameForm::NewGame(void)
{
  int x, y;
  curr = csWhite;
  memset(states, csGray, sizeof states);
  memset(cards, 6, sizeof cards);
  memset(topind, 0, sizeof topind);
  memset(words, 36, sizeof words);
  for (register int i = 0; i < 36; i++)
  {
    do
    {
      x = random(6);
      y = random(6);
    }
    while (words[x][y] != 36);
    words[x][y] = i;
  }
  int pos;
  for (int c = 0; c < 2; c++)
    for (int i = 0; i < 6; i++)
      for (int k = 0; k < 3; k++)
      {
        do
          pos = random(18);
        while (cards[c][pos] != 6);
        cards[c][pos] = i;
      }
  TRect r;
  FieldCanvas->Pen->Color = clBtnFace;
  FieldCanvas->Brush->Color = clBtnFace;
  Rectangle(FieldCanvas->Handle, 0, 0, ClientWidth, h * 6);
  FieldCanvas->Pen->Color = clBlack;
  for (register int x = 0; x < 6; x++)
    for (register int y = 0; y < 6; y++)
    {
      FieldCanvas->Brush->Color = clSilver;
      Rectangle(FieldCanvas->Handle, x * w + dist, y * h + dist,
        x * w + w - dist, y * h + h - dist);
      r = Rect(x * w, y * h + 8, x * w + w, y * h + h);
      DrawTextA(FieldCanvas->Handle, roots->Strings[words[x][y]].c_str(),
        roots->Strings[words[x][y]].Length(), &r, DT_CENTER);
      FieldCanvas->Brush->Color = clGray;
      RoundRect(FieldCanvas->Handle, x * w + dist * 2, y * h + h / 2,
        x * w + w - dist * 2, y * h + h - dist * 2, w / 4, h / 4);
    }
  Field->Invalidate();
  PaintTopCard(csWhite);
  PaintTopCard(csBlack);
  plLeadCard->Caption = LEADHINTS[0];
}
//---------------------------------------------------------------------------
#define CHECKCURR if (curr > 2) score[team] += curr - 2
#define CHECKSTATE if (states[x][y] == team) curr++; \
        else                                         \
        {                                            \
          CHECKCURR;                                 \
          curr = 0;                                  \
        }
void __fastcall TAdjGameForm::EndGame(void)
{
  int x, y, st_x, st_y, curr, i;
  for (int team = 0; team < 2; team++)
  {
    score[team] = 0;
    for(int y = 0; y < 6; y++)     //horz
    {
      curr = 0;
      for (x = 0; x < 6; x++) CHECKSTATE;
      CHECKCURR;
    }
    for(int x = 0; x < 6; x++)    //vert
    {
      curr = 0;
      for (y = 0; y < 6; y++) CHECKSTATE;
      CHECKCURR;
    }
    st_x = 0;  //diag up
    st_y = 1;
    for (i = 0; i < 8; i++)
    {
      if (st_y <= 4) st_y++; else st_x++;
      x = st_x;
      y = st_y;
      curr = 0;
      do
      {
        CHECKSTATE;
        x++;
        y--;
      }
      while (x < 6 && y >= 0);
      CHECKCURR;
    }       
    st_x = 0;  //diag down
    st_y = 4;
    for (i = 0; i < 8; i++)
    {
      if (st_y >= 1) st_y--; else st_x++;
      x = st_x;
      y = st_y;
      curr = 0;
      do
      {
        CHECKSTATE;
        x++;
        y++;
      }
      while (x < 6 && y < 6);
      CHECKCURR;
    }
  }
  if (score[csWhite] == score[csBlack])
    EndGameForm->lblWon->Caption = "Ничья";
  else if (score[csWhite] > score[csBlack])
         EndGameForm->lblWon->Caption = "Белые выиграли";
       else EndGameForm->lblWon->Caption = "Чёрные выиграли";
  EndGameForm->Caption = "Счёт " + IntToStr(score[csWhite]) + ":" +
    IntToStr(score[csBlack]);
  if (EndGameForm->ShowModal() == mrNo) Application->Terminate();
  else NewGame();
}
//---------------------------------------------------------------------------
void __fastcall TAdjGameForm::ProcessMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
  if (states[X / w][Y / h] == csGray &&
    FieldCanvas->Pixels[X][Y] != ColorToRGB(clBtnFace))
  {
    Field->OnMouseUp = &ProcessLead;
    Field->Cursor = crHand;
  }
  else
  {
    Field->OnMouseUp = NULL;
    Field->Cursor = crDefault;
  }
}
//---------------------------------------------------------------------------
void __fastcall TAdjGameForm::ProcessLead(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  X /= w;
  Y /= h;
  if (words[X][Y] / 6 == cards[curr][topind[curr]])
  {
    MsgForm->ShowMsg(gmAdjExists);
    PaintCell(X, Y, curr);
    topind[curr]++;
    PaintTopCard(curr);
    if (topind[curr] == 18)
    {
      EndGame();
      return;
    }
  }
  else MsgForm->ShowMsg(gmAdjNotExist);
  curr = !curr;
  plLeadCard->Caption = LEADHINTS[curr];
}
//---------------------------------------------------------------------------
void __fastcall TAdjGameForm::PaintCell(int x, int y, char state)
{
  FieldCanvas->Brush->Style = bsSolid;
  FieldCanvas->Brush->Color = state == csBlack ? clBlack : clWhite;
  RECT drawRect = {x * w + dist, y * h + dist,
    x * w + w - dist, y * h + h - dist };
  Rectangle(FieldCanvas->Handle, drawRect.left, drawRect.top,
    drawRect.right, drawRect.bottom);
  TRect r = Rect(x * w, y * h + dist * 2, x * w + w, y * h + h);
  FieldCanvas->Font->Color = state == csBlack ? clWhite : clBlack;
  DrawTextA(FieldCanvas->Handle, roots->Strings[words[x][y]].c_str(),
    roots->Strings[words[x][y]].Length(), &r, DT_CENTER);
  r.top += TextHeight;
  DrawTextA(FieldCanvas->Handle, suffixes->Strings[words[x][y] / 6].c_str(),
    suffixes->Strings[words[x][y] / 6].Length(), &r, DT_CENTER);
  Canvas->CopyRect(drawRect, FieldCanvas, drawRect);
  states[x][y] = state;
}
//---------------------------------------------------------------------------
void __fastcall TAdjGameForm::PaintTopCard(int Team)
{
  TImage *Img = Team == csWhite ? CrdWhite : CrdBlack;
  RoundRect(Img->Canvas->Handle, 0, 0, w - dist * 4, h / 2 - dist * 2,
    w / 4, h / 4);
  RECT r = { 0, dist, w - dist * 4, h / 2 - dist * 3};
  DrawTextA(Img->Canvas->Handle,
    suffixes->Strings[cards[Team][topind[Team]]].c_str(),
    suffixes->Strings[cards[Team][topind[Team]]].Length(), &r, DT_CENTER);
  Img->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TAdjGameForm::FormDestroy(TObject *Sender)
{
  delete roots;
  delete suffixes;
}
//---------------------------------------------------------------------------

