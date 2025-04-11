#include "Excepcion.h"

// Constructor
MyException::MyException(const std::string& _message) : message(_message) {}

// Mensaje brindado por la excepci�n
const char* MyException::what() const throw() { return message.c_str(); }
