//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "View.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TViewForm *ViewForm;
//---------------------------------------------------------------------------
__fastcall TViewForm::TViewForm(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------

