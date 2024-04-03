#ifndef __STL_WRAPPER_H
#define __STL_WRAPPER_H

#ifdef __cplusplus
extern "C" {
#endif

int add_mysqlconn_to_map(void *ptrData);
bool remove_mysqlconn_from_map(int idx);
void * get_mysqlconn_data_from_map(int idx);

int add_redisconn_to_map(void *ptrData);
bool remove_redisconn_from_map(int idx);
void * get_redisconn_data_from_map(int idx);

#ifdef __cplusplus
}
#endif

#endif  /* __STL_WRAPPER_H */