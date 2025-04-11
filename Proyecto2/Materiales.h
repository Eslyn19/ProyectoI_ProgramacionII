#pragma once
#include <stdexcept>
#include "Material.h"

class Materiales {
public:
    Materiales();
    ~Materiales();
    void addMaterial(Material* material);
    void removeMaterial(int index);
    Material* getMaterial(int index) const;
    size_t getSize() const;

private:
	void resize();
    Material** materials;
    size_t size;
    size_t capacity;
};