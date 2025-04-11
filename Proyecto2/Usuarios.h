#pragma once
#include "Usuario.h"
#include <fstream>
#include <string>
#include <sstream>

class Users {
public:
    Users();
    ~Users();
    void AddUser(User* user);
	User* getUser(int index) const;
    size_t getSize() const;

private:
    User** users;
    size_t size;
    size_t capacity;
    void resize();
};
