//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <stdio.h>
#include "Dim3Editor.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDim3Frame *Dim3Frame;
//---------------------------------------------------------------------------
__fastcall TDim3Frame::TDim3Frame(TComponent* Owner)
  : TFrame(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TDim3Frame::RepaintMatrix(void)
{
  int w, h, k = udLayer->Position - 1;
  MatrixView->Width = w = TW * m + 1;
  MatrixView->Height = h = TH * m + 1;
  MatrixView->Picture->Graphic = NULL;
  TCanvas *cnv = MatrixView->Canvas;
  HDC dc = cnv->Handle;
  cnv->Font->Size = 14;
  cnv->Pen->Width = 2;
  for (int i = 0; i <= m; i++)
  {
    cnv->MoveTo(0, i * TH);
    cnv->LineTo(w, i * TH);
  }
  for (int j = 0; j <= m; j++)
  {
    cnv->MoveTo(j * TW, 0);
    cnv->LineTo(j * TW, h);
  }
  AnsiString text;
  TRect r;
  for (int i = 0; i < m; i++)
    for (int j = 0; j < m; j++)
    {
      text = a[i][j][k];
      r = TRect(j * TW, i * TH, (j + 1) * TW, (i + 1) * TH);
      DrawText(dc, text.c_str(), text.Length(), &r,
        DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }
}
//---------------------------------------------------------------------------
void __fastcall TDim3Frame::LoadFromFile(const AnsiString FileName)
{
  FILE *in_file = fopen(FileName.c_str(), "rt");
  if (in_file == NULL)
  {
    ShowError("File cannot be opened!");
    return;
  }
  fscanf(in_file, "%i", &m);
  if (m > MAX_DIM)
  {
    ShowError(("An array dimension cannot be more than " +
      IntToStr(MAX_DIM)).c_str());
    m = udM->Position;
    goto ready;
  }
  udM->Position = m;
  udLayer->Position = 1;
  for (int k = 0; k < m; k++)
    for (int i = 0; i < m; i++)
      for (int j = 0; j < m; j++)
        fscanf(in_file, "%i", &a[i][j][k]);
  RepaintMatrix();
  ready:
  fclose(in_file);
}
//---------------------------------------------------------------------------
void __fastcall TDim3Frame::SaveToFile(const AnsiString FileName)
{
  FILE *out_file = fopen(FileName.c_str(), "w+t");
  if (out_file == NULL)
  {
    ShowError("File cannot be created!");
    return;
  }
  fprintf(out_file, "%i\n", m);
  for (int k = 0; k < m; k++, fprintf(out_file, "\n"))
    for (int i = 0; i < m; i++, fprintf(out_file, "\n"))
      for (int j = 0; j < n; j++)
        fprintf(out_file, "%i ", a[i][j][k]);
  fclose(out_file);
}
//---------------------------------------------------------------------------
void __fastcall TDim3Frame::udMClick(TObject *Sender, TUDBtnType Button)
{
  m = udM->Position;
  udLayer->Position = 1;
  udLayer->Max = m;
  RepaintMatrix();
}
//---------------------------------------------------------------------------
void __fastcall TDim3Frame::udLayerClick(TObject *Sender,
      TUDBtnType Button)
{
  RepaintMatrix();
}
//---------------------------------------------------------------------------
void __fastcall TDim3Frame::btnOpenClick(TObject *Sender)
{
  MainForm->OpenDlg->DefaultExt = ".av3";
  MainForm->OpenDlg->Filter =
    "Three-dimensional matrixes (*.av3)|*.av3|All files (*.*)|*.*";
  if (MainForm->OpenDlg->Execute())
    LoadFromFile(MainForm->OpenDlg->FileName);
}
//---------------------------------------------------------------------------
void __fastcall TDim3Frame::btnSaveClick(TObject *Sender)
{
  MainForm->SaveDlg->DefaultExt = ".av3";
  MainForm->SaveDlg->Filter =
    "Three-dimensional matrixes (*.av3)|*.av3|All files (*.*)|*.*";
  if (MainForm->SaveDlg->Execute())
    SaveToFile(MainForm->SaveDlg->FileName);
}
//---------------------------------------------------------------------------

