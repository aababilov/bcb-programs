//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
  TImage *Image1;
  TButton *bntNewton;
  TButton *bntMandel;
  TLabeledEdit *edtColCoeff;
  TLabeledEdit *edtMaxIter;
  TLabeledEdit *edtBailOut;
  TLabeledEdit *edtPLeft;
  TLabeledEdit *edtPWidth;
  TLabeledEdit *edtPTop;
  TLabeledEdit *edtPHeight;
  TButton *btnJulia;
  TTimer *Timer1;
  TButton *btnRecolor;
  void __fastcall bntMandelClick(TObject *Sender);
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall btnJuliaClick(TObject *Sender);
  void __fastcall Timer1Timer(TObject *Sender);
  void __fastcall bntNewtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
