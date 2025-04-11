#include "GestorPrestamo.h"

#include <iostream>

GestorPrestamo::GestorPrestamo() : size(0), capacity(10)
{
	users = new User * [capacity];
}

GestorPrestamo::~GestorPrestamo() {
	for (size_t i = 0; i < size; ++i) {
		delete users[i];
	}
	delete[] users;
}

void GestorPrestamo::resize() {
	capacity *= 2;
	User** newUsers = new User * [capacity];
	for (size_t i = 0; i < size; ++i) {
		newUsers[i] = users[i];
	}
	delete[] users;
	users = newUsers;
}

void GestorPrestamo::addUser(User* user) {
	if (size >= capacity) {
		resize();
	}
	users[size++] = user;
}

void GestorPrestamo::EditarUser(int index) {
    if (index < 0 || index >= size) {
        std::cerr << "Indice fuera de rango." << std::endl;
        return;
    }

    User* usuario = users[index];

    int opcion;
    do {
        std::cout << char(175) << " Seleccione el atributo a editar del Usuario:\n";
        std::cout << "\n1. Nombre" << std::endl;
        std::cout << "2. Apellido" << std::endl;
        std::cout << "3. ID" << std::endl;
        std::cout << "0. Salir" << std::endl;
        std::cout << "\n> Ingrese su opcion: ";
        std::cin >> opcion;
        std::cin.ignore();

        std::string nuevoValor;

        switch (opcion) {
        case 1:
            std::cout << "\n>Ingrese nuevo nombre: ";
            std::getline(std::cin, nuevoValor);
            usuario->setName(nuevoValor);
            std::cout << std::endl;
            break;
        case 2:
            std::cout << "\n>Ingrese nuevo apellido: ";
            std::getline(std::cin, nuevoValor);
            usuario->setSurname(nuevoValor);
            std::cout << std::endl;
            break;
        case 3:
            std::cout << "\n>Ingrese nuevo ID: ";
            std::getline(std::cin, nuevoValor);
            usuario->setID(nuevoValor);
            std::cout << std::endl;
            break;
        case 0:
            std::cout << "\nSaliendo de la edición del usuario.\n";
            break;
        default:
            std::cout << "\n>Opcion no valida." << std::endl;
        }
		std::cout << ">Usuario editado exitosamente." << std::endl;
        break;
    } while (opcion != 5);
}


bool GestorPrestamo::existeID(const std::string& idBuscado) {
	for (int i = 0; i < size; ++i) {
		if (users[i]->getID() == idBuscado) {
			return true;
		}
	}
	return false;
}

void GestorPrestamo::displayUsers() const {
	if (size == 0) {
		std::cout << "No hay materiales en el inventario." << std::endl;
	}

	for (size_t i = 0; i < size; ++i) {
		std::cout << users[i]->toString() << std::endl;
	}
}

void GestorPrestamo::mostrarUsuariosInactivos() const {
    std::cout << "- - Usuarios No Activos\n";
	std::cout << "------------------------\n";
    bool hayInactivos = false;

    for (size_t i = 0; i < size; ++i) {
        if (!users[i]->getAvailable()) {
            std::cout << "Nombre: " << users[i]->getName() << '\n'
                      << "Apellido/os: " << users[i]->getSurname() << "\n";
            std::cout << "ID: " << users[i]->getID() << "\n";
            std::cout << "Estado: No Activo\n\n";
            hayInactivos = true;
        }

    }

    if (!hayInactivos) {
        std::cout << "No hay usuarios inactivos registrados.\n";
    }
}

void GestorPrestamo::mostrarUsuariosActivos() const {
	std::cout << "- - Usuarios Activos\n";
	std::cout << "------------------------\n";
	bool hayActivos = false;

	for (size_t i = 0; i < size; ++i) {
		if (users[i]->getAvailable()) {
			std::cout << "Nombre: " << users[i]->getName() << '\n'
				<< "Apellido/os: " << users[i]->getSurname() << "\n";
			std::cout << "ID: " << users[i]->getID() << "\n";
			std::cout << "Estado: Activo\n\n";
			hayActivos = true;
		}
	}

	if (!hayActivos) {
		std::cout << "No hay usuarios activos registrados.\n";
	}
}

User** GestorPrestamo::getUsers() const {
	return users;
}

size_t GestorPrestamo::getSize() const {
	return size;
}
