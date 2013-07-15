//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <AppEvnts.hpp>
//---------------------------------------------------------------------------
#define WM_PHTIMER WM_USER + 1
//---------------------------------------------------------------------------
class TPhysonForm : public TForm
{
__published:
  TPanel *ThePanel;
  TImage *PanelImage;
  TPanel *plLeft;
  TPanel *plRight;
  TImage *FormImage;
  TPanel *plTime;
  void __fastcall SmplKeyDown(TObject *Sender, WORD &Key,
    TShiftState Shift);
  void __fastcall MazeKeyDown(TObject *Sender, WORD &Key,
    TShiftState Shift);
  void __fastcall MazeMouseMove(TObject *Sender, TShiftState Shift,
    int X, int Y);
  void __fastcall MazeClick(TObject *Sender);
  void __fastcall FormImageDragOver(TObject *Sender, TObject *Source,
    int X, int Y, TDragState State, bool &Accept);
  void __fastcall FormImageDragDrop(TObject *Sender, TObject *Source,
    int X, int Y);
  void __fastcall PanelImageMouseDown1(TObject *Sender,
    TMouseButton Button, TShiftState Shift, int X, int Y);
  void __fastcall PanelImageMouseDown3(TObject *Sender, TMouseButton Button,
    TShiftState Shift, int X, int Y);
  void __fastcall PanelImageMouseMove(TObject *Sender, TShiftState Shift,
    int X, int Y);
  void __fastcall ThePanelMouseDown(TObject *Sender, TMouseButton Button,
    TShiftState Shift, int X, int Y);
  void __fastcall ApplicationMessage(tagMSG &Msg, bool &Handled);
private:
  void __fastcall NextLevel(void);
  void __fastcall PrepareLevel1(void);
  void __fastcall PrepareLevel2(void);
  void __fastcall PrepareLevel3(void);
  void __fastcall DrawSmile(bool Happy);
  void __fastcall FinishGame(void);
  void __fastcall PrepareSuperGame(void);
  void __fastcall Repainting(void);
protected:
#pragma option push -w-inl
  BEGIN_MESSAGE_MAP
    VCL_MESSAGE_HANDLER(WM_PHTIMER, TMessage, OnPhTimer)
  END_MESSAGE_MAP(TForm)
#pragma option pop
  void __fastcall OnPhTimer(TMessage Msg);
  void __fastcall OnLevel1(void);
  void __fastcall OnLevel3(void);
  void __fastcall SetTimeCaption(void);
public:
  __fastcall TPhysonForm(TComponent* Owner);
  __fastcall ~TPhysonForm(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TPhysonForm *PhysonForm;
//---------------------------------------------------------------------------
#endif
