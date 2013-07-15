//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <IniFiles.hpp>
#include "ConnectForm.h"
#include "SqlProvider.h"
#include "msgroutines.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfm_connect *fm_connect;
using std::string;
using std::vector;
#define CONN_SECT "Connection"
#define strncasecmp stricmp
//---------------------------------------------------------------------------
__fastcall Tfm_connect::Tfm_connect(TComponent* Owner)
        : TForm(Owner)
{
        TIniFile *ini = new TIniFile(ChangeFileExt(Application->ExeName,
                ".ini"));
        edt_host->Text = ini->ReadString(CONN_SECT, "Host", "localhost");
        edt_port->Text = IntToStr(ini->ReadInteger(CONN_SECT, "Port", 0));
        edt_user->Text = ini->ReadString(CONN_SECT, "User", "root");
        edt_password->Text = ini->ReadString(CONN_SECT, "Password", "");
        default_db = ini->ReadString(CONN_SECT, "DataBase", "new_db");
        delete ini;
}
//---------------------------------------------------------------------------
void Tfm_connect::reload_dbs()
{
        if (!sql_provider.is_connected())
                return;
        sql_provider.read_db_list();
        int idx = 0;
        for (vector<string>::const_iterator i = sql_provider.get_dbs().begin();
                i != sql_provider.get_dbs().end();
                ++i, ++idx) {
                db_name->Items->Add(i->c_str());
                if (strncasecmp(default_db.c_str(), i->c_str()) == 0)
                        db_name->ItemIndex = idx;
        }
}
//---------------------------------------------------------------------------
void __fastcall Tfm_connect::Button1Click(TObject *Sender)
{
        db_name->Clear();
        sql_provider.connect(edt_host->Text.c_str(),
                edt_user->Text.c_str(), edt_password->Text.c_str(),
                StrToIntDef(edt_port->Text, 0));
        btn_select_db->Enabled = sql_provider.is_connected();
        if (!sql_provider.is_connected()) {
                show_error(String("Невозможно соединиться с сервером:\n")
                        + sql_provider.error());
        } else {
                reload_dbs();
        }
}
//---------------------------------------------------------------------------
void __fastcall Tfm_connect::btn_select_dbClick(TObject *Sender)
{
        String db = db_name->Text;
        sql_provider.read_db_list();
        for (vector<string>::const_iterator i = sql_provider.get_dbs().begin();
                i != sql_provider.get_dbs().end();
                ++i) {
                if (strncasecmp(db.c_str(), i->c_str()) == 0) {
                        if (sql_provider.set_db_name(i->c_str())) {
                                show_error(String("Невозможно выбрать базу данных:\n")
                                       + sql_provider.error());
                        } else {
                                Close();
                        }
                        return;
                }
        }
        if (sql_provider.query(("CREATE DATABASE `" +
                db + "`").c_str())) {
               show_error(String("Невозможно создать базу данных:\n")
                       + sql_provider.error());
               return;
        }
        if (sql_provider.set_db_name(db.c_str())) {
                show_error(String("Невозможно выбрать базу данных:\n")
                        + sql_provider.error());
                return;
        }
        Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfm_connect::FormDestroy(TObject *Sender)
{
        TIniFile *ini = new TIniFile(ChangeFileExt(Application->ExeName,
                ".ini"));
        ini->WriteString(CONN_SECT, "Host", edt_host->Text);
        ini->WriteInteger(CONN_SECT, "Port", StrToIntDef(edt_port->Text, 0));
        ini->WriteString(CONN_SECT, "User", edt_user->Text);
        ini->WriteString(CONN_SECT, "Password", edt_password->Text);
        ini->WriteString(CONN_SECT, "DataBase", db_name->Text);
        delete ini;
}
//---------------------------------------------------------------------------

