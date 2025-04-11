#include "Materiales.h"

Materiales::Materiales() : size(0), capacity(2) {
    materials = new Material * [capacity];
}

Materiales::~Materiales() {
    for (int i = 0; i < size; ++i) {
        delete materials[i];
    }
    delete[] materials;
}

void Materiales::addMaterial(Material* material) {
    if (size >= capacity) {
        resize();
    }
    materials[size++] = material;
}

void Materiales::removeMaterial(int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    delete materials[index];
    for (int i = index; i < size - 1; ++i) {
        materials[i] = materials[i + 1];
    }
    --size;
}

Material* Materiales::getMaterial(int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return materials[index];
}

size_t Materiales::getSize() const {
    return size;
}

void Materiales::resize() {
    capacity *= 2;
    Material** newMaterials = new Material * [capacity];
    for (int i = 0; i < size; ++i) {
        newMaterials[i] = materials[i];
    }
    delete[] materials;
    materials = newMaterials;
}