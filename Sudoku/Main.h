//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <Buttons.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TSudokuForm : public TForm
{
__published:	// IDE-managed Components
  TOpenDialog *OpenDlg;
  TMainMenu *MainMnu;
  TMenuItem *miFile;
  TMenuItem *miOpen;
  TMenuItem *miSave;
  TMenuItem *miWork;
  TSaveDialog *SaveDlg;
  TMenuItem *miGo;
  TMenuItem *miByStep;
  TMenuItem *miExtgo;
  void __fastcall FormPaint(TObject *Sender);
  void __fastcall miOpenClick(TObject *Sender);
  void __fastcall miSaveClick(TObject *Sender);
  void __fastcall miGoClick(TObject *Sender);
  void __fastcall miExtgoClick(TObject *Sender);
        void __fastcall FormMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
private:
  void __fastcall LoadFromFile(const char *FileName);
public:	
  __fastcall TSudokuForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSudokuForm *SudokuForm;
//---------------------------------------------------------------------------
#endif
