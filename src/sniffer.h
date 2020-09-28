#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include "Serial/Serial.h"	
#include "Line/Line.h"

#define BUFFERSIZE 2000								//������ ��������, ���������� ��� ������ ��� ������ ������.



DWORD WINAPI Thread(PVOID pvParam);



// ������� �������, �������� ���������
enum Status
{
	EMPTY,
	DATA_RECEIVE,
	READY_TO_SEND
};

// ��������� ��� �������� ���������
typedef struct MyStruct
{
	size_t size = 0;
	char data[BUFFERSIZE];
	unsigned long status = EMPTY;	// 0 - ������; 1 - ���� ������; 2 - ������ �������� � ��� ����, ����� ����������;
}buffer_t;


// ��������� �������� ���������� ��� ������ �������
typedef struct MyStruct1
{
	HANDLE *port = NULL;
	buffer_t *tx_buf = NULL;
	buffer_t *rx_buf = NULL;
}thread_t;

