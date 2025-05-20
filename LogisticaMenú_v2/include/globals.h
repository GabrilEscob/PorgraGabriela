// Prevención de inclusión múltiple del archivo de cabecera
#ifndef GLOBALS_H
#define GLOBALS_H

//JENNIFER ALBA DAYAMI BARRIOS FLORES
//9959-24-10016
//MAYO 2025

// Inclusión de bibliotecas necesarias
#include <vector>          // Para usar std::vector
#include "usuarios.h"      // Manejo de usuarios del sistema
#include "bitacora.h"      // Registro de actividades (auditoría)
#include "reportes.h"      // Generación de reportes
#include "envios.h"        // Gestión de envíos
#include "facturacion.h"   // Procesos de facturación
#include "transportistas.h"// Manejo de transportistas
#include "pedidos.h"       // Gestión de pedidos
#include "inventario.h"    // Control de inventario

// Declaraciones de variables globales (definidas en otro archivo .cpp)

// Gestor principal de pedidos del sistema
extern Pedidos gestorPedidos;

// Gestor principal del inventario de productos
extern Inventario gestorInventario;

// Gestor principal de envíos y logística
extern Envios gestorEnvios;

// Gestor principal de facturación y cobros
extern Facturacion gestorFacturacion;

// Gestor principal para generación de reportes
extern Reportes gestorReportes;

// Usuario actualmente registrado en el sistema
extern usuarios usuarioRegistrado;

// Sistema de registro de actividades (bitácora/auditoría)
extern bitacora auditoria;

// Lista de transportistas disponibles (usando vector en lugar de array)
extern std::vector<Transportistas> listaTransportistas;

// Fin de la definición del archivo de cabecera
#endif // GLOBALS_H
