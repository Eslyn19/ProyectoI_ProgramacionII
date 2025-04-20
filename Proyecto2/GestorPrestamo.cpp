#include "GestorPrestamo.h"
#include "Libro.h"
#include "Revista.h"
#include "MaterialDigital.h"
#include "Persistencia.h"
#include <iostream>

#define WHITE_COLOR "\033[1;37m"
#define GREEN_COLOR "\033[1;32m"
#define CYAN_COLOR "\033[36m"

GestorPrestamo::GestorPrestamo() : size(0), capacity(10), prestamos(nullptr), cantidadPrestamos(0), capacidadPrestamos(0), indiceMaterialSeleccionado()
{
	users = new User * [capacity];
}

GestorPrestamo::~GestorPrestamo() {
	for (size_t i = 0; i < size; ++i) {
		delete users[i];
	}

    for (size_t i = 0; i < cantidadPrestamos; ++i) {
        delete prestamos[i];
    }

    delete[] prestamos;
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

void GestorPrestamo::redimensionarPrestamo() {
    capacidadPrestamos = (capacidadPrestamos == 0) ? 10 : capacidadPrestamos * 2; // Duplicamos el tama�o cada vez
    Prestamo** nuevoArray = new Prestamo * [capacidadPrestamos];
    for (size_t i = 0; i < cantidadPrestamos; ++i) {
        nuevoArray[i] = prestamos[i];
    }
    delete[] prestamos;
    prestamos = nuevoArray;
}

void GestorPrestamo::addUser(User* user) {
	if (size >= capacity) {
		resize();
	}
	users[size++] = user;
}

int GestorPrestamo::getIndicePorID(const std::string& idBuscado) const {
    for (int i = 0; i < size; ++i) {
        if (users[i]->getID() == idBuscado) {
            return i;
        }
    }
    return -1;
}

void GestorPrestamo::EditarUser(const std::string& id) {
    int index = getIndicePorID(id);
    if (index == -1) {
        std::cout << "Usuario no encontrado." << std::endl;
        return;
    }

    User* usuario = users[index];

    int opcion;
    do {
        std::cout << char(175) << " Seleccione el atributo a editar del Usuario:\n";
        std::cout << "\n1. Nombre" << std::endl;
        std::cout << "2. Apellido" << std::endl;
        std::cout << "3. ID" << std::endl;
        std::cout << "4. Estado (Activo/no activo)" << std::endl;
        std::cout << "0. Salir" << std::endl;
        std::cout << "\n> Ingrese su opcion: ";
        std::cin >> opcion;
        std::cin.ignore();

        std::string nuevoValor;

        switch (opcion) {
        case 1:
            std::cout << "\n>Ingrese nuevo nombre: ";
            std::getline(std::cin, nuevoValor);
            if (!esNombreValido(nuevoValor)) {
                std::cout << "\n> Nombre invalido. Debe tener mas de 2 letras y solo contener letras." << std::endl;
            }
            else {
                usuario->setName(nuevoValor);
                std::cout << GREEN_COLOR << "\n>Nombre actualizado.\n" << WHITE_COLOR << std::endl;
            }
            system("pause");
            break;

        case 2:
            std::cout << "\n> Ingrese nuevo apellido: ";
            std::getline(std::cin, nuevoValor);
            if (!esNombreValido(nuevoValor)) {
                std::cout << "\n> Apellido invalido. Debe tener mas de 2 letras y solo contener letras." << std::endl;
            }
            else {
                usuario->setSurname(nuevoValor);
                std::cout << GREEN_COLOR "\n> Apellido actualizado.\n" << WHITE_COLOR << std::endl;
            }
            system("pause");
            break;

        case 3:
            std::cout << "\n>Ingrese nuevo ID (9 digitos): ";
            std::getline(std::cin, nuevoValor);
            if (!esIDValido(nuevoValor)) {
                std::cout << "\n> ID invalido. Debe contener exactamente 9 numeros." << std::endl;
            }
            else if (existeID(nuevoValor)) {
                std::cout << "\n> Ese ID ya existe. No se puede asignar." << std::endl;
            }
            else {
                usuario->setID(nuevoValor);
                std::cout << GREEN_COLOR << "\n> ID actualizado.\n" << WHITE_COLOR << std::endl;
            }
            system("pause");
            break;

        case 4:
            if (usuario->getAvailable()) {
                if (usuario->getMaterial() != "ninguno") {
                    std::cout << "\n> No se puede marcar como 'No disponible' porque el usuario aun tiene un material prestado." << std::endl;
                }
                else {
                    usuario->setAvailability(false);
                    std::cout << GREEN_COLOR << "\n> Estado actualizado a 'No Activo'." << WHITE_COLOR << std::endl;
                }
            }
            else {
                usuario->setAvailability(true);
                std::cout << GREEN_COLOR << "\n> Estado actualizado a 'Activo'." << WHITE_COLOR << std::endl;
            }
            system("pause");
            break;

        case 0:
            std::cout << "\nSaliendo de la edici�n del usuario.\n";
            break;
        default:
            std::cout << "\n> Opcion no valida.\n";
        }
		system("cls");  
    } while (opcion != 0);
}

bool GestorPrestamo::esIDValido(const std::string& id) {
    return id.length() == 9 && std::all_of(id.begin(), id.end(), [](char c) {
        return std::isdigit(static_cast<unsigned char>(c));
    });
}

bool GestorPrestamo::esNombreValido(const std::string& nombre) {
    if (nombre.length() <= 2) return false;
    return std::all_of(nombre.begin(), nombre.end(), [](char c) {
        return std::isalpha(c) || std::isspace(c);
        });
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
		std::cout << "El sistema no tiene usuarios guardados." << std::endl;
	}

    std::cout << CYAN_COLOR << "---------------------------------------" << std::endl;
    std::cout << "|         Usuarios del sistema        |" << std::endl;
    std::cout << "---------------------------------------" << WHITE_COLOR << std::endl << std::endl;


	for (size_t i = 0; i < size; ++i) {
		std::cout << users[i]->toString() << std::endl;
	}
}

