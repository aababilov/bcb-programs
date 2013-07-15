//---------------------------------------------------------------------------


#ifndef IntervalEditorH
#define IntervalEditorH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TIntervalFrame : public TFrame
{
__published:	// IDE-managed Components
  TGroupBox *TheGroupBox;
  TEdit *edtTo;
  TEdit *edtFrom;
  TUpDown *udwFrom;
  TUpDown *udwTo;
  void __fastcall udwFromClick(TObject *Sender, TUDBtnType Button);
private:	// User declarations
public:		// User declarations
  __fastcall TIntervalFrame(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TIntervalFrame *IntervalFrame;
//---------------------------------------------------------------------------
#endif
