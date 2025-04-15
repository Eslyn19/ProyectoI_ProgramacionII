#include "Revista.h"

Revista::Revista(int cantidad, int num_clasificacion, std::string num_catalogo,
    std::string titulo, std::string autor, std::string palabra_clave,
    std::string tipo_material, std::string estado, int volumen, int numero) :
    Material(cantidad, num_clasificacion, num_catalogo, titulo, autor, palabra_clave, tipo_material, estado),
	volumen(volumen), numero(numero) {} 

int Revista::getDiasPrestamo() const {
    return 2;
}

int Revista::getVolumen() const {
    return volumen;
}

void Revista::setVolumen(int volumen) {
    this->volumen = volumen;
}

int Revista::getNumero() const {
    return numero;
}

void Revista::setNumero(int numero) {
    this->numero = numero;
}

std::string Revista::toString() const {
    return "Revista:\n  Titulo: " + getTitulo() +
        "\n  Autor: " + getAutor() +
        "\n  Palabra clave: " + getPalabraClave() +
        "\n  Estado: " + getEstado() +
        "\n  Catalogo: " + getNumCatalogo() +
        "\n  Clasificacion: " + std::to_string(getNumClasificacion()) +
        "\n  Volumen: " + std::to_string(volumen) +
        "\n  Numero: " + std::to_string(numero) +
        "\n  Cantidad: " + std::to_string(getCantidad()) +
        "\n------------------------------------------------------------------------\n";
}
