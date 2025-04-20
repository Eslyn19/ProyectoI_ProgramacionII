#include "Interfaz.h"

#define RED_COLOR "\033[1;31m"
#define WHITE_COLOR "\033[1;37m"
#define GREEN_COLOR "\033[1;32m"
#define BLUE_COLOR "\033[1;34m"
#define YELLOW_COLOR "\033[1;33m"
#define CYAN_COLOR "\033[36m"

// ------------------------------- Entradas del programa -----------------------------------
void Interfaz::Bienvenida() {
    std::cout << YELLOW_COLOR << "---- << Bienvenido al sistema de administracion de materiales >> ----" << WHITE_COLOR << std::endl << std::endl;
}

void Interfaz::MostrarMenu() {
    std::cout << "1. Inclusion de datos de materiales.\n";
    std::cout << "2. Modificacion de datos de materiales.\n";
    std::cout << "3. Reporte de inventario de materiales.\n" << std::endl;
    std::cout << "4. Inclusion de usuarios.\n";
    std::cout << "5. Modificacion de datos de usuarios.\n";
    std::cout << "6. Reporte de usuarios.\n" << std::endl;
    std::cout << "7. Registro de solicitudes de prestamo y devoluciones.\n";
    std::cout << "8. Reporte de materiales en prestamo (general y por tipo de material).\n";
    std::cout << "9. Reporte de prestamos por usuario.\n" << std::endl;
    std::cout << "0. Salir\n";
}

int Interfaz::OpcionMenu() {
    std::string input;
    int opcion;

    while (true) {
        std::cout << std::endl;
        std::cout << YELLOW_COLOR << char(175) << " Opcion: " << WHITE_COLOR;
        std::cin >> input;

        try {
            opcion = std::stoi(input);
            break; // éxito
        }
        catch (const std::invalid_argument&) {
            std::cout << "Entrada invalida. Por favor, ingresa un numero.\n";
        }
        catch (const std::out_of_range&) {
            std::cout << "Numero fuera del rango permitido.\n";
        }
    }

    return opcion;
}

void Interfaz::EsperarBorrar() {
	system("PAUSE");
	system("CLS");
} 

void Interfaz::Borrar() {
    system("CLS");
}

void Interfaz::GuardadoExitoso() {
    std::cout << BLUE_COLOR << "\n----------------------------------------" << std::endl;
    std::cout << "|            Guardado exitoso          |" << std::endl;
    std::cout << "----------------------------------------" << WHITE_COLOR << std::endl << std::endl;
}

void Interfaz::Farewell() {
	std::cout << BLUE_COLOR << "\n----------------------------------------" << std::endl;
	std::cout << "|         Gracias por usar el          |" << std::endl;
	std::cout << "|     sistema de administracion de     |" << std::endl;
	std::cout << "|             biblioteca.              |" << std::endl;
	std::cout << "----------------------------------------" << WHITE_COLOR << std::endl;
}

// ----------------------------------- Opcion 1 del menu -----------------------------------
void Interfaz::MenuElegirMaterial() {
    system("CLS");
    std::cout << CYAN_COLOR << "- - - - - - - - - - - -- - - - - - - - - -" << std::endl;
    std::cout << "|    Seleccione el material a crear...   |" << std::endl;
    std::cout << "- - - - - - - - - - - -- - - - - - - - - -" << WHITE_COLOR << std::endl;
    
    std::cout << "\n1) Libros" << std::endl;
    std::cout << "2) Revistas" << std::endl;
    std::cout << "3) Articulos digitales" << std::endl;
	std::cout << "0) Regresar" << std::endl << std::endl;
}

int Interfaz::ElegirTipoMaterial() {
    int Opc_mat;
    while (true) {
        try {
            std::cout << YELLOW_COLOR << char(175) << " Opcion: " << WHITE_COLOR;

            if (!(std::cin >> Opc_mat)) {
                std::cin.clear(); 
                std::cin.ignore(1000, '\n');
                throw MyException("Entrada no valida. Por favor, ingrese un numero.");
            }

            if (Opc_mat < 0 || Opc_mat > 3) {
                throw MyException("Opcion no valida. Debe ser entre 1 y 3.");
            }

            return Opc_mat;
        }
        catch (const MyException& e) {
            std::cout << e.what() << std::endl;
            system("cls");
            MenuElegirMaterial();
        }
    }
}

