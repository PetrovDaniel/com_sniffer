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
 онтейнер дл€ хранени€ сообщений
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
	ƒостать сообщение из хранилища
	*/
	void GetMesByPortId(HANDLE* port, _buffer_t &mes);
	/*
	ѕоложить сообщение в хранилище
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

public:
	inline _user_id_t init();

protected:
	elem storage[STORAGE_SIZE];

	size_t current_idx = 0;

	/*
	ƒвигаемс€ по массиву по кругу
	*/
	inline size_t getemptyidx();


	
	/*
	количество пользователей хранилища
	*/	
	_user_id_t users_cnt = 0;
};




class MesStorage : public RingStorage<_buffer_t>
{
public:
	void push(_user_id_t port, _buffer_t &mes);
	void pop(_user_id_t port, _buffer_t &mes);
};