void GestorPrestamo::mostrarUsuariosInactivos() const {
    std::cout << CYAN_COLOR << "---------------------------------------" << std::endl;
    std::cout << "|         Usuarios Inactivos          |" << std::endl;
    std::cout << "---------------------------------------" << WHITE_COLOR << std::endl << std::endl;


    bool hayInactivos = false;

    for (size_t i = 0; i < size; ++i) {
        if (!users[i]->getAvailable()) {
            std::cout << "Nombre: " << users[i]->getName() << '\n';
            std::cout << "Apellido/os: " << users[i]->getSurname() << "\n";
            std::cout << "ID: " << users[i]->getID() << "\n";
            std::cout << "Material en prestamo: " << users[i]->getMaterial() << std::endl << std::endl;
            hayInactivos = true;
        }

    }

    if (!hayInactivos) {
        std::cout << "No hay usuarios inactivos registrados.\n" << std::endl;
    }
}

void GestorPrestamo::mostrarUsuariosActivos() const {
    std::cout << CYAN_COLOR << "---------------------------------------" << std::endl;
    std::cout << "|           Usuarios activos          |" << std::endl;
    std::cout << "---------------------------------------" << WHITE_COLOR << std::endl << std::endl;
	
	bool hayActivos = false;

	for (size_t i = 0; i < size; ++i) {
		if (users[i]->getAvailable()) {
			std::cout << "Nombre: " << users[i]->getName() << '\n'
				<< "Apellido/os: " << users[i]->getSurname() << "\n";
			std::cout << "ID: " << users[i]->getID() << "\n";
            std::cout << "Material en prestamo: " << users[i]->getMaterial() << std::endl << std::endl;
			hayActivos = true;
		}
	}

	if (!hayActivos) {
		std::cout << "No hay usuarios activos registrados.\n" << std::endl;
	}
}

User** GestorPrestamo::getUsers() const {
	return users;
}

size_t GestorPrestamo::getSize() const {
	return size;
}

