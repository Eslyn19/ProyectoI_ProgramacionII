#include "Biblioteca.h"
#include "Interfaz.h"
#include "Libro.h"
#include "Persistencia.h"
#include "Revista.h"
#include "MaterialDigital.h"
#include "GestorPrestamo.h"

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
    GestorPrestamos->cargarPrestamos();
}

void Biblioteca::IniciarBiblioteca() {

    Interfaz::Bienvenida();
    Interfaz::MostrarMenu();

    while (true) {
        int opcion = Interfaz::OpcionMenu();
        if (opcion == 0) {
            std::cout << "Saliendo de la Biblioteca...\n"; // hacer funcion
            return;
        }
        else if (opcion == 1) {
            Interfaz::MenuElegirMaterial();
            int tipoMaterial = Interfaz::ElegirTipoMaterial();

            switch (tipoMaterial) {
            case 1: {
                Interfaz::Borrar();
                std::cout << "Agregando un libro...\n" << std::endl;
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
                std::cout << "Agregando una revista...\n" << std::endl;
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
                std::cout << "Agregando un material digital...\n" << std::endl;
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
                if (gestorInventario->mostrarMaterialesPorTipo(LIBRO)) {
                    int indice = Interfaz::ElegirIndiceMaterial();
                    if (!gestorInventario->indiceValido(indice)) {
                        system("cls");
                        break;
                    }
                    else {
                        system("cls");
                        gestorInventario->displayPos(indice);
                        gestorInventario->editarMaterial(indice);
                    }
                    Interfaz::EsperarBorrar();
                }
                else {
                    Interfaz::EsperarBorrar();  // para pausar antes de volver
                }
                break;

            case 2:
                Interfaz::Borrar();
                Interfaz::EditarRevista();
                if (gestorInventario->mostrarMaterialesPorTipo(REVISTA)) {
                    int indice = Interfaz::ElegirIndiceMaterial();
                    if (!gestorInventario->indiceValido(indice)) {
                        system("cls");
                        break;
                    }
                    else {
                        system("cls");
                        gestorInventario->displayPos(indice);
                        gestorInventario->editarMaterial(indice);
                    }
                    Interfaz::EsperarBorrar();
                }
                else {
                    Interfaz::EsperarBorrar();
                }
                break;

            case 3:
                Interfaz::Borrar();
                Interfaz::EditarDigital();
                if (gestorInventario->mostrarMaterialesPorTipo(MATERIAL_DIGITAL)) {
                    int indice = Interfaz::ElegirIndiceMaterial();
                    if (!gestorInventario->indiceValido(indice)) {
                        system("cls");
                        break;
                    }
                    else {
                        system("cls");
                        gestorInventario->displayPos(indice);
                        gestorInventario->editarMaterial(indice);
                    }
                    Interfaz::EsperarBorrar();
                }
                else {
                    Interfaz::EsperarBorrar();
                }
                break;

            default:
                std::cout << "\n> Opción no valida.\n";
                break;
            }

            gestorInventario->saveToFile(RUTA_ARCHIVO);
        }

        else if (opcion == 3) {
            Interfaz::Borrar();
            int opc = Interfaz::MostrarPorMaterial();
            Interfaz::Borrar();

            switch (opc) {
            case 1:
                gestorInventario->mostrarLibros();
                Interfaz::EsperarBorrar();
                break;
            case 2:
                gestorInventario->mostrarRevistas();
                Interfaz::EsperarBorrar();
                break;
            case 3:
                gestorInventario->mostrarMaterialesDigitales();
                Interfaz::EsperarBorrar();
                break;
            case 4:
                gestorInventario->displayMaterials();
                Interfaz::EsperarBorrar();
                break;
            case 0:
                break;
            default:
                std::cerr << "Opcion invalida.\n";
                break;
            }

            Interfaz::Borrar();
        }
        else if (opcion == 4) {
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
                bool _estaActivo = Interfaz::DisponibleNuevoUsuario();
				GestorPrestamos->addUser(new User(_nuevoNombre, _nuevoApellido, _nuevoID, _estaActivo, NINGUNO_MAT));
                persistenciaUsuarios.guardarUsuarios(RUTA_USUARIOS, GestorPrestamos->getUsers(), GestorPrestamos->getSize());

                Interfaz::UsuarioGuardado();
            }
        }
        else if (opcion == 5) {
            std::cin.ignore();
            Interfaz::Borrar();

            Interfaz::MostrarEditarUsuario();

            std::string idBuscar;
            std::getline(std::cin, idBuscar);

            if (!GestorPrestamos->existeID(idBuscar)) {
                std::cout << "\nEl ID ingresado no existe. No se puede editar.\n";
            }
            else {
                system("cls");
                GestorPrestamos->EditarUser(idBuscar); 
                persistenciaUsuarios.guardarUsuarios(RUTA_USUARIOS, GestorPrestamos->getUsers(), GestorPrestamos->getSize());
            }

            Interfaz::EsperarBorrar();
        }

        else if (opcion == 6) {
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
                GestorPrestamos->displayUsers();
                break;
            case 0:
                break;
            default:
                std::cerr << "Opción invalida.\n";
                break;
            }
            Interfaz::EsperarBorrar(); 
        }
        
        // PARTE DE SELECCION DEL MENU PARA LOS PRESTAMOS ------------------------------------------------------------------------
        else if (opcion == 7) { 
            Interfaz::Borrar();
            Interfaz::OpcHacerPrestamoDevolucion();

            int opcPrestamo = Interfaz::OpcionPrestamo();

            size_t cantidadMateriales = gestorInventario->getCantidadMateriales();
            Material** materiales = gestorInventario->getMateriales();

            switch (opcPrestamo) {
            case 1:  // Realizar préstamo
                GestorPrestamos->HacerPrestamo(materiales, cantidadMateriales);
                //persistenciaUsuarios.guardarUsuarios(RUTA_USUARIOS, GestorPrestamos->getUsers(), GestorPrestamos->getSize());
                GestorPrestamos->actualizarArchivoUsuarios(RUTA_USUARIOS);
                break;

            case 2:  // Devolver préstamo
                GestorPrestamos->DevolverPrestamo(materiales, cantidadMateriales);
                //persistenciaUsuarios.guardarUsuarios(RUTA_USUARIOS, GestorPrestamos->getUsers(), GestorPrestamos->getSize());
                GestorPrestamos->actualizarDevolucionMaterial(RUTA_USUARIOS);
                break;

            default:
                std::cout << "Opcion invalida.\n";
                break;
            }
            GestorPrestamos->cargarPrestamos();
            
            

            Interfaz::EsperarBorrar();
        }
        else if (opcion == 8) {
            int c = Interfaz::OpcionMostrarPrestamos();
            switch (c) {
            case 1:
                Interfaz::Borrar();
                GestorPrestamos->MaterialesEnPrestamo();
                Interfaz::EsperarBorrar();
                break;

            case 2: {
				Interfaz::InterfazTipoPrestamos();
                int d = Interfaz::TipoPrestamo();
                switch (d) {
                case 1:
                    Interfaz::Borrar();
                    GestorPrestamos->MostrarLibroPrestamo();
                    Interfaz::EsperarBorrar();
                    break;
                case 2:
                    Interfaz::Borrar();
                    GestorPrestamos->MostrarRevistaPrestamo();
                    Interfaz::EsperarBorrar();
                    break;
                case 3:
                    Interfaz::Borrar();
                    GestorPrestamos->MostrarMaterialDigitalPrestamo();
                    Interfaz::EsperarBorrar();
                    break;
                default:
                    std::cout << "Opción inválida.\n";
                    break;
                }
                break;
            }

            default:
                std::cout << "Opción inválida.\n";
                break;
            }
            }

        else if (opcion == 9) {
            Interfaz::Borrar();
            Interfaz::MostrarPrestamosPorUsuario();

            GestorPrestamos->mostrarPrestamos();
			Interfaz::EsperarBorrar();
        }
        else {
            std::cerr << "La opción no es valida. Por favor, elige una opcion del menu.\n";
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
