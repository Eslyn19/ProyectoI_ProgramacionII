#include "GestorInventario.h"
#include "Libro.h"
#include "Revista.h"
#include "MaterialDigital.h"

#define CYAN_COLOR "\033[36m"
#define WHITE_COLOR "\033[1;37m"

GestorInventario::GestorInventario() : size(0), capacity(2) {
    materials = new Material * [capacity];
}

GestorInventario::~GestorInventario() {
    for (size_t i = 0; i < size; ++i) {
        delete materials[i];
    }
    delete[] materials;
}

void GestorInventario::addMaterial(Material* material) {
    if (size >= capacity) {
        resize();
    }
    materials[size++] = material;
}

// Metodo para guardar o despues de sobreescrinir los materiales en un archivo
void GestorInventario::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    for (size_t i = 0; i < size; ++i) {
        if (Libro* libro = dynamic_cast<Libro*>(materials[i])) {
            file << "Libro,"
                << libro->getCantidad() << ","
                << libro->getNumClasificacion() << ","
                << libro->getNumCatalogo() << ","
                << libro->getTitulo() << ","
                << libro->getAutor() << ","
                << libro->getPalabraClave() << ","
                << libro->getTipoMaterial() << ","
                << libro->getEstado() << std::endl;
        }
        else if (Revista* revista = dynamic_cast<Revista*>(materials[i])) {
            file << "Revista,"
                << revista->getCantidad() << ","
                << revista->getNumClasificacion() << ","
                << revista->getNumCatalogo() << ","
                << revista->getTitulo() << ","
                << revista->getAutor() << ","
                << revista->getPalabraClave() << ","
                << revista->getTipoMaterial() << ","
                << revista->getEstado() << "," 
                << revista->getVolumen() << ","
                << revista->getNumero() << std::endl;
        }
        else if (MaterialDigital* digital = dynamic_cast<MaterialDigital*>(materials[i])) {
            file << "MaterialDigital,"
                << digital->getCantidad() << ","
                << digital->getNumClasificacion() << ","
                << digital->getNumCatalogo() << ","
                << digital->getTitulo() << ","
                << digital->getAutor() << ","
                << digital->getPalabraClave() << ","
                << digital->getTipoMaterial() << ","
                << digital->getEstado() << "," 
                << digital->getTipo() << ","
                << digital->getFormato() << ","
                << (digital->getAcceso() ? "1" : "0") << std::endl;
        }
    }
    file.close();
}

bool GestorInventario::indiceValido(int indice) const {
    return (indice >= 0 && indice < size);
}

/* Metodo para cargar los materiales desde un archivo a el arreglo de materiales
 Cargar al constructor para inicializarlo */
void GestorInventario::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type;
        std::getline(iss, type, ',');

        if (type == LIBRO) {
            int cantidad, num_clasificacion;
            std::string num_catalogo, titulo, autor, palabra_clave, tipo_material, estado;

            std::string temp;
            std::getline(iss, temp, ','); cantidad = std::stoi(temp);
            std::getline(iss, temp, ','); num_clasificacion = std::stoi(temp);
            std::getline(iss, num_catalogo, ',');
            std::getline(iss, titulo, ',');
            std::getline(iss, autor, ',');
            std::getline(iss, palabra_clave, ',');
            std::getline(iss, tipo_material, ',');
            std::getline(iss, estado);

            addMaterial(new Libro(cantidad, num_clasificacion, num_catalogo, titulo, autor, palabra_clave, tipo_material, estado));
        }
        else if (type == REVISTA) {
            int cantidad, num_clasificacion, volumen, numero;
            std::string num_catalogo, titulo, autor, palabra_clave, tipo_material, estado;

            std::string temp;
            std::getline(iss, temp, ','); cantidad = std::stoi(temp);
            std::getline(iss, temp, ','); num_clasificacion = std::stoi(temp);
            std::getline(iss, num_catalogo, ',');
            std::getline(iss, titulo, ',');
            std::getline(iss, autor, ',');
            std::getline(iss, palabra_clave, ',');
            std::getline(iss, tipo_material, ',');
            std::getline(iss, estado, ',');
            std::getline(iss, temp, ','); volumen = std::stoi(temp);
            std::getline(iss, temp); numero = std::stoi(temp);

            addMaterial(new Revista(cantidad, num_clasificacion, num_catalogo, titulo, autor, palabra_clave, tipo_material, estado, volumen, numero));
        }
        else if (type == MATERIAL_DIGITAL) {
            int cantidad, num_clasificacion;
            std::string num_catalogo, titulo, autor, palabra_clave, tipo_material, estado, tipo, formato;
            bool acceso;

            std::string temp;
            std::getline(iss, temp, ','); cantidad = std::stoi(temp);
            std::getline(iss, temp, ','); num_clasificacion = std::stoi(temp);
            std::getline(iss, num_catalogo, ',');
            std::getline(iss, titulo, ',');
            std::getline(iss, autor, ',');
            std::getline(iss, palabra_clave, ',');
            std::getline(iss, tipo_material, ',');
            std::getline(iss, estado, ',');
            std::getline(iss, tipo, ',');
            std::getline(iss, formato, ',');
            std::getline(iss, temp); acceso = (std::stoi(temp) == 1);

            addMaterial(new MaterialDigital(cantidad, num_clasificacion, num_catalogo, titulo, autor, palabra_clave, tipo_material, estado, tipo, formato, acceso));
        }
    }

    file.close();
}

