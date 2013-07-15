//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TableEditor.h"
#include "SqlProvider.h"
#include "msgroutines.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
using std::vector;
Ttable_editor *table_editor;
std::vector<Ttable_editor*> Ttable_editor::editors;
void Ttable_editor::show_table(String table)
{
        for (vector<Ttable_editor*>::iterator i = editors.begin();
                i != editors.end();
                ++i) {
                if ((*i)->get_table_name() == table) {
                        (*i)->Show();
                        return;
                }
        }
        Ttable_editor *ed = new Ttable_editor(Application);
        ed->set_table_name(table);
        ed->Show();
}
void Ttable_editor::invalidate()
{
        for (vector<Ttable_editor*>::iterator i = editors.begin();
                i != editors.end();
                ++i) {
                delete (*i);
        }
        editors.clear();
}
//---------------------------------------------------------------------------
__fastcall Ttable_editor::Ttable_editor(TComponent* Owner)
        : TForm(Owner)
{
        editors.push_back(this);
        edited_row = -1;
}
//---------------------------------------------------------------------------
void __fastcall Ttable_editor::btnReloadClick(TObject *Sender)
{
        load_table();
}
//---------------------------------------------------------------------------
void Ttable_editor::load_table()
{
        if (sql_provider.store_table(tbl_grid, table_name.c_str())) {
                show_error(String("Невозможно прочитать таблицу:\n")
                        + sql_provider.error());
        } else {
                edited_row = -1;
                not_null.resize(tbl_grid->ColCount, false);
                if (tbl_grid->Cells[0][1].IsEmpty()) {
                        new_row = 1;
                        insert_mode();
                } else {
                        noninsert_mode();
                }
        }
}
//---------------------------------------------------------------------------
void Ttable_editor::set_table_name(String name)
{
        table_name = name;
        Caption = "Таблица " + name;
        load_table();
}
//---------------------------------------------------------------------------
void __fastcall Ttable_editor::tbl_gridSetEditText(TObject *Sender,
      int ACol, int ARow, const AnsiString Value)
{
        edited_val = Value;
        edited_row = ARow;
        edited_col = ACol;
}
//---------------------------------------------------------------------------
int Ttable_editor::set_value()
{
        if (edited_row == -1)
                return 0;
        if (tbl_grid->Objects[edited_col][edited_row] && old_val == edited_val) {
                edited_row = -1;
                return 0;
        }
        tbl_grid->OnGetEditText = NULL;
        tbl_grid->OnSetEditText = NULL;
        String query = "UPDATE `" + table_name + "` SET `" +
                tbl_grid->Cells[edited_col][0] + "`=\'" + edited_val +
                "\' WHERE ";
        bool first = true;
        for (int i = 1; i < tbl_grid->ColCount; ++i) {
                if (!first)
                        query += " AND ";
                query += "`" + tbl_grid->Cells[i][0] + "`";
                if (tbl_grid->Objects[i][edited_row]) {
                        query += "=\'" + (i == edited_col ? old_val :
                                tbl_grid->Cells[i][edited_row]) + "\'";
                } else {
                        query += " IS NULL";
                }
                first = false;
        }
        tbl_grid->OnGetEditText = &tbl_gridGetEditText;
        tbl_grid->OnSetEditText = &tbl_gridSetEditText;
        if (sql_provider.query(query.c_str())) {
                show_error(String("Невозможно сохранить редактированное поле:\n") +
                        sql_provider.error());
                tbl_grid->Cells[edited_col][edited_row] = old_val;
                edited_row = -1;
                return 1;
        }
        edited_row = -1;
        return 0;
}
//---------------------------------------------------------------------------
void __fastcall Ttable_editor::tbl_gridSelectCell(TObject *Sender,
      int ACol, int ARow, bool &CanSelect)
{
        if (col != ACol || row != ARow)
                if (set_value()) {
                        CanSelect = false;
                        return;
                }
        col = ACol;
        row = ARow;
}
//---------------------------------------------------------------------------
void __fastcall Ttable_editor::tbl_gridGetEditText(TObject *Sender,
      int ACol, int ARow, AnsiString &Value)
{
        old_val = Value;
}
//---------------------------------------------------------------------------
void __fastcall Ttable_editor::btnAddClick(TObject *Sender)
{       
        new_row = tbl_grid->RowCount;
        tbl_grid->RowCount = new_row + 1;
        insert_mode();
}
//---------------------------------------------------------------------------
void __fastcall Ttable_editor::tbl_gridSelectCellInsert(TObject *Sender,
      int ACol, int ARow, bool &CanSelect)
{
        if (ARow == new_row)
                return;
        if (insert_row())
                CanSelect = false;
}
//---------------------------------------------------------------------------
void __fastcall Ttable_editor::tbl_gridSetEditTextInsert(TObject *Sender,
      int ACol, int ARow, const AnsiString Value)
{
        not_null[ACol] = true;
}
//---------------------------------------------------------------------------
void Ttable_editor::insert_mode()
{           
        tbl_grid->OnSelectCell = NULL;
        tbl_grid->Cells[0][new_row] = IntToStr(new_row);
        for (int j = 1; j < tbl_grid->ColCount; ++j) {
                tbl_grid->Cells[j][new_row] = "NULL";
        }
        not_null.clear();
        tbl_grid->Row = new_row;
        tbl_grid->OnSelectCell = &tbl_gridSelectCellInsert;
        tbl_grid->OnSetEditText = &tbl_gridSetEditTextInsert;
        tbl_grid->OnGetEditText = NULL;
        status->SimpleText = "Добавление записи";
}
//---------------------------------------------------------------------------
void Ttable_editor::noninsert_mode()
{
        tbl_grid->OnSelectCell = &tbl_gridSelectCell;
        tbl_grid->OnSetEditText = &tbl_gridSetEditText;
        tbl_grid->OnGetEditText = &tbl_gridGetEditText;
        new_row = -1;
        status->SimpleText = "";
}
//---------------------------------------------------------------------------
int Ttable_editor::insert_row()
{
        String query = "INSERT INTO `" + table_name + "` SET";
        bool first = true;
        for (int i = 1; i < tbl_grid->ColCount; ++i)
                if (not_null[i]) {
                        if (!first)
                                query += ", ";
                        query += "`" + tbl_grid->Cells[i][0] + "`=\'" +
                                tbl_grid->Cells[i][new_row] + "\'";
                        first = false;
                }
        if (sql_provider.query(query.c_str())) {
                show_error(String("Невозможно добавить строку:\n") +
                        sql_provider.error());
                return 1;
        }
        for (int i = 1; i < tbl_grid->ColCount; ++i)
                tbl_grid->Objects[i][new_row] = (TObject*)
                        (not_null[i] ? 1 : 0);
        noninsert_mode();
        return 0;
}
//---------------------------------------------------------------------------
void __fastcall Ttable_editor::btnSaveClick(TObject *Sender)
{
        if (new_row != -1)
                insert_row();
        else 
                set_value();
}
//---------------------------------------------------------------------------
void __fastcall Ttable_editor::btnCancelClick(TObject *Sender)
{
        if (new_row != -1) {
                tbl_grid->RowCount = new_row;
                noninsert_mode();
                edited_row = -1;
        }
}
//---------------------------------------------------------------------------
void __fastcall Ttable_editor::btnRemoveClick(TObject *Sender)
{
        if (Application->MessageBox("Удалить строку?", "Подтверждение",
                MB_YESNO|MB_ICONQUESTION) != IDYES)
                return;
        int cur = tbl_grid->Row;
        String query = "DELETE FROM `" + table_name + "` WHERE";
        bool first = true;
        for (int i = 1; i < tbl_grid->ColCount; ++i) {
                if (!first)
                        query += " AND ";
                query += "`" + tbl_grid->Cells[i][0] + "`";
                if (tbl_grid->Objects[i][cur]) {
                        query += "=\'" + tbl_grid->Cells[i][cur] + "\'";
                } else {
                        query += " IS NULL";
                }
                first = false;
        }
        if (sql_provider.query(query.c_str())) {
                show_error(String("Невозможно удалить строку:\n") +
                        sql_provider.error());
                return;
        }
        for (int i = cur; i + 1 < tbl_grid->RowCount; ++i) {
                for (int j = 1; j < tbl_grid->ColCount; ++j) {
                        tbl_grid->Objects[j][i] = tbl_grid->Objects[j][i + 1];
                        tbl_grid->Cells[j][i] = tbl_grid->Cells[j][i + 1];
                }
        }

        if (tbl_grid->RowCount <= 2) {
                new_row = 1;
                insert_mode();
        } else {
                tbl_grid->RowCount = tbl_grid->RowCount - 1;
                noninsert_mode();
        }
}
//---------------------------------------------------------------------------

