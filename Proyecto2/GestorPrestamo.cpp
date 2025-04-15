#include "GestorPrestamo.h"

#include <iostream>

GestorPrestamo::GestorPrestamo() : size(0), capacity(10), prestamos(nullptr), cantidadPrestamos(0), capacidadPrestamos(0)
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

    delete[] prestamos, users;
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
    capacidadPrestamos = (capacidadPrestamos == 0) ? 10 : capacidadPrestamos * 2; // Duplicamos el tamaño cada vez
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
                std::cout << "\n> Nombre inválido. Debe tener más de 2 letras y solo contener letras.\n";
            }
            else {
                usuario->setName(nuevoValor);
                std::cout << "\n>Nombre actualizado.\n" << std::endl;
            }
            system("pause");
            break;

        case 2:
            std::cout << "\n> Ingrese nuevo apellido: ";
            std::getline(std::cin, nuevoValor);
            if (!esNombreValido(nuevoValor)) {
                std::cout << "\n> Apellido invalido. Debe tener mas de 2 letras y solo contener letras.\n";
            }
            else {
                usuario->setSurname(nuevoValor);
                std::cout << "\n> Apellido actualizado.\n" << std::endl;
            }
            system("pause");
            break;

        case 3:
            std::cout << "\n>Ingrese nuevo ID (9 digitos): ";
            std::getline(std::cin, nuevoValor);
            if (!esIDValido(nuevoValor)) {
                std::cout << "\n> ID invalido. Debe contener exactamente 9 numeros.\n";
            }
            else if (existeID(nuevoValor)) {
                std::cout << "\n> Ese ID ya existe. No se puede asignar.\n";
            }
            else {
                usuario->setID(nuevoValor);
                std::cout << "\n> ID actualizado.\n" << std::endl;
            }
            system("pause");
            break;

        case 0:
            std::cout << "\nSaliendo de la edición del usuario.\n";
            break;
        default:
            std::cout << "\n> Opcion no valida.\n";
        }
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

	for (size_t i = 0; i < size; ++i) {
		std::cout << users[i]->toString() << std::endl;
	}
}

void GestorPrestamo::mostrarUsuariosInactivos() const {
    std::cout << "- - Usuarios No Activos - -\n" << std::endl;

    bool hayInactivos = false;

    for (size_t i = 0; i < size; ++i) {
        if (!users[i]->getAvailable()) {
            std::cout << "Nombre: " << users[i]->getName() << '\n';
            std::cout << "Apellido/os: " << users[i]->getSurname() << "\n";
            std::cout << "ID: " << users[i]->getID() << "\n";
            std::cout << "Prestamo: " << users[i]->getMaterial() << std::endl << std::endl;
            hayInactivos = true;
        }

    }

    if (!hayInactivos) {
        std::cout << "No hay usuarios inactivos registrados.\n" << std::endl;
    }
}

void GestorPrestamo::mostrarUsuariosActivos() const {
	std::cout << "- - Usuarios Activos - -\n" << std::endl;
	
	bool hayActivos = false;

	for (size_t i = 0; i < size; ++i) {
		if (users[i]->getAvailable()) {
			std::cout << "Nombre: " << users[i]->getName() << '\n'
				<< "Apellido/os: " << users[i]->getSurname() << "\n";
			std::cout << "ID: " << users[i]->getID() << "\n";
            std::cout << "Prestamo: " << users[i]->getMaterial() << std::endl << std::endl;
			hayActivos = true;
		}
	}

	if (!hayActivos) {
		std::cout << "\nNo hay usuarios activos registrados.\n" << std::endl;
	}
}

User** GestorPrestamo::getUsers() const {
	return users;
}

size_t GestorPrestamo::getSize() const {
	return size;
}

