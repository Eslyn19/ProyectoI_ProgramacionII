#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>    
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
#define RUTA_MATERIALES "materiales.txt"
#define RUTA_TEMP "usuarios_temp.txt"
#define RUTA_TMATERIALES "materiales_temp.txt"

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

	// Metodos de prestamo
	void ActualizarUsuarioArchivo(const std::string& idUsuario, const std::string& nuevoMaterial);
	std::string ObtenerTipoMaterial(Material* material);
	void actualizarArchivoUsuarios(const std::string& rutaArchivo);
	void actualizarDevolucionMaterial(const std::string& rutaArchivo);
	void AgregarPrestamoArchivo(const std::string& idUsuario, const std::string& numCatalogo, const std::string& fechaPrestamo, const std::string& fechaDevolucion, const std::string& tipoMaterial); // formato txt
	std::string IDDevolucion() const;
	std::string obtenerTituloPorIDUsuario(const std::string& idUsuario);
	void DevolverPrestamo(std::string idUsuario, Material** materiales, size_t cantidadMateriales);
	void sumarCantidadMaterialTXT(const std::string& tituloBuscado);
	void cargarPrestamos();
	void mostrarPrestamos() const;
	void MaterialesEnPrestamo() const;
	void MostrarLibroPrestamo() const;
	void MostrarRevistaPrestamo() const;
	void MostrarMaterialDigitalPrestamo() const;
	User** getUsers() const;
	size_t getSize() const;
	User* verificarUsuario();
	std::string seleccionarMaterial(Material** materiales, size_t cantidadMateriales);
	void procesarPrestamo(User* usuario, Material** materiales, size_t cantidadMateriales, const std::string& tituloMaterial);
	void actualizarCantidadMaterialTXT(const std::string& titulo);
	bool listaPrestamosVacia() const;

private:
    void resize();
	void redimensionarPrestamo();

	int indiceMaterialSeleccionado;
    User** users;
	PersistenciaUsuarios persistencia;
    size_t size;
    size_t capacity;
	Prestamo** prestamos;
	size_t cantidadPrestamos;
	size_t capacidadPrestamos;
};
