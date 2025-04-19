#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>   // Para std::all_of
#include <cctype>      // Para ::isdigit, ::isalpha, ::isspace
#include <ctime>
#include <iomanip>
#include <sstream>

#include "Usuario.h"
#include "Usuarios.h"
#include "Persistencia.h"
#include "Material.h"
#include "Prestamo.h"
#define RUTA_USUARIOS "usuarios.txt"
#define RUTA_PRESTAMOS "prestamos.txt"
#define RUTA_TEMP "usuarios_temp.txt"
#define FECHA_PRESTAMO "2025-04-19"

class GestorPrestamo {
public:
	GestorPrestamo();
	~GestorPrestamo();
	void addUser(User* user);
	void displayUsers() const;
	void EditarUser(const std::string& id);
	bool existeID(const std::string& idBuscado);

	int getIndicePorID(const std::string& idBuscado) const;
	bool esIDValido(const std::string& id);
	bool esNombreValido(const std::string& nombre);

	void mostrarUsuariosInactivos() const;
	void mostrarUsuariosActivos() const;

	// metodos para prestamos
	void HacerPrestamo(Material** materiales, size_t cantidadMateriales);
	void ActualizarUsuarioArchivo(const std::string& idUsuario, const std::string& nuevoMaterial); // actualiza usuarios.txt con material
	std::string ObtenerTipoMaterial(Material* material);
	void actualizarArchivoUsuarios(const std::string& rutaArchivo);
	void actualizarDevolucionMaterial(const std::string& rutaArchivo);


	void AgregarPrestamoArchivo(const std::string& idUsuario, const std::string& numCatalogo, const std::string& fechaPrestamo, const std::string& fechaDevolucion, const std::string& tipoMaterial); // formato txt
	void DevolverPrestamo(Material** materiales, size_t cantidadMateriales);
	void cargarPrestamos(); // del txt
	void mostrarPrestamos() const;




	User** getUsers() const;
	size_t getSize() const;
private:
    void resize();
	void redimensionarPrestamo();

    User** users;
	PersistenciaUsuarios persistencia;
    size_t size;
    size_t capacity;
	Prestamo** prestamos;
	size_t cantidadPrestamos;
	size_t capacidadPrestamos;
};
