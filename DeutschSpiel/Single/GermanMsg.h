//---------------------------------------------------------------------------

#ifndef GermanMsgH
#define GermanMsgH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
enum TGermanMsg { gmAdjExists, gmAdjNotExist};
//---------------------------------------------------------------------------
class TMsgForm : public TForm
{
__published:	// IDE-managed Components
  TLabel *lblText;
  TImage *Img;
  TBitBtn *BitBtn1;
private:	// User declarations
public:		// User declarations
  __fastcall TMsgForm(TComponent* Owner);
  void __fastcall ShowMsg(TGermanMsg Msg);
};
//---------------------------------------------------------------------------
extern PACKAGE TMsgForm *MsgForm;
//---------------------------------------------------------------------------
#endif
