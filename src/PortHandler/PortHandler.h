#pragma once

#include "../Serial/Serial.h"
#include "../Storage/Storage.h"

class PortHandler
{
public:
	PortHandler(std::string &port_name, long baudrate);
	void Run();


private:
	SerialPort port;
	static MesStorage storage;
	HANDLE *port_ptr;
};