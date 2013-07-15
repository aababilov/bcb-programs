//---------------------------------------------------------------------------

#ifndef MainFormH
#define MainFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include "QueryEditor.h"
//---------------------------------------------------------------------------
class Tmain_form : public TForm
{
__published:	// IDE-managed Components
        TListBox *table_list;
        TMainMenu *MainMenu1;
        TMenuItem *N1;
        TMenuItem *N2;
        TMenuItem *N3;
        TMenuItem *N4;
        TGroupBox *GroupBox1;
        TGroupBox *GroupBox2;
        TSplitter *Splitter1;
        TMenuItem *N5;
        TMenuItem *N6;
        TMenuItem *N7;
        TPageControl *query_tabs;
        TOpenDialog *opendlg;
        TMenuItem *N8;
        TMenuItem *N9;
        TSaveDialog *savedlg;
        TMenuItem *N10;
        TSaveDialog *saverep;
        TMenuItem *N11;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall table_listDblClick(TObject *Sender);
        void __fastcall N6Click(TObject *Sender);
        void __fastcall N7Click(TObject *Sender);
        void __fastcall N8Click(TObject *Sender);
        void __fastcall N9Click(TObject *Sender);
        void __fastcall N4Click(TObject *Sender);
        void __fastcall N2Click(TObject *Sender);
        void __fastcall N10Click(TObject *Sender);
        void __fastcall N11Click(TObject *Sender);
private:
        void reload_tbl_list();
        void new_tab();        
        TTabSheet *tab;
        Tquery_editor *ed;
public:		// User declarations
        __fastcall Tmain_form(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tmain_form *main_form;
//---------------------------------------------------------------------------
#endif
