#pragma once
#include "Material.h"

class MaterialDigital : public Material {
private:
    std::string tipo;
    std::string formato;
    bool acceso;

public:
    MaterialDigital(int cantidad, int num_clasificacion, std::string num_catalogo,
		std::string titulo, std::string autor, std::string palabra_clave, std::string tipo_material,
        std::string estado, std::string tipo, std::string formato, bool acceso);

    int getDiasPrestamo() const override;
	void setTipo(const std::string& tipo);
	void setFormato(const std::string& formato);
	void setAcceso(bool acceso);

    std::string getTipo() const;
    std::string getFormato() const;
    bool getAcceso() const;

    std::string toString() const;
};
