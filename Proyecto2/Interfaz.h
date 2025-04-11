#pragma once
#include "Excepcion.h"
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <conio.h>
#include <stdio.h>

class Interfaz {
public:
	// Entrada del programa
	static void Bienvenida();
	static void MostrarMenu();
	static int OpcionMenu();
	static void EsperarBorrar();
	static void Borrar();
	static void GuardadoExitoso();

	// -----------Opcion 1 del menu------------
	static void MenuElegirMaterial();
	static int ElegirTipoMaterial();
	// Guardar componentes del material
	static int Cantidad();
	static int Num_Clasificacion();
	static std::string Num_Catalogo();
	static std::string Titulo();
	static std::string Autor();
	static std::string Palabra_Clave();
	static std::string Estado();
	// Guardar datos de material nuevo -> libro
	static std::string Tipo_MaterialLibro();
	// Guardar datos de material nuevo -> revista
	static std::string Tipo_MaterialRevista();
	static int Volumen();
	static int Numero();
	// Guardar datos de material nuevo -> digital
	static std::string Tipo_MaterialDigital();
	static std::string Tipo();
	static std::string Formato();
	static bool Acceso();

	// -----------Opcion 2 del menu------------
	static void MenuEditarMaterial();
	static int ElegirIndiceMaterial();
	static int OpcionEditarTipo();
	static void EditarMenuLibro();
	static int OpcionEditarLibro();
	static void EditarMenuRevista();
	static int OpcionEditarRevista();
	static void EditarMenuDigital();
	static int OpcionEditarDigital();
	static void EditarRevista();
	static void EditarLibro();
	static void EditarDigital();
	// -----------Opcion 3 del menu------------
	static void MensajeAgregarUsuario();
	static std::string IDNuevoUsuario();
	static std::string NombreNuevoUsuario();
	static std::string ApellidoNuevoUsuario();
	static bool DisponibleNuevoUsuario();
	static void UsuarioGuardado();
	// -----------Opcion 4 del menu------------
	static void MostrarEditarUsuario();
	// -----------Opcion 6 del menu------------
	static void ReporteInventarioMateriales();
	static int MostrarPorMaterial();
	// -----------Opcion 7 del menu------------
	static void MostrarReporteUsuarios();
	static int MostrarPorActividad();
};