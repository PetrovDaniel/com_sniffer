#include "PortHandler.h"

/*
�������� ���������� � ���������� ������� ������, �� ��� ��� ��������� � ������ ��� private ����� ��������� ������ � ������
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
