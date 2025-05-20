// 9959 24 11603 GABRIELA ESCOBAR
#include <iostream>
#include <vector>
#include <string>
#include "usuarios.h"
#include "MenuPrincipal.h"
#include "Clientes.h"
#include "proveedor.h"
#include "Producto.h"
#include "Almacen.h"
#include "Administracion.h"
#include "transportistas.h"
#include "globals.h"
#include "Inventario.h"

int main() {
    std::cout << "Inicio del programa..." << std::endl;

    // Inicializar todas las listas necesarias
    std::vector<Clientes> listaClientes;
    std::vector<Proveedor> listaProveedores;
    std::vector<Producto> listaProductos;
    std::vector<Almacen> listaAlmacenes;
    std::vector<Administracion> listaAdministradores;
    std::vector<Transportistas> listaTransportistas;

    // Cargar los datos desde archivos
    std::cout << "Cargando clientes..." << std::endl;
    Clientes::cargarDesdeArchivo(listaClientes);

    std::cout << "Cargando almacenes..." << std::endl;
    Almacen::cargarDesdeArchivo(listaAlmacenes);

    std::cout << "Cargando administradores..." << std::endl;
    Administracion::cargarDesdeArchivo(listaAdministradores);

    std::cout << "Cargando transportistas..." << std::endl;
    Transportistas::cargarDesdeArchivo(listaTransportistas);

    std::cout << "Cargando productos..." << std::endl;
    // Cambiado a cargarDesdeArchivoBin (nombre correcto según Producto.h)
    Producto::cargarDesdeArchivoBin(listaProductos);

    std::cout << "Cargando proveedores..." << std::endl;
    Proveedor::cargarDesdeArchivo(listaProveedores);

    std::cout << "Datos cargados correctamente.\n";

    // Sistema de login
    if (usuarioRegistrado.loginUsuarios()) {
        std::cout << "Login exitoso.\n";
        MenuPrincipal::mostrar(
            listaClientes,
            listaProveedores,
            listaProductos,
            listaAlmacenes,
            listaAdministradores,
            listaTransportistas,
            usuarioRegistrado
        );
    } else {
        std::cout << "Login fallido. Saliendo del programa.\n";
    }

    std::cout << "\n\t\t** Sistema de Logistica - Hasta pronto **\n";

    // Guardar datos actualizados
    std::cout << "Guardando clientes..." << std::endl;
    Clientes::guardarEnArchivo(listaClientes);

    std::cout << "Guardando almacenes..." << std::endl;
    Almacen::guardarEnArchivo(listaAlmacenes);

    std::cout << "Guardando administradores..." << std::endl;
    Administracion::guardarEnArchivo(listaAdministradores);

    std::cout << "Guardando transportistas..." << std::endl;
    Transportistas::guardarEnArchivo(listaTransportistas);

    std::cout << "Guardando productos..." << std::endl;
    Producto::guardarEnArchivoBin(listaProductos);

    std::cout << "Guardando proveedores..." << std::endl;
    Proveedor::guardarEnArchivo(listaProveedores);

    system("pause");
    return 0;
}
