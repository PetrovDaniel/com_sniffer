#include "PortHandler.h"

PortHandler::PortHandler(std::string &port_name, long baudrate) : port(port_name, baudrate)
{
	port_ptr = port.getportptr();
}

void PortHandler :: Run()
{
 	for (;;)
 	{
 		_buffer_t buf;
 
 		buf.src = port_ptr;
		
 
		if (buf.size = port.ReadMesFromPort(buf.data))
 			storage.push(buf.src, buf);
 
		storage.pop(port_ptr, buf);
 		if (buf.size > 0)
 			port.WriteToPort(buf.data, buf.size);
	} 	
}
