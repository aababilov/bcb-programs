//---------------------------------------------------------------------------

#ifndef TableEditorH
#define TableEditorH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <vector>
//---------------------------------------------------------------------------
class Ttable_editor : public TForm
{
__published:	// IDE-managed Components
        TStringGrid *tbl_grid;
        TPanel *Panel1;
        TButton *btnAdd;
        TButton *btnRemove;
        TButton *btnSave;
        TButton *btnReload;
        TButton *btnCancel;
        TStatusBar *status;
        void __fastcall btnReloadClick(TObject *Sender);
        void __fastcall tbl_gridSetEditText(TObject *Sender, int ACol,
          int ARow, const AnsiString Value);
        void __fastcall tbl_gridSetEditTextInsert(TObject *Sender, int ACol,
          int ARow, const AnsiString Value);
        void __fastcall tbl_gridSelectCell(TObject *Sender, int ACol,
          int ARow, bool &CanSelect);
        void __fastcall tbl_gridSelectCellInsert(TObject *Sender, int ACol,
          int ARow, bool &CanSelect);
        void __fastcall tbl_gridGetEditText(TObject *Sender, int ACol,
          int ARow, AnsiString &Value);
        void __fastcall btnAddClick(TObject *Sender);
        void __fastcall btnSaveClick(TObject *Sender);
        void __fastcall btnCancelClick(TObject *Sender);
        void __fastcall btnRemoveClick(TObject *Sender);
private:
        String table_name;
        String edited_val, old_val;
        int col, row, edited_row, edited_col, new_row;
        std::vector<bool> not_null;
        int set_value();
        int insert_row();
        void noninsert_mode();
        void insert_mode();
        void load_table();
public:
        static std::vector<Ttable_editor*> editors;
        static void show_table(String table);
        static void invalidate();
        const String get_table_name() const {return table_name; }
        void set_table_name(String name);
        __fastcall Ttable_editor(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Ttable_editor *table_editor;
//---------------------------------------------------------------------------
#endif