/*
void GestorPrestamo::HacerPrestamo(Material** materiales, size_t cantidadMateriales) {
    User* usuario = nullptr;
    std::string idUsuario;
    std::cout << "\n>Ingrese el ID del usuario: ";
    std::cin >> idUsuario;
    std::cin.ignore();

    for (size_t i = 0; i < size; ++i) {
        if (users[i]->getID() == idUsuario) {
            usuario = users[i];
            break;
        }
    }

    if (usuario == nullptr) {
        std::cout << "\nUsuario no encontrado." << std::endl;
        return;
    }

	if (usuario->getAvailable() == false) {
		std::cout << "\nEl usuario no esta activo." << std::endl;
		return;
	}

    if (usuario->getMaterial() != "ninguno") {
        std::cout << "\nEl usuario ya tiene un material prestado." << std::endl;
        return;
    }

    std::cout << "\nMateriales disponibles:\n";
    for (size_t i = 0; i < cantidadMateriales; ++i) {
        std::cout << i << ". " << materiales[i]->getTitulo() << " (Cantidad: " << materiales[i]->getCantidad() << ")\n";
    }

    int indiceMaterial;
    std::cout << "Ingrese el indice del material: ";
    std::cin >> indiceMaterial;
    std::cin.ignore();

    if (indiceMaterial < 0 || static_cast<size_t>(indiceMaterial) >= cantidadMateriales) {
        std::cout << "Indice invalido. No se puede realizar el prestamo.\n";
        return;
    }

    Material* material = materiales[indiceMaterial];

    if (material->getCantidad() <= 0) {
        std::cout << "No hay materiales disponibles para prestar.\n";
        return;
    }

    std::time_t t = std::time(nullptr);
    std::tm now = {};
    localtime_s(&now, &t);

    std::ostringstream ossPrestamo;
    ossPrestamo << std::put_time(&now, "%Y-%m-%d");
    std::string fechaPrestamo = ossPrestamo.str();

    int diasPrestamo = material->getDiasPrestamo(); 
    now.tm_mday += diasPrestamo;
    std::mktime(&now);  // Normaliza la fecha

    std::ostringstream ossDevolucion;
    ossDevolucion << std::put_time(&now, "%Y-%m-%d");
    std::string fechaDevolucion = ossDevolucion.str();

    usuario->setMaterial(material->getTitulo());
    material->setCantidad(material->getCantidad() - 1);

    std::string tipoMaterial = ObtenerTipoMaterial(material);

    std::cout << "\nFecha del Prestamo: " << fechaPrestamo << std::endl;
    std::cout << "Fecha de Devolucion calculada automaticamente: " << fechaDevolucion << std::endl;

    AgregarPrestamoArchivo(usuario->getID(), material->getTitulo(), fechaPrestamo, fechaDevolucion, tipoMaterial);

    std::cout << "\nPrestamo realizado con exito.\n";
}
*/

User* GestorPrestamo::verificarUsuario() {
    std::string idUsuario;
    std::cout << "\n>Ingrese el ID del usuario: ";
    std::cin >> idUsuario;
    std::cin.ignore();

    for (size_t i = 0; i < size; ++i) {
        if (users[i]->getID() == idUsuario) {
            if (!users[i]->getAvailable()) {
                std::cout << "\nEl usuario no esta activo.\n";
                return nullptr;
            }
            if (users[i]->getMaterial() != "ninguno") {
                std::cout << "\nEl usuario ya tiene un material prestado.\n";
                return nullptr;
            }
            return users[i];
        }
    }

    std::cout << "\nUsuario no encontrado.\n";
    return nullptr;
}


std::string GestorPrestamo::seleccionarMaterial(Material** materiales, size_t cantidadMateriales) {
    std::cout << "\nMateriales disponibles:\n";
    for (size_t i = 0; i < cantidadMateriales; ++i) {
        std::cout << i << ". " << materiales[i]->getTitulo()
            << " (Cantidad: " << materiales[i]->getCantidad() << ")\n";
    }

    int indiceMaterial;
    std::cout << "Ingrese el indice del material: ";
    std::cin >> indiceMaterial;
    std::cin.ignore();

    if (indiceMaterial < 0 || static_cast<size_t>(indiceMaterial) >= cantidadMateriales) {
        std::cout << "Indice invalido.\n";
        return "";
    }

    if (materiales[indiceMaterial]->getCantidad() <= 0) {
        std::cout << "No hay materiales disponibles para prestar.\n";
        return "";
    }

    return materiales[indiceMaterial]->getTitulo();
}

