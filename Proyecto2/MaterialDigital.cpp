#include "MaterialDigital.h"

MaterialDigital::MaterialDigital(int cantidad, int num_clasificacion, std::string num_catalogo,
	std::string titulo, std::string autor, std::string palabra_clave, std::string tipo_material,
    std::string estado, std::string tipo, std::string formato, bool acceso)
    : Material(cantidad, num_clasificacion, num_catalogo, titulo, autor, palabra_clave, tipo_material, estado),
    tipo(tipo), formato(formato), acceso(acceso) {}

int MaterialDigital::getDiasPrestamo() const {
    return 5;
}

std::string MaterialDigital::getTipo() const {
    return tipo;
}

std::string MaterialDigital::getFormato() const {
    return formato;
}

bool MaterialDigital::getAcceso() const {
    return acceso;
}

void MaterialDigital::habilitarAcceso() {
    acceso = true;
}

void MaterialDigital::deshabilitarAcceso() {
    acceso = false;
}

void MaterialDigital::setTipo(const std::string& tipo) {
	this->tipo = tipo;
}

void MaterialDigital::setFormato(const std::string& formato) {
	this->formato = formato;
}

void MaterialDigital::setAcceso(bool acceso) {
	this->acceso = acceso;
}


std::string MaterialDigital::toString() const {
    return "Material Digital\n  Titulo: " + getTitulo() +
        "\n  Autor: " + getAutor() +
        "\n  Palabra clave: " + getPalabraClave() +
        "\n  Estado: " + getEstado() +
        "\n  Catalogo: " + getNumCatalogo() +
        "\n  Clasificacion: " + std::to_string(getNumClasificacion()) +
        "\n  Tipo: " + tipo +
        "\n  Formato: " + formato +
        "\n  Acceso: " + (acceso ? "Habilitado" : "No habilitado") +
        "\n  Cantidad: " + std::to_string(getCantidad()) + "\n"
        "\n------------------------------------------------------------------------\n";
}
