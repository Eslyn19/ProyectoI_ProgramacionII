#pragma once
#include <exception>
#include <string>

class MyException : public std::exception
{
public:
    MyException(const std::string& _message);
    const char* what() const throw();

private:
    std::string message;
};