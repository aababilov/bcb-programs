//---------------------------------------------------------------------------

#ifndef AddProblemH
#define AddProblemH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TAddProbForm : public TForm
{
__published:
  TLabeledEdit *edtProbName;
  TLabeledEdit *edtGroup1;
  TLabeledEdit *edtGroup2;
  TLabeledEdit *edtGroup3;
  TBitBtn *btnOK;
  TBitBtn *btnCancel;
  void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
  void __fastcall edtProbNameKeyPress(TObject *Sender, char &Key);
  void __fastcall FormShow(TObject *Sender);
private:
public:		
  __fastcall TAddProbForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAddProbForm *AddProbForm;
//---------------------------------------------------------------------------
#endif
