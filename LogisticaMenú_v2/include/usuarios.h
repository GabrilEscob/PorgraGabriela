//Karina Alejandra Arriaza Ortiz
//9959--24-14190
#ifndef USUARIOS_H
#define USUARIOS_H

#include <string>
#include "bitacora.h"

class usuarios {
public:
    usuarios();  // Constructor

    // Métodos públicos
    bool loginUsuarios();
    void registrarUsuario();
    bool buscarUsuario(const std::string& user, const std::string& pass);

    // Getters
    std::string getId() const { return id; }
    std::string getNombre() const { return nombre; }
    int getNivelAcceso() const { return nivelAcceso; }

    // Setters
    void setNombre(const std::string& n) { nombre = n; }
    void setNivelAcceso(int nivel) { nivelAcceso = nivel; }

private:
    std::string id;
    std::string nombre;
    std::string contrasena;
    int nivelAcceso;

    // Métodos auxiliares privados
    std::string generarCodigoUnico();
    bool esNumero(const std::string& str);
    bool usuarioExiste(const std::string& nombreUsuario);
    std::string leerPasswordSegura();
};

#endif // USUARIOS_H
