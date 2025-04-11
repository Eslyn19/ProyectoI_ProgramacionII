#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "Usuario.h"
#include "Persistencia.h"
#define RUTA_USUARIOS "usuarios.txt"

class GestorPrestamo {
public:
	GestorPrestamo();
	~GestorPrestamo();
	void addUser(User* user);
	void displayUsers() const;
	void EditarUser(int index);
	bool existeID(const std::string& idBuscado);
	void mostrarUsuariosInactivos() const;
	void mostrarUsuariosActivos() const;

	User** getUsers() const;
	size_t getSize() const;
private:
    void resize();
    User** users;
	PersistenciaUsuarios persistencia;
    size_t size;
    size_t capacity;
};