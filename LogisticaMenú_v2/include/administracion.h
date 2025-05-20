//Karina Alejandra Arriaza Ortiz 9959-24-14190
#ifndef ADMINISTRACION_H
#define ADMINISTRACION_H

#include <string>
#include <vector>

class Administracion {
public:
    std::string id;
    std::string nombre;
    std::string cargo;
    std::string departamento;
    std::string telefono;
    std::string email;
    int nivelAcceso;

    // Declaraciones de m�todos
    static void agregar(std::vector<Administracion>& lista, const std::string& usuarioActual);
    static void mostrar(const std::vector<Administracion>& lista);
    static void modificar(std::vector<Administracion>& lista, const std::string& usuarioActual, const std::string& id);
    static void eliminar(std::vector<Administracion>& lista, const std::string& usuarioActual, const std::string& id);

    // Estas son las funciones que deben ser static tambi�n:
    static void guardarEnArchivo(const std::vector<Administracion>& lista);
    static void cargarDesdeArchivo(std::vector<Administracion>& lista);
    std::string getId() const { return id; }

    int getNivelAcceso() const { return nivelAcceso; }
    static std::string generarIdUnico(const std::vector<Administracion>& lista);
    static bool idDisponible(const std::vector<Administracion>& lista, const std::string& id);
    static bool esIdValido(const std::string& id);
};

#endif // ADMINISTRACION_H
