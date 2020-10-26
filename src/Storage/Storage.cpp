#include "Storage.h"




Storage::Storage() : 
	users(0)
{
	storage.reserve(50);
}

Storage::~Storage()
{
	;
}

void Storage::GetMesByPortId(HANDLE* port, _buffer_t &mes)
{
	auto itr = find_if(storage.begin(), storage.end(), [=](_buffer_t mes)
		{
			return (mes.src != port);
		});


	if ((itr != storage.end()))
		mes = *itr;
	else
		mes.size = 0;
}

void Storage::PushMes(_buffer_t &mes)
{
	if(mes.size > 0)
		this->storage.push_back(mes);
}

template <typename T>
size_t RingStorage<T>:: getemptyidx()
{
	return (current_idx++) % STORAGE_SIZE;
}

void MesStorage :: push(HANDLE *port, _buffer_t &mes)
{
	storage[getemptyidx()].data = mes;
	storage[getemptyidx()].data.src = port;
	storage[getemptyidx()].status = _FULL;
}

void MesStorage::pop(HANDLE *port, _buffer_t &mes)
{
	mes.size = 0;

	for (size_t idx = 0; idx < STORAGE_SIZE; idx++)
	{
		if (storage[idx].status == _FULL && storage[idx].data.src == port)
		{
			mes = storage[idx].data;
		}
	}

	return;
}