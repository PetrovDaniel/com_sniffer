#pragma once

#include <tchar.h>
#include <windows.h>
#include <stdio.h>
#include <string>
#include <iostream>

bool OpenPort(HANDLE* hName, char aPort[], DWORD baudrate);
void ClosePort(HANDLE* hName);
bool WriteinPort(HANDLE* hName, char mes[], size_t numbytes);
int ReadPort(HANDLE* hName, char mes[], size_t numbytes);

class SerialPort
{
public:
	SerialPort(std::string port_name, long baudrate);
	~SerialPort();
	void process();

private:
	inline void OpenPort(std::string port_name, long buadrate);
	inline void ClosePort();



private:
	HANDLE port;
};