#include "sedona.h"
#include <stdbool.h>

#include "hiredis.h"
// #define NO_QFORKIMPL //这一行必须加才能正常使用
// #include "win32_hiredis.h"
# include <winsock2.h>
# include <ws2tcpip.h>

#include "stl_wrapper.h"

#ifdef WIN32
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "hiredis.lib")
#pragma comment(lib, "Win32_Interop.lib")
#endif

Cell DB_Redis_dO(SedonaVM* vm, Cell* params)
{
#ifndef WIN32
	return falseCell;
#else
	void* self       = params[0].aval;
	char * address   = params[1].aval;
	int  redis_port  = params[2].ival;

	// 初始化连接对象
	redisContext * redis_conn = redisConnect(address, redis_port);
	if (redis_conn->err)
	{
		printf("Connect to redisServer failed: %s", redis_conn->errstr);
		redisFree(redis_conn);
		return falseCell;
	}
	Cell ret;
	ret.ival = add_redisconn_to_map(redis_conn);
	if (ret.ival != -1)
	{
		return ret;
	}
	else{
		redisFree(redis_conn);
		printf("Failed to add_redisconn_to_map.\n");
		return negOneCell;
	}
#endif
}


Cell DB_Redis_dG(SedonaVM* vm, Cell* params)
{
#ifndef WIN32
	return falseCell;
#else
	char cSQLBuffer[1024];
	void* self = params[0].aval;
	int ctx_idx = params[1].ival;
	char * name = params[2].aval;

	redisContext * redis_conn = get_redisconn_data_from_map(ctx_idx);
	if (redis_conn == NULL)
	{
		printf("redis does not open\r\n");
		return falseCell;
	}

	Cell ret;
	ret.ival = -1;
	memset(cSQLBuffer, 0x00, 1024);
	sprintf(cSQLBuffer, "get %s", name);
	redisReply* objReply = (redisReply*)redisCommand(redis_conn, cSQLBuffer);

	if (objReply->type != REDIS_REPLY_STRING)
	{
		printf("Failed to execute command : %s", cSQLBuffer);
		freeReplyObject(objReply);
		// redisFree(redis_conn);
		return falseCell;
	}
	ret.fval = atof(objReply->str);

	return ret;
#endif
}

Cell DB_Redis_dS(SedonaVM* vm, Cell* params)
{
#ifndef WIN32
	return falseCell;
#else
	char cSQLBuffer[1024];
	void* self = params[0].aval;
	int ctx_idx = params[1].ival;
	char * name = params[2].aval;
	float *value = (float *)params[3].aval;

	redisContext * redis_conn = get_redisconn_data_from_map(ctx_idx);
	if (redis_conn == NULL)
	{
		printf("redis does not open\r\n");
		return falseCell;
	}

	memset(cSQLBuffer, 0x00, 1024);
	sprintf(cSQLBuffer, "set %s %f", name, value[0]);
	redisReply* objReply = (redisReply*)redisCommand(redis_conn, cSQLBuffer);

	if (NULL == objReply)
	{
		printf("Execut command1 failed");
		// redisFree(redis_conn);
		return falseCell;
	}

	if (!(objReply->type == REDIS_REPLY_STATUS && 
		(strcmp(objReply->str, "OK") == 0 || strcmp(objReply->str, "ok") == 0)))
	{
		printf("Failed to execute command: %s", cSQLBuffer);
		freeReplyObject(objReply);
		// redisFree(redis_conn);
		return falseCell;
	}

	return trueCell;
#endif
}

Cell DB_Redis_dE(SedonaVM* vm, Cell* params)
{
#ifndef WIN32
	return falseCell;
#else
	void* self = params[0].aval;
	int ctx_idx = params[1].ival;
	char * strSQL = params[2].aval;

	redisContext * redis_conn = get_redisconn_data_from_map(ctx_idx);
	if (redis_conn == NULL)
	{
		printf("redis does not open\r\n");
		return falseCell;
	}

	redisReply* objReply = (redisReply*)redisCommand(redis_conn, strSQL);

	if (NULL == objReply)
	{
		printf("Execut command1 failed");
		// redisFree(redis_conn); 
		return falseCell;
	}

	if (!(objReply->type == REDIS_REPLY_STATUS &&
		(strcmp(objReply->str, "OK") == 0 || strcmp(objReply->str, "ok") == 0)))
	{
		printf("Failed to execute command: %s", strSQL);
		freeReplyObject(objReply);
		// redisFree(redis_conn);
		return falseCell;
	}

	return trueCell;
#endif
}

Cell DB_Redis_dC(SedonaVM* vm, Cell* params)
{
#ifndef WIN32
	return falseCell;
#else
	void* self = params[0].aval;
	int ctx_idx = params[1].ival;

	redisContext * redis_conn = get_redisconn_data_from_map(ctx_idx);
	if (redis_conn == NULL)
	{
		printf("Redis does not open\r\n");
		return falseCell;
	}
	else
	{
		remove_redisconn_from_map(ctx_idx);
		redisFree(redis_conn); 
	}
	return nullCell;
#endif
}

