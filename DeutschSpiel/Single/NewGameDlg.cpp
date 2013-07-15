//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "NewGameDlg.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TEndGameForm *EndGameForm;
//---------------------------------------------------------------------------
__fastcall TEndGameForm::TEndGameForm(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TEndGameForm::FormShow(TObject *Sender)
{
  MessageBeep(MB_ICONASTERISK);
}
//---------------------------------------------------------------------------

