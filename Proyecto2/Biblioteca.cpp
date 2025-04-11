#include "Biblioteca.h"
#include "Interfaz.h"
#include "Libro.h"
#include "Persistencia.h"
#include "Prestamos.h"
#include "Revista.h"
#include "MaterialDigital.h"

Biblioteca::Biblioteca(std::string _nombre) : nombre(_nombre) {
	gestorInventario = new GestorInventario();
	gestorInventario->loadFromFile(RUTA_ARCHIVO);

    GestorPrestamos = new GestorPrestamo();
    size_t cantidad = 0;
    size_t capacidad = 0;
    User** usuariosCargados = persistenciaUsuarios.cargarUsuarios(RUTA_USUARIOS, cantidad, capacidad);
    for (size_t i = 0; i < cantidad; ++i) {
        GestorPrestamos->addUser(usuariosCargados[i]);
    }
}

void Biblioteca::IniciarBiblioteca() {
    Interfaz::Bienvenida();
    Interfaz::MostrarMenu();

    while (true) {
        int opcion = Interfaz::OpcionMenu();
        if (opcion == 0) {
            std::cout << "Saliendo de la Biblioteca...\n";
            return;
        }
        else if (opcion == 1) {
            Interfaz::MenuElegirMaterial();
            int tipoMaterial = Interfaz::ElegirTipoMaterial();

            switch (tipoMaterial) {
            case 1: {
                Interfaz::Borrar();
                std::cout << "Agregando un libro...\n";
                int cantidad = Interfaz::Cantidad();
                int numClasificacion = Interfaz::Num_Clasificacion();
                std::cin.ignore();
                std::string numCatalogo = Interfaz::Num_Catalogo();
                std::string titulo = Interfaz::Titulo();
                std::string autor = Interfaz::Autor();
                std::string palabraClave = Interfaz::Palabra_Clave();
                std::string tipoMaterialStr = Interfaz::Tipo_MaterialLibro();
                std::string estado = Interfaz::Estado();

                gestorInventario->addMaterial(new Libro(cantidad, numClasificacion, numCatalogo, titulo, autor, palabraClave, tipoMaterialStr, estado));
                gestorInventario->saveToFile(RUTA_ARCHIVO);
                Interfaz::GuardadoExitoso();
                Interfaz::EsperarBorrar();
                break;
            }

            case 2: {
                Interfaz::Borrar();
                std::cout << "Agregando una revista...\n";
                int cantidad = Interfaz::Cantidad();
                int numClasificacion = Interfaz::Num_Clasificacion();
                std::cin.ignore();
                std::string numCatalogo = Interfaz::Num_Catalogo();
                std::string titulo = Interfaz::Titulo();
                std::string autor = Interfaz::Autor();
                std::string palabraClave = Interfaz::Palabra_Clave();
                std::string tipoMaterialStr = Interfaz::Tipo_MaterialRevista();
                std::string estado = Interfaz::Estado();
                std::cin.ignore();
                int volumen = Interfaz::Volumen();
                int numero = Interfaz::Numero();

                gestorInventario->addMaterial(new Revista(cantidad, numClasificacion, numCatalogo, titulo, autor, palabraClave, tipoMaterialStr, estado, volumen, numero));
                gestorInventario->saveToFile(RUTA_ARCHIVO);
                Interfaz::GuardadoExitoso();
                Interfaz::EsperarBorrar();
                break;
            }

            case 3: {
                Interfaz::Borrar();
                std::cout << "Agregando un material digital...\n";
                int cantidad = Interfaz::Cantidad();
                int numClasificacion = Interfaz::Num_Clasificacion();
                std::cin.ignore();
                std::string numCatalogo = Interfaz::Num_Catalogo();
                std::string titulo = Interfaz::Titulo();
                std::string autor = Interfaz::Autor();
                std::string palabraClave = Interfaz::Palabra_Clave();
                std::string tipoMaterialStr = Interfaz::Tipo_MaterialDigital();
                std::string estado = Interfaz::Estado();
                std::cin.ignore();
                std::string tipo = Interfaz::Tipo();
                std::cin.ignore();
                std::string formato = Interfaz::Formato();
                bool acceso = Interfaz::Acceso();

                gestorInventario->addMaterial(new MaterialDigital(cantidad, numClasificacion, numCatalogo, titulo, autor, palabraClave, tipoMaterialStr, estado, tipo, formato, acceso));
                gestorInventario->saveToFile(RUTA_ARCHIVO);
                Interfaz::GuardadoExitoso();
                Interfaz::EsperarBorrar();
                break;
            }

            default:
                std::cout << "Tipo de material no valido.\n";
                break;
            }
        }

        else if (opcion == 2) {
            Interfaz::MenuEditarMaterial();
            int tipo = Interfaz::OpcionEditarTipo();

            switch (tipo) {
            case 0:
                Interfaz::Borrar();
                break;

            case 1:
                Interfaz::Borrar();
                Interfaz::EditarLibro(); 
                gestorInventario->mostrarMaterialesPorTipo(LIBRO); 
                {
                    int indice = Interfaz::ElegirIndiceMaterial(); 
                    system("cls"); 
                    gestorInventario->displayPos(indice); 
                    gestorInventario->editarMaterial(indice); 
                    Interfaz::EsperarBorrar(); 
                }
                break;

            case 2:
                Interfaz::Borrar(); 
                Interfaz::EditarRevista(); 
                gestorInventario->mostrarMaterialesPorTipo(REVISTA); 
                {
                    int indice = Interfaz::ElegirIndiceMaterial(); 
                    system("cls"); 
                    gestorInventario->displayPos(indice);  
                    gestorInventario->editarMaterial(indice); 
                    Interfaz::EsperarBorrar(); 
                }
                break;

            case 3:
                Interfaz::Borrar();
                Interfaz::EditarDigital();
                gestorInventario->mostrarMaterialesPorTipo(MATERIAL_DIGITAL);
                {
                    int indice = Interfaz::ElegirIndiceMaterial();
                    system("cls");
                    gestorInventario->displayPos(indice);
                    gestorInventario->editarMaterial(indice);
                    Interfaz::EsperarBorrar();
                }
                break;

            default:
                std::cout << "\n> Opción no válida.\n";
                break;
            }

            gestorInventario->saveToFile(RUTA_ARCHIVO);
        }

        else if (opcion == 3) {
            std::cin.ignore();
            Interfaz::MensajeAgregarUsuario(); 
              
            std::string _nuevoNombre = Interfaz::NombreNuevoUsuario();
            std::string _nuevoApellido = Interfaz::ApellidoNuevoUsuario();
            std::string _nuevoID = Interfaz::IDNuevoUsuario();
            bool estado = GestorPrestamos->existeID(_nuevoID);
            
            if (estado) {
                std::cout << "Error: El ID ya está en uso. No se puede agregar el usuario.\n";
                Interfaz::EsperarBorrar();
            }
            else {
                // Si no existe, se agrega el usuario
                bool _estaActivo = Interfaz::DisponibleNuevoUsuario();
                GestorPrestamos->addUser(new User(_nuevoNombre, _nuevoApellido, _nuevoID, _estaActivo, "No Material"));
                persistenciaUsuarios.guardarUsuarios(RUTA_USUARIOS, GestorPrestamos->getUsers(), GestorPrestamos->getSize()); 

                Interfaz::UsuarioGuardado();
            }
        }
        else if (opcion == 4) {
            std::cin.ignore(); 
            Interfaz::Borrar(); 
            Interfaz::MostrarEditarUsuario();
            GestorPrestamos->displayUsers(); 

            int indice;
            std::cout << "\n> Ingrese el indice del usuario que desea editar: ";
            std::cin >> indice;
            std::cin.ignore(); 

            if (indice < 0 || indice >= GestorPrestamos->getSize()) { 
                std::cout << "\nIndice invalido. No se puede editar.\n";
            }
            else {
                system("cls");
                GestorPrestamos->EditarUser(indice);
                persistenciaUsuarios.guardarUsuarios(RUTA_USUARIOS, GestorPrestamos->getUsers(), GestorPrestamos->getSize()); 
            }

            Interfaz::EsperarBorrar();
        }
        else if (opcion == 5) {  // Opción para realizar un préstamo
           // Material** materiales = gestorInventario->getMaterials();
           // size_t cantidadMateriales = gestorInventario->get();
            //User** usuarios = GestorPrestamos->getUsers();
            //size_t cantidadUsuarios = GestorPrestamos->getSize();
            std::cout << "Realizando préstamo...\n";

            // Llamamos a la función para realizar un préstamo
            //hacer prestamos de nuevo
           // Prestamo::realizarPrestamo(users, cantidadUsuarios, materials, cantidadMateriales);

            // Mostrar un mensaje de confirmación
            std::cout << "Préstamo realizado con éxito.\n";
        }
        else if (opcion == 6) {
            /*
            Interfaz::ReporteInventarioMateriales();
            gestorInventario->displayMaterials();
            Interfaz::EsperarBorrar();
            */
			Interfaz::Borrar();
			int opc = Interfaz::MostrarPorMaterial();
			Interfaz::Borrar();

			switch (opc) {
			case 1:
				gestorInventario->mostrarLibros();
				break;
			case 2:
				gestorInventario->mostrarRevistas();
				break;
			case 3:
				gestorInventario->mostrarMaterialesDigitales();
				break;
			case 4:
				gestorInventario->displayMaterials(); // Mostrar todos
				break;
			case 0:
                break;
			default:
				std::cerr << "Opción invalida.\n";
				break;
			}

			Interfaz::EsperarBorrar();
        }
        else if (opcion == 7) {
            Interfaz::MostrarReporteUsuarios(); 
            int opc = Interfaz::MostrarPorActividad(); 
            Interfaz::Borrar(); 

            switch (opc) { 
            case 1:
                GestorPrestamos->mostrarUsuariosActivos(); 
                break;
            case 2:
                GestorPrestamos->mostrarUsuariosInactivos(); 
                break;
            case 3:
                GestorPrestamos->displayUsers(); // Mostrar todos
                break;
            case 0:
				Interfaz::Borrar();
                break;
            default:
                std::cerr << "Opción invalida.\n";
                break;
            }
            Interfaz::EsperarBorrar(); 
            }

        else {
            std::cerr << "La opción no es válida. Por favor, elige una opción del menú.\n";
        }
        Interfaz::Bienvenida();
        Interfaz::MostrarMenu();
    }

    system("pause");
}


Biblioteca::~Biblioteca() {
    delete gestorInventario;
    delete GestorPrestamos;
}
