//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TSortEditorForm : public TForm
{
__published:	
  TListView *ProblemList;
  TSplitter *Splttr;
  TTabControl *ProblemTabs;
  TListView *WordsList;
  TPopupMenu *ListsMenu;
  TMenuItem *miAdd;
  TMenuItem *miDelete;
  TPopupMenu *GroupsMenu;
  TMenuItem *miChangeGN;
  void __fastcall miAddClick(TObject *Sender);
  void __fastcall miDeleteClick(TObject *Sender);
  void __fastcall ListsEdited(TObject *Sender, TListItem *Item,
          AnsiString &S);
  void __fastcall ProblemListSelectItem(TObject *Sender, TListItem *Item,
          bool Selected);
  void __fastcall SetWordsList(TObject *Sender);
  void __fastcall miChangeGNClick(TObject *Sender);
private:
public:
  __fastcall TSortEditorForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSortEditorForm *SortEditorForm;
//---------------------------------------------------------------------------
#endif
