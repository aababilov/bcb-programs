//---------------------------------------------------------------------------

#ifndef MainGameH
#define MainGameH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TAdjGameForm : public TForm
{
__published:
  TImage *Field;
  TImage *CrdWhite;
  TPanel *plLeadCard;
  TImage *CrdBlack;
  void __fastcall ProcessMove(TObject *Sender, TShiftState Shift, int X,
    int Y);
  void __fastcall FormShow(TObject *Sender);
  void __fastcall ProcessLead(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
  void __fastcall FormDestroy(TObject *Sender);
private:
  TStringList *roots, *suffixes;
  TCanvas *FieldCanvas;
  void __fastcall NewGame(void);
  void __fastcall PaintCell(int x, int y, char state);
  void __fastcall PaintTopCard(int Team);
  void __fastcall EndGame(void);
public:
  __fastcall TAdjGameForm(TComponent* Owner);
protected:
};
//---------------------------------------------------------------------------
extern PACKAGE TAdjGameForm *AdjGameForm;
//---------------------------------------------------------------------------
#endif
