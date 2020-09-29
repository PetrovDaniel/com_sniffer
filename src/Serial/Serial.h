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
	inline bool PortisValid() { return (port != INVALID_HANDLE_VALUE); }

	/*
		функции работы с портом спрятаны внутри класса, так как будут вызываться внутри process()
	*/
	size_t WriteToPort(char *buf, size_t numbutes);
	size_t ReadAllFromPort(char* buf, size_t numbytes);
	size_t ReadMesFromPort(char* buf, size_t numbytes);





private:
	HANDLE port;
};