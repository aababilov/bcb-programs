//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SrtFile.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
TSortFile SortFile;
//---------------------------------------------------------------------------
TSortFile::TSortFile(void)
{
  ms = new TMemoryStream;
  for (int i = 0; i < 3; i++)
    GroupWords[i] = new TStringList;
}
//---------------------------------------------------------------------------
TSortFile::~TSortFile(void)
{
  for (int i = 0; i < 3; i++)
    delete GroupWords[i];
  delete ms;
}
//---------------------------------------------------------------------------
void TSortFile::LoadFromFile(const AnsiString FileName)
{
  ms->Clear();
  ms->LoadFromFile(FileName);
  char *ptr = static_cast<char*>(ms->Memory);
  for (int i = ms->Size - 1; i >= 0; i--)
    ptr[i] = ~ptr[i];
  for (int i = 0; i < 3; i++)
  {
    GroupNames[i] = ptr;
    GroupWords[i]->Text = GroupNames[i];
    ptr += GroupNames[i].Length() + 1;
    GroupNames[i] = ptr;
    ptr += GroupNames[i].Length() + 1;
  }
}
//---------------------------------------------------------------------------
void TSortFile::SaveToFile(const AnsiString FileName)
{
  ms->Clear();
  AnsiString s;
  for (int i = 0; i < 3; i++)
  {
    s = GroupWords[i]->Text;
    ms->WriteBuffer(s.c_str(), s.Length() + 1);
    ms->WriteBuffer(GroupNames[i].c_str(), GroupNames[i].Length() + 1);
  }
  char *ptr = static_cast<char*>(ms->Memory);
  for (int i = ms->Size - 1; i >= 0; i--)
    ptr[i] = ~ptr[i];
  try
  {
    ms->SaveToFile(FileName);
  }
  catch(...)
  {
    Application->MessageBox(("Невозможно сохранение в файл "
      + FileName).c_str(), "Ошибка!",  MB_ICONERROR);
  }
}
//---------------------------------------------------------------------------
