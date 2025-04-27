# 📚 Sistema de Gestión de Biblioteca

Este proyecto implementa un sistema completo de gestión de biblioteca en C++, permitiendo administrar diferentes tipos de materiales bibliográficos, usuarios y préstamos.

## Características Principales

- Gestión de diferentes tipos de materiales.
- Sistema de préstamos y devoluciones.
- Gestión de usuarios.
- Persistencia de datos.
- Interfaz de usuario por consola.
- Manejo de excepciones.

## 🧱 Estructura del Proyecto

### 📂 Módulos Principales

- **Gestión de Materiales**
  - `Material.h/cpp`: Clase base para todos los materiales.
  - `Libro.h/cpp`: Implementación específica para libros.
  - `Revista.h/cpp`: Implementación específica para revistas.
  - `MaterialDigital.h/cpp`: Implementación para materiales digitales.

- **Gestión de Usuarios**
  - `Usuario.h/cpp`: Manejo de usuarios individuales.
  - `Usuarios.h/cpp`: Gestión de colección de usuarios.

- **Sistema de Préstamos**
  - `GestorPrestamo.h/cpp`: Manejo de préstamos y devoluciones.
  - `Prestamo.h`: Definición de la estructura de préstamos.

- **Gestión de Inventario**
  - `GestorInventario.h/cpp`: Administración del inventario de materiales.
  - `Materiales.h/cpp`: Colección de materiales.

- **Nucleo del Sistema**
  - `Biblioteca.h/cpp`: Núcleo del sistema.
  - `Interfaz.h/cpp`: Interfaz de usuario.
  - `Persistencia.h/cpp`: Manejo de almacenamiento de datos.
  - `Excepcion.h/cpp`: Sistema de manejo de excepciones.

## 🛠️ Requisitos del Sistema

- Compilador C++ compatible con el estándar C++11 o superior.
- Sistema de construcción Visual Studio (archivo de proyecto incluido)

## 🚀 Compilación y Ejecución

1. Abrir el proyecto en Visual Studio
2. Compilar la solución (Ctrl + Shift + B)
3. Ejecutar el programa (F5)

## 💻 Uso del Sistema

El sistema proporciona una interfaz por consola que permite:

1. Gestionar materiales (agregar, eliminar, modificar)
2. Administrar usuarios.
3. Realizar préstamos y devoluciones.
4. Consultar el estado del inventario.
5. Generar reportes

## 🧑‍💻 Autor

Eslyn Jara Calderon
