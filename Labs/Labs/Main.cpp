//---------------------------------------------------------------------------
#define VCL_IOSTREAM
#include <vcl.h>
#include <Registry.hpp>

#define _FM_USE_FASTMATH
#include <math.h>
#include <fstream>
#include <string>
#include <algorithm>

#pragma hdrstop

#include "Main.h"
#include "NonZeros.h"
#include "StudEditor.h"
#include "AboutBAR.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "IntervalEditor"
#pragma link "Graph2D"
#pragma resource "*.dfm"
const int MAX_DIM = 50;

TMainForm *MainForm;
TCanvas *cnv;
int a[MAX_DIM][MAX_DIM][MAX_DIM], k, rows, cols, lyrs;
//---------------------------------------------------------------------------
#define SET_RCL                 \
  rows = udwRows->Position;     \
  cols = udwColumns->Position;  \
  lyrs = udwLayers->Position
//---------------------------------------------------------------------------
void ShowError(char *Msg)
{
  Application->MessageBox(Msg, "Error!", MB_ICONERROR | MB_OK);
}
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
  : TForm(Owner)
{
  SET_RCL;
  ShowMatrix();
  udwIntvZoomClick(NULL, btNext);
  StudEditorForm = new TStudEditorForm(Application);
  if (__argc > 1)
    MainForm->LoadFromFile(__argv[1]);
  XYFieldMouseUp(NULL, mbLeft, TShiftState(), 0, 0);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::actFileOpenBeforeExecute(TObject *Sender)
{
  actFileOpen->Dialog->FilterIndex = pgcProblems->ActivePageIndex < 2 ?
    pgcProblems->ActivePageIndex + 1 : 3;
  actFileOpen->Dialog->DefaultExt = pgcProblems->ActivePageIndex ?
    ".avl" : ".avm";
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::actFileOpenOpenDialogTypeChange(TObject *Sender)
{
  actFileOpen->Dialog->DefaultExt = actFileOpen->Dialog->FilterIndex != 1 ?
    ".avl" : ".avm";
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::actFileOpenAccept(TObject *Sender)
{
  LoadFromFile(actFileOpen->Dialog->FileName);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::actFileSaveAsBeforeExecute(TObject *Sender)
{
  switch (pgcProblems->ActivePageIndex)
  {
    case 0:
    actFileSaveAs->Dialog->DefaultExt = ".avm";
    actFileSaveAs->Dialog->Filter =
      "Matrixes (*.avm)|*.avm|All files (*.*)|*.*";
    break;
    case 1:
    actFileSaveAs->Dialog->DefaultExt = ".avs";
    actFileSaveAs->Dialog->Filter =
      "Student lists (*.avl)|*.avl|All files (*.*)|*.*";
    break;
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::actFileSaveAsAccept(TObject *Sender)
{
  std::ofstream out_file(actFileSaveAs->Dialog->FileName.c_str());
  actFileSaveAs->Dialog->FileName = "";
  if (!out_file)
  {
    ShowError("File cannot be created!");
    return;
  }
  if (pgcProblems->ActivePage == tbsMatrix)
  {
    StoreMatrix();
    out_file << rows << " " << cols << " " << lyrs << "\n";
    for (int k = 0; k < lyrs; k++, out_file << "\n")
      for (int i = 0; i < rows; i++, out_file << "\n")
        for (int j = 0; j < cols; j++)
          out_file << a[i][j][k] << " ";
  }
  else
    for (int to = StudList->Items->Count, j = 0; j < to; j++)
    {
      TListItem *Item = StudList->Items->Item[j];
      out_file << Item->Caption.c_str() << "\n";
      for (int i = 0; i < 8; i++)
        out_file << Item->SubItems->Strings[i] << "\n";
      out_file << "\n";
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::actRegisterExecute(TObject *Sender)
{
  try
  {
    TRegistry *reg = new TRegistry;
    reg->RootKey = HKEY_CLASSES_ROOT;
    reg->OpenKey(".avm", true);
    reg->WriteString("", "AVBARMatrix");
    reg->CloseKey();
    reg->OpenKey("AVBARMatrix", true);
    reg->WriteString("", "AV BAR Matrix");
    reg->OpenKey("DefaultIcon", true);
    reg->WriteString("", Application->ExeName + ",0");
    reg->CloseKey();
    reg->OpenKey("AVBARMatrix\\Shell\\Open\\command", true);
    reg->WriteString("", Application->ExeName + " %1");
    reg->CloseKey();

    reg->OpenKey(".avl", true);
    reg->WriteString("", "AVBARStudList");
    reg->CloseKey();
    reg->OpenKey("AVBARStudList", true);
    reg->WriteString("", "AV BAR Students list");
    reg->OpenKey("DefaultIcon", true);
    reg->WriteString("", Application->ExeName + ",0");
    reg->CloseKey();
    reg->OpenKey("AVBARStudList\\Shell\\Open\\command", true);
    reg->WriteString("", Application->ExeName + " %1");
    reg->CloseKey();

    delete reg;
    Application->MessageBoxA("File types have been successfully registered!",
      "Register", MB_OK | MB_ICONINFORMATION);
  }
  catch (Exception &)
  {
    ShowError("An unrecognized error during registering!");
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::actUnregisterExecute(TObject *Sender)
{
  try
  {
    TRegistry *reg = new TRegistry;
    reg->RootKey = HKEY_CLASSES_ROOT;
    reg->DeleteKey(".avm");
    reg->DeleteKey("AVBARMatrix");
    reg->DeleteKey(".avl");
    reg->DeleteKey("AVBARStudList");
    delete reg;
    Application->MessageBoxA("File types have been successfully unregistered!",
      "Register", MB_OK | MB_ICONINFORMATION);
  }
  catch (Exception &)
  {
    ShowError("An unrecognized error during registering!");
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::actAboutExecute(TObject *Sender)
{
  AboutForm->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::pgcProblemsChange(TObject *Sender)
{
  actFileSaveAs->Enabled = pgcProblems->ActivePageIndex < 2;
  StatusBar->SimpleText = "";
  BlinkTimer->Enabled = pgcProblems->ActivePage == tbsMAX;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::LoadFromFile(const AnsiString FileName)
{
  std::ifstream in_file(FileName.c_str());
  if (!in_file)
  {
    ShowError("File cannot be opened!");
    return;
  }
  switch (FileName[FileName.Length()])
  {
    case 'm':
    case 'M':
    in_file >> rows >> cols >> lyrs;
    if (rows > MAX_DIM || cols > MAX_DIM || lyrs > MAX_DIM)
    {
      ShowError(("An array dimension cannot be more than " +
        IntToStr(MAX_DIM)).c_str());
      return;
    }
    pgcProblems->ActivePage = tbsMatrix;
    udwRows->Position = rows;
    udwColumns->Position = cols;
    udwLayers->Position = lyrs;
    udwLayer->Position = 1;
    for (int k = 0; k < lyrs; k++)
      for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
          in_file >> a[i][j][k];
    ShowMatrix();
    break;
    case 'l':
    case 'L':
    pgcProblems->ActivePage = tbsStudents;
    std::string tmps;
    StudList->Items->BeginUpdate();
    StudList->Clear();
    for (;;)
    {
      using std::getline;
      getline(in_file, tmps);
      if (!(tmps.length() && in_file)) goto ready;
      TListItem *Item = StudList->Items->Add();
      Item->Caption = tmps.c_str();
      for (int i = 0; i < 8; i++)
      {
        getline(in_file, tmps);
        Item->SubItems->Add(tmps.c_str());
      }
      while (in_file.get() != '\n')
        if (!in_file) goto ready;
    }
    ready:
    StudList->Items->EndUpdate();
    break;
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::GraphMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
  POINT ip = {X, Y};
  TLDPoint ldp;
  static_cast<TGraph2D*>(Sender)->Pixel2Coord(&ip, &ldp, 1);
  AnsiString s;
  s.printf("Mouse at (%.2Lf, %.2Lf)", ldp.x, ldp.y);
  StatusBar->SimpleText = s;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TMainForm::DimensionsChange(TObject *Sender, TUDBtnType Button)
{
  StoreMatrix();
  if (chbCube->Checked)
  {
    udwRows->Position = static_cast<TUpDown *>(Sender)->Position;
    udwColumns->Position = static_cast<TUpDown *>(Sender)->Position;
    udwLayers->Position = static_cast<TUpDown *>(Sender)->Position;
  }
  if (udwLayers->Position < udwLayer->Position)
    udwLayer->Position = 1;
  SET_RCL;
  udwLayer->Max = lyrs;
  udwSK->Max = cols;
  edtSK->Text = udwSK->Position;
  ShowMatrix();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::udwLayerClick(TObject *Sender,
      TUDBtnType Button)
{
  ShowMatrix();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::udwLayerChanging(TObject *Sender,
      bool &AllowChange)
{
  StoreMatrix();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::StoreMatrix(void)
{
  int k = udwLayer->Position - 1;
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++)
      a[i][j][k] = StrToIntDef(MatrixGrid->Cells[j + 1][i + 1], a[i][j][k]);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ShowMatrix(void)
{
  MatrixGrid->RowCount = rows + 1;
  MatrixGrid->ColCount = cols + 1;
  int k = udwLayer->Position - 1;
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++)
      MatrixGrid->Cells[j + 1][i + 1] = a[i][j][k];
  for (int i = 1; i <= rows; i++)
    MatrixGrid->Cells[0][i] = i;
  for (int j = 1; j <= cols; j++)
    MatrixGrid->Cells[j][0] = j;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::chbCubeClick(TObject *Sender)
{
  if (chbCube->Checked)
  {
    udwColumns->Position = udwRows->Position;
    udwLayers->Position = udwRows->Position;
    if (udwLayers->Position < udwLayer->Position)
      udwLayer->Position = 1;
    StoreMatrix();
    ShowMatrix();
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::btnSortColsClick(TObject *Sender)
{
  static int tmp[MAX_DIM];
  StoreMatrix();
  for (int j = 0; j < cols; j++)
    for (int k = 0; k < lyrs; k++)
    {
      for (int i = 0; i < rows; i++)
        tmp[i] = a[i][j][k];
      std::sort(tmp, tmp + rows);
      for (int i = 0; i < rows; i++)
        a[i][j][k] = tmp[i];
    }
  ShowMatrix();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::btnGetListClick(TObject *Sender)
{
  int cnt = 0;
  StoreMatrix();
  ShowMatrix();
  NonZerosForm->lbxNonZeros->Clear();
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++)
      for (int k = 0; k < lyrs; k++)
        if (a[i][j][k])
        {
          NonZerosForm->lbxNonZeros->Items->Add("a[" +
            IntToStr(i + 1) + "][" +
            IntToStr(j + 1) + "][" +
            IntToStr(k + 1) + "] = " +
            IntToStr(a[i][j][k]));
          cnt++;
        }
  NonZerosForm->Caption = "Count of nonzero elements: " + IntToStr(cnt);
  NonZerosForm->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::btnRecalculateClick(TObject *Sender)
{
  StoreMatrix();
  int k = udwLayer->Position - 1;
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++)
      if (a[i][j][k])
        a[i][j][k] += (i + 1) * (j + 1);
  ShowMatrix();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::btnFindSClick(TObject *Sender)
{
  StoreMatrix();
  long double x = StrToFloatDef(edtSX->Text, 0), s = 0;
  int j = udwSK->Position - 1, k = udwLayer->Position - 1;
  for (int i = MainForm->udwRows->Position - 1; i >= 0; i--)
    s = s * x + a[i][j][k];
  edtSX->Text = FloatToStr(x);
  edtSS->Text = FloatToStr(s);
  ShowMatrix();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#define ITEM_FROM_PST                                                 \
  Item->Caption = StudEditorForm->edtFullName->Text;                  \
  Item->SubItems->Add(DateToStr(StudEditorForm->dateBirth->Date));    \
  Item->SubItems->Add(StudEditorForm->edtResidence->Text);            \
  Item->SubItems->Add(StudEditorForm->edtPlaceBirth->Text);           \
  Item->SubItems->Add(StudEditorForm->edtTestBook->Text);             \
  Item->SubItems->Add(StudEditorForm->cbxFavSubject->Text);           \
  Item->SubItems->Add(StudEditorForm->edtSection->Text);              \
  Item->SubItems->Add(StudEditorForm->edtForLang->Text);              \
  Item->SubItems->Add(StudEditorForm->edtGrant->Text)
void __fastcall TMainForm::btnAddStudentClick(TObject *Sender)
{
  StudEditorForm->edtFullName->Text = "";
  StudEditorForm->dateBirth->Date = AnsiString("01.01.1989");
  StudEditorForm->edtResidence->Text = "";
  StudEditorForm->edtPlaceBirth->Text = "";
  StudEditorForm->edtTestBook->Text = "";
  StudEditorForm->cbxFavSubject->ItemIndex = 0;
  StudEditorForm->edtSection->Text = "";
  StudEditorForm->edtForLang->Text = "";
  StudEditorForm->edtGrant->Text = 0;

  StudEditorForm->Caption = "New student";
  if (StudEditorForm->ShowModal() == mrOk)
  {
    TListItem *Item = StudList->Items->Add();
    ITEM_FROM_PST;
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::btnDeleteStudentClick(TObject *Sender)
{
  if (StudList->Selected &&
    Application->MessageBox("Are you sure?", "Deleting",
    MB_YESNO | MB_ICONQUESTION) == IDYES)
    StudList->DeleteSelected();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::btnEditStudentClick(TObject *Sender)
{
  TListItem *Item = StudList->Selected;
  if (!Item) return;
  TStrings *s = Item->SubItems;
  StudEditorForm->edtFullName->Text = Item->Caption;
  StudEditorForm->dateBirth->Date = StrToDate(s->Strings[0]);
  StudEditorForm->edtResidence->Text = s->Strings[1];
  StudEditorForm->edtPlaceBirth->Text = s->Strings[2];
  StudEditorForm->edtTestBook->Text = s->Strings[3];
  StudEditorForm->cbxFavSubject->ItemIndex =
    StudEditorForm->cbxFavSubject->Items->IndexOf(s->Strings[4]);
  StudEditorForm->edtSection->Text = s->Strings[5];
  StudEditorForm->edtForLang->Text = s->Strings[6];
  StudEditorForm->edtGrant->Text = s->Strings[7];

  StudEditorForm->Caption = "Editing";
  StudEditorForm->ShowModal();
  Item->SubItems->Clear();
  ITEM_FROM_PST;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::StudListColumnClick(TObject *Sender,
      TListColumn *Column)
{
  which = Column->Index - 1;
  StudList->AlphaSort();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::StudListCompare(TObject *Sender,
      TListItem *Item1, TListItem *Item2, int Data, int &Compare)
{
  TDateTime t1, t2;
  int i1, i2;
  switch (which)
  {
    case -1:
    Compare = AnsiStrIComp(Item1->Caption.c_str(), Item2->Caption.c_str());
    break;
    case 0:
    t1 = StrToDate(Item1->SubItems->Strings[0]);
    t2 = StrToDate(Item2->SubItems->Strings[0]);
    if (t1 < t2) Compare = -1;
    else if (t1 == t2) Compare = 0;
    else Compare = 1;
    break;
    case 7:
    i1 = StrToInt(Item1->SubItems->Strings[7]);
    i2 = StrToInt(Item2->SubItems->Strings[7]);
    if (i1 < i2) Compare = -1;
    else if (i1 == i2) Compare = 0;
    else Compare = 1;
    break;
    default:
    Compare = AnsiStrIComp(Item1->SubItems->Strings[which].c_str(),
      Item2->SubItems->Strings[which].c_str());
  }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
long double x = 1, y = 1;
const long double CIRCLE_R = 37.4;
inline long double sqrl(long double __x)
{
  return __x * __x;
}
//---------------------------------------------------------------------------
#ifndef _FM_USE_FASTMATH
long double Fibonacci(int n)
{
  return n > 2 ? Fibonacci(n - 1) + Fibonacci(n - 2) : 1;
}
long double Factorial(int n)
{
  return n > 2 ? n * Factorial(n) : n;
}
long double MAX(void)
{
  if (y == 0) return 0;
  long double t = 1 + fabsl(x / y) * 2.05 - 0.001 * exp(x * x);
  return
    n < 1 || x < 0 || t == 0 || sqrtl(x * x + y * y) > CIRCLE_R ?
    0 :
    y > 0 ?
    sqrl(sinl(powl(x * sqrtl(y) + expl(x), n))) / t +
      Fibonacci(n) :
    x * y / 2 + expl(x) +
      sqrl(sinl(powl(x + sqrtl(-y) + expl(x), n))) / t +
      Factorial(n);
}
#else
long double Fibonacci(int n)
{
  long double a = 1, b = 1, t;
  for (; n > 2; n--)
  {
    t = b;
    b = a;
    a = a + t;
  }
  return a;
}
long double Factorial(long double n)
{
  long double b = 1;
  for (; n > 1; n--) b *= n;
  return b;
}
long double MAX(long double n)
{
  if (y == 0) return 0;
  long double t = 1 + fabsl(x / y) * 2.05 - 0.001 * exp(x * x);
  return
    n < 1 || n >= 13 || x < 0 || t == 0 || sqrtl(x * x + y * y) > CIRCLE_R ?
    0 :
    y > 0 ?
    sqrl(sinl(powl(x * sqrtl(y) + expl(x / 100), n))) / t +
      Fibonacci(n) :
    x * y / 2 + expl(x) +
      sqrl(sinl(powl(x + sqrtl(-y) + expl(x / 100), n))) / t +
      Factorial(n);
}
#endif
//---------------------------------------------------------------------------
void __fastcall TMainForm::BlinkTimerTimer(TObject *Sender)
{
  XYShape->Visible = !XYShape->Visible;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::XYFieldMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  POINT ip = {X, Y};
  TLDPoint ldp;
  XYField->Pixel2Coord(&ip, &ldp, 1);
  XYShape->Left = X;
  XYShape->Top = Y;
  x = ldp.x;
  y = ldp.y;
  MAXGraph->Redraw();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::XYFieldRedraw(TGraph2D *Sender)
{
  Sender->BackBrush->Style = bsSolid;
  Sender->Clear();
  TLDPoint pnts[] =
  {
    {CIRCLE_R, CIRCLE_R},
    {-CIRCLE_R, -CIRCLE_R},
    {CIRCLE_R, 0},
    {0, CIRCLE_R}
  };
  TPoint ps[4];
  cnv = Sender->Buffer->Canvas;
  cnv->Brush->Color = static_cast<TColor>(0xA0A0FF);
  cnv->Pen->Width = 1;
  Sender->Coord2Pixel(pnts, ps, 4);
  cnv->Pie(ps[0].x, ps[0].y, ps[1].x, ps[1].y,
    ps[2].x, ps[2].y, ps[3].x, ps[3].y);

  pnts[2].x = 0;
  pnts[2].y = -CIRCLE_R;
  pnts[3].x = CIRCLE_R;
  pnts[3].y = 0;
  cnv->Brush->Color = static_cast<TColor>(0xA0FFA0);
  Sender->Coord2Pixel(pnts, ps, 4);
  cnv->Pie(ps[0].x, ps[0].y, ps[1].x, ps[1].y,
    ps[2].x, ps[2].y, ps[3].x, ps[3].y);

  Sender->BackBrush->Style = bsClear;
  Sender->Clear();
  Sender->DrawTips();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::MAXGraphRedraw(TGraph2D *Sender)
{
  try
  {
    Sender->Clear();
    Sender->DrawGraph(&MAX);
    Sender->DrawTips();
  }
  catch(...)
  {
  }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TMainForm::btnSeriesCalculateClick(TObject *Sender)
{
  long double need_e = StrToFloatDef(edtSeriesE->Text, 0.05),
    x = StrToFloatDef(edtSeriesX->Text, 1), Summ = 0, prev, curr;
  int k;

  if (need_e < 0) need_e = 0.05;
  for (Summ = prev = - x * x * x / 3, k = 2; k < 500; k++)
  {
    curr = -prev * x * x * (2 * k - 1) / (k * (2 * k + 1));
    Summ += curr;
    if (fabsl(fabsl(curr) - fabsl(prev)) < need_e)
      break;
    prev = curr;
  }

  edtNumMembers->Text = IntToStr(k);
  edtSerSum->Text = FloatToStr(Summ);
  edtLastMember->Text = FloatToStr(curr);
  edtSeriesX->Text = FloatToStr(x);
  edtSeriesE->Text = FloatToStr(need_e);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
long double Funct(long double x)
{
  return 3.7*x*x*x-7.9*x*x+14.3;
}

void __fastcall TMainForm::btnCenterClick(TObject *Sender)
{
  PolynomGraph->XAxis->Center = 0;
  PolynomGraph->YAxis->Center = 0;
  PolynomGraph->Redraw();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::btnSolveClick(TObject *Sender)
{
  double ans = 0, tol = StrToFloatDef(edtTolerance->Text, 0.005),
    iLo = SolveInterval->udwFrom->Position,
    iHi = SolveInterval->udwTo->Position;
  if (Funct(iLo)*Funct(iHi) > 0)
    Application->MessageBox("There are no answers on this interval.",
      "Ready!", MB_OK | MB_ICONINFORMATION);
  else
  {
    for (;;)
    {
      if (Funct((iLo+iHi)/2) == 0)
      {
        ans = (iLo+iHi)/2;
        break;
      }
      if (Funct(iLo)*Funct((iLo+iHi)/2) > 0)
        iLo = (iLo+iHi)/2;
      else iHi = (iLo+iHi)/2;
      if (iHi - iLo < tol)
      {
        ans = (iLo+iHi)/2;
        break;
      }
    }
    Application->MessageBox(("x = " + FloatToStr(ans)).c_str(), "Ready!",
      MB_OK | MB_ICONINFORMATION);
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::udwIntvZoomClick(TObject *Sender, TUDBtnType Button)
{
  if (Sender != udwZoom)
  {
    DrawInterval->udwTo->Min = DrawInterval->udwFrom->Position + 1;
    DrawInterval->edtTo->Text = DrawInterval->udwTo->Position;
    PolynomGraph->XAxis->SetInterval(DrawInterval->udwFrom->Position,
      DrawInterval->udwTo->Position);
    PolynomGraph->YAxis->PixelsPerUnit = PolynomGraph->XAxis->PixelsPerUnit;
    udwZoom->Position = PolynomGraph->XAxis->PixelsPerUnit;
  }
  else
  {
    PolynomGraph->XAxis->PixelsPerUnit = udwZoom->Position;
    PolynomGraph->YAxis->PixelsPerUnit = udwZoom->Position;
    DrawInterval->udwFrom->Position = PolynomGraph->XAxis->Min;
    DrawInterval->udwTo->Position = PolynomGraph->XAxis->Max;
  }
  SetupPolynom();
  PolynomGraph->Redraw();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::PolynomGraphRedraw(TGraph2D *Sender)
{
  PolynomGraph->Clear();
  PolynomGraph->DrawGraph(Funct);
  PolynomGraph->DrawTips();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::PolynomGraphChanged(TGraph2D *Sender)
{
  if (PolynomGraph->XAxis->PixelsPerUnit > udwZoom->Max)
  {
    PolynomGraph->XAxis->PixelsPerUnit = udwZoom->Max;
    PolynomGraph->YAxis->PixelsPerUnit = udwZoom->Max;
  }
  else
    if (PolynomGraph->XAxis->PixelsPerUnit < udwZoom->Min)
    {
      PolynomGraph->XAxis->PixelsPerUnit = udwZoom->Min;
      PolynomGraph->YAxis->PixelsPerUnit = udwZoom->Min;
    }
  udwZoom->Position = PolynomGraph->XAxis->PixelsPerUnit;
  DrawInterval->udwFrom->Position = PolynomGraph->XAxis->Min;
  if (static_cast<int>(PolynomGraph->XAxis->Max) >
      static_cast<int>(PolynomGraph->XAxis->Min))
    DrawInterval->udwTo->Position = PolynomGraph->XAxis->Max;
  else
    DrawInterval->udwTo->Position = PolynomGraph->XAxis->Min + 1;
  SetupPolynom();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SetupPolynom(void)
{
  long double t_step = (int)(70 / PolynomGraph->XAxis->PixelsPerUnit);
  if (!t_step)
  {
    t_step = 0.5;
    PolynomGraph->Precision = 1;
  }
  else PolynomGraph->Precision = 0;
  PolynomGraph->XAxis->TipStep = t_step;
  PolynomGraph->XAxis->GridStep = t_step;
  PolynomGraph->YAxis->TipStep = t_step;
  PolynomGraph->YAxis->GridStep = t_step;
}
//---------------------------------------------------------------------------
