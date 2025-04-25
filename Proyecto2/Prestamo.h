#pragma once
#include <string>

class Prestamo {
public:
    Prestamo(std::string _idUsuario, std::string _Titulo, std::string _fechaPrestamo, std::string _fechaDevolucion, std::string _tipoMat)
        : idUsuario(_idUsuario), Titulo(_Titulo), fechaPrestamo(_fechaPrestamo), fechaDevolucion(_fechaDevolucion), tipoMaterial(_tipoMat) {
    }

    std::string getIdUsuario() const { return idUsuario; }
    void setIdUsuario(const std::string& nuevoId) { idUsuario = nuevoId; }
    std::string getTitulo() const { return Titulo; }
    std::string getFechaPrestamo() const { return fechaPrestamo; }
    std::string getFechaDevolucion() const { return fechaDevolucion; }
    std::string getTipoMaterial() const { return tipoMaterial; }

private:
    std::string idUsuario;
    std::string Titulo;
    std::string fechaPrestamo;
    std::string fechaDevolucion;
    std::string tipoMaterial; 
};
