#pragma once

				   
#include <vector>
#include <algorithm>
#include "../general_types.h"

#define STORAGE_SIZE 50

enum _Status
{
	_EMPTY,
	_FULL
};



/*
Контейнер для хранения сообщений
*/
class Storage
{
private:
	std::vector<_buffer_t> storage;
	size_t users;
public:
	Storage();
	~Storage();

	/*
	Достать сообщение из хранилища
	*/
	void GetMesByPortId(HANDLE* port, _buffer_t &mes);
	/*
	Положить сообщение в хранилище
	*/
  	void PushMes(_buffer_t &mes);

	size_t operator++() { return users++; }
};












template <typename T>
class RingStorage
{
	typedef struct
	{
		T data;
		unsigned long status = _EMPTY;
	}elem;

protected:
	elem storage[STORAGE_SIZE];

	size_t current_idx = 0;

	/*
	Двигаемся по массиву по кругу
	*/
	inline size_t getemptyidx();
};




class MesStorage : public RingStorage<_buffer_t>
{
public:
	void push(HANDLE *port, _buffer_t &mes);
	void pop(HANDLE *port, _buffer_t &mes);
};