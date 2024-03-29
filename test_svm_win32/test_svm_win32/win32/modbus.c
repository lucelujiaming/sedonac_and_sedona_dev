#include "sedona.h"
#include <stdio.h>
#ifdef WIN32
#include <io.h>
#include <process.h>
#else
#include <unistd.h>
#endif
#include <string.h>
#include <stdlib.h>
#include <errno.h>


Cell ModBus_remDev_dRtuO(SedonaVM* vm, Cell* params)
{
    int ctx_idx = params[1].ival;
    int band = params[2].ival;
    int parity = params[3].ival;
    int data_bit = params[4].ival;
    int stop_bit = params[5].ival;
    int retry_delay = params[6].ival;
    int rto = params[7].ival;

    Cell ret;
    {
        extern int rtu_open(int ctx_idx, int band, int parity, int data_bit, int stop_bit, int retry_delay, int rto);
        ret.ival = rtu_open(ctx_idx, band, parity, data_bit, stop_bit, retry_delay, rto);
		printf("[%s:%s:%d] return %d\n",
                 __FILE__, __FUNCTION__, __LINE__, ret.ival);
    }

    return ret;
}

Cell ModBus_remDev_dRtuC(SedonaVM* vm, Cell* params)
{
    int ctx_idx = params[1].ival;

    Cell ret;
    {
		printf("[%s:%s:%d] rtu_close %d\n",
                 __FILE__, __FUNCTION__, __LINE__, ctx_idx);
        extern int rtu_close(int ctx_idx);
        ret.ival = rtu_close(ctx_idx);
		printf("[%s:%s:%d] return %d\n",
                 __FILE__, __FUNCTION__, __LINE__, ret.ival);
    }

    return ret;
}

Cell ModBus_remDev_dRtuA(SedonaVM* vm, Cell* params)
{
    int ctx_idx = params[1].ival;
    int device_addr = params[2].ival;
    int addr = params[3].ival;
    int len = params[4].ival;
    int refreshms = params[5].ival;
    int pointdelay = params[6].ival;

    Cell ret;
    {
        extern int rtu_add(int ctx_idx, int device_addr, int addr, int len, int refreshms, int reg_delay);
        ret.ival = rtu_add(ctx_idx, device_addr, addr, len, refreshms, pointdelay);
		printf("[%s:%s:%d] return %d\n",
                 __FILE__, __FUNCTION__, __LINE__, ret.ival);
    }

    return ret;
}

Cell ModBus_remDev_dRtuR(SedonaVM* vm, Cell* params)
{
    int ctx_idx = params[1].ival;
    int device_addr = params[2].ival;
    int addr = params[3].ival;
    int len = params[4].ival;
    float *buf = (float *)params[5].aval;

    Cell ret;
    ret.ival = -1;
    if (len > 0) {
        extern int rtu_read(int ctx_idx, int device_addr, int addr, float *buf, int len);
        int result = rtu_read(ctx_idx, device_addr, addr, buf, len);
		//	printf("[%s:%s:%d] return %d\n",
        //         __FILE__, __FUNCTION__, __LINE__, result);
        if (result > 0) {
            ret.ival = result;
        }
    }

    return ret;
}

Cell ModBus_remDev_dRtuW(SedonaVM* vm, Cell* params)
{
    int ctx_idx = params[1].ival;
    int device_addr = params[2].ival;
    int addr = params[3].ival;
    int len = params[4].ival;
	float *buf = (float *)params[5].aval;

    Cell ret;
    ret.ival = -1;
    if (len > 0) {
        extern int rtu_write(int ctx_idx, int device_addr, int addr, float *buf, int len);
        int result = rtu_write(ctx_idx, device_addr, addr, buf, len);
		printf("[%s:%s:%d] return %d\n",
                 __FILE__, __FUNCTION__, __LINE__, result);
        if (result > 0) {
            ret.ival = result;
        }
    }

    return ret;
}

Cell ModBus_locDev_dRtuO(SedonaVM* vm, Cell* params)
{
    int ctx_idx = params[1].ival;
    int band = params[2].ival;
    int parity = params[3].ival;
    int data_bit = params[4].ival;
    int stop_bit = params[5].ival;

    Cell ret;
    {
        extern int rtu_master_open(int ctx_idx, int band, int parity, int data_bit, int stop_bit);
        ret.ival = rtu_master_open(ctx_idx, band, parity, data_bit, stop_bit);
		printf("[%s:%s:%d] return %d\n",
                 __FILE__, __FUNCTION__, __LINE__, ret.ival);
    }

    return ret;
}

Cell ModBus_locDev_dRtuC(SedonaVM* vm, Cell* params)
{
    int ctx_idx = params[1].ival;

    Cell ret;
    {
		printf("[%s:%s:%d] rtu_master_close %d\n",
                 __FILE__, __FUNCTION__, __LINE__, ctx_idx);
        extern int rtu_master_close(int ctx_idx);
        ret.ival = rtu_master_close(ctx_idx);
		printf("[%s:%s:%d] return %d\n",
                 __FILE__, __FUNCTION__, __LINE__, ret.ival);
    }

    return ret;
}