void GestorPrestamo::procesarPrestamo(User* usuario, Material** materiales, size_t cantidadMateriales, const std::string& tituloMaterial) {
    Material* material = nullptr;

    for (size_t i = 0; i < cantidadMateriales; ++i) {
        if (materiales[i]->getTitulo() == tituloMaterial) {
            material = materiales[i];
            break;
        }
    }

    if (!material) {
        std::cout << "Material no encontrado.\n";
        return;
    }

    std::time_t t = std::time(nullptr);
    std::tm now = {};
    localtime_s(&now, &t);

    std::ostringstream ossPrestamo;
    ossPrestamo << std::put_time(&now, "%Y-%m-%d");
    std::string fechaPrestamo = ossPrestamo.str();

    now.tm_mday += material->getDiasPrestamo();
    std::mktime(&now);

    std::ostringstream ossDevolucion;
    ossDevolucion << std::put_time(&now, "%Y-%m-%d");
    std::string fechaDevolucion = ossDevolucion.str();

    usuario->setMaterial(tituloMaterial);
    material->setCantidad(material->getCantidad() - 1);

    std::string tipoMaterial = ObtenerTipoMaterial(material);
    AgregarPrestamoArchivo(usuario->getID(), tituloMaterial, fechaPrestamo, fechaDevolucion, tipoMaterial);

    // Aqu� puedes llamar al m�todo para guardar la nueva cantidad en el archivo
    // gestorInventario->actualizarCantidadMaterialPorTitulo(tituloMaterial);

    std::cout << "\nFecha del Prestamo: " << fechaPrestamo;
    std::cout << "\nFecha de Devolucion: " << fechaDevolucion;
    std::cout << "\nPrestamo realizado con exito.\n";

    system("pause");
}


void GestorPrestamo::ActualizarUsuarioArchivo(const std::string& idUsuario, const std::string& nuevoMaterial) {
    std::ifstream archivo(RUTA_USUARIOS);
    std::ofstream archivoTemp(RUTA_TEMP);
    std::string linea;

    if (archivo.is_open() && archivoTemp.is_open()) {
        while (std::getline(archivo, linea)) {
            std::stringstream ss(linea);
            std::string id, nombre, apellido, estado, material;
            std::getline(ss, nombre, ',');
            std::getline(ss, apellido, ',');
            std::getline(ss, id, ',');
            std::getline(ss, estado, ',');
            std::getline(ss, material);

            // Si encontramos al usuario, cambiamos su material
            if (id == idUsuario) {
                material = nuevoMaterial; // Actualizamos el material
            }

            // Escribimos la l�nea actualizada (o sin cambios) en el archivo temporal
            archivoTemp << nombre << "," << apellido << "," << id << "," << estado << "," << material << "\n";
        }

        archivo.close();
        archivoTemp.close();

        // Reemplazamos el archivo original con el archivo temporal
        std::remove(RUTA_USUARIOS);
        std::rename(RUTA_TEMP, RUTA_USUARIOS);
    }
    else {
        std::cerr << "Error al abrir el archivo de usuarios.\n";
    }
}

void GestorPrestamo::AgregarPrestamoArchivo(const std::string& idUsuario, const std::string& Titulo, const std::string& fechaPrestamo, const std::string& fechaDevolucion, const std::string &tipoMaterial) {
	std::ofstream archivo(RUTA_PRESTAMOS, std::ios::app);
	if (archivo.is_open()) {
		archivo << idUsuario << "," << Titulo << "," << fechaPrestamo << "," << fechaDevolucion << 
            "," << tipoMaterial << "\n";
		archivo.close();
	}
	else {
		std::cerr << "Error al abrir el archivo de prestamos." << std::endl;
	}
}

void GestorPrestamo::cargarPrestamos() {
    std::ifstream archivo(RUTA_PRESTAMOS);
    std::string linea;

    if (archivo.is_open()) {
        while (std::getline(archivo, linea)) {
            std::stringstream ss(linea);
            std::string idUsuario, Titulo, fechaPrestamo, fechaDevolucion, tipoMaterial;

            std::getline(ss, idUsuario, ',');
            std::getline(ss, Titulo, ',');
            std::getline(ss, fechaPrestamo, ',');
			std::getline(ss, fechaDevolucion, ',');
            std::getline(ss, tipoMaterial);

            // Redimensionar el arreglo de pr�stamos si es necesario
            if (cantidadPrestamos == capacidadPrestamos) {
                redimensionarPrestamo();
            }

            // Crear un nuevo objeto de pr�stamo y agregarlo al arreglo
            prestamos[cantidadPrestamos] = new Prestamo(idUsuario, Titulo, fechaPrestamo, fechaDevolucion, tipoMaterial);
            ++cantidadPrestamos;
        }
        archivo.close();
    }
}

