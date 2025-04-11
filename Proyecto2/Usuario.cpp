#include "Usuario.h"

// Constructores
User::User() : name(""), surname(""), ID(""), isAvailable(false), material("") {}
User::User(std::string _name, std::string _surname, std::string _ID, bool _available, std::string _material) :
    name(_name), surname(_surname), ID(_ID), isAvailable(_available), material(_material) {}

// Metodos setters
void User::setName(const std::string& _name) { name = _name; }
void User::setSurname(const std::string& _surname) { surname = _surname; }
void User::setID(const std::string& _ID) { ID = _ID; }
void User::setAvailability(bool _available) { isAvailable = _available; }
void User::setMaterial(const std::string& _material) { material = _material; }

// Metodos getters
std::string User::getName() const { return name; }
std::string User::getSurname() const { return surname; }
std::string User::getID() const { return ID; }
bool User::getAvailable() const { return isAvailable; }
std::string User::getMaterial() const { return material; }

// Metodo toString
std::string User::toString() const
{
    std::stringstream ss;
    ss << "Nombre: " << name << '\n';
    ss << "Apellidos: " << surname << '\n';
    ss << "ID: " << ID << std::endl;
    ss << "Estado: " << (isAvailable ? "Activo" : "No Activo") << std::endl;
	ss << "Material: " << material << std::endl;
    return ss.str();
}

// Destructor
User::~User() {}