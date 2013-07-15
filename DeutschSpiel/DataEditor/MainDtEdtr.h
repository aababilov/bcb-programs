//---------------------------------------------------------------------------

#ifndef MainDtEdtrH
#define MainDtEdtrH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TDataEditorForm : public TForm
{
__published:	// IDE-managed Components
  TPageControl *EditorPages;
  TTabSheet *pgPassword;
  TLabeledEdit *edtCurrPassword;
  TLabeledEdit *edtNewPassword;
  TButton *btnSetPassword;
  TTabSheet *pgWords;
  TGroupBox *gbSuffixes;
  TGroupBox *gbRoots;
  TTabSheet *pgHosts;
  TListView *lwSuffixes;
  TListView *lwRoots;
  TListView *lwHosts;
  TPopupMenu *HostMenu;
  TMenuItem *miAdd;
  TMenuItem *miDelete;
  void __fastcall FormDestroy(TObject *Sender);
  void __fastcall btnSetPasswordClick(TObject *Sender);
  void __fastcall DeleteHost(TObject *Sender);
  void __fastcall AddHost(TObject *Sender);
  void __fastcall lwSuffixesSelectItem(TObject *Sender, TListItem *Item,
          bool Selected);
  void __fastcall lwRootsEdited(TObject *Sender, TListItem *Item,
          AnsiString &S);
private:
  AnsiString DatFile, Password;
  TStringList *roots, *suffixes, *hosts;
  TMemoryStream *dat;
  int suffix;
public:
  __fastcall TDataEditorForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDataEditorForm *DataEditorForm;
//---------------------------------------------------------------------------
#endif
