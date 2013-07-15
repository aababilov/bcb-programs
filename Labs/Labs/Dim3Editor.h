//---------------------------------------------------------------------------


#ifndef Dim3EditorH
#define Dim3EditorH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TDim3Frame : public TFrame
{
__published:
  TScrollBox *MatrixScroll;
  TImage *MatrixView;
  TLabeledEdit *edtLayer;
  TUpDown *udLayer;
  TLabeledEdit *edtM;
  TUpDown *udM;
  TButton *btnOpen;
  TButton *btnSave;
  TButton *btnSpec;
  void __fastcall udMClick(TObject *Sender, TUDBtnType Button);
  void __fastcall udLayerClick(TObject *Sender, TUDBtnType Button);
  void __fastcall btnOpenClick(TObject *Sender);
  void __fastcall btnSaveClick(TObject *Sender);
private:                              
public:
  __fastcall TDim3Frame(TComponent* Owner);
  void __fastcall LoadFromFile(const AnsiString FileName);
  void __fastcall SaveToFile(const AnsiString FileName);
  void __fastcall RepaintMatrix(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TDim3Frame *Dim3Frame;
//---------------------------------------------------------------------------
#endif
