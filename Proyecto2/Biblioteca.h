#pragma once
#include "GestorInventario.h"
#include "GestorPrestamo.h"
#include <string>
#define NINGUNO_MAT "ninguno"

class Biblioteca {
public:
	Biblioteca(std::string _nombre);
	void IniciarBiblioteca();
	~Biblioteca();
private:
	std::string nombre;
	GestorInventario* gestorInventario;
	GestorPrestamo* GestorPrestamos;
	PersistenciaUsuarios persistenciaUsuarios;
};