#include "Material.h"

// Constructores sin parametros
Material::Material() : cantidad(0), num_clasificacion(0), num_catalogo(""), titulo(""), autor(""), palabra_clave(""), tipo_material(""), estado("") {}

// Constructor con parametros
Material::Material(int a, int b, std::string c, std::string d, std::string e, std::string f, std::string g, std::string h)
	: cantidad(a), num_clasificacion(b), num_catalogo(c), titulo(d), autor(e), palabra_clave(f), tipo_material(g), estado(h) {}

// Metodos setters
void Material::setCantidad(int _cantidad) { cantidad = _cantidad; }
void Material::setNumClasificacion(int _num_clasificacion) { num_clasificacion = _num_clasificacion; }
void Material::setNumCatalogo(const std::string _num_catalogo) { num_catalogo = _num_catalogo; }
void Material::setTitulo(const std::string& _titulo) { titulo = _titulo; }
void Material::setAutor(const std::string& _autor) { autor = _autor; }
void Material::setPalabraClave(const std::string& _palabra_clave) { palabra_clave = _palabra_clave; }
void Material::setTipoMaterial(const std::string& _tipo_material) { tipo_material = _tipo_material; }
void Material::setEstado(const std::string& _estado) { estado = _estado; }

// Metodos getters
int Material::getCantidad() const { return cantidad; }
int Material::getNumClasificacion() const { return num_clasificacion; }
std::string Material::getNumCatalogo() const { return num_catalogo; }
std::string Material::getTitulo() const { return titulo; }
std::string Material::getPalabraClave() const { return palabra_clave; }
std::string Material::getAutor() const { return autor; }
std::string Material::getTipoMaterial() const { return tipo_material; }
std::string Material::getEstado() const { return estado; }

// Metodo toString
std::string Material::toString() const
{
	std::stringstream ss;
	ss << "Titulo:" << titulo << "\n"
		<< "Autor:" << autor << "\n"
		<< "Tipo de Material:" << tipo_material << "\n"
		<< "Cantidad: " << cantidad << "\n"
		<< "Numero de Clasificacion: " << num_clasificacion << "\n"
		<< "Numero de Catalogo: " << num_catalogo << "\n"
		<< "Palabra Clave:" << palabra_clave << "\n"
		<< "Estado:" << estado << "\n"
		<< "----------------------------------------";
	return ss.str();
}

Material::~Material() {}