// 9959-24-11603 GE
#ifndef REPORTES_H
#define REPORTES_H

#include <vector>
#include <string>
#include <ctime>
#include "bitacora.h"
#include "usuarios.h"

// Declaraciones externas para mantener compatibilidad
extern bitacora auditoria;
extern usuarios usuarioRegistrado;

class Reportes {
public:
    // Estructura que representa un reporte
    struct DatosReporte {
        std::string id;                // ID unico del reporte
        std::string tipo;              // Tipo de reporte (ventas, inventario, etc.)
        std::time_t fechaGeneracion;   // Fecha de creacion del reporte
        std::string contenido;         // Contenido textual del reporte
    };

    // Lista estatica que almacena todos los reportes generados
    static std::vector<DatosReporte> listaReportes;

    // Constructor: carga los reportes desde archivo binario al iniciar
    Reportes();

    // Metodo publico para generar reportes, version sin parametros (usa globales)
    void generarReportes();

    // Metodo publico para generar reportes, version con parametros
    void generarReportes(bitacora& auditoria, const usuarios& usuario);

    // Genera un informe de ventas simulado
    void informeVentas(bitacora& auditoria, const usuarios& usuario);

    // Genera un analisis de tiempos de entrega
    void analisisTiemposEntrega(bitacora& auditoria, const usuarios& usuario);

    // Genera un reporte de inventarios
    void reporteInventarios(bitacora& auditoria, const usuarios& usuario);

    // Genera una evaluacion de proveedores
    void evaluacionProveedores(bitacora& auditoria, const usuarios& usuario);

    // Guarda los reportes en un archivo binario
    static void guardarEnArchivoBin(const std::vector<DatosReporte>& lista);

    // Carga los reportes desde un archivo binario
    static void cargarDesdeArchivoBin(std::vector<DatosReporte>& lista);

private:
    // Genera un ID unico dentro de un rango fijo (3800-3850)
    static std::string generarIdUnico(const std::vector<DatosReporte>& lista);

    // Verifica si un ID esta disponible en la lista
    static bool idDisponible(const std::vector<DatosReporte>& lista, const std::string& id);

    // Muestra mensaje de "procesando..." con retardo visual
    void mostrarProcesando(const std::string& mensaje);
};

#endif // REPORTES_H
