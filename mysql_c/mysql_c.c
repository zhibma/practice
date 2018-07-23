#include <stdio.h>
#include <mysql/mysql.h>

#define FIELED_BUFFER_SIZE  256

int mysql_call_entry(MYSQL *);
int get_column_value(void *, MYSQL_ROW, int);

int main()
{
    int i_ret_val = 0;
    MYSQL *p_db_handle = NULL;
    unsigned int ui_timeout = 5;

    p_db_handle = mysql_init(NULL);

    mysql_options(p_db_handle, MYSQL_OPT_CONNECT_TIMEOUT, (const char *)&ui_timeout);

    mysql_real_connect(p_db_handle, "192.168.56.1", "admin", "admin", "mysql", 0, NULL, 0);

    if(0 == mysql_errno(p_db_handle))
    {
        printf("[INFO] Connect to database system success.\n");
        i_ret_val = mysql_call_entry(p_db_handle);
    }
    else
    {
        fprintf(stderr, "[ERROR] %s\n", mysql_error(p_db_handle));
        mysql_close(p_db_handle);
        i_ret_val = 1;
        return i_ret_val;
    }

    mysql_close(p_db_handle);
    return i_ret_val;
}

int mysql_call_entry(MYSQL *p_db_handle)
{
    int i_ret_val = 0;
    int i_row = 0;
    int i_col = 0;
    MYSQL_RES *p_results = NULL;
    MYSQL_ROW row = NULL;
    char buf[FIELED_BUFFER_SIZE] = {0};

    i_ret_val = mysql_query(p_db_handle, "select host, user, max_connections from user");
    if(0 != i_ret_val)
    {
        fprintf(stderr, "[ERROR] %s\n", mysql_error(p_db_handle));
        i_ret_val = 1;
        return i_ret_val;
    }
    p_results = mysql_store_result(p_db_handle);

    i_row = mysql_num_rows(p_results);
    i_col = mysql_field_count(p_db_handle);

    printf("Get %d rows %d columns.\n", i_row, i_col);

    if(0 < i_row)
    {
        row = mysql_fetch_row(p_results);
        get_column_value((void *)&buf, row, 0);

        printf("column value = %s\n", buf);
    }

    mysql_free_result(p_results);
    return i_ret_val;
}

/*万能列值获取函数，完善中。。。*/
int get_column_value(void *p_out, MYSQL_ROW row, int column)
{
    snprintf((char *)p_out, FIELED_BUFFER_SIZE, "%s", row[column]);
    return 0;
}
