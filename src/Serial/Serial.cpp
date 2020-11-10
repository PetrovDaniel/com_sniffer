// Функции для работы с сериальными портами с WINAPI
//
#include "Serial.h"

/// <summary> Открытие порта для записи и чтения </summary>
/// <param name="hName"> Указатель порта. </param>
/// <param name="aPort"> Адрес порта. </param>
/// <returns> 
/// true - порт открыт.
/// false - не удалось открыть порт. 
/// </returns>
bool OpenPort(HANDLE* hName, char aPort[], DWORD baudrate)
{
	DCB dcb;
	bool result;

	if (!hName)
		return false;

	wchar_t PortNameW[MAX_PATH];

	MultiByteToWideChar(0, 0, aPort, -1, PortNameW, sizeof(PortNameW) / sizeof(char));


	*hName = CreateFile(aPort/*PortNameW*/, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);
	if (*hName == INVALID_HANDLE_VALUE)
	{
		printf("Could not open port\n");
		result = false;
	}
	else
	{
		printf("Port %s open\n", aPort);

		GetCommState(*hName, &dcb);
		dcb.BaudRate = baudrate;
		dcb.StopBits = ONESTOPBIT;
		dcb.Parity = NOPARITY;
		dcb.ByteSize = 8;
		SetCommState(*hName, &dcb);

		result = true;
	}

	return result;
}

///<summary> Функция закрытия порта. </symmary>
///<param name="hName"> Название порта. </param>
void ClosePort(HANDLE* hName)
{
	if (*hName != INVALID_HANDLE_VALUE)
		CloseHandle(*hName);
}

/// <summary> Функция записи массива в порт. </symmary>
/// <param name="Hname"> Указатель порта. </param>
/// <param name="mes"> Массив для записи. </param>
///<param name="numbytes"> Размер сообщения, посылаемого в порт. </param>
/// <returns> 
/// true - массив записан в порт.
/// false - массив не записан в порт. 
/// </returns>
bool WriteinPort(HANDLE* hName, char mes[], size_t numbytes)
{
	DWORD wrtnbytes = 0;			// счётчик записанных байт.
	bool result = true;

	if (!hName)
		return false;
	if (!mes)
		return false;

	if (*hName != INVALID_HANDLE_VALUE)
	{
		if (false == WriteFile(*hName, mes, (DWORD)numbytes, &wrtnbytes, NULL))
		{
			printf("Could not write to port (error %d)\n", GetLastError());
			result = false;
		}
		//else
		//	printf("Wrote %d bytes successfully \n", wrtnbytes);
	}

	return result;
}

/// <summary> Функция чтения из порта и записи в массив. </summary>
/// <param name="hName"> Указатель порта. </param>
/// <param name="mes"> Массив для чтения. </param>
///<param name="numbytes">Размер буфера для записи.</param>
/// <returns> 
///  !=0 - Данные из порта записаны в массив. </returns>
///  0 - Данные из порта не прочитаны. 
///</returns>
int ReadPort(HANDLE* hName, char mes[], size_t numbytes)
{
	static DWORD sizemes = 0;		//Счетчик прочитанных байт.
	DWORD lpError;
	COMSTAT lpStat;
	int i;
	int result = 0;

	if (!hName)
		return 0;
	if (!mes)
		return 0;
	if (*hName != INVALID_HANDLE_VALUE)
	{
		ClearCommError(*hName, &lpError, &lpStat);
		// нет ошибок и в буфере есть данные 
		if (lpError == 0 && lpStat.cbInQue != 0)
		{
			for (i = 0; i != numbytes; i++)
				mes[i] = 0;
			if (false != ReadFile(*hName, mes, (DWORD)numbytes, &sizemes, NULL))
			{
				//printf("Text read from port. \n");
				result = sizemes;
			}
			else
				printf("Could not read from port (error %d).\n", GetLastError());
		}
	}
	return result;
}

SerialPort::SerialPort(const std::string& port_name, long baudrate)
{
	OpenPort(port_name, baudrate);
}

SerialPort ::~SerialPort()
{
	ClosePort();
}

