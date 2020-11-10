#pragma once
// Класс читает сообщения из порта и упаковывает в структуру 

#include "../SerialInterface/SerialInterface.h"
#include "../Serial/Serial.h"

#include <memory>

class DataLinkLayer
{

private:
    /* data */
    std::unique_ptr<ISerialInterface> port;
    //ISerialInterface port;
public:
    DataLinkLayer(const std::string &port_name, long baudrate);
    ~DataLinkLayer();
    size_t WriteMes(_buffer_t &mes);
    size_t ReadMes(_buffer_t &mes);
};