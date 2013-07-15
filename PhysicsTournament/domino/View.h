//---------------------------------------------------------------------------

#ifndef ViewH
#define ViewH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TViewForm : public TForm
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
  __fastcall TViewForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TViewForm *ViewForm;

//---------------------------------------------------------------------------
#endif
