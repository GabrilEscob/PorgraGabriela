//Karina Alejandra Arriaza Ortiz 9959-24-15190
// modificado por // 9959-24-11603 GE
#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <vector>
#include <string>
#include "Producto.h"
#include "Almacen.h"
#include "Proveedor.h"

// Declaración adelantada para resolver dependencias circulares
class usuarios;
class bitacora;

class Inventario {
public:

    struct ProveedorRegistro {
        char id[10];
        char nombre[50];
        char telefono[15];
    };

    static std::vector<Inventario> listaInventario;

    static void codificar(char* data, size_t len);
    static void decodificar(char* data, size_t len);

    struct ItemInventario {
        std::string idProducto;
        std::string idAlmacen;
        std::string idProveedores;
        int cantidad;
        std::string ubicacion;
        std::string fechaIngreso;
        std::string lote;
    };

     void consultarStockCompleto();

    // Métodos estáticos para gestión de archivos
    static std::vector<Producto> cargarProductosDesdeArchivo();
    static void guardarProductosEnArchivo(const std::vector<Producto>& productos);
    static std::vector<Almacen> cargarAlmacenesDesdeArchivo();
    static void guardarAlmacenesEnArchivo(const std::vector<Almacen>& almacenes);
    static std::vector<Proveedor> cargarProveedoresDesdeArchivo();
    static void guardarProveedoresEnArchivo(const std::vector<Proveedor>& proveedores);

    // Métodos de la clase
    void controlInventario();
    void ajustarInventario();
    void reporteExistencias();
    void mostrarInventario();
    void agregarProductoAInventario();
    void transferirEntreAlmacenes();
    void buscarProductoEnInventario();
    void generarReporteInventario();
    void registrarMercancias();

    // Métodos auxiliares
    static bool verificarDisponibilidad(const std::string& idProducto, int cantidadRequerida);
    static std::vector<ItemInventario> obtenerProductosBajoStockMinimo();
    static std::vector<ItemInventario> obtenerProductosPorAlmacen(const std::string& idAlmacen);
    static int obtenerStockTotalProducto(const std::string& idProducto);

private:
    std::vector<ItemInventario> cargarInventarioDesdeArchivo();
    static std::string generarIdRegistroUnico(const std::vector<ItemInventario>& inventario);
};

#endif // INVENTARIO_H
