#pragma once

#include <windows.h>

#define BUFFERSIZE 2000								//Размер массивов, выделяемых для записи или чтения портов.

// структура для хранения сообщений
typedef struct
{
	size_t size = 0;
	char data[BUFFERSIZE];
	HANDLE* src;						//от какого порта это сообщение
}_buffer_t;


