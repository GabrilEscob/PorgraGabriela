// 9959-24-11603 GE
#ifndef REPORTES_H
#define REPORTES_H

#include <vector>
#include <string>
#include <ctime>
#include "bitacora.h"
#include "usuarios.h"
#include "clientes.h"
#include "proveedor.h"
#include "producto.h"
#include "Almacen.h"
#include "transportistas.h"
#include "pedidos.h"
#include "envios.h"
#include <map>

// Declaraciones externas para mantener compatibilidad
extern bitacora auditoria;
extern usuarios usuarioRegistrado;

class Reportes {
public:
    struct DatosReporte {
        std::string id;
        std::string tipo;
        std::time_t fechaGeneracion;
        std::string contenido;
    };

    static std::vector<DatosReporte> listaReportes;

    Reportes();

    // Métodos CRUD
    void crearReporte(const std::string& tipo, const std::string& contenido);
    void consultarReportes();
    void modificarReporte(const std::string& id, const std::string& nuevoContenido);
    void eliminarReporte(const std::string& id);

    // Métodos específicos de generación de reportes
    void generarReportes();
    void generarReportes(bitacora& auditoria, const usuarios& usuario);

    void informeVentas(const std::vector<Pedidos>& pedidos,
                      const std::vector<Clientes>& clientes,
                      const std::vector<Producto>& productos);

    void analisisTiemposEntrega(const std::vector<Envios>& envios,
                               const std::vector<Pedidos>& pedidos,
                               const std::vector<Transportistas>& transportistas);

    void reporteInventarios(const std::vector<Producto>& productos,
                           const std::vector<Almacen>& almacenes);

    void evaluacionProveedores(const std::vector<Proveedor>& proveedores,
                              const std::vector<Producto>& productos);

    // Métodos de persistencia
    static void guardarEnArchivoBin(const std::vector<DatosReporte>& lista);
    static void cargarDesdeArchivoBin(std::vector<DatosReporte>& lista);

private:
    static std::string generarIdUnico(const std::vector<DatosReporte>& lista);
    static bool idDisponible(const std::vector<DatosReporte>& lista, const std::string& id);
    void mostrarProcesando(const std::string& mensaje);

    // Métodos auxiliares para formateo
    std::string formatearFecha(time_t fecha);
    std::string generarTabla(const std::vector<std::vector<std::string>>& datos);
};

#endif // REPORTES_H
