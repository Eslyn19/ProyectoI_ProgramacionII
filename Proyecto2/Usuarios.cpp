#include "Usuarios.h"

Users::Users() : size(0), capacity(2) {
    users = new User * [capacity];
}

Users::~Users() {
    for (int i = 0; i < size; ++i) {
        delete users[i];
    }
    delete[] users;
}

void Users::AddUser(User* user) {
    if (size >= capacity) {
        resize();
    }
    users[size++] = user;
}

User* Users::getUser(int index) const {
	if (index < 0 || index >= size) {
		throw std::out_of_range("Index out of range");
	}
	return users[index];
}

size_t Users::getSize() const {
	return size;
}

void Users::resize() {
	capacity *= 2;
	User** newUsers = new User * [capacity];
	for (int i = 0; i < size; ++i) {
		newUsers[i] = users[i];
	}
	delete[] users;
	users = newUsers;
}
