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
        switch (opcion) {
        case 0:
            Interfaz::Farewell();
            return;

        case 1: {
            Interfaz::MenuElegirMaterial();
            int tipoMaterial = Interfaz::ElegirTipoMaterial();

            switch (tipoMaterial) {
            case 1: {
                Interfaz::AgregandoLibroInterfaz();

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
                Interfaz::AgregandoRevistaInterfaz();

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
                Interfaz::AgregandoDigitalInterfaz();

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

			case 0:
				Interfaz::Borrar();
				break;

            default:
                break;
            }
            break;
        }

        case 2: {
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
                        Interfaz::Borrar();
                        break;
                    }
                    else {
                        Interfaz::Borrar();
                        gestorInventario->displayPos(indice);
                        gestorInventario->editarMaterial(indice);
                    }
                    Interfaz::EsperarBorrar();
                }
                else {
                    Interfaz::EsperarBorrar();
                }
                break;

            case 2:
                Interfaz::Borrar();
                Interfaz::EditarRevista();

                if (gestorInventario->mostrarMaterialesPorTipo(REVISTA)) {
                    int indice = Interfaz::ElegirIndiceMaterial();

                    if (!gestorInventario->indiceValido(indice)) {
                        Interfaz::Borrar();
                        break;
                    }
                    else {
                        Interfaz::Borrar();
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
                        Interfaz::Borrar();
                        break;
                    }
                    else {
                        Interfaz::Borrar();
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
                break;
            }
            gestorInventario->saveToFile(RUTA_ARCHIVO);
            break;
        }

        case 3: {
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
                break;
            }

            Interfaz::Borrar();
            break;
        }

        case 4: {
            std::cin.ignore();
            Interfaz::MensajeAgregarUsuario();

            std::string _nuevoNombre = Interfaz::NombreNuevoUsuario();
            std::string _nuevoApellido = Interfaz::ApellidoNuevoUsuario();
            std::string _nuevoID = Interfaz::IDNuevoUsuario();
            bool estado = GestorPrestamos->existeID(_nuevoID);

            if (estado) {
                Interfaz::WarningID();
                Interfaz::EsperarBorrar();
            }
            else {
                bool _estaActivo = Interfaz::DisponibleNuevoUsuario();
                GestorPrestamos->addUser(new User(_nuevoNombre, _nuevoApellido, _nuevoID, _estaActivo, NINGUNO_MAT));
                persistenciaUsuarios.guardarUsuarios(RUTA_USUARIOS, GestorPrestamos->getUsers(), GestorPrestamos->getSize());

                Interfaz::GuardadoExitoso();
                Interfaz::EsperarBorrar();
            }
            break;
        }

        case 5: {
            std::cin.ignore();
            Interfaz::MostrarEditarUsuario();

            std::string idBuscar;
            std::getline(std::cin, idBuscar);

            if (!GestorPrestamos->existeID(idBuscar)) {
                Interfaz::WarningExistingID();
            }
            else {
                Interfaz::Borrar();
                GestorPrestamos->EditarUser(idBuscar);
                persistenciaUsuarios.guardarUsuarios(RUTA_USUARIOS, GestorPrestamos->getUsers(), GestorPrestamos->getSize());
            }
            break;
        }

        case 6: {
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
                break;
            }
            Interfaz::EsperarBorrar();
            break;
        }

        case 7: {
            if (!gestorInventario->VerificarLista()) {
                Interfaz::MostrarVacio();
                Interfaz::EsperarBorrar();
                break;
            }

            Interfaz::Borrar();
            Interfaz::OpcHacerPrestamoDevolucion();

            int opcPrestamo = Interfaz::OpcionPrestamo();

            size_t cantidadMateriales = gestorInventario->getCantidadMateriales();
            Material** materiales = gestorInventario->getMateriales();

            if (opcPrestamo == 1) {
                User* usuario = GestorPrestamos->verificarUsuario();
                if (usuario == nullptr) return;

                std::string tituloMaterial = GestorPrestamos->seleccionarMaterial(materiales, cantidadMateriales);
                if (tituloMaterial == "") return;

                GestorPrestamos->procesarPrestamo(usuario, materiales, cantidadMateriales, tituloMaterial);
                GestorPrestamos->actualizarArchivoUsuarios(RUTA_USUARIOS);
                GestorPrestamos->actualizarCantidadMaterialTXT(tituloMaterial);
                Interfaz::PrestamoExitoso();
            }
            else if (opcPrestamo == 2) {
                std::string idUsuario = GestorPrestamos->IDDevolucion();
                std::string titulo = GestorPrestamos->obtenerTituloPorIDUsuario(idUsuario);

                GestorPrestamos->DevolverPrestamo(idUsuario, materiales, cantidadMateriales);
                GestorPrestamos->actualizarDevolucionMaterial(RUTA_USUARIOS);
                GestorPrestamos->sumarCantidadMaterialTXT(titulo); 
				Interfaz::DevolucionExitosa();
            }

            GestorPrestamos->cargarPrestamos();
            Interfaz::Borrar();
            break;
        }


        case 8: {
            int c = Interfaz::OpcionMostrarPrestamos();
            switch (c) {
            case 0:
                Interfaz::Borrar();
                break;
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
                    break;
                }
                break;
            }
            default:
                break;
            }
            break;
        }

        case 9: {
            Interfaz::Borrar();
            Interfaz::MostrarPrestamosPorUsuario();

            GestorPrestamos->mostrarPrestamos();
            Interfaz::EsperarBorrar();
            break;
        }

        default:
            Interfaz::InvalidEntry();
            break;
        }

        Interfaz::Bienvenida();
        Interfaz::MostrarMenu();
    }
    Interfaz::EsperarBorrar();
}

Biblioteca::~Biblioteca() {
    delete gestorInventario;
    delete GestorPrestamos;
}