// Aumentar el tamano de arreglo por si se llena
void GestorInventario::resize() {
    capacity *= 2;
    Material** newMaterials = new Material * [capacity];
    for (size_t i = 0; i < size; ++i) {
        newMaterials[i] = materials[i];
    }
    delete[] materials;
    materials = newMaterials;
}

// Mostrar todos los materiales
void GestorInventario::displayMaterials() const {
    if (size == 0) {
        std::cout << "No hay materiales en el inventario." << std::endl;
    }

    std::cout << CYAN_COLOR << "---------------------------------------" << std::endl;
    std::cout << "|         Lista de materiales         |" << std::endl;
    std::cout << "---------------------------------------" << WHITE_COLOR << std::endl << std::endl;
   
    for (size_t i = 0; i < size; ++i) {
        std::cout << materials[i]->toString() << std::endl;
    }    
}

bool GestorInventario::mostrarMaterialesPorTipo(const std::string& tipoBuscado) const {
    int index = 0;
    bool encontrado = false;

    for (int i = 0; i < size; ++i) {
        if (materials[i]->getTipoMaterial() == tipoBuscado) {
            std::cout << "Posicion en inventario[" << index << "]\n" << materials[i]->toString() << std::endl;
            encontrado = true;
        }
        index++;
    }
    return encontrado;
}

size_t GestorInventario::getSize() const {
	return size;
}

void GestorInventario::editarMaterial(int index) {
    try {
        if (index < 0 || index >= size) {
            std::cerr << "Indice fuera de rango." << std::endl;
            return;
        }

        Material* material = materials[index];

        if (Libro* libro = dynamic_cast<Libro*>(material)) {
            editarLibro(libro);
        }
        else if (Revista* revista = dynamic_cast<Revista*>(material)) {
            editarRevista(revista);
        }
        else if (MaterialDigital* digital = dynamic_cast<MaterialDigital*>(material)) {
            editarMaterialDigital(digital);
        }
        else {
            std::cerr << "Tipo de material desconocido." << std::endl;
        }
    }
    catch (std::exception& ex) {
        std::cerr << "Out of range" << ex.what() << std::endl;
        return;
    }
}

