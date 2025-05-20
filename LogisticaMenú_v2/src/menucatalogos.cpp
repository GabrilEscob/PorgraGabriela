#include "MenuCatalogos.h"
#include "MenuClientes.h"
#include "MenuProveedores.h"
#include "MenuProductos.h"
#include "MenuAlmacenes.h"
#include "MenuAdministracion.h"
#include "MenuTransportistas.h"
#include <iostream>
#include <limits>

//JENNIFER ALBA DAYAMI BARRIOS FLORES
//9959-24-10016
//MAYO 2025

using namespace std;

// Implementación del menú de catálogos
void MenuCatalogos::mostrar(vector<Clientes>& clientes,
                          vector<Proveedor>& proveedores,
                          vector<Producto>& productos,
                          vector<Almacen>& almacenes,
                          vector<Administracion>& administradores,
                          vector<Transportistas>& transportistas,
                          usuarios& usuarioActual) {
    int opcion;

    do {
        // Limpiar la pantalla en cada iteración
        system("cls");

        // Mostrar encabezado del menú con información del usuario
        cout << "\t\t====================================\n"
             << "\t\t|        MENÚ CATÁLOGOS           |\n"
             << "\t\t| Usuario: " << usuarioActual.getNombre() << "\n"
             << "\t\t| Nivel: " << usuarioActual.getNivelAcceso() << "\n"
             << "\t\t====================================\n"
             << "\t\t1. Clientes\n"
             << "\t\t2. Proveedores\n"
             << "\t\t3. Productos\n"
             << "\t\t4. Almacenes\n"
             << "\t\t5. Transportistas\n";

        // Mostrar opción adicional si el usuario tiene nivel de acceso alto (admin)
        if(usuarioActual.getNivelAcceso() >= 3) {
            cout << "\t\t6. Administración\n";
        }

        // Opción para volver al menú principal
        cout << "\t\t7. Volver al menú principal\n"
             << "\t\t====================================\n"
             << "\t\tSeleccione una opción: ";

        // Validar entrada del usuario (solo números enteros)
        while(!(cin >> opcion)) {
            cin.clear(); // Limpiar estado de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar buffer
            cout << "\t\tEntrada inválida. Ingrese un número: ";
        }
        cin.ignore(); // Limpiar el salto de línea sobrante

        // Ejecutar la acción correspondiente a la opción seleccionada
        switch(opcion) {
            case 1:
                // Llamar al menú de clientes
                MenuClientes::mostrar(clientes, usuarioActual);
                break;

            case 2:
                // Llamar al menú de proveedores
                MenuProveedores::mostrar(proveedores, usuarioActual);
                break;

            case 3:
                // Llamar al menú de productos
                MenuProductos::mostrar(productos, usuarioActual);
                break;

            case 4:
                // Llamar al menú de almacenes
                MenuAlmacenes::mostrar(almacenes, usuarioActual);
                break;

            case 5:
                // Llamar al menú de transportistas
                MenuTransportistas::mostrar(transportistas, usuarioActual);
                break;

            case 6:
                // Solo disponible si el usuario tiene nivel 3 o superior
                if(usuarioActual.getNivelAcceso() >= 3) {
                    MenuAdministracion::mostrar(administradores, usuarioActual);
                } else {
                    // Si no tiene acceso, se muestra un mensaje de error
                    cout << "\n\t\tAcceso denegado. Nivel insuficiente.\n";
                    system("pause");
                }
                break;

            case 7:
                // Volver al menú principal (salir del bucle)
                return;

            default:
                // Mensaje para opciones no válidas
                cout << "\n\t\tOpción inválida. Intente nuevamente.\n";
                system("pause");
        }

    } while(true); // Repetir hasta que el usuario seleccione la opción de salir
}
