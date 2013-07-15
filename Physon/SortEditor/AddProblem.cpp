//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AddProblem.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAddProbForm *AddProbForm;
//---------------------------------------------------------------------------
__fastcall TAddProbForm::TAddProbForm(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TAddProbForm::FormCloseQuery(TObject *Sender,
      bool &CanClose)
{
  if (ModalResult == mrOk)
  {
    CanClose = edtProbName->Text.Length() && edtGroup1->Text.Length() &&
      edtGroup2->Text.Length() && edtGroup3->Text.Length();
    if (!CanClose)
      Application->MessageBoxA("Заполните все поля!", "Ошибка!",
        MB_OK | MB_ICONERROR);
  }
}
//---------------------------------------------------------------------------
void __fastcall TAddProbForm::edtProbNameKeyPress(TObject *Sender,
      char &Key)
{
  static AnsiString NotUsed = "/\\:*?\"<>|";
  if (NotUsed.Pos(Key))
  {
    Application->MessageBoxA(("Имя задачи не должно содержать символов " +
      NotUsed).c_str(), "Недопустимый символ", MB_OK | MB_ICONERROR);
    Key = 0;
  }
}
//---------------------------------------------------------------------------
void __fastcall TAddProbForm::FormShow(TObject *Sender)
{
  edtProbName->Text = "";
  edtGroup1->Text = "";
  edtGroup2->Text = "";
  edtGroup3->Text = "";
}
//---------------------------------------------------------------------------

