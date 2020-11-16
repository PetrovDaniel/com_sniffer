// Функции для работы с сериальными портами с WINAPI
//
#include "Serial.h"


SerialPort::SerialPort(const std::string& port_name, long baudrate)
{
	OpenPort(port_name, baudrate);
	this->port_name = port_name;
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
		throw std::runtime_error("Invalid port name " + port_name);

	this->port = CreateFile(port_name.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);

	if (!PortisValid())
		throw std::runtime_error("Cannot open port " + port_name);

	std::cout << "port open " << port_name << std::endl;
	/*
	По хорошему, надо переделать и передавать всю структуру в конструктор класса
	*/

	DCB dcb;

	if(!GetCommState(this->port, &dcb))
		throw std::runtime_error("Cannot get port settings");

	dcb.BaudRate = baudrate;
	dcb.StopBits = ONESTOPBIT;
	dcb.Parity = NOPARITY;
	dcb.ByteSize = 8;

	if(!SetCommState(this->port, &dcb))
		throw std::runtime_error("Cannot set port settings");
	
	return;
}

/** @brief функция закрытия порта
*/
void SerialPort::ClosePort()
{
	CloseHandle(port);
	std::cout << "Port " << this->port_name << " closed." << std::endl;
}

/** @brief функция записи в порт
*/
size_t SerialPort::WriteToPort(char *buf, size_t numbytes)
{
	DWORD wrtnbytes = 0;			// счётчик записанных байт.

	if (!buf)
		throw std::runtime_error("Invalid buf");

	if ( !(WriteFile(this->port, buf, static_cast<DWORD>(numbytes), &wrtnbytes, NULL)))
		throw std::runtime_error("Could not write to port error ");

	std::cout << std::endl << "<---";
	for (size_t i = 0; i < numbytes; i++)
		std::cout << std::hex << static_cast<int>(buf[i]);

	//std::cout << buf;

	return static_cast<size_t>(wrtnbytes);
}
/** @brief функция чтения из порта
*/
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
			throw std::runtime_error("Could not read from port error ");
	}

	return static_cast<size_t>(sizemes);
}