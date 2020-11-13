#include "PortHandler.h"

/*
Создание переменной в глобальной области памяти, но так как объявлена в классе как private имеет видимость только в классе
*/
RingStorage<_buffer_t> PortHandler::storage;




PortHandler::PortHandler(const std::string &port_name, long baudrate) : port(port_name, baudrate)
{
	id = storage.init();
}

void PortHandler :: Run()
{

 	{
		if (buf.size = port.ReadMes(buf))
 			storage.push(id, buf);

		storage.pop(id, buf);

 		if (buf.size > 0)
			port.WriteMes(buf);
	} 	
}
