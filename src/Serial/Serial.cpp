// ������� ��� ������ � ����������� ������� � WINAPI
//
#include "Serial.h"

/// <summary> �������� ����� ��� ������ � ������ </summary>
/// <param name="hName"> ��������� �����. </param>
/// <param name="aPort"> ����� �����. </param>
/// <returns> 
/// true - ���� ������.
/// false - �� ������� ������� ����. 
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

///<summary> ������� �������� �����. </symmary>
///<param name="hName"> �������� �����. </param>
void ClosePort(HANDLE* hName)
{
	if (*hName != INVALID_HANDLE_VALUE)
		CloseHandle(*hName);
}

/// <summary> ������� ������ ������� � ����. </symmary>
/// <param name="Hname"> ��������� �����. </param>
/// <param name="mes"> ������ ��� ������. </param>
///<param name="numbytes"> ������ ���������, ����������� � ����. </param>
/// <returns> 
/// true - ������ ������� � ����.
/// false - ������ �� ������� � ����. 
/// </returns>
bool WriteinPort(HANDLE* hName, char mes[], size_t numbytes)
{
	DWORD wrtnbytes = 0;			// ������� ���������� ����.
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

/// <summary> ������� ������ �� ����� � ������ � ������. </summary>
/// <param name="hName"> ��������� �����. </param>
/// <param name="mes"> ������ ��� ������. </param>
///<param name="numbytes">������ ������ ��� ������.</param>
/// <returns> 
///  !=0 - ������ �� ����� �������� � ������. </returns>
///  0 - ������ �� ����� �� ���������. 
///</returns>
int ReadPort(HANDLE* hName, char mes[], size_t numbytes)
{
	static DWORD sizemes = 0;		//������� ����������� ����.
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
		// ��� ������ � � ������ ���� ������ 
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

/** @brief ������� �������� �����
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
	�� ��������, ���� ���������� � ���������� ��� ��������� � ����������� ������
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

/** @brief ������� �������� �����
*/
void SerialPort::ClosePort()
{
	CloseHandle(port);			
}

/** @brief ������� ������ � ����
*/
size_t SerialPort::WriteToPort(char *buf, size_t numbytes)
{
	DWORD wrtnbytes = 0;			// ������� ���������� ����.

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
	static DWORD sizemes = 0;		//������� ����������� ����.
	DWORD lpError;
	COMSTAT lpStat;
	int result = 0;

	if (!buf)
		return 0;

	ClearCommError(this->port, &lpError, &lpStat);
	// ��� ������ � � ������ ���� ������ 
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
	DWORD sizemes = 0;		//������� ����������� ����.
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
	������ �� ������ ����� ���� �� ������� ������ ������� � ������ �� ����� �������
	���� ��������� ���. ��� ���� � �����. � �� ����� ����� �������, �� ����������, ��� ������ �� ���������
	�� ��������� ������ � ������� ���������� ������� � ���������� ��.
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