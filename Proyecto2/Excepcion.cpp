#include "Excepcion.h"

MyException::MyException(const std::string& _message) : message(_message) {}

const char* MyException::what() const throw() { return message.c_str(); }
