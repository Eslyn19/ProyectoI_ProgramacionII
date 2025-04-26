#include "Prestamo.h"

Prestamo::Prestamo(std::string _idUsuario, std::string _Titulo, std::string _fechaPrestamo, std::string _fechaDevolucion, std::string _tipoMat)
    : idUsuario(_idUsuario), Titulo(_Titulo), fechaPrestamo(_fechaPrestamo), fechaDevolucion(_fechaDevolucion), tipoMaterial(_tipoMat) {}

std::string Prestamo::getIdUsuario() { return idUsuario; }
std::string Prestamo::getTitulo() { return Titulo; }
std::string Prestamo::getFechaPrestamo() { return fechaPrestamo; }
std::string Prestamo::getFechaDevolucion() { return fechaDevolucion; }
std::string Prestamo::getTipoMaterial() { return tipoMaterial; }

void Prestamo::setIdUsuario(std::string n) { idUsuario = n; }