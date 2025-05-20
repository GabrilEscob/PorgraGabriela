#ifndef MENUPROCESOS_H
#define MENUPROCESOS_H

//JENNIFER ALBA DAYAMI BARRIOS FLORES
//9959-24-10016
//MAYO 2025

#include <vector>
// Forward declarations
class Clientes;
class Producto;
class Almacen;
class usuarios;

class MenuProcesos
{
public:
    // Método para mostrar el menú principal
    void mostrar(std::vector<Clientes>& clientes,
            std::vector<Producto>& productos,
            std::vector<Almacen>& almacenes);
};

#endif // MENUPROCESOS_H
