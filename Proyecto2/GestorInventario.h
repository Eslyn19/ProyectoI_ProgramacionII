#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "Material.h"
#include "Libro.h"
#include "Revista.h"
#include "MaterialDigital.h"

#define RUTA_ARCHIVO "materiales.txt"
#define LIBRO "Libro"
#define REVISTA "Revista"
#define MATERIAL_DIGITAL "MaterialDigital"

class GestorInventario {
public:
    GestorInventario();
    ~GestorInventario();
    void addMaterial(Material* material);
    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
    void displayMaterials() const;
    void displayPos(int indice) const;
    bool mostrarMaterialesPorTipo(const std::string& tipoBuscado) const;
    bool indiceValido(int indice) const;
    void editarMaterial(int tipo);

    void mostrarLibros() const;
    void mostrarRevistas() const;
    void mostrarMaterialesDigitales() const;

    void editarLibro(Libro* libro);
    void editarRevista(Revista* revista);
    void editarMaterialDigital(MaterialDigital* digital);

    // Opcion 5 del menu
    Material** getMateriales(); // Retorna el arreglo de materiales
    size_t getCantidadMateriales(); // Retorna la cantidad actual de materiales
	size_t getSize() const; // Retorna el tamaño actual del arreglo

  
private:
    void resize();
    Material** materials;
    size_t size;
    size_t capacity;
};