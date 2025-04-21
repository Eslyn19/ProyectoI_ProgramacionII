📚 Sistema de Gestión de Préstamos de Materiales

🛠️ **Funcionalidades**

Registro de usuarios y materiales.

Préstamo y devolución de materiales.

Actualización automática de archivos.

🧱 Estructura del Proyecto

Clase Base Material

Clase abstracta de la cual heredan:

Libro

Revista

MaterialDigital

Puedes agregar más tipos de materiales fácilmente heredando de Material.

Gestores:

GestorInventario: administra materiales.

GestorPrestamo: gestiona préstamos, devoluciones y usuarios.

Interfaz: gestiona la interacción con el usuario.

📂 Archivos Importantes

usuarios.txt: contiene los usuarios y el material que tienen (si aplica).

materiales.txt: contiene todos los materiales registrados.

prestamos.txt: registro de préstamos activos.
