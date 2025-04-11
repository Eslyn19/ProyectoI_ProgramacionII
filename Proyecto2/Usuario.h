#pragma once
#include <iostream>
#include <string>
#include <sstream>

class User
{
public:
    User();
    User(std::string _name, std::string _surname, std::string _ID, bool _available, std::string _material);
    ~User();

    void setName(const std::string& _name);
    void setSurname(const std::string& _Surname);
    void setID(const std::string& _ID);
    void setAvailability(bool _available);
	void setMaterial(const std::string& _material);

    std::string getName() const;
    std::string getSurname() const;
    std::string getID() const;
    std::string toString() const;
    bool getAvailable() const;
	std::string getMaterial() const;

private:
    std::string name;
    std::string surname;
    std::string ID;
    bool isAvailable;
    std::string material;
};