int Interfaz::Cantidad() {
    std::cin.clear();
    int _cant;

    while (true) {
        try {
            std::cout << char(175) << " Cantidad del elemento: ";
            std::cin >> _cant;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                std::cerr << "Error: Entrada invalida. Ingrese un numero entero." << std::endl;
                continue;
            }

            if (_cant <= 0 || _cant >= 99) {
                throw MyException("Error: La cantidad debe estar entre 1 y 99.");
            }

            break;
        }
        catch (const std::invalid_argument&) {
            std::cerr << "Error: Entrada invalida. Ingrese un numero entero." << std::endl;
        }
        catch (const std::out_of_range&) {
            std::cerr << "Error: Numero fuera de rango." << std::endl;
        }
        catch (const MyException& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    std::cout << std::endl;
    return _cant;
}

int Interfaz::Num_Clasificacion(){
    std::cin.clear();
    int NumClas;

    while (true) {
        try {
            std::cout << char(175) << " Numero de clasificacion: ";
            std::cin >> NumClas;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                throw std::invalid_argument("Error: Entrada invalida. Ingrese un numero entero.");
            }

            if (NumClas < 1 || NumClas >= 300) {
                throw MyException("Error: Numero de catalogo invalido. Debe ser un numero entre 1 y 300.");
            }

            break;
        }
        catch (const std::invalid_argument& e) {
            std::cerr << e.what() << std::endl;
        }
        catch (const MyException& e) {
            std::cerr << e.what() << std::endl;
        }
    }
	return NumClas;
}

std::string Interfaz::Num_Catalogo() {
	std::cin.clear();
	std::string _num_catalogo;

	while (true) {
		try {
			std::cout << std::endl << char(175) << " Numero de catalogo: ";
			std::getline(std::cin, _num_catalogo);

			if (_num_catalogo.empty()) {
				throw MyException("Error: El numero de catalogo no puede estar vacio.");
			}

			break;
		}
		catch (const MyException& e) {
			std::cerr << e.what() << std::endl;
		}
	}

	return _num_catalogo;
}

std::string Interfaz::Titulo() {
	std::cin.clear();
	std::string _titulo;

	while (true) {
		try {
            std::cout << std::endl << char(175) << " Titulo del libro: ";
			std::getline(std::cin, _titulo);

			if (_titulo.empty()) {
				throw MyException("Error: El titulo no puede estar vacio.");
			}

			break;
		}
		catch (const MyException& e) {
			std::cerr << e.what() << std::endl;
		}
	}

	return _titulo;
}

std::string Interfaz::Autor() {
	std::cin.clear();
	std::string _autor;

	while (true) {
		try {
            std::cout << std::endl << char(175) << " Autor del libro: ";
			std::getline(std::cin, _autor);

			if (_autor.empty()) {
				throw MyException("Error: El autor no puede estar vacio.");
			}

			break;
		}
		catch (const MyException& e) {
			std::cerr << e.what() << std::endl;
		}
	}

	return _autor;
}

