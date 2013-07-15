//---------------------------------------------------------------------------

#ifndef AboutBARH
#define AboutBARH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class TAboutForm : public TForm
{
__published:	// IDE-managed Components
  TLabel *lblDevelopers;
  TImage *imgSupervisor;
  TImage *imgDevelopers;
  TImage *imgSponsor;
  TLabel *lblSponsor;
  TLabel *lblSupervisor;
  TButton *btnOK;
private:	// User declarations
public:		// User declarations
  __fastcall TAboutForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAboutForm *AboutForm;
//---------------------------------------------------------------------------
#endif
