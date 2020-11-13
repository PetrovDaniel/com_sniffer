#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <iostream>
#include <windows.h>

#include "../general_types.h"
#include "../SerialInterface/SerialInterface.h"


#define START_MES	0x0a
#define END_MES		0x0d

class SerialPort : public ISerialInterface
{
public:
	//void process();
	/*
	функции работы с портом спр€таны внутри класса, так как будут вызыватьс€ внутри process()
	*/
	// класс наследник имеет свой конструктор и деструктор
	SerialPort(const std::string& port_name, long baudrate);
	~SerialPort();

	size_t WriteToPort(char *buf, size_t numbutes);
	size_t ReadFromPort(char *buf, size_t numbytes);

private:
	inline void OpenPort(const std::string &port_name, long buadrate);
	inline void ClosePort();
	inline bool PortisValid() { return (port != INVALID_HANDLE_VALUE); }

private:
	HANDLE port;

	/*
		общее хранилище дл€ всех экземпл€ров класса
	*/
	//Storage storage;
};