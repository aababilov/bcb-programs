//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <AppEvnts.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
  TPanel *ViewPanel;
  TTimer *Timer1;
  TButton *Start;
	TButton *btnChangeTimer;
  void __fastcall FormDestroy(TObject *Sender);
  void __fastcall ViewPanelMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
  void __fastcall ViewPanelMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
  void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
  void __fastcall Timer1Timer(TObject *Sender);
  void __fastcall StartClick(TObject *Sender);
	void __fastcall btnChangeTimerClick(TObject *Sender);
	void __fastcall Repainting(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
