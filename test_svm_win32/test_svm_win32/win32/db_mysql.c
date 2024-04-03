#include "sedona.h"
#include <stdio.h>
#include <stdbool.h>
#ifdef WIN32
# include <windows.h>
#include <tchar.h>

#include <winsock.h>
#include <mysql.h>
#else
#include <unistd.h>
#endif
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "stl_wrapper.h"

#ifdef WIN32
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "libmysql.lib")
#endif

Cell DB_MySQL_dO(SedonaVM* vm, Cell* params)
{
#ifndef WIN32
	return falseCell;
#else
	void* self       = params[0].aval;
	char * address   = params[1].aval;
	int  mysql_port  = params[2].ival;
	char * user_name = params[3].aval;
	char * password  = params[4].aval;
	char * database  = params[5].aval;

	// 初始化连接对象
	MYSQL *mysql_conn = mysql_init(NULL);

	if (mysql_conn == NULL) {
		printf("Failed to initialize MySQL connection.\n");
		return negOneCell;
	}

	mysql_options(mysql_conn, MYSQL_SET_CHARSET_NAME, "utf8"); // 设置连接字符集为 utf8，防止中文乱码

	if (mysql_real_connect(mysql_conn, address, user_name, password, database, mysql_port, NULL, 0) == NULL) {
		printf("Connect to MYSQLServer failed: %s", mysql_error(mysql_conn));
		return negOneCell;
	}

	Cell ret;
	ret.ival = add_mysqlconn_to_map(mysql_conn);
	if (ret.ival != -1)
	{
		return ret;
	}
	else{
		mysql_close(mysql_conn);
		printf("Failed to add_mysqlconn_to_map.\n");
		return negOneCell;
	}
#endif
}


Cell DB_MySQL_dI(SedonaVM* vm, Cell* params)
{
#ifndef WIN32
	return falseCell;
#else
	char cSQLBuffer[1024];
	void* self = params[0].aval;
	int ctx_idx  = params[1].ival;
	char * name  = params[2].aval;
	int type     = params[3].ival;
	float *value = (float *)params[4].aval;

	MYSQL *mysql_conn = get_mysqlconn_data_from_map(ctx_idx);
	if (mysql_conn == NULL)
	{
		printf("MySQL does not open\r\n");
		return falseCell;
	}

	Cell ret;
	ret.ival = -1;
	memset(cSQLBuffer, 0x00, 1024);
	sprintf(cSQLBuffer, "INSERT INTO modbus_record_data (name, type, value) VALUES ('%s', %d, %f)",
		name, type, value[0]);
	mysql_query(mysql_conn, cSQLBuffer);

	ret.ival = (unsigned long)mysql_affected_rows(mysql_conn);
	return ret;
#endif
}

Cell DB_MySQL_dD(SedonaVM* vm, Cell* params)
{
#ifndef WIN32
	return falseCell;
#else
	char cSQLBuffer[1024];
	void* self = params[0].aval;
	int ctx_idx = params[1].ival;
	char * name = params[2].aval;

	MYSQL *mysql_conn = get_mysqlconn_data_from_map(ctx_idx);
	if (mysql_conn == NULL)
	{
		printf("MySQL does not open\r\n");
		return falseCell;
	}

	Cell ret;
	ret.ival = -1;
	memset(cSQLBuffer, 0x00, 1024);
	sprintf(cSQLBuffer, "delete from modbus_record_data where name='%s'", name);
	mysql_query(mysql_conn, cSQLBuffer);

	ret.ival = (unsigned long)mysql_affected_rows(mysql_conn);
	return ret;
#endif
}

Cell DB_MySQL_dU(SedonaVM* vm, Cell* params)
{
#ifndef WIN32
	return falseCell;
#else
	char cSQLBuffer[1024];
	void* self = params[0].aval;
	int ctx_idx = params[1].ival;
	char * name = params[2].aval;
	float *value = (float *)params[3].aval;

	MYSQL *mysql_conn = get_mysqlconn_data_from_map(ctx_idx);
	if (mysql_conn == NULL)
	{
		printf("MySQL does not open\r\n");
		return falseCell;
	}

	Cell ret;
	ret.ival = -1;
	memset(cSQLBuffer, 0x00, 1024);
	sprintf(cSQLBuffer, "update modbus_record_data set value='%f' where name='%s'", *value, name);
	mysql_query(mysql_conn, cSQLBuffer);

	ret.ival = (unsigned long)mysql_affected_rows(mysql_conn);
	return ret;
#endif
}

Cell DB_MySQL_dS(SedonaVM* vm, Cell* params)
{
#ifndef WIN32
	return falseCell;
#else
	char cSQLBuffer[1024];
	void* self = params[0].aval;
	int ctx_idx = params[1].ival;
	char * name = params[2].aval;

	MYSQL *mysql_conn = get_mysqlconn_data_from_map(ctx_idx);
	if (mysql_conn == NULL)
	{
		printf("MySQL does not open\r\n");
		return falseCell;
	}

	Cell ret;
	ret.ival = -1;
	memset(cSQLBuffer, 0x00, 1024);
	sprintf(cSQLBuffer, "select value from modbus_record_data where name='%s'", name);
	mysql_query(mysql_conn, cSQLBuffer);

	MYSQL_RES *result = mysql_store_result(mysql_conn);

	MYSQL_ROW row;
	while ((row = mysql_fetch_row(result)) != NULL) {
		ret.fval = atof(row[0]);
		break;
	}
	return ret;
#endif
}

Cell DB_MySQL_dE(SedonaVM* vm, Cell* params)
{
#ifndef WIN32
	return falseCell;
#else
	void* self = params[0].aval;
	int ctx_idx = params[1].ival;
	char * strSQL = params[2].aval;

	MYSQL *mysql_conn = get_mysqlconn_data_from_map(ctx_idx);
	if (mysql_conn == NULL)
	{
		printf("MySQL does not open\r\n");
		return falseCell;
	}

	Cell ret;
	ret.ival = -1;
	mysql_query(mysql_conn, strSQL);

	ret.ival = (unsigned long)mysql_affected_rows(mysql_conn);
	return ret;
#endif
}

Cell DB_MySQL_dC(SedonaVM* vm, Cell* params)
{
#ifndef WIN32
	return falseCell;
#else
	void* self = params[0].aval;
	int ctx_idx = params[1].ival;

	MYSQL *mysql_conn = get_mysqlconn_data_from_map(ctx_idx);
	if (mysql_conn == NULL)
	{
		printf("MySQL does not open\r\n");
		return falseCell;
	}
	else
	{
		remove_mysqlconn_from_map(ctx_idx);
		mysql_close(mysql_conn); 
	}
	return nullCell;
#endif
}