void GestorInventario::editarLibro(Libro* libro) {
    int opcion;
    do {
        std::cout << '\n' << char(175) << "Seleccione el atributo a editar del Libro:" << std::endl;
        std::cout << "\n1. Cantidad" << std::endl;
        std::cout << "2. Numero de Clasificacion" << std::endl;
        std::cout << "3. Numero de Catalogo" << std::endl;
        std::cout << "4. Titulo" << std::endl;
        std::cout << "5. Autor" << std::endl;
        std::cout << "6. Palabra Clave" << std::endl;
        std::cout << "7. Tipo de Material" << std::endl;
        std::cout << "8. Estado" << std::endl;
        std::cout << "9. Salir" << std::endl;
        std::cout << "\n> Ingrese su opcion: ";
        std::cin >> opcion;
        std::cin.ignore(); 

        std::string nuevoValor;
        int nuevoIntValor;

        switch (opcion) {
        case 1:
            std::cout << "\n>Ingrese nueva cantidad: ";
            std::cin >> nuevoIntValor;
            std::cin.ignore();
            libro->setCantidad(nuevoIntValor);
            break;
        case 2:
            std::cout << "\n>Ingrese nuevo numero de clasificacion: ";
            std::cin >> nuevoIntValor;
            std::cin.ignore();
            libro->setNumClasificacion(nuevoIntValor);
            break;
        case 3:
            std::cout << "\n>Ingrese nuevo numero de catalogo: ";
            std::getline(std::cin, nuevoValor);
            libro->setNumCatalogo(nuevoValor);
            break;
        case 4:
            std::cout << "\n>Ingrese nuevo titulo: ";
            std::getline(std::cin, nuevoValor);
            libro->setTitulo(nuevoValor);
            break;
        case 5:
            std::cout << "\n>Ingrese nuevo autor: ";
            std::getline(std::cin, nuevoValor);
            libro->setAutor(nuevoValor);
            break;
        case 6:
            std::cout << "\n>Ingrese nueva palabra clave: ";
            std::getline(std::cin, nuevoValor);
            libro->setPalabraClave(nuevoValor);
            break;
        case 7:
            std::cout << "\n>Ingrese nuevo tipo de material: ";
            std::getline(std::cin, nuevoValor);
            libro->setTipoMaterial(nuevoValor);
            break;
        case 8:
            std::cout << "\n>Ingrese nuevo estado: ";
            std::getline(std::cin, nuevoValor);
            libro->setEstado(nuevoValor);
            break;
        case 9:
            std::cout << "\nSaliendo de la edicion del Libro." << std::endl;
            break;
        default:
            std::cout << "\n>Opcion no valida." << std::endl;
        }
    } while (opcion != 9);
}

void GestorInventario::editarRevista(Revista* revista) {
    int opcion;
    do {
        std::cout << '\n' << char(175) << "Seleccione el atributo a editar de la Revista:" << std::endl;
        std::cout << "1. Cantidad" << std::endl;
        std::cout << "2. Numero de Clasificacion" << std::endl;
        std::cout << "3. Numero de Catalogo" << std::endl;
        std::cout << "4. Titulo" << std::endl;
        std::cout << "5. Autor" << std::endl;
        std::cout << "6. Palabra Clave" << std::endl;
        std::cout << "7. Tipo de Material" << std::endl;
        std::cout << "8. Estado" << std::endl;
        std::cout << "9. Volumen" << std::endl;
        std::cout << "10. Numero" << std::endl;
        std::cout << "11. Salir" << std::endl;
        std::cout << "Ingrese su opcion: ";
        std::cin >> opcion;
        std::cin.ignore();

        std::string nuevoValor;
        int nuevoIntValor;

        switch (opcion) {
        case 1:
            std::cout << "\n>Ingrese nueva cantidad: ";
            std::cin >> nuevoIntValor;
            std::cin.ignore();
            revista->setCantidad(nuevoIntValor);
            break;
        case 2:
            std::cout << "\n>Ingrese nuevo numero de clasificacion: ";
            std::cin >> nuevoIntValor;
            std::cin.ignore();
            revista->setNumClasificacion(nuevoIntValor);
            break;
        case 3:
            std::cout << "\n>Ingrese nuevo numero de catalogo: ";
            std::getline(std::cin, nuevoValor);
            revista->setNumCatalogo(nuevoValor);
            break;
        case 4:
            std::cout << "\n>Ingrese nuevo titulo: ";
            std::getline(std::cin, nuevoValor);
            revista->setTitulo(nuevoValor);
            break;
        case 5:
            std::cout << "\n>Ingrese nuevo autor: ";
            std::getline(std::cin, nuevoValor);
            revista->setAutor(nuevoValor);
            break;
        case 6:
            std::cout << "\n>Ingrese nueva palabra clave: ";
            std::getline(std::cin, nuevoValor);
            revista->setPalabraClave(nuevoValor);
            break;
        case 7:
            std::cout << "\n>Ingrese nuevo tipo de material: ";
            std::getline(std::cin, nuevoValor);
            revista->setTipoMaterial(nuevoValor);
            break;
        case 8:
            std::cout << "\n>Ingrese nuevo estado: ";
            std::getline(std::cin, nuevoValor);
            revista->setEstado(nuevoValor);
            break;
        case 9:
            std::cout << "\n>Ingrese nuevo volumen: ";
            std::cin >> nuevoIntValor;
            std::cin.ignore();
            revista->setVolumen(nuevoIntValor);
            break;
        case 10:
            std::cout << "\n>Ingrese nuevo numero: ";
            std::cin >> nuevoIntValor;
            std::cin.ignore();
            revista->setNumero(nuevoIntValor);
            break;
        case 11:
            std::cout << "\n>Saliendo de la edicion de la Revista." << std::endl;
            break;
        default:
            std::cout << "\n>Opción no valida." << std::endl;
        }
    } while (opcion != 11);
}

