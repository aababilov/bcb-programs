//---------------------------------------------------------------------------

#ifndef ConnectFormH
#define ConnectFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class Tfm_connect : public TForm
{
__published:	// IDE-managed Components
        TLabeledEdit *edt_host;
        TLabeledEdit *edt_port;
        TLabeledEdit *edt_user;
        TLabeledEdit *edt_password;
        TButton *Button1;
        TButton *btn_select_db;
        TComboBox *db_name;
        TGroupBox *GroupBox1;
        TGroupBox *gb_select_db;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall btn_select_dbClick(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
private:
        String default_db;
public:		
        __fastcall Tfm_connect(TComponent* Owner);
        void reload_dbs();
};
//---------------------------------------------------------------------------
extern PACKAGE Tfm_connect *fm_connect;
//---------------------------------------------------------------------------
#endif
