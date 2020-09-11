#include "Line.h"

///<summary> Получение строки с клавиатуры</summary>
///<param name="buf"> Указатель на указатель на буфер </param> 
/// <returns>
/// Длина массива
/// </returns>
unsigned long GetString(char** buf)
{
	char c;
	unsigned long i = 0;
	unsigned long max_cnt = 0;

	for (;;)
	{
		if ((i + 1) > MAX_PATH * max_cnt)
		{
			max_cnt++;
			char* temp = (char*)calloc((MAX_PATH * max_cnt), sizeof(char));
			if (temp)
			{
				ZeroMemory(temp, (MAX_PATH * max_cnt));
				memcpy(temp, *buf, sizeof(char) * i);
				if (*buf)
					free(*buf);
				*buf = temp;
			}
			else
			{
				return 0;
			}
		}

		c = getchar();

		if (c == '\n' && i == 0)	//при повторном входе в функцию, getchar первым байтом ловит "\n", пропускаем его
			continue;

		if (c == '\n')
			break;

		if (c == '\\')
		{
			(*buf)[i] = c;
			i++;
		}

		(*buf)[i] = c;

		i++;

	}

	return i;
}

/// <summary> Функция записи массива в файл в HEX </summary>
/// <param name="buffer"> Массив для записи. </param>
/// <param name="ffile"> Файл для записи. </param>
///<param name="length">Длинна массива. </param>
int write_to_file(char buffer[], FILE* ffile, size_t length)
{
	int tmp_lng;
	time_t		ttime;
	struct tm* ptr;
	char		buff_to_file[2000 * 4];

	if (!buffer)
		return 1;
	if (!ffile)
		return 1;
	if (!length)
		return 1;
	tmp_lng = 0;
	memset(buff_to_file, 0x00, (2000 * 4));
	for (int i = 0; i < length; i++)
	{
		tmp_lng += sprintf(&buff_to_file[tmp_lng], "%02x ", (unsigned char)buffer[i]);
	}
	ttime = time(NULL);
	ptr = localtime(&ttime);
	fwrite(("%s ", asctime(ptr)), 4, 6, ffile);
	fwrite(" - ", 3, 1, ffile);
	fwrite(buff_to_file, 1, tmp_lng, ffile);
	fwrite("\n", 1, 1, ffile);
	return 0;
}