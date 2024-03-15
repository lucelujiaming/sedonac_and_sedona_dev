// test_ftpclient.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ftp_client.h"


//gcc -o ftp ftp.h ftp.c main.c

int main(){

	char host[64] = { 0 };
	memcpy(host, "192.168.168.77", strlen("192.168.168.77"));  //ip
	int port = 2121;
	char user[64] = { 0 };
	memcpy(user, "ftpuser", strlen("ftpuser"));   //用户
	char pwd[64] = { 0 };
	memcpy(pwd, "123456", strlen("123456"));    //密码
	int ret = ftp_connect(host, port, user, pwd);   //连接

	printf("ret=%d\n", ret);

	long long unsigned int fileSize = 0;
	// int stop = 1;
	// fileSize = 0;
	// int down = ftp_retrfile(ret, "svm", "svm", &fileSize); // , &stop);
	// printf("\ndown = %d,fileSize=%d\n", down, (int)fileSize); //  , stop);

	fileSize = 0;
	int up = ftp_storfile(ret, "app.scode.bak", "app.scode.bak", &fileSize); // , &stop);
	printf("\nup = %d,fileSize=%d\n", up, (int)fileSize); //  , stop);
	return  0;

}