std::string Interfaz::Palabra_Clave() {
    std::cin.clear();
    std::string _palabra_clave;

    while (true) {
        try {
            std::cout << std::endl << char(175) << " Palabra clave del libro: ";
            std::getline(std::cin, _palabra_clave);

            if (_palabra_clave.empty()) {
                throw MyException("Error: La palabra clave no puede estar vacía.");
            }

            // Verificar que no tenga números
            for (char c : _palabra_clave) {
                if (isdigit(static_cast<unsigned char>(c))) {
                    throw MyException("Error: La palabra clave no puede contener números.");
                }
            }

            break;
        }
        catch (const MyException& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    return _palabra_clave;
}

std::string Interfaz::Tipo_MaterialLibro() { return "Libro"; }

std::string Interfaz::Tipo_MaterialRevista() { return "Revista"; }

std::string Interfaz::Tipo_MaterialDigital() {
    std::cin.clear();
    std::string _estado;
    int opcion;

    std::cout << std::endl << char(175) << " Tipo Digital";
    while (true) {
        std::cout << "\n1) CD" << std::endl;
        std::cout << "2) DVD" << std::endl;
        std::cout << "3) BluRay" << std::endl;
        std::cout << "\n> ";
        std::cin >> opcion;

        try {
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                throw MyException("Entrada invalida. Intente nuevamente.");
            }

            switch (opcion) {
            case 1: _estado = "CD"; break;
            case 2: _estado = "DVD"; break;
            case 3: _estado = "BluRay"; break;
            default:
                throw MyException("Opcion invalida. Intente nuevamente.");
            }

            break;
        }
        catch (const MyException& e) {
            std::cerr << e.what() << std::endl;
        }
    }
    return _estado;
}

std::string Interfaz::Estado() {
    std::cin.clear();
    std::string _estado;
    int opcion;

    std::cout << std::endl << char(175) << " Estado del material";
    while (true) {
        std::cout << "\n1) Nuevo" << std::endl;
        std::cout << "2) Usado" << std::endl;
        std::cout << "3) Da" << char(164) << "ado" << std::endl;
        std::cout << "4) Perdido" << std::endl;
        std::cout << "\n> ";
        std::cin >> opcion;

        try {
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                throw MyException("Entrada invalida. Intente nuevamente.");
            }

            switch (opcion) {
            case 1: _estado = "Nuevo"; break;
            case 2: _estado = "Usado"; break;
            case 3: _estado = "Danado"; break;
            case 4: _estado = "Perdido"; break;
            default:
                throw MyException("Opcion invalida. Intente nuevamente.");
            }

            break;
        } catch (const MyException& e) {
            std::cerr << e.what() << std::endl;
        }
    }
    return _estado;
}

int Interfaz::Volumen() {
    int volumen;
    std::string entrada;

    while (true) {
        try {
            std::cout << std::endl << char(175) << " Volumen de la revista: ";
            std::getline(std::cin, entrada);

            // Validar que la entrada contiene solo dígitos
            if (entrada.empty() || entrada.find_first_not_of("0123456789") != std::string::npos) {
                throw MyException("Error: Solo se permiten numeros enteros entre 1 y 99.");
            }

            volumen = std::stoi(entrada);

            if (volumen < 1 || volumen > 99) {
                throw MyException("Error: El numero debe estar entre 1 y 99.");
            }

            break;
        }
        catch (const MyException& e) {
            std::cerr << e.what() << std::endl;
        }
        catch (const std::exception&) {
            std::cerr << "Error: Entrada no valida." << std::endl;
        }
    }

    return volumen;
}

int Interfaz::Numero() {
    int numero;
    std::string entrada;

    while (true) {
        try {
            std::cout << std::endl << char(175) << " Numero de la revista: ";
            std::getline(std::cin, entrada);

            // Validar que la entrada contiene solo digitos
            if (entrada.empty() || entrada.find_first_not_of("0123456789") != std::string::npos) {
                throw MyException("Error: Solo se permiten numeros enteros entre 1 y 99.");
            }

            numero = std::stoi(entrada);

            if (numero < 1 || numero > 99) {
                throw MyException("Error: El numero debe estar entre 1 y 99.");
            }

            break;
        }
        catch (const MyException& e) {
            std::cerr << e.what() << std::endl;
        }
        catch (const std::exception&) {
            std::cerr << "Error: Entrada no valida." << std::endl;
        }
    }

    return numero;
}

std::string Interfaz::Tipo() {
	std::cin.clear();
	std::string _tipo;

	while (true) {
		try {
            std::cout << std::endl << char(175) << " Tipo de material digital: ";
			std::getline(std::cin, _tipo);

			if (_tipo.empty()) {
				throw MyException("Error: El tipo no puede estar vacio.");
			}

			break;
		}
		catch (const MyException& e) {
			std::cerr << e.what() << std::endl;
		}
	}

	return _tipo;
}

std::string Interfaz::Formato() {
	std::cin.clear();
	std::string _formato;

	while (true) {
		try {
            std::cout << std::endl << char(175) << " Formato del material digital: ";
			std::getline(std::cin, _formato);

			if (_formato.empty()) {
				throw MyException("Error: El formato no puede estar vacio.");
			}

			break;
		}
		catch (const MyException& e) {
			std::cerr << e.what() << std::endl;
		}
	}

	return _formato;
}

