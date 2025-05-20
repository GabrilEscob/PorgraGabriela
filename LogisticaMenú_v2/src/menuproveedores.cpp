// Angoly Araujo Mayo 2025 9959-24-17623

#include "MenuProveedores.h"  // Incluye el encabezado donde se declara la clase MenuProveedores
#include <iostream>           // Librería estándar para entrada y salida
using namespace std;          // Permite evitar el uso del prefijo std::

/*
 * Método estático que muestra el menú de gestión de proveedores.
 * Permite al usuario actual realizar acciones como agregar, mostrar,
 * modificar y eliminar proveedores.
 */
void MenuProveedores::mostrar(vector<Proveedor>& lista, usuarios& usuarioActual) {
    // Se agregan los datos guardados previamente
    Proveedor::cargarDesdeArchivoBinario(lista);

    int opcion; // Variable para almacenar la opción del menú elegida por el usuario

    do {
        system("cls"); // Limpia la pantalla (Windows)
        // Muestra el encabezado del menú y el nombre del usuario actual
        cout << "\t\t=== MENÚ PROVEEDORES ===\n"
             << "\t\t| Usuario: " << usuarioActual.getNombre() << "\n"
             << "\t\t1. Agregar proveedor\n"
             << "\t\t2. Mostrar proveedores\n"
             << "\t\t3. Modificar proveedor\n"
             << "\t\t4. Eliminar proveedor\n"
             << "\t\t5. Volver\n"
             << "\t\t========================\n"
             << "\t\tIngrese opción: ";
        cin >> opcion; // Lee la opción seleccionada

        string id; // Variable para capturar el ID del proveedor cuando se requiere
        switch(opcion) {
            case 1:
                Proveedor::agregar(lista, usuarioActual.getNombre());
                break;
            case 2:
                Proveedor::mostrar(lista);
                break;
            case 3:
                cout << "\t\tIngrese ID del proveedor a modificar: ";
                cin >> id;
                Proveedor::modificar(lista, usuarioActual.getNombre(), id);
                break;
            case 4:
                cout << "\t\tIngrese ID del proveedor a eliminar: ";
                cin >> id;
                Proveedor::eliminar(lista, usuarioActual.getNombre(), id);
                break;
            case 5:
                return;
            default:
                cout << "\t\tOpción inválida\n";
        }

        cout << "\n\t\tPresione Enter para continuar...";
        cin.ignore(); // Limpia el buffer de entrada
        cin.get();    // Espera a que el usuario presione Enter
    } while(opcion != 5); // Se repite hasta que el usuario elija volver
}
