#include "Persistencia.h"
#include <fstream>
#include <sstream>
#include <iostream>

void PersistenciaUsuarios::guardarUsuarios(const std::string& ruta, User** usuarios, size_t cantidad) {
    std::ofstream outFile(ruta, std::ios::out);
    if (!outFile.is_open()) {
        std::cerr << "No se pudo abrir el archivo para guardar.\n";
        return;
    }

    for (size_t i = 0; i < cantidad; ++i) {
        outFile << usuarios[i]->getName() << ","
            << usuarios[i]->getSurname() << ","
            << usuarios[i]->getID() << ","
			<< (usuarios[i]->getAvailable() ? "1" : "0") << ","
            << "No Material" << "\n";
    }

    outFile.close();
}

User** PersistenciaUsuarios::cargarUsuarios(const std::string& ruta, size_t& cantidad, size_t& capacidad) {
    std::ifstream inFile(ruta, std::ios::in);
    if (!inFile.is_open()) {
        std::cerr << "No se pudo abrir el archivo para cargar.\n";
        return nullptr;
    }

    cantidad = 0;
    capacidad = 10;
    User** usuarios = new User * [capacidad];
    std::string linea;

    while (std::getline(inFile, linea)) {
        std::istringstream iss(linea);
        std::string name, surname, id, available, material;
        std::getline(iss, name, ',');
        std::getline(iss, surname, ',');
        std::getline(iss, id, ',');
        std::getline(iss, available, ',');
        std::getline(iss, material, ',');

        bool isAvailable = (available == "1");
        if (cantidad >= capacidad) {
            capacidad *= 2;
            User** temp = new User * [capacidad];
            for (size_t i = 0; i < cantidad; ++i)
                temp[i] = usuarios[i];
            delete[] usuarios;
            usuarios = temp;
        }

        usuarios[cantidad++] = new User(name, surname, id, isAvailable, material);
    }

    inFile.close();
    return usuarios;
}