bool Interfaz::Acceso() {
	std::cin.clear();
	bool acceso;
	int opcion;

    std::cout << std::endl << char(175) << " Acceso al material digital";
	while (true) {
		std::cout << "\n1) Habilitado" << std::endl;
		std::cout << "2) Deshabilitado" << std::endl;
		std::cout << "\n> ";
		std::cin >> opcion;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cerr << "Entrada invalida. Intente nuevamente." << std::endl;
			continue;
		}

		switch (opcion) {
		case 1: acceso = true; break;
		case 2: acceso = false; break;
		default:
			std::cerr << "Opcion invalida. Intente nuevamente." << std::endl;
			continue;
		}

		break;
	}
	return acceso;
}

void Interfaz::AgregandoLibroInterfaz() {
	system("cls");
	std::cout << CYAN_COLOR << "----------------------------------------" << std::endl;
	std::cout << "|         Agregando un libro           |" << std::endl;
	std::cout << "----------------------------------------" << WHITE_COLOR << std::endl << std::endl;
}

void Interfaz::AgregandoRevistaInterfaz() {
	system("cls");
	std::cout << CYAN_COLOR << "----------------------------------------" << std::endl;
	std::cout << "|        Agregando una revista         |" << std::endl;
	std::cout << "----------------------------------------" << WHITE_COLOR << std::endl << std::endl;
}

void Interfaz::AgregandoDigitalInterfaz() {
	system("cls");
	std::cout << CYAN_COLOR << "----------------------------------------" << std::endl;
	std::cout << "|     Agregando un material digital    |" << std::endl;
	std::cout << "----------------------------------------" << WHITE_COLOR << std::endl << std::endl;
}

// ----------------------------------- Opcion 2 del menu -----------------------------------
std::string Interfaz::BuscarPorTitulo() {
    std::string Titulo;
    std::cout << "Titulo del material: ";
    std::getline(std::cin, Titulo);

    try {
        if (Titulo.empty()) {
            throw MyException("El titulo no puede estar vacio.");
        }
    }
    catch (const MyException& e) {
        std::cerr << e.what() << std::endl;
        return "";
    }

    return Titulo;
}

void Interfaz::MenuEditarMaterial() {
    system("cls");
    std::cout << CYAN_COLOR << "----------------------------------------" << std::endl;
    std::cout << "|         Editar tipo material         |" << std::endl;
    std::cout << "----------------------------------------" << WHITE_COLOR << std::endl;

    std::cout << "\n1. Libros" << std::endl;
    std::cout << "2. Revistas" << std::endl;
    std::cout << "3. Materiales digitales" << std::endl;
    std::cout << "0. Volver al menu" << std::endl << std::endl;
}

int Interfaz::OpcionEditarTipo() {
    int opcion;
    while (true) {
        std::cout << YELLOW_COLOR << char(175) << " Opcion: " << WHITE_COLOR;
        if (!(std::cin >> opcion)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            MenuEditarMaterial();
            continue;
        }
        if (opcion < 0 || opcion > 3) {
            MenuEditarMaterial();
            continue;
        }
        return opcion;
    }
}

int Interfaz::ElegirIndiceMaterial() {
    int indice;
    std::cout << "Ingrese el indice del material a editar: ";

    try {
        if (!(std::cin >> indice)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            throw MyException("Entrada invalida. Debe ingresar un numero.");
        }
    }
    catch (const MyException& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    return indice;
}

void Interfaz::EditarMenuLibro() {
	system("cls");
	std::cout << "1. Editar cantidad\n";
	std::cout << "2. Editar numero de clasificacion\n";
	std::cout << "3. Editar numero de catalogo\n";
	std::cout << "4. Editar titulo\n";
	std::cout << "5. Editar autor\n";
	std::cout << "6. Editar palabra clave\n";
    std::cout << "7. Editar Tipo de material\n";
	std::cout << "8. Editar estado\n";
}

int Interfaz::OpcionEditarLibro() {
	int opcion;
	while (true) {
		std::cout << "\n> Opcion: ";
		if (!(std::cin >> opcion)) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			EditarMenuLibro();
			continue;
		}
		if (opcion < 1 || opcion > 8) {
			EditarMenuLibro();
			continue;
		}
		return opcion;
	}
}

