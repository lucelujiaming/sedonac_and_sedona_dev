#include "stdafx.h"
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

#include "board.h"
#pragma warning( disable : 4996) 

static unsigned char res_uart_table[MAX_MODBUSRTU_NUM];

int acquire_uart(int idx, char *name)
{
    if (idx < 0 || idx >= MAX_MODBUSRTU_NUM) {
        return -1;
    }
    if (res_uart_table[idx] == 0) {
        char* uart_name[MAX_MODBUSRTU_NUM] = {"6", "7"};
        strcat(name, "/");
        strcat(name, "d");
        strcat(name, "e");
        strcat(name, "v");
        strcat(name, "/");
        strcat(name, "t");
        strcat(name, "t");
        strcat(name, "y");
        strcat(name, "S");
        strcat(name, uart_name[idx]);
        res_uart_table[idx] = 1;
        return idx;
    }
    return -1;
}

void release_uart(int idx)
{
    if (idx < 0 || idx >= MAX_MODBUSRTU_NUM) {
        return;
    }
    if (res_uart_table[idx] == 1) {
        res_uart_table[idx] = 0;
    }
}

#ifdef WIN32
void led_blink(int led_idx){}
void led_on(int led_idx){}
void led_off(int led_idx){}
#endif
