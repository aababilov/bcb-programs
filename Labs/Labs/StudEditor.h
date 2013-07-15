//---------------------------------------------------------------------------

#ifndef StudEditorH
#define StudEditorH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TStudEditorForm : public TForm
{
__published:	// IDE-managed Components
  TLabel *lblFavSubject;
  TLabel *lblDateBirth;
  TLabeledEdit *edtTestBook;
  TLabeledEdit *edtSection;
  TLabeledEdit *edtResidence;
  TLabeledEdit *edtPlaceBirth;
  TLabeledEdit *edtGrant;
  TLabeledEdit *edtFullName;
  TLabeledEdit *edtForLang;
  TDateTimePicker *dateBirth;
  TComboBox *cbxFavSubject;
  TButton *btnOK;
  TButton *btnCancel;
  void __fastcall FormShow(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
  __fastcall TStudEditorForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TStudEditorForm *StudEditorForm;
//---------------------------------------------------------------------------
#endif