void Interfaz::EditarMenuRevista() {
	system("cls");
	std::cout << "1. Editar cantidad\n";
	std::cout << "2. Editar numero de clasificacion\n";
	std::cout << "3. Editar numero de catalogo\n";
	std::cout << "4. Editar titulo\n";
	std::cout << "5. Editar autor\n";
	std::cout << "6. Editar palabra clave\n";
	std::cout << "7. Editar Tipo de material\n";
	std::cout << "8. Editar estado\n";
	std::cout << "9. Editar volumen\n";
	std::cout << "10. Editar numero\n";
}   

int Interfaz::OpcionEditarRevista() {
	int opcion;
	while (true) {
		std::cout << "\n> Opcion: ";
		if (!(std::cin >> opcion)) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			EditarMenuRevista();
			continue;
		}
		if (opcion < 1 || opcion > 10) {
			EditarMenuRevista();
			continue;
		}
		return opcion;
	}
}

void Interfaz::EditarMenuDigital() {
	system("cls");
	std::cout << "1. Editar cantidad\n";
	std::cout << "2. Editar numero de clasificacion\n";
	std::cout << "3. Editar numero de catalogo\n";
	std::cout << "4. Editar titulo\n";
	std::cout << "5. Editar autor\n";
	std::cout << "6. Editar palabra clave\n";
	std::cout << "7. Editar Tipo de material\n";
	std::cout << "8. Editar estado\n";
	std::cout << "9. Editar tipo\n";
	std::cout << "10. Editar formato\n";
	std::cout << "11. Editar acceso\n";
}
 
int Interfaz::OpcionEditarDigital() {
	int opcion;
	while (true) {
		std::cout << "\n> Opcion: ";
		if (!(std::cin >> opcion)) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			EditarMenuDigital();
			continue;
		}
		if (opcion < 1 || opcion > 11) {
			EditarMenuDigital();
			continue;
		}
		return opcion;
	}
}

void Interfaz::EditarLibro() {
    std::cout << GREEN_COLOR << "---------------------------------------" << std::endl;
    std::cout << "|    Editar libro en el sistema...     |" << std::endl;
    std::cout << "---------------------------------------" << WHITE_COLOR << std::endl << std::endl;
}

void Interfaz::EditarRevista() {
    std::cout << GREEN_COLOR << "---------------------------------------" << std::endl;
    std::cout << "|    Editar revista en el sistema...  |" << std::endl;
    std::cout << "---------------------------------------" << WHITE_COLOR << std::endl << std::endl;
}

void Interfaz::EditarDigital() { 
    std::cout << GREEN_COLOR << "------------------------------------------------" << std::endl;
    std::cout << "|    Editar material digital en el sistema...  |" << std::endl;
    std::cout << "------------------------------------------------" << WHITE_COLOR << std::endl << std::endl;
}

// ----------------------------------- Opcion 3 del menu -----------------------------------

void Interfaz::MensajeAgregarUsuario() {
    system("CLS");

	std::cout << RED_COLOR << "Aviso: El ID del usuario debe ser un numero de 9 digitos." << std::endl;
	std::cout << "El nombre y apellido del usuario deben contener solo letras." << std::endl;
	std::cout << "El ID no debe contener letras y no debe estar en uso." << std::endl;
	std::cout << "El nombre y apellido deben tener al menos 3 caracteres." << WHITE_COLOR << std::endl << std::endl;

    std::cout << "- - - - - - - - - - - -- - - - - - - - - -" << std::endl;
    std::cout << "|    Agregar nuevo usuario al sistema... |" << std::endl;
    std::cout << "- - - - - - - - - - - -- - - - - - - - - -";
}

