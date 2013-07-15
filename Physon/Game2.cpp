//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Game2.h"
#include "Utils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TGame2Form *Game2Form;
int ScGamer, ScComp;
const int P_STEP = 32, E_D = 24;
//---------------------------------------------------------------------------
void ModifyPicture(TPaintBox *PntBox, int New)
{
  if (PntBox->Tag < New)
  {
    PntBox->Canvas->Brush->Color = clOlive;
    for (int i = PntBox->Tag; i < New; i++)
      PntBox->Canvas->Ellipse(i % 4 * P_STEP, i / 4 * P_STEP,
        i % 4 * P_STEP + E_D, i / 4 * P_STEP + E_D);
  }
  else
  {
    PntBox->Canvas->Brush->Color = clBtnFace;
    for (int i = New; i < PntBox->Tag; i++)
      PntBox->Canvas->FillRect(Rect(i % 4 * P_STEP, i / 4 * P_STEP,
        i % 4 * P_STEP + E_D, i / 4 * P_STEP + E_D));
  }
  PntBox->Tag = New;
}
//---------------------------------------------------------------------------
__fastcall TGame2Form::TGame2Form(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
#define CheckRest(n) if (Rest < n) btn##n->Enabled = false
void __fastcall TGame2Form::btnClick(TObject *Sender)
{
  ModifyPicture(pbGamer, ScGamer +=
    static_cast<TSpeedButton*>(Sender)->Tag);
  ModifyPicture(pbRest, 20 - ScGamer - ScComp);
  if (20 - ScGamer - ScComp == 0)
  {
    OnClose = NULL;
    Tag = 1;
    Close();
    return;
  }
  Sleep(1000);
  if (ScComp + ScGamer < 16) ScComp += random(4) + 1;
  else ScComp = 20 - ScGamer;
  int Rest = 20 - ScGamer - ScComp;
  ModifyPicture(pbRest, Rest);
  ModifyPicture(pbComp, ScComp);
  CheckRest(4);
  CheckRest(3);
  CheckRest(2);
  CheckRest(1);
  if (Rest == 0)
  {
    Sleep(1000);
    OnClose = NULL;
    Tag = 0;
    Close();
    return;
  }
}
//---------------------------------------------------------------------------
void __fastcall TGame2Form::pbRestPaint(TObject *Sender)
{
  ModifyPicture(pbRest, 20 - ScGamer - ScComp);  
}
//---------------------------------------------------------------------------
void __fastcall TGame2Form::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  Application->Terminate();
}
//---------------------------------------------------------------------------
