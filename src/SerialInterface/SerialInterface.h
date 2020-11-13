// абстрактный класс интерфейс для работы с сериальным портом
// задел на кроссплатформенность кода

#pragma once

#include <string>

class ISerialInterface
{
public:
//     virtual ISerialInterface() = 0;
//    virtual ~ISerialInterface() = 0;
    virtual size_t WriteToPort(char *buf, size_t numbutes) = 0;
    virtual size_t ReadFromPort(char *buf, size_t numbytes) = 0;
protected:
    virtual void OpenPort(const std::string &port_name, long baudrate) = 0;
    virtual void ClosePort() = 0;
};