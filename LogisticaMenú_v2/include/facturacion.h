// Angoly Araujo Mayo 2025
// 9959-24-17623

#ifndef FACTURACION_H
#define FACTURACION_H

#include <iostream>
using namespace std;

// Estructura que representa una factura individual
struct Factura {
    int idFactura;          // Identificador �nico de la factura
    int idCliente;          // Identificador del cliente asociado
    int idPedido;           // Identificador del pedido relacionado
    float monto;            // Monto total de la factura
    bool pagada;            // Estado de pago de la factura (true si est� pagada)
    char cliente[50];       // Nombre del cliente (no se usa activamente, pero se mantiene por compatibilidad)
};

// Clase que maneja las operaciones relacionadas con facturaci�n
class Facturacion {
private:
    // Nombre del archivo donde se guardan las facturas
    const char* archivoFacturas = "facturas.bin";

    // Nombre del archivo donde se guarda la bit�cora de acciones
    const char* archivoBitacora = "bitacora.bin";

    // Guarda una factura en el archivo binario
    void guardarEnArchivo(Factura factura);

    // Muestra informaci�n de los clientes (definici�n pendiente)
    void mostrarClientes();

    // Muestra informaci�n de los pedidos (definici�n pendiente)
    void mostrarPedidos();

    // Genera un nuevo ID �nico para una factura
    int generarIdFactura();

    // Registra una acci�n en la bit�cora (como crear, modificar, eliminar una factura)
    void registrarBitacora(const Factura& factura, const string& accion, const string& usuario = "Usuario");

public:
    // Muestra el men� principal del m�dulo de facturaci�n
    void mostrarMenuFacturacion();

    // Crea una nueva factura y la guarda
    void crearFactura();

    // Muestra todas las facturas existentes
    void mostrarFacturas();

    // Permite modificar los datos de una factura
    void modificarFactura();

    // Elimina una factura del archivo
    void eliminarFactura();
};

#endif

