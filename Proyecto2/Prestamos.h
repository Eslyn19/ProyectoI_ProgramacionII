/*#pragma once
#include "Usuario.h"
#include "Material.h"
#include <iostream>
#include <fstream>
#include <string>

class Prestamo {
public:
    // Constructor para inicializar el préstamo
    Prestamo(User* usuario, Material* material) {
        this->usuario = usuario;
        this->material = material;
        this->fechaPrestamo = obtenerFechaActual();

        // Asignar el material al usuario
        usuario->setMaterial(material);
    }

    // Método estático para realizar un préstamo, donde el usuario selecciona el material
    static void realizarPrestamo(User** usuarios, size_t cantidadUsuarios, Material** materiales, size_t cantidadMateriales) {
        std::string idUsuario;
        std::cout << "Ingrese el ID del usuario para realizar el préstamo: ";
        std::cin >> idUsuario;

        // Buscar al usuario por su ID
        User* usuarioEncontrado = nullptr;
        for (size_t i = 0; i < cantidadUsuarios; ++i) {
            if (usuarios[i]->getID() == idUsuario) {
                usuarioEncontrado = usuarios[i];
                break;
            }
        }

        // Si el usuario no existe
        if (!usuarioEncontrado) {
            std::cout << "Usuario no encontrado.\n";
            return;
        }

        // Mostrar materiales disponibles
        std::cout << "Materiales disponibles:\n";
        for (size_t i = 0; i < cantidadMateriales; ++i) {
            std::cout << i + 1 << ". " << materiales[i]->getTitulo() << std::endl;
        }

        // Selección del material
        int seleccionMaterial;
        std::cout << "Seleccione el número del material a prestar: ";
        std::cin >> seleccionMaterial;

        // Validar que la selección sea válida
        if (seleccionMaterial < 1 || seleccionMaterial > cantidadMateriales) {
            std::cout << "Selección inválida.\n";
            return;
        }

        Material* materialSeleccionado = materiales[seleccionMaterial - 1];

        // Crear el préstamo
        Prestamo* prestamo = new Prestamo(usuarioEncontrado, materialSeleccionado);

        // Guardar el préstamo en el archivo
        guardarPrestamoEnArchivo(usuarioEncontrado, materialSeleccionado);
    }

private:
    User* usuario;  // Puntero al usuario
    Material* material;  // Puntero al material
    std::string fechaPrestamo;  // Fecha del préstamo

    // Método para obtener la fecha actual (puedes usar una librería de fechas como std::chrono)
    std::string obtenerFechaActual() {
        return "2025-04-09";  // Un ejemplo de fecha estática
    }

    // Método estático para guardar el préstamo en el archivo
    static void guardarPrestamoEnArchivo(User* usuario, Material* material) {
        std::ofstream archivo("ListaPrestamos.txt", std::ios::app); // Abrir archivo en modo 'append'

        if (archivo.is_open()) {
            archivo << "Usuario: " << usuario->getName() << " "
                << usuario->getSurname() << "\n";
            archivo << "Material: " << material->getTitulo() << "\n";
            archivo << "Fecha de Préstamo: " << "2025-04-09" << "\n"; // Utiliza la fecha real aquí
            archivo << "----------------------\n";
            archivo.close();
        }
        else {
            std::cerr << "Error al abrir el archivo para guardar el préstamo.\n";
        }
    }
};
*/