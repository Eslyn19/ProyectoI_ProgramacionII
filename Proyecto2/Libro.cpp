#include "Libro.h"

Libro::Libro(int cantidad, int num_clasificacion, std::string num_catalogo,
    std::string titulo, std::string autor, std::string palabra_clave,
	std::string tipo_material, std::string estado) : Material(cantidad, num_clasificacion, num_catalogo, titulo, autor, palabra_clave, tipo_material, estado) {}


int Libro::getDiasPrestamo() const {
    return 7;
}

std::string Libro::toString() const {
    return "Libro\n  Titulo: " + getTitulo() +
        "\n  Autor: " + getAutor() +
        "\n  Palabra clave: " + getPalabraClave() +
        "\n  Tipo de material: " + getTipoMaterial() +
        "\n  Estado: " + getEstado() +
        "\n  Catalogo: " + getNumCatalogo() +
        "\n  Clasificacion: " + std::to_string(getNumClasificacion()) +
        "\n  Cantidad: " + std::to_string(getCantidad()) +
        "\n------------------------------------------------------------------------\n";
}
