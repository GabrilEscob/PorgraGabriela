#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H

//JENNIFER ALBA DAYAMI BARRIOS FLORES
//9959-24-10016
//MAYO 2025

// Incluye las bibliotecas necesarias
#include <vector>              // Para usar contenedores vector
#include "Clientes.h"          // Manejo de clientes
#include "Proveedor.h"         // Gestión de proveedores
#include "Producto.h"          // Administración de productos
#include "Almacen.h"           // Control de almacenes
#include "Administracion.h"    // Gestión administrativa
#include "transportistas.h"    // Manejo de transportistas
#include "usuarios.h"         // Control de usuarios
#include "pedidos.h"

// Clase que implementa el menú principal del sistema
class MenuPrincipal {
public:
    // Muestra el menú principal con todas las opciones del sistema
    // Recibe como parámetros las listas de cada entidad del sistema:
    // clientes - Lista de clientes registrados
    // proveedores - Lista de proveedores del sistema
    // productos - Inventario de productos
    // almacenes - Lista de almacenes disponibles
    // administradores - Personal administrativo
    // transportistas - Lista de transportistas
    // usuarioActual - Usuario que ha iniciado sesión
    static void mostrar(
        std::vector<Clientes>& clientes,
        std::vector<Proveedor>& proveedores,
        std::vector<Producto>& productos,
        std::vector<Almacen>& almacenes,
        std::vector<Administracion>& administradores,
        std::vector<Transportistas>& transportistas,
        usuarios& usuarioActual
    );
};

// Fin del archivo de encabezado
#endif // MENUPRINCIPAL_H