void GestorPrestamo::mostrarPrestamos() const {
    if (size == 0) {
        std::cerr << "No hay prestamos de materiales" << std::endl;
    }

    for (size_t i = 0; i < cantidadPrestamos; ++i) {
        std::cout << "Usuario ID: " << prestamos[i]->getIdUsuario() << "\n"
            << "Titulo: " << prestamos[i]->getTitulo() << "\n"
            << "Fecha de prestamo: " << prestamos[i]->getFechaPrestamo() << "\n"
            << "Fecha de devolucion: " << prestamos[i]->getFechaDevolucion() << "\n"
			<< "Tipo de material: " << prestamos[i]->getTipoMaterial() << "\n" << std::endl;
    }
}

std::string GestorPrestamo::IDDevolucion() const {
	std::string idUsuario;
	std::cout << "\n>Ingrese el ID del usuario: ";
	std::cin >> idUsuario;
	std::cin.ignore();
	return idUsuario;
}

void GestorPrestamo::DevolverPrestamo(std::string idUsuario, Material** materiales, size_t cantidadMateriales) {
    bool encontrado = false;
    std::string catalogoPrestado;

    // Buscar pr�stamo en el arreglo
    for (size_t i = 0; i < cantidadPrestamos; ++i) {
        if (prestamos[i]->getIdUsuario() == idUsuario) {
            encontrado = true;
            catalogoPrestado = prestamos[i]->getTitulo();

            // Liberar memoria del pr�stamo
            delete prestamos[i];

            // Mover los elementos hacia la izquierda
            for (size_t j = i; j < cantidadPrestamos - 1; ++j) {
                prestamos[j] = prestamos[j + 1];
            }

            --cantidadPrestamos;
            break;
        }
    }

    if (!encontrado) {
        std::cout << "No se encontro un prestamo para ese usuario.\n";
        return;
    }

    // Devolver el material al inventario
    for (size_t i = 0; i < cantidadMateriales; ++i) {
        if (materiales[i]->getTitulo() == catalogoPrestado) {
            materiales[i]->setCantidad(materiales[i]->getCantidad() + 1);
            break;
        }
    }

    // Actualizar el archivo de pr�stamos
    std::ofstream archivoTemp(RUTA_TEMP);
    if (archivoTemp.is_open()) {
        for (size_t i = 0; i < cantidadPrestamos; ++i) {
            archivoTemp << prestamos[i]->getIdUsuario() << ","
                << prestamos[i]->getTitulo() << ","
                << prestamos[i]->getFechaPrestamo() << ","
                << prestamos[i]->getFechaDevolucion() << ","
			    << prestamos[i]->getTipoMaterial() << "\n";
        }
        archivoTemp.close();
        std::remove(RUTA_PRESTAMOS);
        std::rename(RUTA_TEMP, RUTA_PRESTAMOS);
    }
    else {
        std::cerr << "No se pudo abrir el archivo temporal para actualizar los prestamos.\n";
    }

    // Actualizar estado del usuario en archivo (ponerlo como "No Material")
    ActualizarUsuarioArchivo(idUsuario, "ninguno");

    for (size_t i = 0; i < capacity; ++i) {
        if (users[i]->getID() == idUsuario) {
            users[i]->setMaterial("ninguno");
            break;
        }
    }

    std::cout << "\nPrestamo devuelto con exito.\n";
    system("pause");
}

std::string GestorPrestamo::ObtenerTipoMaterial(Material* material) {
    if (dynamic_cast<Libro*>(material)) {
        return "libro";
    }
    else if (dynamic_cast<Revista*>(material)) {
        return "revista";
    }
    else if (dynamic_cast<MaterialDigital*>(material)) {
        return "digital";
    }
    return "desconocido";
}

