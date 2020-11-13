#pragma once

#include "../Storage/Storage.h"
#include "../DataLinkLayer/DataLinkLayer.h"

class PortHandler
{
public:
	PortHandler(const std::string &port_name, long baudrate);
	void Run();


private:
	DataLinkLayer port;
	static RingStorage<_buffer_t> storage;
	_user_id_t id;
	_buffer_t buf;
};