void GestorInventario::editarMaterialDigital(MaterialDigital* digital) {
    int opcion;
    do {
        std::cout << '\n' << char(175) << "Seleccione el atributo a editar del Material Digital:" << std::endl;
        std::cout << "1. Cantidad" << std::endl;
        std::cout << "2. Numero de Clasificacion" << std::endl;
        std::cout << "3. Numero de Catalogo" << std::endl;
        std::cout << "4. Titulo" << std::endl;
        std::cout << "5. Autor" << std::endl;
        std::cout << "6. Palabra Clave" << std::endl;
        std::cout << "7. Tipo de Material" << std::endl;
        std::cout << "8. Estado" << std::endl;
        std::cout << "9. Tipo" << std::endl;
        std::cout << "10. Formato" << std::endl;
        std::cout << "11. Acceso" << std::endl;
        std::cout << "12. Salir" << std::endl;
        std::cout << "Ingrese su opcion: ";
        std::cin >> opcion;
        std::cin.ignore();

        std::string nuevoValor;
        int nuevoIntValor;
        bool nuevoBoolValor;

        switch (opcion) {
        case 1:
            std::cout << "\n> Ingrese nueva cantidad: ";
            std::cin >> nuevoIntValor;
            std::cin.ignore();
            digital->setCantidad(nuevoIntValor);
            break;
        case 2:
            std::cout << "\n>Ingrese nuevo numero de clasificacion: ";
            std::cin >> nuevoIntValor;
            std::cin.ignore();
            digital->setNumClasificacion(nuevoIntValor);
            break;
        case 3:
            std::cout << "\n>Ingrese nuevo numero de catalogo: ";
            std::getline(std::cin, nuevoValor);
            digital->setNumCatalogo(nuevoValor);
            break;
        case 4:
            std::cout << "\n>Ingrese nuevo titulo: ";
            std::getline(std::cin, nuevoValor);
            digital->setTitulo(nuevoValor);
            break;
        case 5:
            std::cout << "\n>Ingrese nuevo autor: ";
            std::getline(std::cin, nuevoValor);
            digital->setAutor(nuevoValor);
            break;
        case 6:
            std::cout << "\n>Ingrese nueva palabra clave: ";
            std::getline(std::cin, nuevoValor);
            digital->setPalabraClave(nuevoValor);
            break;
        case 7:
            std::cout << "\n>Ingrese nuevo tipo de material: ";
            std::getline(std::cin, nuevoValor);
            digital->setTipoMaterial(nuevoValor);
            break;
        case 8:
            std::cout << "\n>Ingrese nuevo estado: ";
            std::getline(std::cin, nuevoValor);
            digital->setEstado(nuevoValor);
            break;
        case 9:
            std::cout << "\n>Ingrese nuevo tipo: ";
            std::getline(std::cin, nuevoValor);
            digital->setTipo(nuevoValor);
            break;
        case 10:
            std::cout << "\n>Ingrese nuevo formato: ";
            std::getline(std::cin, nuevoValor);
            digital->setFormato(nuevoValor);
            break;
        case 11:
            std::cout << "\n>Ingrese nuevo acceso (1 para sí, 0 para no): ";
            std::cin >> nuevoBoolValor;
            std::cin.ignore();
            digital->setAcceso(nuevoBoolValor);
            break;
        case 12:
            std::cout << "\n>Saliendo de la edicion del Material Digital." << std::endl;
            break;
        default:
            std::cout << "\n>Opción no valida." << std::endl;
        }
    } while (opcion != 12);
}

