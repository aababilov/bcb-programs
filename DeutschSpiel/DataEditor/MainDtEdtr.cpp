//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainDtEdtr.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDataEditorForm *DataEditorForm;
//---------------------------------------------------------------------------
__fastcall TDataEditorForm::TDataEditorForm(TComponent* Owner)
  : TForm(Owner)
{
  DatFile = ExtractFilePath(ParamStr(0)) + "game.dat";
  roots = new TStringList;
  suffixes = new TStringList;
  hosts = new TStringList;
  dat = new TMemoryStream;
  if (FileExists(DatFile))
  {
    TMemoryStream *dat = new TMemoryStream;
    dat->LoadFromFile(DatFile);
    for (register char *i = static_cast<char *>(dat->Memory) +
      dat->Size - 1; i >= static_cast<char *>(dat->Memory); i--)
      *i = ~ *i;
    char buf[400];
    dat->Read(buf, 16);
    Password = buf;
    int len;
    dat->Read(&len, sizeof len);
    if (len)
    {
      dat->Read(buf, len);
      buf[len] = 0;
      roots->SetText(buf);
      for (int i = 0; i < 6; i++)
        lwRoots->Items->Add()->Caption = roots->Strings[i];
    }
    dat->Read(&len, sizeof len);
    if (len)
    {
      dat->Read(buf, len);
      buf[len] = 0;
      suffixes->SetText(buf);
      for (int i = 0; i < 6; i++)
        lwSuffixes->Items->Add()->Caption = suffixes->Strings[i];
    }
    dat->Read(&len, sizeof len);
    if (len)
    {
      dat->Read(buf, len);
      buf[len] = 0;
      hosts->SetText(buf);
      for (int i = 0; i < hosts->Count; i++)
        lwHosts->Items->Add()->Caption = hosts->Strings[i];
    }
  }
  else
  {
    for (int i = 0; i < 36; i++) roots->Add("");
    for (int i = 0; i < 6; i++)
    {
      lwRoots->Items->Add();
      lwSuffixes->Items->Add();
    }
    Password = "D";
  }
}
//---------------------------------------------------------------------------
void __fastcall TDataEditorForm::FormDestroy(TObject *Sender)
{
  char buf[] = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
  int len;
  lstrcpy(buf, Password.c_str());
  dat->Clear();
  dat->Write(buf, 16);

  len = roots->Text.Length();
  dat->Write(&len, sizeof len);
  roots->SaveToStream(dat);

  suffixes->Clear();
  for (int i = 0; i < 6; i++)
    suffixes->Add(lwSuffixes->Items->Item[i]->Caption);
  len = suffixes->Text.Length();
  dat->Write(&len, sizeof len);
  suffixes->SaveToStream(dat);

  hosts->Clear();
  for (int i = 0; i < lwHosts->Items->Count; i++)
    hosts->Add(lwHosts->Items->Item[i]->Caption);
  len = hosts->Text.Length();
  dat->Write(&len, sizeof len);
  hosts->SaveToStream(dat);

  for (register char *i = static_cast<char *>(dat->Memory) +
    dat->Size - 1; i >= static_cast<char *>(dat->Memory); i--)
      *i = ~ *i;
  DeleteFileA(DatFile);
  dat->SaveToFile(DatFile);
  SetFileAttributesA(DatFile.c_str(), faHidden | faArchive);
  delete dat;
  delete roots;
  delete suffixes;
}
//---------------------------------------------------------------------------
void __fastcall TDataEditorForm::btnSetPasswordClick(TObject *Sender)
{
  if (edtNewPassword->Text.data() == NULL)
    Application->MessageBoxA("A password cannot be an empty string!",
    "Cannot set new password!", MB_ICONEXCLAMATION | MB_OK);
  else
    if (edtCurrPassword->Text == Password)
    {
      Password = edtNewPassword->Text;
      Application->MessageBoxA("The password was sucessfully stored!",
       "Information", MB_ICONINFORMATION | MB_OK);
    }
    else Application->MessageBoxA("You've written a wrong password!",
      "Cannot set new password!", MB_ICONERROR | MB_OK);
}
//---------------------------------------------------------------------------
void __fastcall TDataEditorForm::DeleteHost(TObject *Sender)
{
  lwHosts->DeleteSelected();
}
//---------------------------------------------------------------------------
void __fastcall TDataEditorForm::AddHost(TObject *Sender)
{
  lwHosts->Items->Add()->Caption = "0.0.0.0";
}
//---------------------------------------------------------------------------
void __fastcall TDataEditorForm::lwSuffixesSelectItem(TObject *Sender,
      TListItem *Item, bool Selected)
{
  if (Selected)
  {
    suffix = lwSuffixes->ItemIndex;
    for (int i = 0; i < 6; i++)
     lwRoots->Items->Item[i]->Caption = roots->Strings[i + suffix * 6];
  }
}
//---------------------------------------------------------------------------
void __fastcall TDataEditorForm::lwRootsEdited(TObject *Sender,
      TListItem *Item, AnsiString &S)
{
  if (S.Length() > 9) S.Delete(10, S.Length() - 9);
  roots->Strings[Item->Index + suffix * 6] = S;
}
//---------------------------------------------------------------------------




