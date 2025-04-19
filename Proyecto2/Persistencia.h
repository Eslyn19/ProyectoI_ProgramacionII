#pragma once
#include <string>
#include "Usuario.h"

class PersistenciaUsuarios {
public:
    PersistenciaUsuarios() = default;

    void guardarUsuarios(const std::string& ruta, User** usuarios, size_t cantidad);
    void guardarUsuariosPrestamo(const std::string& ruta, User** usuarios, size_t cantidad);
    User** cargarUsuarios(const std::string& ruta, size_t& cantidad, size_t& capacidad);
};
