//9959 24 11603 GE
#ifndef ALMACEN_H
#define ALMACEN_H

#include <vector>
#include <string>
#include <algorithm>

// Estructura para almacenar datos de un almacen en formato binario
struct AlmacenRegistro {
    char id[10];            // Codigo identificador (max 9 caracteres)
    char direccion[100];    // Direccion fisica (max 99 caracteres)
    int capacidad;          // Capacidad en metros cuadrados
    char responsable[50];   // Nombre del responsable (max 49 caracteres)
    char contacto[30];      // Contacto telefonico/email (max 29 caracteres)
    char estado[20];        // Estado: "operativo" o "en mantenimiento"
};

class Almacen {
public:
    // --- METODOS CRUD ---
    // Agrega un nuevo almacen a la lista
    static void agregar(std::vector<Almacen>& lista, const std::string& usuarioActual);

    // Modifica un almacen existente
    static void modificar(std::vector<Almacen>& lista, const std::string& usuarioActual, const std::string& id);

    // Elimina un almacen de la lista
    static void eliminar(std::vector<Almacen>& lista, const std::string& usuarioActual, const std::string& id);

    // Muestra todos los almacenes en consola
    static void mostrar(const std::vector<Almacen>& lista);

    // --- PERSISTENCIA ---
    // Guarda la lista en archivo binario (con codificacion XOR)
    static void guardarEnArchivoBinario(const std::vector<Almacen>& lista);

    // Carga la lista desde archivo binario (con decodificacion XOR)
    static void cargarDesdeArchivoBinario(std::vector<Almacen>& lista);

    // --- WRAPPERS ---
    // Guarda la lista en archivo (alias de guardarEnArchivoBinario)
    static void guardarEnArchivo(std::vector<Almacen>& lista);

    // Carga la lista desde archivo (alias de cargarDesdeArchivoBinario)
    static void cargarDesdeArchivo(std::vector<Almacen>& lista);

    // --- VALIDACIONES ---
    // Genera un ID unico dentro del rango permitido
    static std::string generarIdUnico(const std::vector<Almacen>& lista);

    // Verifica si un ID no esta en uso
    static bool idDisponible(const std::vector<Almacen>& lista, const std::string& id);

    // Valida que un ID este en el rango correcto (3260-3310)
    static bool esIdValido(const std::string& id);

    // Valida que el estado sea "operativo" o "en mantenimiento"
    static bool validarEstado(const std::string& estado);

    // --- SETTERS ---
    void setId(const std::string& id) { this->id = id; }
    void setNombre(const std::string& nombre) { this->nombre = nombre; }
    void setDireccion(const std::string& direccion) { this->direccion = direccion; }
    void setCapacidad(int capacidad) { this->capacidad = capacidad; }
    void setEspacioDisponible(int espacioDisponible) { this->espacioDisponible = espacioDisponible; }

    // --- GETTERS ---
    std::string getId() const { return id; }
    std::string getNombre() const { return nombre; }
    std::string getDireccion() const { return direccion; }
    int getCapacidad() const { return capacidad; }
    std::string getResponsable() const { return responsable; }
    std::string getContacto() const { return contacto; }
    std::string getEstado() const { return estado; }
    int getEspacioDisponible() const { return espacioDisponible; }

private:
    // --- ATRIBUTOS ---
    std::string id;          // Codigo identificador
    std::string nombre;      // Nombre del almacén (nuevo campo)
    std::string direccion;   // Ubicacion fisica
    int capacidad;           // Espacio en m²
    int espacioDisponible;   // Espacio disponible en m² (nuevo campo)
    std::string responsable; // Persona a cargo
    std::string contacto;    // Telefono/email
    std::string estado;      // Estado actual

    // --- CONVERSIONES ---
    // Convierte objeto Almacen a estructura binaria
    static AlmacenRegistro toRegistro(const Almacen& a);

    // Convierte estructura binaria a objeto Almacen
    static Almacen fromRegistro(const AlmacenRegistro& reg);

    // --- CIFRADO ---
    // Aplica codificacion XOR a los datos
    static void codificar(char* data, size_t len);

    // Aplica decodificacion XOR a los datos
    static void decodificar(char* data, size_t len);

    // --- CONSTANTES ---
    static constexpr char XOR_KEY = 0xAA;  // Clave para cifrado XOR
    static const int CODIGO_INICIAL;       // Valor minimo para IDs (3260)
    static const int CODIGO_FINAL;         // Valor maximo para IDs (3310)
};

#endif // ALMACEN_H
