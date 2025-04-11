#pragma once
#include "Material.h"

class Revista : public Material {
private:
    int volumen;
    int numero;

public:
    Revista(int cantidad, int num_clasificacion, std::string num_catalogo,
        std::string titulo, std::string autor, std::string palabra_clave,
        std::string tipo_material, std::string estado, int volumen, int numero);

    int getDiasPrestamo() const override;
    int getVolumen() const;
    int getNumero() const;
    void setVolumen(int volumen);
    void setNumero(int numero);

    std::string toString() const;
};
