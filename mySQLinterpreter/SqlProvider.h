//---------------------------------------------------------------------------

#ifndef SqlProviderH
#define SqlProviderH
//---------------------------------------------------------------------------
#include <winsock2.h>
#include "mysql/mysql.h"
#include <vector>
#include <string>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class MySqlProvider {
private:
        MYSQL mysql;
        bool connected;
        std::vector<std::string> tables, dbs;
        std::string cur_db;
        unsigned int store_list(std::vector<std::string> &list, MYSQL_RES *result);
public:
        MySqlProvider() :connected(false) {}
        ~MySqlProvider() { close(); }
        bool connect(const char *host,
                   const char *user,
                   const char *passwd,
                   unsigned int port);
        void close();
        const char *error();
        unsigned int err_no();
        bool is_connected() const { return connected; }
        unsigned int read_table_list()
        {  return store_list(tables, mysql_list_tables(&mysql, NULL)); }
        unsigned int read_db_list()
        {  return store_list(dbs, mysql_list_dbs(&mysql, NULL)); }
        unsigned int store_result(TStringGrid *grid);
        unsigned int store_table(TStringGrid *grid, const char *tbl_name);
        my_ulonglong affected_rows();
        int query(const char *q);
        const std::vector<std::string> &get_tables() const {return tables; }
        const std::vector<std::string> &get_dbs() const {return dbs; }
        const std::string &db_name() const { return cur_db; }
        int set_db_name(const std::string &db_name);
};

extern MySqlProvider sql_provider;
#endif
