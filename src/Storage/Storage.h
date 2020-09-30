#pragma once


#include <vector>
#include <algorithm>
#include "../sniffer.h"

class Storage
{
private:
	std::vector<buffer_t> storage;
	size_t users = 0;
public:
	buffer_t *GetMesByPortId(HANDLE* port);
	void PushMes(buffer_t *mes, HANDLE *port);
	size_t operator++() { return users++; }
};