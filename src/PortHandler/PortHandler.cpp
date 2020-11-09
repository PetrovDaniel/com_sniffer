#include "PortHandler.h"

/*
�������� ���������� � ���������� ������� ������, �� ��� ��� ��������� � ������ ��� private ����� ��������� ������ � ������
*/
MesStorage PortHandler::storage;




PortHandler::PortHandler(std::string &port_name, long baudrate) : port(port_name, baudrate)
{
	id = storage.init();
}

void PortHandler :: Run()
{
	static _buffer_t buf;

	buf.src = id;

 	//for (;;)
 	{
		if (buf.size = port.ReadMes(buf))
 			storage.push(buf.src, buf);
 
// 		if (buf.size > 0)
// 		{
// 			std::cout << buf.data << std::endl;
// 		}

		storage.pop(id, buf);

 		if (buf.size > 0)
			port.WriteMes(buf);
	} 	
}