Cell ModBus_locDev_dRtuA(SedonaVM* vm, Cell* params)
{
    int ctx_idx = params[1].ival;
    int device_addr = params[2].ival;
    int addr = params[3].ival;
    int len = params[4].ival;

    Cell ret;
    {
        extern int rtu_master_add(int ctx_idx, int device_addr, int addr, int len);
        ret.ival = rtu_master_add(ctx_idx, device_addr, addr, len);
		printf("[%s:%s:%d] return %d\n",
                 __FILE__, __FUNCTION__, __LINE__, ret.ival);
    }

    return ret;
}

Cell ModBus_locDev_dRtuR(SedonaVM* vm, Cell* params)
{
    // printf("[%s:%s:%d] Enter\n", __FILE__, __FUNCTION__, __LINE__);
    int ctx_idx = params[1].ival;
    // printf("[%s:%s:%d] ctx_idx = %d \n",__FILE__, __FUNCTION__, __LINE__, ctx_idx);
    int device_addr = params[2].ival;
    // printf("[%s:%s:%d] device_addr = %d \n",__FILE__, __FUNCTION__, __LINE__, device_addr);
    int addr = params[3].ival;
    // printf("[%s:%s:%d] addr = %d \n",__FILE__, __FUNCTION__, __LINE__, addr);
    int len = params[4].ival;
    // printf("[%s:%s:%d] len = %d \n",__FILE__, __FUNCTION__, __LINE__, len);
	float *buf = (float *)params[5].aval;
    // printf("[%s:%s:%d] len = %f \n",__FILE__, __FUNCTION__, __LINE__, buf[0]);

    Cell ret;
    ret.ival = -1;
    if (len > 0) {
        extern int rtu_master_read(int ctx_idx, int device_addr, int addr, float *buf, int len);
    	// printf("[%s:%s:%d] Enter\n", __FILE__, __FUNCTION__, __LINE__);
        int result = rtu_master_read(ctx_idx, device_addr, addr, buf, len);
	// printf("[%s:%s:%d] return %d\n",
        //         __FILE__, __FUNCTION__, __LINE__, result);
        if (result > 0) {
            ret.ival = result;
        }
    }

    return ret;
}

Cell ModBus_locDev_dRtuW(SedonaVM* vm, Cell* params)
{
    int ctx_idx = params[1].ival;
    int device_addr = params[2].ival;
    int addr = params[3].ival;
    int len = params[4].ival;
	float *buf = (float *)params[5].aval;

    Cell ret;
    ret.ival = -1;
    if (len > 0) {
        extern int rtu_master_write(int ctx_idx, int device_addr, int addr, float *buf, int len);
        int result = rtu_master_write(ctx_idx, device_addr, addr, buf, len);
		printf("[%s:%s:%d] return %d\n",
                 __FILE__, __FUNCTION__, __LINE__, result);
        if (result > 0) {
            ret.ival = result;
        }
    }

    return ret;
}

Cell ModBus_remDev_dTcpO(SedonaVM* vm, Cell* params)
{
	char *ip = (char *)params[1].aval;
    int port = params[2].ival;

    Cell ret;
    {
        extern int tcp_open(char *ip, int port);
        ret.ival = tcp_open(ip, port);
		printf("[%s:%s:%d] return %d\n",
                 __FILE__, __FUNCTION__, __LINE__, ret.ival);
    }

    return ret;
}

Cell ModBus_remDev_dTcpC(SedonaVM* vm, Cell* params)
{
    int ctx_idx = params[1].ival;

    Cell ret;
    {
        extern int tcp_close(int ctx_idx);
		printf("[%s:%s:%d] tcp_close %d\n",
                 __FILE__, __FUNCTION__, __LINE__, ctx_idx);
        ret.ival = tcp_close(ctx_idx);
		printf("[%s:%s:%d] return %d\n",
                 __FILE__, __FUNCTION__, __LINE__, ret.ival);
    }

    return ret;
}

Cell ModBus_remDev_dTcpA(SedonaVM* vm, Cell* params)
{
    int ctx_idx = params[1].ival;
    int device_addr = params[2].ival;
    int addr = params[3].ival;
    int len = params[4].ival;
    int refreshms = params[5].ival;

    Cell ret;
    {
        extern int tcp_add(int ctx_idx, int device_addr, int addr, int len, int refreshms);
        ret.ival = tcp_add(ctx_idx, device_addr, addr, len, refreshms);
		printf("[%s:%s:%d] return %d\n",
                 __FILE__, __FUNCTION__, __LINE__, ret.ival);
    }

    return ret;
}

