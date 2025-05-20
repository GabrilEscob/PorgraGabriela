// Angoly Araujo Mayo 2025 9959-24-17623


#ifndef MENUPROVEEDORES_H
#define MENUPROVEEDORES_H
#pragma once  // Previene inclusiones múltiples del archivo de encabezado

#include <vector>          // Para manejar listas de proveedores
#include "proveedor.h"     // Encabezado de la clase Proveedor
#include "usuarios.h"      // Encabezado de la clase usuarios (usuario actual)

/*
 * Clase MenuProveedores
 * Encapsula el menú de opciones relacionadas con la gestión de proveedores.
 */
class MenuProveedores {
public:
    static void mostrar(std::vector<Proveedor>& lista, usuarios& usuarioActual);
};

#endif // MENUPROVEEDORES_H

