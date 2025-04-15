#pragma once
#include <string>

class Prestamo {
public:
    Prestamo(std::string _idUsuario, std::string _numCatalogo, std::string _fechaPrestamo, std::string _fechaDevolucion, std::string _tipoMat)
        : idUsuario(_idUsuario), numCatalogo(_numCatalogo), fechaPrestamo(_fechaPrestamo), fechaDevolucion(_fechaDevolucion), tipoMaterial(_tipoMat) {
    }

    std::string getIdUsuario() const { return idUsuario; }
    std::string getNumCatalogo() const { return numCatalogo; }
    std::string getFechaPrestamo() const { return fechaPrestamo; }
    std::string getFechaDevolucion() const { return fechaDevolucion; }
    std::string getTipoMaterial() const { return tipoMaterial; }

private:
    std::string idUsuario;
    std::string numCatalogo;
    std::string fechaPrestamo;
    std::string fechaDevolucion;
    std::string tipoMaterial; // REVISTA  - LIBRO - MATERIAL DIGITAL 
};
