//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "SrtFile.h"
#include "AddProblem.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSortEditorForm *SortEditorForm;
String problemspath;
//---------------------------------------------------------------------------
void OnDuplicate(void)
{
  Application->MessageBox("Названия не должны повторяться!",
    "Ошибка!", MB_OK | MB_ICONERROR);
}
//---------------------------------------------------------------------------
__fastcall TSortEditorForm::TSortEditorForm(TComponent* Owner)
  : TForm(Owner)
{
  problemspath = ExtractFilePath(ParamStr(0)) + "Problems";
  if (DirectoryExists(problemspath))
  {
    WIN32_FIND_DATA find_data;
    HANDLE HFind = FindFirstFile((problemspath + "\\*.srt").c_str(),
      &find_data);
    if (HFind != INVALID_HANDLE_VALUE)
    {
      do
      {
        find_data.cFileName[strlen(find_data.cFileName) - 4] = 0;
        ProblemList->Items->Add()->Caption = find_data.cFileName;
      }
      while (FindNextFile(HFind, &find_data));
      FindClose(HFind);
    }
  }
  else
    CreateDir(problemspath);
  problemspath += "\\";
  if (ProblemList->Items->Count)
    ProblemList->Selected = ProblemList->Items->Item[0];
  AddProbForm = new TAddProbForm(Application);
  ProblemList->OnKeyPress = AddProbForm->edtProbNameKeyPress;
}
//---------------------------------------------------------------------------
void __fastcall TSortEditorForm::miAddClick(TObject *Sender)
{
  if (ActiveControl == ProblemList)
  {
    if (AddProbForm->ShowModal() != mrOk) return;
    if (ProblemList->FindCaption(0, AddProbForm->edtProbName->Text,
      false, true, false))
    {
      OnDuplicate();
      return;
    }
    ProblemList->Selected = ProblemList->Items->Add();
    ProblemList->Selected->Caption = AddProbForm->edtProbName->Text;
    for (int i = 0; i < 3; i++)
      SortFile.GroupWords[i]->Clear();
    SortFile.GroupNames[0] = AddProbForm->edtGroup1->Text;
    SortFile.GroupNames[1] = AddProbForm->edtGroup2->Text;
    SortFile.GroupNames[2] = AddProbForm->edtGroup3->Text;
    for (int i = 0; i < 3; i++)
      ProblemTabs->Tabs->Strings[i] = SortFile.GroupNames[i];
    SetWordsList(NULL);
  }
  else
  {
    AnsiString word;
    if (!InputQuery("Новое слово", "Введите слово:", word)) return;
    SortFile.GroupWords[ProblemTabs->TabIndex]->Add(word);
    WordsList->Items->Add()->Caption = word;
  }
}
//---------------------------------------------------------------------------
void __fastcall TSortEditorForm::miDeleteClick(TObject *Sender)
{
  if (!static_cast<TListView*>(ActiveControl)->Selected)
    return;
  if (ActiveControl == ProblemList)
  {
    if (Application->MessageBoxA(
      ("Вы действительно хотите удалить задачу " +
       ProblemList->Selected->Caption + "?").c_str(),
      "Подтверждение удаления", MB_YESNO | MB_ICONQUESTION) == IDNO)
      return;
    ProblemList->OnSelectItem = NULL;
    DeleteFileA(problemspath + ProblemList->Selected->Caption + ".srt");
    int i = ProblemList->Selected->Index;
    ProblemList->DeleteSelected();
    ProblemList->OnSelectItem = ProblemListSelectItem;
    if (ProblemList->Items->Count == 0) return;
    if (i >= ProblemList->Items->Count) i = 0;
    ProblemList->Selected = ProblemList->Items->Item[i];
  }
  else
  {
    SortFile.GroupWords[ProblemTabs->TabIndex]->Delete
      (WordsList->Selected->Index);
    WordsList->DeleteSelected();
  }
}
//---------------------------------------------------------------------------
void __fastcall TSortEditorForm::ListsEdited(TObject *Sender,
  TListItem *Item, AnsiString &S)
{
  if (Sender == ProblemList) 
  {
    TListItem *WithSameText = ProblemList->FindCaption(0, S, false, true,
      false);
    if (WithSameText && WithSameText != Item)
    {
      S = Item->Caption;
      OnDuplicate();
      return;
    }
    DeleteFileA(problemspath + Item->Caption + ".srt");
  }
  else
    SortFile.GroupWords[ProblemTabs->TabIndex]->Strings[Item->Index] = S;
}
//---------------------------------------------------------------------------
void __fastcall TSortEditorForm::ProblemListSelectItem(TObject *Sender,
      TListItem *Item, bool Selected)
{
  if (Selected)
  {
    if (FileExists(problemspath + Item->Caption + ".srt"))
    {
      SortFile.LoadFromFile(problemspath + Item->Caption + ".srt");
      SetWordsList(NULL);
      for (int i = 0; i < 3; i++)
        ProblemTabs->Tabs->Strings[i] = SortFile.GroupNames[i];
    }
  }
  else SortFile.SaveToFile(problemspath + Item->Caption + ".srt");
}
//---------------------------------------------------------------------------
void __fastcall TSortEditorForm::SetWordsList(TObject *Sender)
{
  TStringList *sl = SortFile.GroupWords[ProblemTabs->TabIndex];
  WordsList->Clear();
  for (int i = sl->Count - 1; i >= 0; i--)
    WordsList->Items->Add()->Caption = sl->Strings[i];
}
//---------------------------------------------------------------------------
void __fastcall TSortEditorForm::miChangeGNClick(TObject *Sender)
{
  AnsiString word;
  if (!InputQuery("Новое название", "Введите название:", word)) return;
  for (int i = 0; i < 3; i++)
    if (SortFile.GroupNames[i] == word)
      if (i != ProblemTabs->TabIndex)
      {
        OnDuplicate();
        return;
      }
  SortFile.GroupNames[ProblemTabs->TabIndex] = word;
  ProblemTabs->Tabs->Strings[ProblemTabs->TabIndex] = word;
}
//---------------------------------------------------------------------------

