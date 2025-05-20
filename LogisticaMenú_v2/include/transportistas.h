//Karina Alejandra Arriaza Ortiz 9959-24-14190
#ifndef TRANSPORTISTAS_H
#define TRANSPORTISTAS_H
//KARINA ALEJANDRA ARRIAZA ORTIZ
//MAYO 2025
//9959--24-14190
#include <iostream>
#include <vector>
#include <string>

class Transportistas{

public:
    std::string id;
    std::string nombre;
    std::string telefono;
    std::string vehiculo;
    std::string disponibilidad;

    static std::vector<Transportistas> getTransportistasDisponibles();

    // M todos est ticos
    static std::string generarIdUnico(const std::vector<Transportistas>& lista);
    static bool idDisponible(const std::vector<Transportistas>& lista, const std::string& id);
    static bool esIdValido(const std::string& id);

    // M todos de instancia
    void agregar(std::vector<Transportistas>& lista, const std::string& usuarioActual);
    void mostrar(const std::vector<Transportistas>& lista);
    void modificar(std::vector<Transportistas>& lista, const std::string& usuarioActual, const std::string& id);
    void eliminar(std::vector<Transportistas>& lista, const std::string& usuarioActual, const std::string& id);
    static void cargarDesdeArchivo(std::vector<Transportistas>& lista);
    static void guardarEnArchivo(const std::vector<Transportistas>& lista);

};

#endif // TRANSPORTISTAS_H