void GestorInventario::mostrarLibros() const {
    std::cout << CYAN_COLOR << "---------------------------------------" << std::endl;
    std::cout << "|            Lista de libros          |" << std::endl;
    std::cout << "---------------------------------------" << WHITE_COLOR << std::endl << std::endl;

    for (size_t i = 0; i < size; ++i) {
        Libro* libro = dynamic_cast<Libro*>(materials[i]);
        if (libro != nullptr) {
            std::cout << "Cantidad: " << libro->getCantidad() << "\n";
            std::cout << "Clasificacion: " << libro->getNumClasificacion() << "\n";
            std::cout << "Catalogo: " << libro->getNumCatalogo() << "\n";
            std::cout << "Titulo: " << libro->getTitulo() << "\n";
            std::cout << "Autor: " << libro->getAutor() << "\n";
            std::cout << "Palabra clave: " << libro->getPalabraClave() << "\n";
            std::cout << "Tipo: " << libro->getTipoMaterial() << "\n";
            std::cout << "Estado: " << libro->getEstado() << "\n\n";
        }
    }
}


void GestorInventario::mostrarRevistas() const {
    std::cout << CYAN_COLOR << "---------------------------------------" << std::endl;
    std::cout << "|          Lista de revistas          |" << std::endl;
    std::cout << "---------------------------------------" << WHITE_COLOR << std::endl << std::endl;

    for (size_t i = 0; i < size; ++i) {
        Revista* revista = dynamic_cast<Revista*>(materials[i]);
        if (revista != nullptr) {
            std::cout << "Cantidad: " << revista->getCantidad() << "\n";
            std::cout << "Clasificacion: " << revista->getNumClasificacion() << "\n";
            std::cout << "Catalogo: " << revista->getNumCatalogo() << "\n";
            std::cout << "Titulo: " << revista->getTitulo() << "\n";
            std::cout << "Autor: " << revista->getAutor() << "\n";
            std::cout << "Palabra clave: " << revista->getPalabraClave() << "\n";
            std::cout << "Tipo: " << revista->getTipoMaterial() << "\n";
            std::cout << "Estado: " << revista->getEstado() << "\n";
            std::cout << "Volumen: " << revista->getVolumen() << "\n";
            std::cout << "Numero: " << revista->getNumero() << "\n\n";
        }
    }
}


void GestorInventario::mostrarMaterialesDigitales() const {
    std::cout << CYAN_COLOR << "---------------------------------------" << std::endl;
    std::cout << "|      Lista de material digital      |" << std::endl;
    std::cout << "---------------------------------------" << WHITE_COLOR << std::endl << std::endl;

    for (size_t i = 0; i < size; ++i) {
        MaterialDigital* digital = dynamic_cast<MaterialDigital*>(materials[i]);
        if (digital != nullptr) {
            std::cout << "Cantidad: " << digital->getCantidad() << "\n";
            std::cout << "Clasificacion: " << digital->getNumClasificacion() << "\n";
            std::cout << "Catalogo: " << digital->getNumCatalogo() << "\n";
            std::cout << "Titulo: " << digital->getTitulo() << "\n";
            std::cout << "Autor: " << digital->getAutor() << "\n";
            std::cout << "Palabra clave: " << digital->getPalabraClave() << "\n";
            std::cout << "Tipo material: " << digital->getTipoMaterial() << "\n";
            std::cout << "Estado: " << digital->getEstado() << "\n";
            std::cout << "Tipo digital: " << digital->getTipo() << "\n";
            std::cout << "Formato: " << digital->getFormato() << "\n";
            std::cout << "Acceso: " << (digital->getAcceso() ? "Activado" : "No activado") << "\n\n";
        }
    }
}

void GestorInventario::displayPos(int indice) const{
    std::cout << "- - Material elegido - -\n" << materials[indice]->toString();
}

Material** GestorInventario::getMateriales() {
    return this->materials;
}

size_t GestorInventario::getCantidadMateriales() {
    return this->size;
}