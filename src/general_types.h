#pragma once

#include <windows.h>

#define BUFFERSIZE 2000								//������ ��������, ���������� ��� ������ ��� ������ ������.

// ��������� ��� �������� ���������
typedef struct
{
	size_t size = 0;
	char data[BUFFERSIZE];
	HANDLE* src;						//�� ������ ����� ��� ���������
}_buffer_t;


