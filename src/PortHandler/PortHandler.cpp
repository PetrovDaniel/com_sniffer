#include "PortHandler.h"

/*
�������� ���������� � ���������� ������� ������, �� ��� ��� ��������� � ������ ��� private ����� ��������� ������ � ������
*/
MesStorage PortHandler::storage;




PortHandler::PortHandler(std::string &port_name, long baudrate) : port(port_name, baudrate)
{
	port_ptr = port.getportptr();
}

void PortHandler :: Run()
{
	static _buffer_t buf;

	buf.src = port_ptr;

 	//for (;;)
 	{
		if (buf.size = port.ReadMesFromPort(buf.data))
 			storage.push(buf.src, buf);
 
// 		if (buf.size > 0)
// 		{
// 			std::cout << buf.data << std::endl;
// 		}

		storage.pop(port_ptr, buf);

 		if (buf.size > 0)
 			port.WriteToPort(buf.data, buf.size);
	} 	
}
