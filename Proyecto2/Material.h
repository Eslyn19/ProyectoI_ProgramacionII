#pragma once
#include <string>
#include <sstream>

class Material
{
public:
    Material();
    Material(int, int, std::string, std::string, std::string, std::string, std::string, std::string);

    void setCantidad(int _cantidad);
    void setNumClasificacion(int _num_clasificacion);
    void setNumCatalogo(const std::string _num_catalogo);
    void setTitulo(const std::string& _titulo);
    void setAutor(const std::string& _autor);
    void setPalabraClave(const std::string& _palabra_clave);
    void setTipoMaterial(const std::string& _tipo_material);
    void setEstado(const std::string& _estado);

    int getCantidad() const;
    int getNumClasificacion() const;
    std::string getNumCatalogo() const;
    std::string getTitulo() const;
    std::string getPalabraClave() const;
    std::string getAutor() const;
    std::string getTipoMaterial() const;
    std::string getEstado() const;

    virtual std::string toString() const = 0;
    virtual int getDiasPrestamo() const = 0;
    virtual ~Material();

protected:
    int cantidad;
    int num_clasificacion;
    std::string num_catalogo;
    std::string titulo;
    std::string autor;
    std::string palabra_clave;
    std::string tipo_material;
    std::string estado;
};