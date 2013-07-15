//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#include "UView.h"
#include <mmsystem.h>
TStand *Stand;
float Step_X = 2, Step_Y = 0;
bool PausePlay = true;
//---------------------------------------------------------------------------
__fastcall TStand::TStand(TComponent* Owner)
        : TForm(Owner)
{
  PlaySound("System Start",0, SND_ASYNC);
}
//---------------------------------------------------------------------------
void __fastcall TStand::sbtnPauseClick(TObject *Sender)
{
  if (PausePlay)
  {
    Go->Enabled = false;
    if (Step_X > 3) Step_X = 2;
    if (-Step_X > 3) Step_X = -2;
    if (Step_Y > 3) Step_Y = 2;
    if (-Step_Y > 3) Step_Y = -2;
    sbtnPause->Glyph->LoadFromFile("Play.bmp");
  }
  else
  {
    Go->Enabled = true;
    sbtnPause->Glyph->LoadFromFile("Pause.bmp");
    PlaySound("System Start",0, SND_ASYNC);
  }
  PausePlay = !PausePlay;
}
//---------------------------------------------------------------------------
void __fastcall TStand::TurnLeftClick(TObject *Sender)
{
  if (Step_X)
  {
    Step_Y = -Step_X;
    Step_X = 0;
    if (Step_Y > 0)
      View->CarView->Picture->LoadFromFile("CarDown.bmp");
    else
      View->CarView->Picture->LoadFromFile("CarUp.bmp");
  }
  else
  {
    Step_X = Step_Y;
    Step_Y = 0;
    if (Step_X > 0)
      View->CarView->Picture->LoadFromFile("CarRight.bmp");
    else
      View->CarView->Picture->LoadFromFile("CarLeft.bmp");
  }
}
//---------------------------------------------------------------------------
void __fastcall TStand::TurnRightClick(TObject *Sender)
{
  if (Step_X)
  {
    Step_Y = Step_X;
    Step_X = 0;
    if (Step_Y > 0)
      View->CarView->Picture->LoadFromFile("CarDown.bmp");
    else
      View->CarView->Picture->LoadFromFile("CarUp.bmp");
  }
  else
  {
    Step_X = -Step_Y;
    Step_Y = 0;
    if (Step_X > 0)
      View->CarView->Picture->LoadFromFile("CarRight.bmp");
    else
      View->CarView->Picture->LoadFromFile("CarLeft.bmp");
  }
}
//---------------------------------------------------------------------------
void __fastcall TStand::GoTimer(TObject *Sender)
{
  View->CarView->Top+= Step_Y;
  View->CarView->Left+= Step_X;
  int x =(View->CarView->Left + View->CarView->Width) *
    View->RoadView->Picture->Bitmap->Width /
    View->ClientWidth,
      y =(View->CarView->Top + View->CarView->Height) *
    View->RoadView->Picture->Bitmap->Height /
    View->ClientHeight;
  if (
    View->RoadView->Picture->Bitmap->Canvas->Pixels[x][y] == 65280)
  {
    Go->Enabled = false;
    ShowMessage("It is not possible!");
    Step_X = -Step_X;
    Step_Y = -Step_Y;
    Go->Enabled = true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TStand::SlowerClick(TObject *Sender)
{
  if (Step_X > 3) Step_X -= 2;
  if (-Step_X > 3) Step_X += 2;
  if (Step_Y > 3) Step_Y -= 2;
  if (-Step_Y > 3) Step_Y += 2;
}
//---------------------------------------------------------------------------

void __fastcall TStand::QuickerClick(TObject *Sender)
{
  if (Step_X > 0) Step_X += 2;
  if (Step_X < 0) Step_X -= 2;
  if (Step_Y > 0) Step_Y += 2;
  if (Step_Y < 0) Step_Y -= 2;
}
//---------------------------------------------------------------------------


void __fastcall TStand::TurnBackClick(TObject *Sender)
{
  Step_X = -Step_X;
  Step_Y = -Step_Y;
}
//---------------------------------------------------------------------------

