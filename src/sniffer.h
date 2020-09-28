#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include "Serial/Serial.h"	
#include "Line/Line.h"

#define BUFFERSIZE 2000								//Размер массивов, выделяемых для записи или чтения портов.



DWORD WINAPI Thread(PVOID pvParam);



// статусы буферов, хранящих сообщения
enum Status
{
	EMPTY,
	DATA_RECEIVE,
	READY_TO_SEND
};

// структура для хранения сообщений
typedef struct MyStruct
{
	size_t size = 0;
	char data[BUFFERSIZE];
	unsigned long status = EMPTY;	// 0 - пустой; 1 - есть данные; 2 - данные записаны в лог файл, можно отправлять;
}buffer_t;


// структура хранящая инофрмацию для работы потоков
typedef struct MyStruct1
{
	HANDLE *port = NULL;
	buffer_t *tx_buf = NULL;
	buffer_t *rx_buf = NULL;
}thread_t;

