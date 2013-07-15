//---------------------------------------------------------------------------

#include <algorithm>

#include "SqlProvider.h"

using std::max;

//---------------------------------------------------------------------------

#pragma package(smart_init)

MySqlProvider sql_provider;

bool MySqlProvider::connect(const char *host,
                   const char *user,
                   const char *passwd,
                   unsigned int port)
{
        close();
        mysql_init(&mysql);
        //mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP,"your_prog_name");
        if (!mysql_real_connect(&mysql,
                host ? host: "localhost",
                user ? user : "root",
                passwd ? passwd : "",
                NULL,
                port ? port : 3306,
                NULL, 0))
                return false;
        connected = true;
        mysql_autocommit(&mysql, 1);
        return true;
}

int MySqlProvider::set_db_name(const std::string &db_name)
{                                                   
        cur_db = db_name;
        int ret = mysql_select_db(&mysql, cur_db.c_str());
        return ret;
}

void MySqlProvider::close()
{
        if (connected) {
                mysql_close(&mysql);
                connected = false;
        }
}

const char *MySqlProvider::error()
{
        return mysql_error(&mysql);
}

unsigned int MySqlProvider::err_no()
{
        return mysql_errno(&mysql);
}

unsigned int MySqlProvider::store_list(std::vector<std::string> &list, MYSQL_RES *result)
{
        list.clear();         
        if (!result) {
                return err_no();
        }
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result)) != NULL)
        {
                unsigned long *lengths = mysql_fetch_lengths(result);
                list.push_back(std::string(row[0], lengths[0]));
        }
        mysql_free_result(result);
        return 0;
}

int MySqlProvider::query(const char *q)
{
        return mysql_query(&mysql, q);
}

unsigned int MySqlProvider::store_result(TStringGrid *grid)
{
        MYSQL_RES *result = mysql_store_result(&mysql);
        if (!result)
                return 1;
        unsigned int num_fields = mysql_num_fields(result);
        my_ulonglong num_rows = mysql_num_rows(result);
        grid->ColCount = max(num_fields + 1, 2);
        grid->RowCount = max(num_rows + 1, 2);
        grid->FixedCols = 1;
        grid->FixedRows = 1;
        grid->Cells[0][0] = "¹";

        MYSQL_FIELD *field;
        for (unsigned col = 0; col < num_fields; ++col) {
                field = mysql_fetch_field(result);
                grid->Cells[col + 1][0] = String(field->name);
        }
        for (my_ulonglong i = 0; i < num_rows; ++i)
                grid->Cells[0][i + 1] = IntToStr((long long)(i + 1));
        if (num_rows == 0)
                grid->Cells[0][1] = "";

        MYSQL_ROW row;
        for (my_ulonglong i = 0;
                i < num_rows && (row = mysql_fetch_row(result)) != NULL;
                ++i) {
                unsigned long *lengths;
                lengths = mysql_fetch_lengths(result);
                for (unsigned j = 0; j < num_fields; ++j) {
                        grid->Cells[j + 1][i + 1] =
                                row[j] ? String(row[j], lengths[j]) :
                                String("NULL");
                        grid->Objects[j + 1][i + 1] = (TObject*)row[j];
                }
        }
        free_and_return:
        mysql_free_result(result);
        return 0;
}

unsigned int MySqlProvider::store_table(TStringGrid *grid, const char *tbl_name)
{
        int ret = query((std::string("SELECT * FROM `") +
                tbl_name + "`").c_str());
        if (ret)
                return ret;
        return store_result(grid);
}

my_ulonglong MySqlProvider::affected_rows()
{
        return mysql_affected_rows(&mysql);
}

