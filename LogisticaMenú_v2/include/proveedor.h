// Angoly Araujo Mayo 2025 9959-24-17623
#ifndef PROVEEDOR_H
#define PROVEEDOR_H

#include <vector>
#include <string>

// Registro fijo para guardar en archivo binario
struct ProveedorRegistro {
    char id[10];
    char nombre[50];
    char contacto[50];  // Añadir este campo
    char telefono[20];
};


class Proveedor {
public:
    // Métodos...
    static void codificar(char* texto, size_t tam);
    static void decodificar(char* texto, size_t tam);

    // Métodos CRUD
    static void agregar(std::vector<Proveedor>& lista, const std::string& usuarioActual);
    static void modificar(std::vector<Proveedor>& lista, const std::string& usuarioActual, const std::string& id);
    static void eliminar(std::vector<Proveedor>& lista, const std::string& usuarioActual, const std::string& id);
    static void mostrar(const std::vector<Proveedor>& lista);

    // Persistencia (solo binario)
    static void guardarEnArchivoBinario(const std::vector<Proveedor>& lista);
    static void cargarDesdeArchivoBinario(std::vector<Proveedor>& lista);

    // Wrappers usados por main.cpp (simulan nombres genéricos)
    static void guardarEnArchivo(std::vector<Proveedor>& lista);
    static void cargarDesdeArchivo(std::vector<Proveedor>& lista);

    // Validación y generación de ID
    static std::string generarIdUnico(const std::vector<Proveedor>& lista);
    static bool idDisponible(const std::vector<Proveedor>& lista, const std::string& id);
    static bool esIdValido(const std::string& id);

    // Setters
    void setId(const std::string& id) { this->id = id; }
    void setNombre(const std::string& nombre) { this->nombre = nombre; }
    void setContacto(const std::string& contacto) { this->contacto = contacto; }
    void setTelefono(const std::string& telefono) { this->telefono = telefono; }

    // Getters
    std::string getId() const { return id; }
    std::string getNombre() const { return nombre; }
    std::string getContacto() const { return contacto; }
    std::string getTelefono() const { return telefono; }

private:

    const char* archivoProveedores = "Proveedores.bin";
    const char* archivoBitacora = "bitacora.bin";


    std::string id;
    std::string nombre;
    std::string contacto;  // Nuevo campo
    std::string telefono;

    // Conversión registro <-> objeto
    static ProveedorRegistro toRegistro(const Proveedor& p);
    static Proveedor fromRegistro(const ProveedorRegistro& reg);

    static void guardarEnBitacora(const std::string& usuario, const std::string& accion, const Proveedor& proveedor);
    static constexpr char XOR_KEY = 0xAA;
};

#endif // PROVEEDOR_H

