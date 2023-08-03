#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#ifdef WIN32
#include <time.h>
#include <windows.h>
#else
#include <sys/sem.h>
#include <sys/time.h>
#endif
#include "board.h"

#ifdef WIN32
#include < time.h >
#include <windows.h>
#if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
  #define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
#else
  #define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
#endif
struct timezone 
{
  int  tz_minuteswest; /* minutes W of Greenwich */
  int  tz_dsttime;     /* type of dst correction */
};

struct timeval
{
    long tv_sec; 
    long tv_usec; 
};

static const unsigned __int64 epoch = 116444736000000000L;
int gettimeofday(struct timeval * tp,void * tzp)
{
	FILETIME    file_time;
	SYSTEMTIME  system_time;
	ULARGE_INTEGER ularge;
 
	GetSystemTime(&system_time);
	SystemTimeToFileTime(&system_time, &file_time);
	ularge.LowPart = file_time.dwLowDateTime;
	ularge.HighPart = file_time.dwHighDateTime;
 
	tp->tv_sec = (long) ((ularge.QuadPart - epoch) / 10000000L);
	tp->tv_usec = (long) (system_time.wMilliseconds * 1000);
 
	return 0;
}

#endif

unsigned int get_tick_s(void)
{
    unsigned int ret = 0;
    struct timeval tv;

    if(sizeof(ret) == 8 && gettimeofday(&tv, NULL) == 0){
        unsigned long long s = (unsigned long long)tv.tv_sec;
        unsigned long long us = (unsigned long long)tv.tv_usec;
        ret = s * 1000 + us / 1000;
    }

    return ret;
}

#ifdef WIN32
unsigned _int64 get_tick_ms(void)
#else
unsigned long long get_tick_ms(void)
#endif
{
#ifdef WIN32
    unsigned _int64 ret = 0;
	unsigned _int64 s   = 0;
	unsigned _int64 us  = 0;
#else
    unsigned long long ret = 0;
	unsigned long long s   = 0;
	unsigned long long us  = 0;
#endif
    struct timeval tv;

    if(sizeof(ret) == 8 && gettimeofday(&tv, NULL) == 0){
#ifdef WIN32
        s = (unsigned _int64)tv.tv_sec;
        us = (unsigned _int64)tv.tv_usec;
#else
        s = (unsigned long long)tv.tv_sec;
        us = (unsigned long long)tv.tv_usec;
#endif
        ret = s * 1000 + us / 1000;
    }

    return ret;
}

int date_check(unsigned int *date)
{
    int result = 0;

    int year = (*date / 10000) % 10000;
    int month = (*date / 100) % 100;
    int day = *date % 100;

    if (year < 2019) {
        year = 2019;
        result = 1;
    }

    if (year > 2099) {
        year = 2099;
        result = 1;
    }

    if (month < 1) {
        month = 1;
        result = 1;
    }

    if (month > 12) {
        month = 12;
        result = 1;
    }

    if (day < 1) {
        day = 1;
        result = 1;
    }

    if (day > 31) {
        day = 31;
        result = 1;
    }

    if (result == 1) {
        *date = (unsigned int)(year * 10000 + month * 100 + day);
    }

    return result;
}

int time_check(int *time)
{
    int result = 0;

    int hour = (*time / 10000) % 100;
    int min = (*time / 100) % 100;
    int sec = *time % 100;

    if (hour < 0) {
        hour = 0;
        result = 1;
    }

    if (hour > 23) {
        hour = 23;
        result = 1;
    }

    if (min < 0) {
        min = 0;
        result = 1;
    }

    if (min > 59) {
        min = 59;
        result = 1;
    }

    if (sec < 0) {
        sec = 0;
        result = 1;
    }

    if (sec > 59) {
        sec = 59;
        result = 1;
    }

    if (result == 1) {
        *time = hour * 10000 + min * 100 + sec;
    }

    return result;
}
