//---------------------------------------------------------------------------

#ifndef NonZerosH
#define NonZerosH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TNonZerosForm : public TForm
{
__published:	// IDE-managed Components
  TListBox *lbxNonZeros;
private:	// User declarations
public:		// User declarations
  __fastcall TNonZerosForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TNonZerosForm *NonZerosForm;
//---------------------------------------------------------------------------
#endif
