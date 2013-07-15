//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "StudEditor.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TStudEditorForm *StudEditorForm;
//---------------------------------------------------------------------------
__fastcall TStudEditorForm::TStudEditorForm(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TStudEditorForm::FormShow(TObject *Sender)
{
  edtFullName->SetFocus();  
}
//---------------------------------------------------------------------------
void __fastcall TStudEditorForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  try
  {
    StrToInt(edtGrant->Text);
  }
  catch(EConvertError &)
  {
    edtGrant->Text = "0";
  }
}
//---------------------------------------------------------------------------

