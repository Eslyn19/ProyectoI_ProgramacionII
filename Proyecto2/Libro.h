#pragma once
#include "Material.h"

class Libro : public Material {
public:
    Libro(int cantidad, int num_clasificacion, std::string num_catalogo,
        std::string titulo, std::string autor, std::string palabra_clave,
        std::string tipo_material, std::string estado);

    int getDiasPrestamo() const;

    std::string toString() const;
};