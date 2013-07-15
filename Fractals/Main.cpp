//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "Fractals.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
TFloat PLeft = 0.00408, PWidth = 0.00002, PTop = 0.84282, PHeight
 = PWidth, BailOut = 3.0;
int colCoeff;
void __fastcall TForm1::bntMandelClick(TObject *Sender)
{
  FormCreate(NULL);
  BailOut = StrToFloatDef(edtBailOut->Text, 16);
  Image1->Picture->Graphic = NULL;
  DrawFractal(Image1->Canvas->Handle, Mandelbrot,
    MPLeft, MPTop, MPWidth, MPWidth, 0xD0, 16, colCoeff);
  Image1->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
  colCoeff = StrToIntDef(edtColCoeff->Text, 0x3FFF);
  PLeft = StrToFloatDef(edtPLeft->Text, PLeft);
  PTop = StrToFloatDef(edtPTop->Text, PTop);
  PWidth = StrToFloatDef(edtPWidth->Text, PWidth);
  PHeight = StrToFloatDef(edtPHeight->Text, PHeight);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::btnJuliaClick(TObject *Sender)
{
  FormCreate(NULL);
  DrawFractal(Image1->Canvas->Handle, Julia,
    PLeft, PTop, PWidth, PWidth, 40, 16, colCoeff);
  Image1->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
  Timer1->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::bntNewtonClick(TObject *Sender)
{
  FormCreate(NULL);
  Image1->Picture->Graphic = NULL;
  DrawFractal(Image1->Canvas->Handle, Newton,
    NPLeft, NPTop, NPWidth, NPWidth,
    30, 0.7, colCoeff);
  Image1->Refresh();
}
//---------------------------------------------------------------------------

