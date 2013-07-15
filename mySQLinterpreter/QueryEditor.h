//---------------------------------------------------------------------------


#ifndef QueryEditorH
#define QueryEditorH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Grids.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class Tquery_editor : public TFrame
{
__published:
        TMemo *query_text;
        TMemo *query_log;
        TStringGrid *query_grid;
        TPanel *Panel1;
        TButton *btn_exec;
        TSplitter *Splitter1;
        TEdit *edt_filename;
        void __fastcall btn_execClick(TObject *Sender);
private:
        String filename;
public:
        __fastcall Tquery_editor(TComponent* Owner);
        void load_file(String name);
        void save_file(String name);
        void execute_query();        
};
//---------------------------------------------------------------------------
extern PACKAGE Tquery_editor *query_editor;
//---------------------------------------------------------------------------
#endif