void GestorPrestamo::actualizarArchivoUsuarios(const std::string& rutaArchivo) {
    std::ifstream archivoEntrada(rutaArchivo);
    std::ofstream archivoTemporal(RUTA_TEMP);

    if (!archivoEntrada.is_open() || !archivoTemporal.is_open()) {
        std::cerr << "Error al abrir los archivos." << std::endl;
        return;
    }

    std::string linea;
    while (std::getline(archivoEntrada, linea)) {
        std::istringstream ss(linea);
        std::string campo;
        std::string nuevaLinea;
        std::string nombreUsuario;
        bool esPrimerCampo = true;
        bool actualizado = false;

        int campoIndex = 0;
        while (std::getline(ss, campo, ',')) {
            if (campoIndex == 0) {
                nombreUsuario = campo;
            }

            if (!actualizado && campo == "ninguno") {
                for (int i = 0; i < size; ++i) {
                    if (users[i]->getName() == nombreUsuario) {
                        campo = users[i]->getMaterial();
                        actualizado = true;
                        break;
                    }
                }
            }

            if (!esPrimerCampo) {
                nuevaLinea += ",";
            }
            nuevaLinea += campo;
            esPrimerCampo = false;
            campoIndex++;
        }

        archivoTemporal << nuevaLinea << std::endl;
    }

    archivoEntrada.close();
    archivoTemporal.close();

    std::remove(rutaArchivo.c_str());
    std::rename(RUTA_TEMP, rutaArchivo.c_str());
}

void GestorPrestamo::actualizarDevolucionMaterial(const std::string& rutaArchivo) {
    std::ifstream archivoEntrada(rutaArchivo);
    std::ofstream archivoTemporal(RUTA_TEMP);
    
    if (!archivoEntrada.is_open() || !archivoTemporal.is_open()) {
        std::cerr << "Error al abrir los archivos." << std::endl;
        return;
    }

    std::string linea;
    while (std::getline(archivoEntrada, linea)) {
        std::istringstream ss(linea);
        std::string campo;
        std::string nuevaLinea;
        std::string idUsuario;
        bool esPrimerCampo = true;

        int campoIndex = 0;
        while (std::getline(ss, campo, ',')) {
            if (campoIndex == 0) {
                idUsuario = campo;
            }

            if (campoIndex == 2) { 
                for (int i = 0; i < size; ++i) {
                    if (users[i]->getID() == idUsuario) {
                        campo = "ninguno";
                        users[i]->setMaterial("ninguno");
                        break;
                    }
                }
            }

            if (!esPrimerCampo) {
                nuevaLinea += ",";
            }
            nuevaLinea += campo;
            esPrimerCampo = false;
            campoIndex++;
        }

        archivoTemporal << nuevaLinea << std::endl;
    }

    archivoEntrada.close();
    archivoTemporal.close();

    std::remove(rutaArchivo.c_str());
    std::rename(RUTA_TEMP, rutaArchivo.c_str());
}

void GestorPrestamo::MostrarLibroPrestamo() const {
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "|       Material libro en prestamo     |" << std::endl;
    std::cout << "----------------------------------------" << std::endl << std::endl;

	for (size_t i = 0; i < cantidadPrestamos; ++i) {
		if (prestamos[i]->getTipoMaterial() == "libro") {
			std::cout 
				<< "Titulo: " << prestamos[i]->getTitulo() << "\n"
				<< "Fecha de prestamo: " << prestamos[i]->getFechaPrestamo() << "\n"
				<< "Fecha de devolucion: " << prestamos[i]->getFechaDevolucion() << "\n" << std::endl;
		}
	}
}

void GestorPrestamo::MostrarRevistaPrestamo() const {
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "|     Material revista en prestamo     |" << std::endl;
    std::cout << "----------------------------------------" << std::endl << std::endl;

	for (size_t i = 0; i < cantidadPrestamos; ++i) {
		if (prestamos[i]->getTipoMaterial() == "revista") {
			std::cout
				<< "Titulo: " << prestamos[i]->getTitulo() << "\n"
				<< "Fecha de prestamo: " << prestamos[i]->getFechaPrestamo() << "\n"
				<< "Fecha de devolucion: " << prestamos[i]->getFechaDevolucion() << "\n" << std::endl;
		}
	}
}

void GestorPrestamo::MostrarMaterialDigitalPrestamo() const {
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "|     Material digital en prestamo     |" << std::endl;
    std::cout << "----------------------------------------" << std::endl << std::endl;

	for (size_t i = 0; i < cantidadPrestamos; ++i) {
		if (prestamos[i]->getTipoMaterial() == "digital") {
			std::cout 
				<< "Titulo: " << prestamos[i]->getTitulo() << "\n"
				<< "Fecha de prestamo: " << prestamos[i]->getFechaPrestamo() << "\n"
				<< "Fecha de devolucion: " << prestamos[i]->getFechaDevolucion() << "\n" << std::endl;
		}
	}
}

