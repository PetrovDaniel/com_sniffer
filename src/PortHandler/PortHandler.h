#pragma once

//#include "../Serial/Serial.h"
#include "../Storage/Storage.h"
#include "../DataLinkLayer/DataLinkLayer.h"

class PortHandler
{
public:
	PortHandler(std::string &port_name, long baudrate);
	void Run();


private:
	DataLinkLayer port;
	static MesStorage storage;
	_user_id_t id;
	_buffer_t buf;
};