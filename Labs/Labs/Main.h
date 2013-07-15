//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <AppEvnts.hpp>
#include <ActnCtrls.hpp>
#include <ActnList.hpp>
#include <ActnMan.hpp>
#include <ActnMenus.hpp>
#include <StdActns.hpp>
#include <ToolWin.hpp>
#include <ImgList.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include <Graph2D.h>
#include "IntervalEditor.h"
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:
  TStatusBar *StatusBar;
  TImageList *ActionImages;
  TActionMainMenuBar *MainMnu;
  TActionManager *ActionMgr;
  TFileOpen *actFileOpen;
  TFileSaveAs *actFileSaveAs;
  TFileExit *actFileExit;
  TAction *actRegister;
  TAction *actUnregister;
  TAction *actAbout;

  TPageControl *pgcProblems;
  TTabSheet *tbsMatrix;
  TTabSheet *tbsStudents;
  TTabSheet *tbsMAX;
  TTabSheet *tbsSeries;
  TTabSheet *tbsPolynom;

  TStringGrid *MatrixGrid;
  TButton *btnRecalculate;
  TUpDown *udwRows;
  TButton *btnSortCols;
  TButton *btnGetList;
  TButton *btnFindS;
  TLabeledEdit *edtLayer;
  TUpDown *udwLayer;
  TLabeledEdit *edtRows;
  TLabeledEdit *edtColumns;
  TUpDown *udwColumns;
  TLabeledEdit *edtLayers;
  TUpDown *udwLayers;
  TCheckBox *chbCube;
  TGroupBox *gbDimensions;
  TGroupBox *gbFindS;
  TLabeledEdit *edtSX;
  TLabeledEdit *edtSK;
  TUpDown *udwSK;
  TLabeledEdit *edtSS;
  
  TTimer *BlinkTimer;
  TGraph2D *XYField;
  TGraph2D *MAXGraph;
  TShape *XYShape;  

  TListView *StudList;
  TButton *btnAddStudent;
  TButton *btnDeleteStudent;
  TButton *btnEditStudent;

  TGroupBox *gbTolerance;
  TEdit *edtTolerance;
  TUpDown *udwZoom;
  TLabeledEdit *edtZoom;
  TIntervalFrame *DrawInterval;
  TIntervalFrame *SolveInterval;
  TButton *btnSolve;
  TGraph2D *PolynomGraph;
  TBitBtn *btnCenter;

  TButton *btnSeriesCalculate;
  TLabeledEdit *edtSeriesX;
  TLabeledEdit *edtSeriesE;
  TLabeledEdit *edtSerSum;
  TLabeledEdit *edtNumMembers;
  TLabeledEdit *edtLastMember;
  TShape *WhiteRect;
  TLabel *lblHere;
  TLabel *lblR;

  void __fastcall actFileOpenBeforeExecute(TObject *Sender);
  void __fastcall actFileOpenOpenDialogTypeChange(TObject *Sender);  
  void __fastcall actFileOpenAccept(TObject *Sender);
  void __fastcall actFileSaveAsBeforeExecute(TObject *Sender);
  void __fastcall actFileSaveAsAccept(TObject *Sender);
  void __fastcall actAboutExecute(TObject *Sender);
  void __fastcall actRegisterExecute(TObject *Sender);
  void __fastcall actUnregisterExecute(TObject *Sender);
  void __fastcall GraphMouseMove(TObject *Sender, TShiftState Shift,
    int X, int Y);
  void __fastcall pgcProblemsChange(TObject *Sender);

  void __fastcall DimensionsChange(TObject *Sender, TUDBtnType Button);
  void __fastcall udwLayerClick(TObject *Sender, TUDBtnType Button);
  void __fastcall udwLayerChanging(TObject *Sender, bool &AllowChange);
  void __fastcall chbCubeClick(TObject *Sender);
  void __fastcall btnSortColsClick(TObject *Sender);
  void __fastcall btnGetListClick(TObject *Sender);
  void __fastcall btnRecalculateClick(TObject *Sender);
  void __fastcall btnFindSClick(TObject *Sender);

  void __fastcall btnAddStudentClick(TObject *Sender);
  void __fastcall btnDeleteStudentClick(TObject *Sender);
  void __fastcall btnEditStudentClick(TObject *Sender);
  void __fastcall StudListColumnClick(TObject *Sender,
          TListColumn *Column);
  void __fastcall StudListCompare(TObject *Sender, TListItem *Item1,
          TListItem *Item2, int Data, int &Compare);

  void __fastcall BlinkTimerTimer(TObject *Sender);
  void __fastcall XYFieldMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
  void __fastcall XYFieldRedraw(TGraph2D *Sender);
  void __fastcall MAXGraphRedraw(TGraph2D *Sender);

  void __fastcall btnSeriesCalculateClick(TObject *Sender);

  void __fastcall btnCenterClick(TObject *Sender);
  void __fastcall btnSolveClick(TObject *Sender);
  void __fastcall udwIntvZoomClick(TObject *Sender, TUDBtnType Button);
  void __fastcall PolynomGraphRedraw(TGraph2D *Sender);
  void __fastcall PolynomGraphChanged(TGraph2D *Sender);
private:
  int which;
  void __fastcall LoadFromFile(const AnsiString FileName);
  void __fastcall ShowMatrix(void);
  void __fastcall StoreMatrix(void);
  void __fastcall SetupPolynom(void);
public:
  __fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
