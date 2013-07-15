//---------------------------------------------------------------------------

#ifndef Game2H
#define Game2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TGame2Form : public TForm
{
__published:
  TSpeedButton *btn1;
  TSpeedButton *btn4;
  TSpeedButton *btn3;
  TSpeedButton *btn2;
  TPanel *plGamer;
  TPaintBox *pbGamer;
  TPanel *plComp;
  TPaintBox *pbComp;
  TPanel *plButtons;
  TPanel *plRules;
  TLabel *lblTitle;
  TLabel *lblRules1;
  TLabel *lblRules2;
  TLabel *lblGamer;
  TLabel *lblComp;
  TPanel *plRest;
  TPaintBox *pbRest;
  TLabel *lblHeap;
  void __fastcall btnClick(TObject *Sender);
  void __fastcall pbRestPaint(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:
public:
  __fastcall TGame2Form(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGame2Form *Game2Form;
//---------------------------------------------------------------------------
#endif
