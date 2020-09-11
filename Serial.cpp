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