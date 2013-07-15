//---------------------------------------------------------------------------

#ifndef Game1H
#define Game1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <AppEvnts.hpp>
//---------------------------------------------------------------------------
class TGame1Form : public TForm
{
__published:
  TLabel *lblTitle;
  TLabel *lblRules1;
  TLabel *lblRules2;
  TLabel *lblRules3;
  TLabel *lblRules4;
  TPanel *plBoard;
  TPaintBox *FieldView;
  TPanel *plInfo;
  TLabel *lblCapWhite;
  TLabel *lblCapBlack;
  TLabel *lblCapLead;
  TLabel *lblScWhite;
  TLabel *lblScBlack;
  TLabel *lblLead;
  TPanel *plRules;
  void __fastcall FieldImageMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
  void __fastcall FieldViewPaint(TObject *Sender);
  void __fastcall FieldViewMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:
  void __fastcall FinishGame(void);
public:
  __fastcall TGame1Form(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGame1Form *Game1Form;
//---------------------------------------------------------------------------
#endif
