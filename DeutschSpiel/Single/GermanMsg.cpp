//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "GermanMsg.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMsgForm *MsgForm;
//---------------------------------------------------------------------------
__fastcall TMsgForm::TMsgForm(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TMsgForm::ShowMsg(TGermanMsg Msg)
{
  switch (Msg)
  {
    case gmAdjExists:
      Caption = "Верно!";
      lblText->Caption = "Это прилагательное существует";
      Img->Picture->Icon->Handle = LoadIconA(HInstance, "MERRY");
      MessageBeep(MB_ICONASTERISK);
      break;
    case gmAdjNotExist:
      Caption = "Неверно!";
      lblText->Caption = "Такого прилагательного не существует";
      Img->Picture->Icon->Handle = LoadIconA(HInstance, "SAD");
      MessageBeep(MB_ICONHAND);
      break;
  }
  ShowModal();
}
//---------------------------------------------------------------------------

