//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <AppEvnts.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TSettingsForm : public TForm
{
__published:
  TTimer *Timer;
  TButton *Button2;
  TLabeledEdit *leLength;
  TLabeledEdit *leWidth;
  TLabeledEdit *leThickness;
  TLabeledEdit *leStep;
  TLabeledEdit *leDomCount;
  TLabeledEdit *leDelta_T;
  TLabeledEdit *leTollerance;
  TApplicationEvents *ApplicationEvents1;
  TLabeledEdit *leInterval;
  TPanel *ViewPanel;
  TLabel *lblInfo;
  void __fastcall TimerTimer(TObject *Sender);
  void __fastcall Button2Click(TObject *Sender);
  void __fastcall ApplicationEvents1Message(tagMSG &Msg, bool &Handled);
  void __fastcall FormDestroy(TObject *Sender);
  void __fastcall ViewPanelMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
  void __fastcall ViewPanelMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
  void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
public:		// User declarations
  __fastcall TSettingsForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSettingsForm *SettingsForm;
void SetView(void);
void RedrawPicture(void);
//---------------------------------------------------------------------------
#endif
