#include "DataLinkLayer.h"



DataLinkLayer::DataLinkLayer(const std::string &port_name, long baudrate)
{
	port = std::make_unique<SerialPort>(port_name, baudrate);
}

DataLinkLayer::~DataLinkLayer()
{
    ;
}

size_t DataLinkLayer::WriteMes(_buffer_t &mes)
{
    return port->WriteToPort(mes.data, mes.size);
}

size_t DataLinkLayer::ReadMes(_buffer_t &mes)
{
    static bool cmd = false;
	static char temp_cmd[BUFFERSIZE];
	static int cmd_lenght = 0;

    char temp;

    for(int i = 0; i < BUFFERSIZE; i++)
    {
        /*
        нечего читать  - до свидания!
        */
        if (!(port->ReadFromPort(&temp, 1)))
		    break;

        /*
        поймали флаг начала команды - запонимаем ее
        */
		if (temp == START_MES)
			{
				cmd = true;
				cmd_lenght = 0;
				std::cout << std::endl << "--->";
			}

		if (cmd)
		{
			std::cout << std::hex << static_cast<int>(temp) << " ";
			temp_cmd[cmd_lenght] = temp;
			cmd_lenght++;

			if (temp == END_MES)
			{
				memcpy(mes.data, temp_cmd, cmd_lenght);
				cmd = false;
				return static_cast<size_t>(cmd_lenght);
			}
		}
    }

    return 0;
}