#include "sniffer.h"


///<summary> Функция потока.</symmary>
///<param_name"x2">После завершиния первого потока и выполнения функции принимает значение "4".<param>
DWORD WINAPI Thread(PVOID pvParam)
{

	thread_t *strct = (thread_t *)pvParam;
	int i = 0;
	bool cmd = false;
	DWORD lpError;
	COMSTAT lpStat;
	DWORD sizemes = 0;		//Счетчик прочитанных байт.
	char mes_temp[2];
	memset(mes_temp, 0x00, 2);
	//((thread_t*)strct)->port // указатель на обработчик 
	for (;;)
	{
		if (strct->rx_buf->status == EMPTY)
		{
			ClearCommError(*(strct->port), &lpError, &lpStat);
			if (lpError == 0)
			{
				if (lpStat.cbInQue > 0)
				{
					

					for (int j = 0; j < lpStat.cbInQue; j++)
					{
						if(!(ReadFile(*(strct->port), mes_temp, 1, &sizemes, NULL)))
							break;

						if (mes_temp[0] == 0x0a)
						{
							cmd = true;
						}

						if (cmd)
						{
							strct->rx_buf->data[i] = mes_temp[0];
							i++;
							if (mes_temp[0] == 0x0d)
							{
								cmd = false;
								printf("\n%08lx\t", strct->port);
								for (int k = 0; k < i; k++)
								{
									printf("%02x ", (unsigned char)strct->rx_buf->data[k]);
								}
								strct->rx_buf->status = DATA_RECEIVE;
								strct->rx_buf->size = i;
								i = 0;
								break;
							}
						}
					}
				}
			}
		}

		if (strct->tx_buf->status == READY_TO_SEND)
		{
			WriteinPort(strct->port, strct->tx_buf->data, strct->tx_buf->size);
			strct->tx_buf->status = EMPTY;
		}

		Sleep(50);
	}

	return 0;
}

//int main(int argc, char *argv[])
// {
// 
// 	HANDLE port1 = NULL;										//Указатель порта.
// 	HANDLE port2 = NULL;
// 	DWORD ThreadID1;										//Идентификатор первого потока.
// 	DWORD ThreadID2;									//Идентификатор второго потока.
// 	char *buf = NULL;
// 	DWORD baudrate = 0;
// 
// 
// 	printf("Enter baudrate: ");
// 	if (!GetString(&buf))
// 	{
// 		printf("\n Error! \n");
// 		return 0;
// 	}
// 
// 	baudrate = (DWORD) atoi(buf);
// 
// 	// получаем имя первого порта и пытаемся открыть его
// 
// 
// 	printf("Enter name COM port first point: ");
// 	if (!GetString(&buf))
// 	{
// 		printf("\n Error! \n");
// 		return 0;
// 	}
// 
// 	if(!OpenPort(&port1, buf, baudrate))
// 		return 0;
// 
// 	// получаем имя первого порта и пытаемся открыть его
// 	printf("Enter name COM port second point: ");
// 	if (!GetString(&buf))
// 	{
// 		printf("\n Error! \n");
// 		return 0;
// 	}
// 
// 	if (!OpenPort(&port2, buf, baudrate))
// 		return 0;
// 
// 	thread_t port_1_strct;
// 	port_1_strct.port = &port1;
// 	thread_t port_2_strct;
// 	port_2_strct.port = &port2;
// 
// 	buffer_t out_port1_in_port_2;
// 	buffer_t out_port2_in_port_1;
// 
// 	// сохраняем указатели на буферы в обе структуры для потоков
// 	port_1_strct.tx_buf = &out_port2_in_port_1;
// 	port_1_strct.rx_buf = &out_port1_in_port_2;
// 
// 	port_2_strct.tx_buf = &out_port1_in_port_2;
// 	port_2_strct.rx_buf = &out_port2_in_port_1;
// 
// 	ZeroMemory(out_port1_in_port_2.data, BUFFERSIZE);
// 	ZeroMemory(out_port2_in_port_1.data, BUFFERSIZE);
// 
// 
// 	HANDLE hThread1 = CreateThread(NULL, 0, Thread, (PVOID)&port_1_strct, 0, &ThreadID1);	//Создание первого потока.
// 	HANDLE hThread2 = CreateThread(NULL, 0, Thread, (PVOID)&port_2_strct, 0, &ThreadID2);	//Создание второго потока.
// 	
// 	FILE *fq = fopen("LOG.txt", "w");
// 
// 
// 	for (;;)
// 	{
// 		if (out_port1_in_port_2.status == DATA_RECEIVE)
// 		{
// 			if (write_to_file(out_port1_in_port_2.data, fq, out_port1_in_port_2.size))
// 				printf("\n Error! Can't write to file \n");
// 			out_port1_in_port_2.status = READY_TO_SEND;
// 		}
// 
// 		if (out_port2_in_port_1.status == DATA_RECEIVE)
// 		{
// 			if (write_to_file(out_port2_in_port_1.data, fq, out_port2_in_port_1.size))
// 				printf("\n Error! Can't write to file \n");
// 			out_port2_in_port_1.status = READY_TO_SEND;
// 		}
// 
// 		Sleep(10);
// 	}
// 
// 	free(buf);
// 	ClosePort(&port1);
// 	ClosePort(&port2);
// 	fclose(fq);
// 
// 	return 0;
// }

int main()
{
	std::string port_name = "COM3";

	PortHandler sp(port_name, 9600);
	return 0;
}