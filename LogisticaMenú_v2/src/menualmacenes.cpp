//9959 24 11603 GABRIELA ESCOBAR
#include "MenuAlmacenes.h"
#include "Almacen.h"
#include <iostream>
#include <limits>

using namespace std;

// Muestra el menu de gestion de almacenes
// lista: Referencia al vector de almacenes
// usuarioActual: Referencia al usuario que esta usando el sistema
void MenuAlmacenes::mostrar(vector<Almacen>& lista, usuarios& usuarioActual) {
    // Cargar datos de almacenes desde archivo
    Almacen::cargarDesdeArchivo(lista);

    int opcion;
    string input;

    do {
        system("cls");
        // Mostrar encabezado del menu
        cout << "=== MENU ALMACENES ===\n"
             << "Usuario: " << usuarioActual.getNombre() << "\n\n"
             << "1. Agregar almacen\n"
             << "2. Mostrar almacenes\n"
             << "3. Modificar almacen\n"
             << "4. Eliminar almacen\n"
             << "5. Volver\n"
             << "Seleccione: ";

        // Validar entrada numerica
        while (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida. Ingrese un numero: ";
        }
        cin.ignore();

        // Procesar opcion seleccionada
        switch(opcion) {
            case 1:  // Agregar nuevo almacen
                Almacen::agregar(lista, usuarioActual.getNombre());
                break;

            case 2:  // Mostrar lista de almacenes
                Almacen::mostrar(lista);
                break;

            case 3: {  // Modificar almacen existente
                Almacen::mostrar(lista);
                cout << "ID a modificar: ";
                getline(cin, input);
                Almacen::modificar(lista, usuarioActual.getNombre(), input);
                break;
            }

            case 4: {  // Eliminar almacen
                Almacen::mostrar(lista);
                cout << "ID a eliminar: ";
                getline(cin, input);
                Almacen::eliminar(lista, usuarioActual.getNombre(), input);
                break;
            }

            case 5:  // Salir del menu
                return;

            default:  // Opcion no valida
                cout << "Opcion invalida\n";
        }

        // Pausa antes de continuar
        cout << "\nPresione Enter para continuar...";
        cin.get();
    } while(true);  // Bucle infinito hasta que se seleccione salir
}
