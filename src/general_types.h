#pragma once

#include <windows.h>

#define BUFFERSIZE 2000								//������ ��������, ���������� ��� ������ ��� ������ ������.


typedef unsigned int _user_id_t;

// ��������� ��� �������� ���������
typedef struct
{
	size_t size = 0;
	char data[BUFFERSIZE];
	_user_id_t src;						//�� ������ ����� ��� ���������
}_buffer_t;