/** @brief функция открытия порта
*/
void SerialPort::OpenPort(const std::string &port_name, long baudrate)
{

	if (port_name.length() == 0)
		throw "Invalid port name - " + port_name;

	this->port = CreateFile(port_name.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);

	if (!PortisValid())
		throw "Invalid port name!";

	std::cout << "port open " << port_name << std::endl;
	/*
	По хорошему, надо переделать и передавать всю структуру в конструктор класса
	*/

	DCB dcb;

	if(!GetCommState(this->port, &dcb))
		throw "Cannot get port settings";

	dcb.BaudRate = baudrate;
	dcb.StopBits = ONESTOPBIT;
	dcb.Parity = NOPARITY;
	dcb.ByteSize = 8;

	if(!SetCommState(this->port, &dcb))
		throw "Cannot set port settings";
	
	return;
}

/** @brief функция закрытия порта
*/
void SerialPort::ClosePort()
{
	CloseHandle(port);			
}

/** @brief функция записи в порт
*/
size_t SerialPort::WriteToPort(char *buf, size_t numbytes)
{
	DWORD wrtnbytes = 0;			// счётчик записанных байт.

	if (!buf)
		throw "Invalid buf";

	if ( !(WriteFile(this->port, buf, static_cast<DWORD>(numbytes), &wrtnbytes, NULL)))
		throw "Could not write to port error " + GetLastError();

	std::cout << std::endl << "<---";
	for (size_t i = 0; i < numbytes; i++)
		std::cout << std::hex << static_cast<int>(buf[i]);

	//std::cout << buf;

	return static_cast<size_t>(wrtnbytes);
}

size_t SerialPort::ReadFromPort(char* buf, size_t numbytes)
{
	static DWORD sizemes = 0;		//Счетчик прочитанных байт.
	DWORD lpError;
	COMSTAT lpStat;
	int result = 0;

	if (!buf)
		return 0;

	ClearCommError(this->port, &lpError, &lpStat);
	// нет ошибок и в буфере есть данные 
	if (lpError == 0 && lpStat.cbInQue != 0)
	{
		//ZeroMemory(buf, numbytes);
	
		if ( !(ReadFile(this->port, buf, static_cast<DWORD>(numbytes), &sizemes, NULL)))
			throw "Could not read from port error ";
	}

	return static_cast<size_t>(sizemes);
}



size_t SerialPort::ReadMesFromPort(char* buf)
{
	DWORD sizemes = 0;		//Счетчик прочитанных байт.
	DWORD lpError;
	COMSTAT lpStat;
	LPVOID lpData;

	char temp;

	static bool cmd = false;
	static char temp_cmd[BUFFERSIZE];
	static int cmd_lenght = 0;


	lpData = static_cast<LPVOID>(&temp);


	if (!buf || this->port == INVALID_HANDLE_VALUE)
		return 0;


	/*
	Читаем по одному байту пока не получим начало команды и читаем до конца команды
	Если прочитали все. что было в порту. и не нашли конец команды, то возвращаем, что ничего не прочитали
	На следующем заходе в функцию дочитываем команду и возвращаем ее.
	*/
	ClearCommError(this->port, &lpError, &lpStat);
	if (lpError == 0)
	{
		if (lpStat.cbInQue > 0)
		{

			for (int j = 0; j < lpStat.cbInQue; j++)
			{
				if (!(ReadFile(this->port, lpData, 1, &sizemes, NULL)))
					break;

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
						memcpy(buf, temp_cmd, cmd_lenght);
						//ZeroMemory(buf, cmd_lenght);
						//memset(temp_cmd, NULL, cmd_lenght);
						cmd = false;
						return cmd_lenght;
					}
				}
			}
		}
	}

	return 0;
}


// void SerialPort::process()
// {
// 	if (!PortisValid())
// 		return;	// !!!!!!
// 	
// 	for (;;)
// 	{
// 		_buffer_t buf;
// 
// 		buf.src = &(this->port);
// 
// 		if (buf.size = ReadMesFromPort(buf.data))
// 			storage.PushMes(buf);
// 
// 		storage.GetMesByPortId(&(this->port), buf);
// 		if (buf.size > 0)
// 		{
// 			WriteToPort(buf.data, buf.size);
// 		}
// 
// 	}
// }