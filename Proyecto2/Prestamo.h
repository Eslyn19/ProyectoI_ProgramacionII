#pragma once
#include <string>

class Prestamo {
public:
    Prestamo(std::string _idUsuario, std::string _Titulo, std::string _fechaPrestamo, std::string _fechaDevolucion, std::string _tipoMat);

    std::string getIdUsuario();
    std::string getTitulo();
    std::string getFechaPrestamo();
    std::string getFechaDevolucion();
    std::string getTipoMaterial();
    void setIdUsuario(std::string n);

private:
    std::string idUsuario;
    std::string Titulo;
    std::string fechaPrestamo;
    std::string fechaDevolucion;
    std::string tipoMaterial; 
};
