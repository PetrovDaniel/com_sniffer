#include "Storage.h"




// Storage::Storage() : 
// 	users(0)
// {
// 	storage.reserve(50);
// }
// 
// Storage::~Storage()
// {
// 	;
// }
// 
// void Storage::GetMesByPortId(HANDLE* port, _buffer_t &mes)
// {
// 	auto itr = find_if(storage.begin(), storage.end(), [=](_buffer_t mes)
// 		{
// 			return (mes.src != port);
// 		});
// 
// 
// 	if ((itr != storage.end()))
// 		mes = *itr;
// 	else
// 		mes.size = 0;
// }
// 
// void Storage::PushMes(_buffer_t &mes)
// {
// 	if(mes.size > 0)
// 		this->storage.push_back(mes);
// }










// template <typename T>
// size_t RingStorage<T>:: getemptyidx()
// {
// 	return (current_idx = (current_idx++) % STORAGE_SIZE);
// }
// 
// template <typename T>
// size_t RingStorage<T>:: init()
// {
// 	return users_cnt++;
// }
// 
// template <typename T>
// void RingStorage<T>::pop(_user_id_t user_id, T &data)
// {
// 	size_t idx = getemptyidx();
// 	storage[idx].data = data;
// 	storage[idx].user_id = user_id;
// 	storage[idx].status = _FULL;
// 
// 	return;
// }
// 
// template <typename T>
// void RingStorage<T>::push(_user_id_t user_id, T &data)
// {
// 	memset(data, NULL, sizeof(T));
// 
// 	for (size_t idx = 0; idx < STORAGE_SIZE; idx++)
// 	{
// 		size_t last_elem = (current_idx - idx) % STORAGE_SIZE;
// 
// 		if (storage[last_elem].user_id != user_id && storage[last_elem].status == _FULL)
// 		{
// 			data = storage[last_elem].data;
// 			storage[last_elem].status = _EMPTY;
// 		}
// 	}
// 
// 	return;
// }

// void MesStorage :: push(_user_id_t port, _buffer_t &mes)
// {
// 	size_t idx = getemptyidx();
// 	storage[idx].data = mes;
// 	storage[idx].user_id = port;
// 	storage[idx].status = _FULL;
// }


//!!! @warn !!!! данная функция работает корректно только с двумя пользователями
// void MesStorage::pop(_user_id_t port, _buffer_t &mes)
// {
// 	mes.size = 0;
// 
// 	for (size_t idx = 0; idx < STORAGE_SIZE; idx++)
// 	{
// 		if (storage[idx].status == _FULL && storage[idx].data.src != port)
// 		{
// 			mes = storage[idx].data;
// 			storage[idx].status = _EMPTY;
// 		}
// 	}
// 
// 	return;
// }