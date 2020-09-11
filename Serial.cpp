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


	*hName = CreateFile(PortNameW, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);
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