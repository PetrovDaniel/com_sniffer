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

SerialPort::SerialPort(std::string port_name, long baudrate)
{
	try
	{
		SerialPort::OpenPort(port_name, baudrate);
	}
	catch (const std::string &str)
	{
		std::cout << "Error: " << str << std::endl;
	}
}

SerialPort::~SerialPort()
{
	ClosePort();
}

/** @brief функция открытия порта
*/
void SerialPort::OpenPort(std::string port_name, long baudrate)
{

	if (port_name.length() == 0)
		throw "Invalid port name - " + port_name;

	this->port = CreateFile(port_name.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);

	if (PortisValid())
		throw "Invalid port name!";

	std::cout << "port open" << port_name << std::endl;
	/*
	По хорошему, надо переделать и передавать всю структуру в конструктор класса
	*/

	DCB dcb;

	GetCommState(this->port, &dcb);
	dcb.BaudRate = baudrate;
	dcb.StopBits = ONESTOPBIT;
	dcb.Parity = NOPARITY;
	dcb.ByteSize = 8;
	SetCommState(this->port, &dcb);
	
	return;
}

/** @brief функция закрытия порта
*/
void SerialPort::ClosePort()
{
	if (PortisValid())
		CloseHandle(port);			
}

/** @brief функция записи в порт
*/
size_t SerialPort::WriteToPort(char *buf, size_t numbytes)
{
	DWORD wrtnbytes = 0;			// счётчик записанных байт.

	if (!buf)
		throw "Invalid buf";

	if (PortisValid())
		if ( !(WriteFile(this->port, buf, static_cast<DWORD>(numbytes), &wrtnbytes, NULL)))
			throw "Could not write to port error " + GetLastError();

	return static_cast<size_t>(wrtnbytes);
}

size_t SerialPort::ReadAllFromPort(char* buf, size_t numbytes)
{
	static DWORD sizemes = 0;		//Счетчик прочитанных байт.
	DWORD lpError;
	COMSTAT lpStat;
	int result = 0;

	if (!buf)
		return 0;

	if (PortisValid())
	{
		ClearCommError(this->port, &lpError, &lpStat);
		// нет ошибок и в буфере есть данные 
		if (lpError == 0 && lpStat.cbInQue != 0)
		{
			ZeroMemory(buf, numbytes);

			if ( !(ReadFile(this->port, buf, static_cast<DWORD>(numbytes), &sizemes, NULL)))
				throw "Could not read from port error " + GetLastError();
		}
	}
	return static_cast<size_t>(sizemes);
}

size_t SerialPort::ReadMesFromPort(char* buf, size_t numbytes)
{
	return 0;
}