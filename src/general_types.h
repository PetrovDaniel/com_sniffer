#pragma once

#include <windows.h>

#define BUFFERSIZE 2000								//Размер массивов, выделяемых для записи или чтения портов.


typedef unsigned int _user_id_t;

// структура для хранения сообщений
typedef struct
{
	size_t size = 0;
	char data[BUFFERSIZE];
	_user_id_t src;						//от какого порта это сообщение
}_buffer_t;


