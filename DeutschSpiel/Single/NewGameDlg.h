//---------------------------------------------------------------------------

#ifndef NewGameDlgH
#define NewGameDlgH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TEndGameForm : public TForm
{
__published:	// IDE-managed Component
  TBitBtn *BitBtn1;
  TBitBtn *BitBtn2;
  TLabel *lblNewGame;
  TLabel *lblWon;
  void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall TEndGameForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TEndGameForm *EndGameForm;
//---------------------------------------------------------------------------
#endif
