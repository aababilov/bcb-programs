//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "QueryEditor.h"
#include "SqlProvider.h"
#include "msgroutines.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tquery_editor *query_editor;
//---------------------------------------------------------------------------
__fastcall Tquery_editor::Tquery_editor(TComponent* Owner)
        : TFrame(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tquery_editor::btn_execClick(TObject *Sender)
{
        execute_query();
}
//---------------------------------------------------------------------------
void Tquery_editor::execute_query()
{
        if (sql_provider.query(query_text->Text.c_str())) {
                query_log->Visible = true;
                query_log->Text = sql_provider.error();
                query_grid->Visible = false;
                return;
        }
        if (sql_provider.store_result(query_grid)) {
                query_log->Visible = true;
                query_log->Text = "Запрос выполнен успешно; обработанных строк: " +
                        IntToStr((long long)sql_provider.affected_rows());
                query_grid->Visible = false;
                return;
        }
        query_grid->Visible = true;
        query_log->Visible = false;
}
//---------------------------------------------------------------------------
void Tquery_editor::load_file(String name)
{
        try {
                query_text->Lines->LoadFromFile(name);
        } catch (...) {
                show_error("Невозможно загрузить файл\n" + name);
                return;
        }
        filename = name;
        ((TTabSheet*)Parent)->Caption = ExtractFileName(name);
        edt_filename->Text = name;
}

void Tquery_editor::save_file(String name)
{
        try {
                query_text->Lines->SaveToFile(name);
       } catch (...) {
                show_error("Невозможно сохранить файл\n" + name);
                return;
        }
        filename = name;
        ((TTabSheet*)Parent)->Caption = ExtractFileName(name);
        edt_filename->Text = name;
}