void GestorPrestamo::MaterialesEnPrestamo() const {
    std::cout << "----------------------------------" << std::endl;
    std::cout << "|     Materiales en prestamo     |" << std::endl;
    std::cout << "----------------------------------" << std::endl << std::endl;

	for (size_t i = 0; i < cantidadPrestamos; ++i) {
		std::cout << "Titulo del material: " << prestamos[i]->getTitulo() << "\n"
			<< "Tipo de material: " << prestamos[i]->getTipoMaterial() << "\n"
			<< "Fecha de prestamo: " << prestamos[i]->getFechaPrestamo() << "\n"
			<< "Fecha de devolucion: " << prestamos[i]->getFechaDevolucion() << "\n" << std::endl;
	}
}

void GestorPrestamo::actualizarCantidadMaterialTXT(const std::string& tituloBuscado) {
    std::ifstream archivoEntrada(RUTA_MATERIALES);
    std::ofstream archivoTemporal(RUTA_TMATERIALES);

    if (!archivoEntrada || !archivoTemporal) {
        std::cout << "Error abriendo el archivo." << std::endl;
        return;
    }

    std::string linea;
    while (std::getline(archivoEntrada, linea)) {
        std::istringstream ss(linea);
        std::string campos[20]; // hasta 20 campos por si acaso
        int index = 0;

        while (std::getline(ss, campos[index], ',') && index < 20) {
            index++;
        }

        // Titulo est� en campo 4, Cantidad est� en campo 1
        if (campos[4] == tituloBuscado) {
            int cantidad = std::stoi(campos[1]);  // campo 1 = cantidad
            if (cantidad > 0) {
                cantidad -= 1;
            }
            campos[1] = std::to_string(cantidad); // actualizamos cantidad correctamente

            // Escribimos todos los campos con coma
            for (int i = 0; i < index; ++i) {
                archivoTemporal << campos[i];
                if (i < index - 1) archivoTemporal << ",";
            }
            archivoTemporal << "\n";
        }
        else {
            archivoTemporal << linea << "\n";
        }
    }

    archivoEntrada.close();
    archivoTemporal.close();

    std::remove(RUTA_MATERIALES);
    std::rename(RUTA_TMATERIALES, RUTA_MATERIALES);
}

void GestorPrestamo::sumarCantidadMaterialTXT(const std::string& tituloBuscado) {
    std::ifstream archivoEntrada(RUTA_MATERIALES);
    std::ofstream archivoTemporal(RUTA_TMATERIALES);

    if (!archivoEntrada || !archivoTemporal) {
        std::cout << "Error abriendo el archivo de materiales.\n";
        return;
    }

    std::string linea;
    while (std::getline(archivoEntrada, linea)) {
        std::istringstream ss(linea);
        std::string campos[20];
        int index = 0;

        while (std::getline(ss, campos[index], ',') && index < 20) {
            index++;
        }

        // Titulo est� en campo 4, Cantidad en campo 1
        if (campos[4] == tituloBuscado) {
            int cantidad = std::stoi(campos[1]);
            cantidad += 1; // Aqu� sumamos
            campos[1] = std::to_string(cantidad);

            for (int i = 0; i < index; ++i) {
                archivoTemporal << campos[i];
                if (i < index - 1) archivoTemporal << ",";
            }
            archivoTemporal << "\n";
        }
        else {
            archivoTemporal << linea << "\n";
        }
    }

    archivoEntrada.close();
    archivoTemporal.close();

    std::remove(RUTA_MATERIALES);
    std::rename(RUTA_TMATERIALES, RUTA_MATERIALES);

    std::cout << "Cantidad del material actualizada correctamente (+1).\n";
}

std::string GestorPrestamo::obtenerTituloPorIDUsuario(const std::string& idUsuario) {
    for (size_t i = 0; i < cantidadPrestamos; ++i) {
        if (prestamos[i]->getIdUsuario() == idUsuario) {
            return prestamos[i]->getTitulo();
        }
    }
    return "";
}
