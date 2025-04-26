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
    Interfaz::showWelcome();
    Interfaz::showMenu();

    while (true) {
        int opcion = Interfaz::getMenuOption();
        switch (opcion) {
        case 0:
            Interfaz::showFarewell();
            return;

        case 1: {
            Interfaz::showMaterialTypeMenu();
            int tipoMaterial = Interfaz::getMaterialType();

            switch (tipoMaterial) {
            case 1: {
                Interfaz::showAddBookInterface();

                int cantidad = Interfaz::getQuantity();
                int numClasificacion = Interfaz::getClassificationNumber();
                std::cin.ignore();

                std::string numCatalogo = Interfaz::getCatalogNumber();
                std::string titulo = Interfaz::getTitle();
                std::string autor = Interfaz::getAuthor();
                std::string palabraClave = Interfaz::getKeyword();
                std::string tipoMaterialStr = Interfaz::getBookType();
                std::string estado = Interfaz::getStatus();

                gestorInventario->addMaterial(new Libro(cantidad, numClasificacion, numCatalogo, titulo, autor, palabraClave, tipoMaterialStr, estado));
                gestorInventario->saveToFile(RUTA_ARCHIVO);

                Interfaz::showSaveSuccess();
                Interfaz::waitAndClear();
                break;
            }

            case 2: {
                Interfaz::showAddMagazineInterface();

                int cantidad = Interfaz::getQuantity();
                int numClasificacion = Interfaz::getClassificationNumber();
                std::cin.ignore();

                std::string numCatalogo = Interfaz::getCatalogNumber();
                std::string titulo = Interfaz::getTitle();
                std::string autor = Interfaz::getAuthor();
                std::string palabraClave = Interfaz::getKeyword();
                std::string tipoMaterialStr = Interfaz::getMagazineType();
                std::string estado = Interfaz::getStatus();
                std::cin.ignore();
                int volumen = Interfaz::getVolume();
                int numero = Interfaz::getIssueNumber();

                gestorInventario->addMaterial(new Revista(cantidad, numClasificacion, numCatalogo, titulo, autor, palabraClave, tipoMaterialStr, estado, volumen, numero));
                gestorInventario->saveToFile(RUTA_ARCHIVO);

                Interfaz::showSaveSuccess();
                Interfaz::waitAndClear();
                break;
            }

            case 3: {
               
                Interfaz::showAddDigitalInterface();

                int cantidad = Interfaz::getQuantity();
                int numClasificacion = Interfaz::getClassificationNumber();
                std::cin.ignore();

                std::string numCatalogo = Interfaz::getCatalogNumber();
                std::string titulo = Interfaz::getTitle();
                std::string autor = Interfaz::getAuthor();
                std::string palabraClave = Interfaz::getKeyword();
                std::string tipoMaterialStr = Interfaz::getDigitalType();
                std::cin.ignore();
                std::string estado = Interfaz::getStatus();
                std::string formato = Interfaz::getDigitalFormat();
                bool acceso = Interfaz::getAccessStatus();

                gestorInventario->addMaterial(new MaterialDigital(cantidad, numClasificacion, numCatalogo, titulo, autor, palabraClave, tipoMaterialStr, estado, tipoMaterialStr, formato, acceso));
                gestorInventario->saveToFile(RUTA_ARCHIVO);

                Interfaz::showSaveSuccess();
                Interfaz::waitAndClear();
                break;
            }

            case 0:
                Interfaz::clearScreen();
                break;

            default:
                break;
            }
            break;
        }

        case 2: {
            Interfaz::clearScreen();

            gestorInventario->displayToEdit();
            int indice = Interfaz::getMaterialIndex();

            if (!gestorInventario->indiceValido(indice)) {
                Interfaz::clearScreen();
            }
            else {
                Interfaz::clearScreen();
                gestorInventario->displayPos(indice);
                gestorInventario->editarMaterial(indice);
            }

            Interfaz::waitAndClear();
            gestorInventario->saveToFile(RUTA_ARCHIVO);
            break;
        }

        case 3: {
            Interfaz::clearScreen();
            int opc = Interfaz::getMaterialReportOption();

            Interfaz::clearScreen();
            switch (opc) {
            case 1:
                gestorInventario->mostrarLibros();
                Interfaz::waitAndClear();
                break;
            case 2:
                gestorInventario->mostrarRevistas();
                Interfaz::waitAndClear();
                break;
            case 3:
                gestorInventario->mostrarMaterialesDigitales();
                Interfaz::waitAndClear();
                break;
            case 4:
                gestorInventario->displayMaterials();
                Interfaz::waitAndClear();
                break;
            case 0:
                break;
            default:
                break;
            }

            Interfaz::clearScreen();
            break;
        }

        case 4: {
            std::cin.ignore();
            Interfaz::showAddUserMessage();

            std::string _nuevoNombre = Interfaz::getNewUserName();
            std::string _nuevoApellido = Interfaz::getNewUserSurname();
            std::string _nuevoID = Interfaz::getNewUserID();
            bool estado = GestorPrestamos->existeID(_nuevoID);

            if (estado) {
                Interfaz::showIDWarning();
                Interfaz::waitAndClear();
            }
            else {
                bool _estaActivo = Interfaz::getNewUserAvailability();
                GestorPrestamos->addUser(new User(_nuevoNombre, _nuevoApellido, _nuevoID, _estaActivo, NINGUNO_MAT));
                persistenciaUsuarios.guardarUsuarios(RUTA_USUARIOS, GestorPrestamos->getUsers(), GestorPrestamos->getSize());

                Interfaz::showSaveSuccess();
                Interfaz::waitAndClear();
            }
            break;
        }

        case 5: {
            std::cin.ignore();
            Interfaz::showEditUserInterface();

            std::string idBuscar;
            std::getline(std::cin, idBuscar);

            if (!GestorPrestamos->existeID(idBuscar)) {
                Interfaz::showExistingIDWarning();
            }
            else {
                Interfaz::clearScreen();
                GestorPrestamos->EditarUser(idBuscar);
                
                persistenciaUsuarios.guardarUsuarios(RUTA_USUARIOS, GestorPrestamos->getUsers(), GestorPrestamos->getSize());
            }
            break;
        }

        case 6: {
            int opc = Interfaz::getActivityReportOption();
            Interfaz::clearScreen();

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
            Interfaz::waitAndClear();
            break;
        }

        case 7: {
            if (!gestorInventario->VerificarLista()) {
                Interfaz::showEmptyMessage();
                Interfaz::waitAndClear();
                break;
            }

            Interfaz::clearScreen();
            Interfaz::showLoanReturnMenu();

            int opcPrestamo = Interfaz::getLoanOption();

            size_t cantidadMateriales = gestorInventario->getCantidadMateriales();
            Material** materiales = gestorInventario->getMateriales();

            if (opcPrestamo == 1) {
                User* usuario = GestorPrestamos->verificarUsuario();
                if (usuario == reinterpret_cast<User*>(-1)) {
                    Interfaz::waitAndClear();
                    break;
                }
                std::string tituloMaterial = GestorPrestamos->seleccionarMaterial(materiales, cantidadMateriales);
                if (tituloMaterial == "") return;

                GestorPrestamos->procesarPrestamo(usuario, materiales, cantidadMateriales, tituloMaterial);
                GestorPrestamos->actualizarArchivoUsuarios(RUTA_USUARIOS);
                GestorPrestamos->actualizarCantidadMaterialTXT(tituloMaterial);
                Interfaz::showLoanSuccess();
            }
            else if (opcPrestamo == 2) {
                std::string idUsuario = GestorPrestamos->IDDevolucion();
                std::string titulo = GestorPrestamos->obtenerTituloPorIDUsuario(idUsuario);
                
                if (titulo != "") {
                    GestorPrestamos->DevolverPrestamo(idUsuario, materiales, cantidadMateriales);
                    GestorPrestamos->actualizarDevolucionMaterial(RUTA_USUARIOS);
                    GestorPrestamos->sumarCantidadMaterialTXT(titulo);
                    Interfaz::showReturnSuccess();
                }
            }

            GestorPrestamos->cargarPrestamos();
            Interfaz::clearScreen();
            break;
        }

        case 8: {
            int c = Interfaz::getLoanReportOption();
            switch (c) {
            case 0:
                Interfaz::clearScreen();
                break;
            case 1:
                Interfaz::clearScreen();
                GestorPrestamos->MaterialesEnPrestamo();
                Interfaz::waitAndClear();
                break;
            case 2: {
                Interfaz::showLoanTypeInterface();
                int d = Interfaz::getLoanType();
                switch (d) {
                case 1:
                    Interfaz::clearScreen();
                    GestorPrestamos->MostrarLibroPrestamo();
                    Interfaz::waitAndClear();
                    break;
                case 2:
                    Interfaz::clearScreen();
                    GestorPrestamos->MostrarRevistaPrestamo();
                    Interfaz::waitAndClear();
                    break;
                case 3:
                    Interfaz::clearScreen();
                    GestorPrestamos->MostrarMaterialDigitalPrestamo();
                    Interfaz::waitAndClear();
                    break;
                case 4:
                    Interfaz::clearScreen();
                default:
                    Interfaz::clearScreen();
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
            Interfaz::clearScreen();
            Interfaz::showUserLoansReport();

            GestorPrestamos->mostrarPrestamos();
            Interfaz::waitAndClear();
            break;
        }

        default:
            Interfaz::showInvalidEntry();
            break;
        }

        Interfaz::showWelcome();
        Interfaz::showMenu();
    }
    Interfaz::waitAndClear();
}

Biblioteca::~Biblioteca() {
    delete gestorInventario;
    delete GestorPrestamos;
}