std::string Interfaz::IDNuevoUsuario() {
    std::cin.clear();
    std::string newID;

    std::cin.clear();
    while (true) {
        try {
            std::cout << std::endl << char(169) << "> ID del usuario: ";
            std::getline(std::cin, newID);

            if (newID.length() != 9) {
                std::cout << "El ID debe tener entre 9 caracteres. Intenta de nuevo." << std::endl;
                continue;
            }

            bool tieneLetras = false;
            for (char c : newID) {
                if (!std::isdigit(c)) {
                    tieneLetras = true;
                    break;
                }
            }

            if (tieneLetras) {
                std::cout << "El ID no debe contener letras. Intenta de nuevo." << std::endl;
                continue;
            }
            break;
        }
        catch (const MyException& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    return newID;
}

std::string Interfaz::NombreNuevoUsuario()
{
    std::string newName;
    while (true)
    {
        try {
            std::cout << std::endl << std::endl << char(169) << "> Nombre del usuario: ";
            std::getline(std::cin, newName);

            bool esValido = true;
            for (char c : newName)
            {
                if (!std::isalpha(c) && c != ' ')
                {
                    esValido = false;
                    break;
                }
            }

            if (newName.length() < 3) {
                std::cout << "Error: nombre muy corto!" << std::endl;
                continue;
            }

            if (esValido && !newName.empty())
            {
                return newName;
            }
            else
            {
                std::cout << "Error: El nombre solo debe contener letras y espacios. Intente de nuevo." << std::endl;
            }
        }
        catch (const MyException& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}

std::string Interfaz::ApellidoNuevoUsuario()
{
    std::string newSurname;
    while (true)
    {
        try {
            std::cout << std::endl << char(169) << "> Apellidos del usuario: ";
            std::getline(std::cin, newSurname);

            bool esValido = true;
            for (char c : newSurname)
            {
                if (!std::isalpha(c) && c != ' ')
                {
                    esValido = false;
                    break;
                }
            }

            if (newSurname.length() < 3) {
                std::cout << "Error: apellido muy corto!" << std::endl;
                continue;
            }

            if (esValido && !newSurname.empty())
            {
                return newSurname;
            }
            else
            {
                std::cout << "Error: Apellido solo debe contener letras y espacios. Intente de nuevo." << std::endl;
            }
        }
        catch (const MyException& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}

bool Interfaz::DisponibleNuevoUsuario() { return true; }

void Interfaz::UsuarioGuardado() {
	std::cout << "\n-> Usuario guardado exitosamente! <-" << std::endl << std::endl;
    system("PAUSE");
	system("CLS");
}

// ----------------------------------- Opcion 4 del menu -----------------------------------

void Interfaz::MostrarEditarUsuario() {
    system("CLS");

    std::cout << RED_COLOR << "Aviso: Asegurese de que el ID del usuario sea correcto." << std::endl;
    std::cout << "El nombre y apellido del usuario deben contener solo letras." << std::endl;
    std::cout << "El ID no debe contener letras y debe estar en uso." << std::endl;
    std::cout << "El nombre y apellido deben tener al menos 3 caracteres." << WHITE_COLOR << std::endl << std::endl;

    std::cout << "- - - - - - - - - - - - - - - - - - - -" << std::endl;
    std::cout << "|    Editar usuario en el sistema...  |" << std::endl;
    std::cout << "- - - - - - - - - - - - - - - - - - - -" << std::endl;

    std::cout << "\n> ";
}

void Interfaz::WarningID() {
    std::cout << "Error: El ID ya está en uso. No se puede agregar el usuario." << std::endl;
}

// ----------------------------------- Opcion 5 del menu -----------------------------------
void Interfaz::OpcHacerPrestamoDevolucion() {
	system("CLS");
    std::cout << GREEN_COLOR << "---------------------------------------" << std::endl;
    std::cout << "|       Prestamos y Devoluciones      |" << std::endl;
    std::cout << "---------------------------------------" << WHITE_COLOR << std::endl << std::endl;
	std::cout << "1. Hacer prestamo\n";
	std::cout << "2. Hacer devolucion\n";
	std::cout << "0. Volver al menu\n";
}

int Interfaz::OpcionPrestamo() {
	int opc;
	while (true) {
		std::cout << "\n> Opcion: ";
		if (std::cin >> opc && opc >= 0 && opc <= 2) {
			return opc;
		}
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		std::cout << "\nOpcion no valida" << std::endl;
	}
}

void Interfaz::WarningExistingID() {
    std::cout << "\nEl ID ingresado no existe. No se puede editar." << std::endl;
    system("pause");
    system("cls");
}

// ----------------------------------- Opcion 6 del menu -----------------------------------

void Interfaz::ReporteInventarioMateriales() {
    system("CLS");
    std::cout << "- - Reporte de inventario de materiales detallado- -" << std::endl <<
        "------------------------------------------------------------------------\n\n";
}

int Interfaz::MostrarPorMaterial() {
	int opc;
    std::cout << GREEN_COLOR << "-------------------------------" << std::endl;
    std::cout << "|     Reporte de Materiales   |" << std::endl;
    std::cout << "-------------------------------" << WHITE_COLOR << std::endl << std::endl;

	std::cout << "1) Libros\n";
	std::cout << "2) Revistas\n";
	std::cout << "3) Materiales digitales\n";
	std::cout << "4) Todos\n";
	std::cout << "0) Regresar\n";

	while (true) {
		std::cout << "\n> Opcion: ";
		if (std::cin >> opc && opc >= 0 && opc <= 4) {
			return opc;
		}

		std::cin.clear();
		std::cin.ignore(1000, '\n');
		std::cout << "\nEntrada invalida. Por favor, ingrese un numero entre 0 y 4.\n";
	}
}

// ----------------------------------- Opcion 7 del menu -----------------------------------

void Interfaz::MostrarReporteUsuarios() {
    system("CLS");
    std::cout << GREEN_COLOR << "-----------------------------" << std::endl;
    std::cout << "|     Reporte de Usuarios   |" << std::endl;
    std::cout << "-----------------------------" << WHITE_COLOR << std::endl << std::endl;
}

int Interfaz::MostrarPorActividad() {
    int opc;
    std::cout << "1. Activos" << std::endl;
    std::cout << "2. Inactivos" << std::endl;
    std::cout << "3. Todos" << std::endl;
    std::cout << "0. Volver al menu" << std::endl;

    while (true) {
        std::cout << "\n> Opcion: ";
        if (std::cin >> opc && opc >= 0 && opc <= 3) {
            return opc;
        }

        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "\nEntrada inválida. Por favor, ingrese un numero entre 0 y 3.\n";
    }
}
// ----------------------------------- Opcion 8 del menu -----------------------------------
// 
int Interfaz::OpcionMostrarPrestamos() {
	system("CLS");
	int opc;
    std::cout << GREEN_COLOR << "-------------------------------------------------" << std::endl;
    std::cout << "|     Reporte de prestamos por general o tipo   |" << std::endl;
    std::cout << "-------------------------------------------------" << WHITE_COLOR << std::endl << std::endl;
	std::cout << "1. Reporte general de prestamos\n";
	std::cout << "2. Reporte por tipo de material\n";
	std::cout << "0. Volver al menu\n";
	while (true) {
		std::cout << "\n> Opcion: ";
		if (std::cin >> opc && opc >= 0 && opc <= 2) {
			return opc;
		}
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		std::cout << "\nEntrada inválida. Por favor, ingrese un numero entre 0 y 2.\n";
	}
}

void Interfaz::InterfazTipoPrestamos() {
	system("CLS");
    std::cout << GREEN_COLOR << "----------------------------------------" << std::endl;
    std::cout << "|     Tipo de Material en prestamo     |" << std::endl;
    std::cout << "----------------------------------------" << WHITE_COLOR << std::endl << std::endl;
	std::cout << "1. Libros\n";
	std::cout << "2. Revistas\n";
	std::cout << "3. Materiales digitales\n";
	std::cout << "0. Volver al menu\n";
}

int Interfaz::TipoPrestamo() {
	int opc;
	while (true) {
		std::cout << "\n> Opcion: ";
		if (std::cin >> opc && opc >= 0 && opc <= 3) {
			return opc;
		}
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		std::cout << "\nEntrada inválida. Por favor, ingrese un numero entre 0 y 3.\n";
	}
}

// ----------------------------------- Opcion 9 del menu -----------------------------------
void Interfaz::MostrarPrestamosPorUsuario() {
    std::cout << GREEN_COLOR << "------------------------------------------" << std::endl;
    std::cout << "|     Reporte de prestamos por usuarios   |" << std::endl;
    std::cout << "------------------------------------------" << WHITE_COLOR << std::endl << std::endl;
}

void Interfaz::InvalidEntry() {
    std::cerr << "La opción no es valida. Por favor, elige una opcion del menu." << std::endl;
}