void GestorPrestamo::HacerPrestamo(Material** materiales, size_t cantidadMateriales) {
    User* usuario = nullptr;
    std::string idUsuario;
    std::cout << "Ingrese el ID del usuario: ";
    std::cin >> idUsuario;
    std::cin.ignore();

    for (size_t i = 0; i < size; ++i) {
        if (users[i]->getID() == idUsuario) {
            usuario = users[i];
            break;
        }
    }

    if (usuario == nullptr) {
        std::cout << "Usuario no encontrado. No se puede realizar el prestamo.\n";
        return;
    }

    /* corregir
    if (usuario->getMaterial() == "!Material") {
        std::cout << "El usuario ya tiene un material prestado.\n";
        return;
    }*/

    // Mostrar materiales disponibles
    std::cout << "Materiales disponibles:\n";
    for (size_t i = 0; i < cantidadMateriales; ++i) {
        std::cout << i << ". " << materiales[i]->getTitulo() << " (Cantidad: " << materiales[i]->getCantidad() << ")\n";
    }

    // Elegir material por índice
    int indiceMaterial;
    std::cout << "Ingrese el indice del material: ";
    std::cin >> indiceMaterial;
    std::cin.ignore();

    if (indiceMaterial < 0 || static_cast<size_t>(indiceMaterial) >= cantidadMateriales) {
        std::cout << "Índice inválido. No se puede realizar el préstamo.\n";
        return;
    }

    Material* material = materiales[indiceMaterial];

    if (material->getCantidad() <= 0) {
        std::cout << "No hay materiales disponibles para prestar.\n";
        return;
    }

    // Realizar el préstamo
    usuario->setMaterial(material->getNumCatalogo());
    material->setCantidad(material->getCantidad() - 1);
   //td::string tipoMaterial = material->getTipo(); // Asegúrate que Material tiene un método getTipo()

    // Pedir fechas manualmente
    std::string fechaPrestamo, fechaDevolucion;
    std::cout << "Ingrese la fecha de préstamo (ej: 2025-04-14): ";
    std::getline(std::cin, fechaPrestamo);
    std::cout << "Ingrese la fecha de devolución (ej: 2025-04-21): ";
    std::getline(std::cin, fechaDevolucion);

    // Guardar en archivo .txt
    AgregarPrestamoArchivo(usuario->getID(), material->getNumCatalogo(), fechaPrestamo, fechaDevolucion, "libro");


    // Actualizar archivo de usuarios solo después del éxito del préstamo
    //ActualizarUsuarioArchivo(usuario->getID(), "Material"); buscar porque no cambia

    // Actualizar lista de préstamos en memoria
    cargarPrestamos(RUTA_PRESTAMOS);

    std::cout << "Préstamo realizado con éxito.\n";
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

            // Escribimos la línea actualizada (o sin cambios) en el archivo temporal
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


void GestorPrestamo::AgregarPrestamoArchivo(const std::string& idUsuario, const std::string& numCatalogo, const std::string& fechaPrestamo, const std::string& fechaDevolucion, const std::string &tipoMaterial) {
	std::ofstream archivo(RUTA_PRESTAMOS, std::ios::app);
	if (archivo.is_open()) {
		archivo << idUsuario << "," << numCatalogo << "," << fechaPrestamo << "," << fechaDevolucion << 
            ", " << tipoMaterial << "\n";
		archivo.close();
	}
	else {
		std::cerr << "Error al abrir el archivo de prestamos." << std::endl;
	}
}

void GestorPrestamo::cargarPrestamos(const std::string& rutaArchivo) {
    std::ifstream archivo(rutaArchivo);
    std::string linea;

    if (archivo.is_open()) {
        while (std::getline(archivo, linea)) {
            std::stringstream ss(linea);
            std::string idUsuario, numCatalogo, fechaPrestamo, fechaDevolucion, tipoMaterial;

            std::getline(ss, idUsuario, ',');
            std::getline(ss, numCatalogo, ',');
            std::getline(ss, fechaPrestamo, ',');
			std::getline(ss, fechaDevolucion, ',');
            std::getline(ss, tipoMaterial);

            // Redimensionar el arreglo de préstamos si es necesario
            if (cantidadPrestamos == capacidadPrestamos) {
                redimensionarPrestamo();
            }

            // Crear un nuevo objeto de préstamo y agregarlo al arreglo
            prestamos[cantidadPrestamos] = new Prestamo(idUsuario, numCatalogo, fechaPrestamo, fechaDevolucion, tipoMaterial);
            ++cantidadPrestamos;
        }
        archivo.close();
    }
    else {
        std::cerr << "Error al abrir el archivo de préstamos.\n";
    }
}

void GestorPrestamo::mostrarPrestamos() const {
    for (size_t i = 0; i < cantidadPrestamos; ++i) {
        std::cout << "Usuario ID: " << prestamos[i]->getIdUsuario() << "\n"
            << "Catalogo material: " << prestamos[i]->getNumCatalogo() << "\n"
            << "Fecha de prestamo: " << prestamos[i]->getFechaPrestamo() << "\n"
            << "Fecha de devolucion: " << prestamos[i]->getFechaDevolucion() << "\n"
			<< "Tipo de material: " << prestamos[i]->getTipoMaterial() << "\n" << std::endl;
    }
}

void GestorPrestamo::DevolverPrestamo(Material** materiales, size_t cantidadMateriales) {
    std::string idUsuario;
    std::cout << "Ingrese el ID del usuario que desea devolver el préstamo: ";
    std::cin >> idUsuario;
    std::cin.ignore();

    bool encontrado = false;
    std::string catalogoPrestado;

    // Buscar préstamo en el arreglo
    for (size_t i = 0; i < cantidadPrestamos; ++i) {
        if (prestamos[i]->getIdUsuario() == idUsuario) {
            encontrado = true;
            catalogoPrestado = prestamos[i]->getNumCatalogo();

            // Liberar memoria del préstamo
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
        std::cout << "No se encontró un préstamo para ese usuario.\n";
        return;
    }

    // Devolver el material al inventario
    for (size_t i = 0; i < cantidadMateriales; ++i) {
        if (materiales[i]->getNumCatalogo() == catalogoPrestado) {
            materiales[i]->setCantidad(materiales[i]->getCantidad() + 1);
            break;
        }
    }

    // Actualizar el archivo de préstamos
    std::ofstream archivoTemp("prestamos_temp.txt");
    if (archivoTemp.is_open()) {
        for (size_t i = 0; i < cantidadPrestamos; ++i) {
            archivoTemp << prestamos[i]->getIdUsuario() << ","
                << prestamos[i]->getNumCatalogo() << ","
                << prestamos[i]->getFechaPrestamo() << ","
                << prestamos[i]->getFechaDevolucion() << "\n"
			    << prestamos[i]->getTipoMaterial() << "\n";
        }
        archivoTemp.close();
        std::remove(RUTA_PRESTAMOS);
        std::rename("prestamos_temp.txt", RUTA_PRESTAMOS);
    }
    else {
        std::cerr << "No se pudo abrir el archivo temporal para actualizar los préstamos.\n";
    }

    // Actualizar estado del usuario en archivo (ponerlo como "No Material")
    ActualizarUsuarioArchivo(idUsuario, "No Material");

    std::cout << "Préstamo devuelto con éxito.\n";
}
