#ifndef MENUCLIENTES_H
#define MENUCLIENTES_H

// Evita inclusiones múltiples del mismo archivo
// "Include guard" para asegurar que el archivo se incluya solo una vez durante la compilación

#include "Clientes.h"  // Incluye la definición de la clase Clientes
#include "usuarios.h"  // Incluye la definición de la clase usuarios
#include <vector>      // Necesario para utilizar std::vector

/**
 * @class MenuClientes
 * @brief Clase que gestiona la interfaz del menú de clientes.
 *
 * Esta clase ofrece una función estática para mostrar el menú de operaciones
 * relacionadas con los clientes: agregar, mostrar, modificar, eliminar y guardar datos.
 */
class MenuClientes {
public:
    /**
     * @brief Muestra el menú de opciones para la gestión de clientes.
     *
     * @param listaClientes Referencia a un vector que contiene la lista de clientes registrados.
     * @param usuarioActual Referencia al objeto que representa al usuario que ha iniciado sesión.
     */
    static void mostrar(std::vector<Clientes>& listaClientes, usuarios& usuarioActual);
};

#endif // MENUCLIENTES_H
