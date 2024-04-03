#include "stl_wrapper.h"
#include <time.h>

#define MAP_MYSQLCONN    0
#define MAP_REDISCONN    1
#define MAP_MAX          2

#define RETRY_COUNT        1024

#include <map>
using namespace std;

map<int, void*> g_map[MAP_MAX];
bool add_to_map(int iType, int idx, void *ptrData);
bool remove_from_map(int iType, int idx);
void * get_data_from_map(int iType, int idx);


int add_redisconn_to_map(void *ptrData)
{
	srand(time(NULL));
	int iRetryCount = 0;
	int idx = rand();
	while (true)
	{
		if (get_redisconn_data_from_map(idx))
		{
			idx = rand();
			iRetryCount++;
			if (iRetryCount >= RETRY_COUNT)
			{
				printf("rand() failed");
				return -1;
			}
		}
		else
		{
			break;
		}
	}
	if (add_to_map(MAP_REDISCONN, idx, ptrData))
	{
		return idx;
	}
	else
	{
		return -1;
	}
}
bool remove_redisconn_from_map(int idx)
{
	return remove_from_map(MAP_REDISCONN, idx);
}
void * get_redisconn_data_from_map(int idx)
{
	return get_data_from_map(MAP_REDISCONN, idx);
	// return (void *)100;
}
int add_mysqlconn_to_map(void *ptrData)
{
	srand(time(NULL));
	int iRetryCount = 0;
	int idx = rand();
	while (true)
	{
		if (get_mysqlconn_data_from_map(idx))
		{
			idx = rand();
			iRetryCount++;
			if (iRetryCount >= RETRY_COUNT)
			{
				printf("rand() failed");
				return -1;
			}
		}
		else
		{
			break;
		}
	}
	if (add_to_map(MAP_MYSQLCONN, idx, ptrData))
	{
		return idx;
	}
	else
	{
		return -1;
	}
}
bool remove_mysqlconn_from_map(int idx)
{
	return remove_from_map(MAP_MYSQLCONN, idx);
}
void * get_mysqlconn_data_from_map(int idx)
{
	return get_data_from_map(MAP_MYSQLCONN, idx);
	// return (void *)100;
}

bool add_to_map(int iType, int idx, void *ptrData)
{
	if (iType < MAP_MAX)
	{
		g_map[iType][idx] = ptrData;
		return true;
	}
	return false;
}
bool remove_from_map(int iType, int idx)
{
	map<int, void*>::iterator it;
	if (iType < MAP_MAX)
	{
		it = g_map[iType].find(idx);
		if (it != g_map[iType].end())
		{
			g_map[iType].erase(it);
			return true;
		}
	}
	return false;

}
void * get_data_from_map(int iType, int idx)
{
	map<int, void*>::iterator it;
	if (iType < MAP_MAX)
	{
		it = g_map[iType].find(idx);
		if (it != g_map[iType].end())
		{
			return it->second;
		}
	}
	return NULL;
}