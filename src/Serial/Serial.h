#pragma once

#define _CRT_SECURE_NO_WARNINGS


#include <tchar.h>
#include <stdio.h>
#include <string>
#include <iostream>
//#include "../Storage/Storage.h"
#include "../general_types.h"


bool OpenPort(HANDLE* hName, char aPort[], DWORD baudrate);
void ClosePort(HANDLE* hName);
bool WriteinPort(HANDLE* hName, char mes[], size_t numbytes);
int ReadPort(HANDLE* hName, char mes[], size_t numbytes);

#define START_MES	0x0a
#define END_MES		0x0d

class SerialPort
{
public:
	SerialPort(std::string &port_name, long baudrate);
	~SerialPort();
	//void process();
	/*
	функции работы с портом спр€таны внутри класса, так как будут вызыватьс€ внутри process()
	*/
	size_t WriteToPort(char *buf, size_t numbutes);
	size_t ReadAllFromPort(char* buf, size_t numbytes);
	size_t ReadMesFromPort(char* buf);
	inline HANDLE *getportptr() { return &port; }
private:
	inline void OpenPort(std::string &port_name, long buadrate);
	inline void ClosePort();
	inline bool PortisValid() { return (port != INVALID_HANDLE_VALUE); }

private:
	HANDLE port;

	/*
		общее хранилище дл€ всех экземпл€ров класса
	*/
	//Storage storage;
};