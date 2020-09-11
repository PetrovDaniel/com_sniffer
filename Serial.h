#pragma once

#include <tchar.h>
#include <windows.h>
#include <stdio.h>

bool OpenPort(HANDLE* hName, char aPort[], DWORD baudrate);
void ClosePort(HANDLE* hName);
bool WriteinPort(HANDLE* hName, char mes[], size_t numbytes);
int ReadPort(HANDLE* hName, char mes[], size_t numbytes);