Cell ModBus_remDev_dTcpR(SedonaVM* vm, Cell* params)
{
    int ctx_idx = params[1].ival;
    int device_addr = params[2].ival;
    int addr = params[3].ival;
    int len = params[4].ival;
	float *buf = (float *)params[5].aval;

    Cell ret;
    ret.ival = -1;
    if (len > 0) {
        extern int tcp_read(int ctx_idx, int device_addr, int addr, float *buf, int len);
        int result = tcp_read(ctx_idx, device_addr, addr, buf, len);
		// printf("[%s:%s:%d] return %d\n",
        //          __FILE__, __FUNCTION__, __LINE__, result);
        if (result > 0) {
            ret.ival = result;
        }
    }

    return ret;
}

Cell ModBus_remDev_dTcpW(SedonaVM* vm, Cell* params)
{
    int ctx_idx = params[1].ival;
    int device_addr = params[2].ival;
    int addr = params[3].ival;
    int len = params[4].ival;
	float *buf = (float *)params[5].aval;

    Cell ret;
    ret.ival = -1;
    if (len > 0) {
        extern int tcp_write(int ctx_idx, int device_addr, int addr, float *buf, int len);
        int result = tcp_write(ctx_idx, device_addr, addr, buf, len);
		printf("[%s:%s:%d] return %d\n",
                 __FILE__, __FUNCTION__, __LINE__, result);
        if (result > 0) {
            ret.ival = result;
        }
    }

    return ret;
}

Cell ModBus_locDev_dTcpO(SedonaVM* vm, Cell* params)
{
    int port = params[1].ival;

    Cell ret;
    {
        extern int tcp_master_open(int port);
        ret.ival = tcp_master_open(port);
		printf("[%s:%s:%d] return %d\n",
                 __FILE__, __FUNCTION__, __LINE__, ret.ival);
    }

    return ret;
}

Cell ModBus_locDev_dTcpC(SedonaVM* vm, Cell* params)
{
    int ctx_idx = params[1].ival;

    Cell ret;
    {
		printf("[%s:%s:%d] tcp_master_close %d\n",
                 __FILE__, __FUNCTION__, __LINE__, ctx_idx);
        extern int tcp_master_close(int ctx_idx);
        ret.ival = tcp_master_close(ctx_idx);
		printf("[%s:%s:%d] return %d\n",
                 __FILE__, __FUNCTION__, __LINE__, ret.ival);
    }

    return ret;
}

Cell ModBus_locDev_dTcpA(SedonaVM* vm, Cell* params)
{
    int ctx_idx = params[1].ival;
    int device_addr = params[2].ival;
    int addr = params[3].ival;
    int len = params[4].ival;

    Cell ret;
    {
        extern int tcp_master_add(int ctx_idx, int device_addr, int addr, int len);
        ret.ival = tcp_master_add(ctx_idx, device_addr, addr, len);
		printf("[%s:%s:%d] return %d\n",
                 __FILE__, __FUNCTION__, __LINE__, ret.ival);
    }

    return ret;
}

Cell ModBus_locDev_dTcpR(SedonaVM* vm, Cell* params)
{
    //	printf("[%s:%s:%d] Enter\n",
    //	 __FILE__, __FUNCTION__, __LINE__);
    int ctx_idx = params[1].ival;
    int device_addr = params[2].ival;
    int addr = params[3].ival;
    int len = params[4].ival;
	float *buf = (float *)params[5].aval;
    // int i = 0 ;
    Cell ret;
    ret.ival = -1;
    if (len > 0) {
        extern int tcp_master_read(int ctx_idx, int device_addr, int addr, float *buf, int len);
        int result = tcp_master_read(ctx_idx, device_addr, addr, buf, len);
	//	printf("[%s:%s:%d] return %d\n",
        //         __FILE__, __FUNCTION__, __LINE__, result);
	//	printf("[%s:%s:%d] return data %d\n",
        //         __FILE__, __FUNCTION__, __LINE__, len);
	//	for(i = 0 ; i < len; i++)
	//	{
	//		printf("[%s:%s:%d] return data[%d] = %f\n",
        //         		__FILE__, __FUNCTION__, __LINE__, i, buf[i]);
        //	}
        if (result > 0) {
            ret.ival = result;
        }
    }

    return ret;
}

Cell ModBus_locDev_dTcpW(SedonaVM* vm, Cell* params)
{
    int ctx_idx = params[1].ival;
    int device_addr = params[2].ival;
    int addr = params[3].ival;
    int len = params[4].ival;
	float *buf = (float *)params[5].aval;

    Cell ret;
    ret.ival = -1;
    if (len > 0) {
        extern int tcp_master_write(int ctx_idx, int device_addr, int addr, float *buf, int len);
        int result = tcp_master_write(ctx_idx, device_addr, addr, buf, len);
		printf("[%s:%s:%d] return %d\n",
                 __FILE__, __FUNCTION__, __LINE__, result);
        if (result > 0) {
            ret.ival = result;
        }
    }

    return ret;
}
