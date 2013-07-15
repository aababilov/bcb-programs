//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "IntervalEditor.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TIntervalFrame *IntervalFrame;
//---------------------------------------------------------------------------
__fastcall TIntervalFrame::TIntervalFrame(TComponent* Owner)
  : TFrame(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TIntervalFrame::udwFromClick(TObject *Sender,
      TUDBtnType Button)
{
  udwTo->Min = udwFrom->Position + 1;
  edtTo->Text = udwTo->Position;
}
//---------------------------------------------------------------------------
