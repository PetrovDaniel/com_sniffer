#include "PortHandler.h"

/*
�������� ���������� � ���������� ������� ������, �� ��� ��� ��������� � ������ ��� private ����� ��������� ������ � ������
*/
MesStorage PortHandler::storage;




PortHandler::PortHandler(std::string &port_name, long baudrate) : port(port_name, baudrate)
{
	id = storage.init();
	//buf.src = id;
}

void PortHandler :: Run()
{

 	//for (;;)
 	{
		if (buf.size = port.ReadMes(buf))
 			storage.push(id, buf);
 
// 		if (buf.size > 0)
// 		{
// 			std::cout << buf.data << std::endl;
// 		}

		storage.pop(id, buf);

 		if (buf.size > 0)
			port.WriteMes(buf);
	} 	
}
