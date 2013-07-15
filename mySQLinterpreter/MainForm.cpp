//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop


#include "MainForm.h"
#include "SqlProvider.h"
#include "ConnectForm.h"
#include "TableEditor.h"
#include <cstdio>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tmain_form *main_form;
using std::string;
using std::vector;
//---------------------------------------------------------------------------
__fastcall Tmain_form::Tmain_form(TComponent* Owner)
        : TForm(Owner)
{
        N6Click(NULL);
}
//---------------------------------------------------------------------------
void __fastcall Tmain_form::FormShow(TObject *Sender)
{
        fm_connect->reload_dbs();
        fm_connect->ShowModal();
        if (sql_provider.is_connected())
                reload_tbl_list();
}
//---------------------------------------------------------------------------
void __fastcall Tmain_form::table_listDblClick(TObject *Sender)
{
        int item = table_list->ItemIndex;
        if (item == -1)
                return;
        Ttable_editor::show_table(table_list->Items->Strings[item]);
}
//---------------------------------------------------------------------------
void Tmain_form::reload_tbl_list()
{
        Ttable_editor::invalidate();
        table_list->Clear();
        sql_provider.read_table_list();
        const vector<string> &tbls = sql_provider.get_tables();
        for (vector<string>::const_iterator i = tbls.begin();
                i != tbls.end();
                ++i) {
                table_list->Items->Add(i->c_str());
        }
}
//---------------------------------------------------------------------------
void Tmain_form::new_tab()
{
        tab = new TTabSheet(query_tabs);
        tab->PageControl = query_tabs;
        ed = new Tquery_editor(tab);
        ed->Parent = tab;
        tab->Show();
}
//---------------------------------------------------------------------------
void __fastcall Tmain_form::N6Click(TObject *Sender)
{
        new_tab();
        tab->Caption = "Новый запрос";
}
//---------------------------------------------------------------------------
void __fastcall Tmain_form::N7Click(TObject *Sender)
{
        if (!opendlg->Execute())
                return;
        String filename = opendlg->FileName;
        new_tab();
        ed->load_file(filename);
}
//---------------------------------------------------------------------------
void __fastcall Tmain_form::N8Click(TObject *Sender)
{
        if (query_tabs->ActivePage == NULL)
                return;
        if (!savedlg->Execute())
                return;
        ed = (Tquery_editor*)query_tabs->ActivePage->Controls[0];
        ed->save_file(savedlg->FileName);
}
//---------------------------------------------------------------------------
void __fastcall Tmain_form::N9Click(TObject *Sender)
{
        if (query_tabs->ActivePage == NULL)
                return;
        delete query_tabs->ActivePage;                
}
//---------------------------------------------------------------------------
void __fastcall Tmain_form::N4Click(TObject *Sender)
{
        reload_tbl_list();
}
//---------------------------------------------------------------------------
void __fastcall Tmain_form::N2Click(TObject *Sender)
{
        fm_connect->ShowModal();
        if (sql_provider.is_connected())
                reload_tbl_list();
}
//---------------------------------------------------------------------------
void __fastcall Tmain_form::N10Click(TObject *Sender)
{
        if (query_tabs->ActivePage == NULL)
                return;
        ed = (Tquery_editor*)query_tabs->ActivePage->Controls[0];
        ed->execute_query();
}
//---------------------------------------------------------------------------
void __fastcall Tmain_form::N11Click(TObject *Sender)
{
        if (query_tabs->ActivePage == NULL)
                return;
        if (!saverep->Execute())
                return;
        ed = (Tquery_editor*)query_tabs->ActivePage->Controls[0];
        TStringGrid *query_grid = ed->query_grid;
        using namespace std;
        FILE *f = fopen(saverep->FileName.c_str(), "w+t");
        fprintf(f, "<html><body><table border=1 cellpadding=\"10\" " 
"style=\"border-collapse:collapse;border:solid\">\n");
        for (int i = 0; i < query_grid->RowCount; ++i) {
                fprintf(f, "<tr>\n");
                for (int j = 0; j < query_grid->ColCount; ++j) {
                        fprintf(f, "<td>%s</td>\n", query_grid->Cells[j][i]);
                }
                fprintf(f, "</tr>\n");
        }
        fprintf(f, "</table></body></html>\n");
        fclose(f);
}
//---------------------------------------------------------------------------

