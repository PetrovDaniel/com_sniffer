#pragma once

#include <cstddef>
#include "../general_types.h"

#define STORAGE_SIZE 50

enum _Status
{
	_EMPTY,
	_FULL
};

template <typename T>
class RingStorage
{
	typedef struct
	{
		T data;
		unsigned long status = _EMPTY;
		_user_id_t user_id;
	}elem;

public:
	
	_user_id_t init();
	
	void pop(_user_id_t user_id, T &data);
	
	void push(_user_id_t user_id, T &data);

protected:
	elem storage[STORAGE_SIZE];

	size_t current_idx = 0;

	/*
	Двигаемся по массиву по кругу
	*/
	inline size_t getemptyidx();


	
	/*
	количество пользователей хранилища
	*/	
	_user_id_t users_cnt = 0;
};


/*
Реализация методов шаблонного класса должна быть в одном файле с декларацией!
*/
template <typename T>
size_t RingStorage<T>::getemptyidx()
{
	return (current_idx = (current_idx++) % STORAGE_SIZE);
}

template <typename T>
_user_id_t RingStorage<T>::init()
{
	return users_cnt++;
}

template <typename T>
void RingStorage<T>::pop(_user_id_t user_id, T& data)
{
	size_t idx = getemptyidx();
	storage[idx].data = data;
	storage[idx].user_id = user_id;
	storage[idx].status = _FULL;

	return;
}

template <typename T>
void RingStorage<T>::push(_user_id_t user_id, T& data)
{
	memset(&data, 0, sizeof(T));

	for (size_t idx = 0; idx < STORAGE_SIZE; idx++)
	{
		size_t last_elem = (current_idx - idx) % STORAGE_SIZE;	// идем в обратную сторону от последнего заполненного элемента

		if (storage[last_elem].user_id != user_id && storage[last_elem].status == _FULL)
		{
			data = storage[last_elem].data;
			storage[last_elem].status = _EMPTY;
		}
	}

	return;
}