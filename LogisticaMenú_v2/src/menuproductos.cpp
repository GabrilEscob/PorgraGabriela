// JENNIFER ALBA DAYAMI BARRIOS FLORES
// 9959-24-10016
// MAYO 2025
// modificado por // 9959-24-11603 GE
#include "MenuProductos.h"
#include "Producto.h"
#include <iostream>
#include <limits>

using namespace std;

void MenuProductos::mostrar(vector<Producto>& listaProductos, usuarios& usuarioActual) {
    int opcion;
    string input;

    // Cargar productos desde archivo al iniciar
    Producto::cargarDesdeArchivoBin(listaProductos);

    do {
        system("cls");
        cout << "\t\t=== MENÚ PRODUCTOS ===\n"
             << "\t\t| Usuario: " << usuarioActual.getNombre() << "\n"
             << "\t\t1. Agregar producto\n"
             << "\t\t2. Mostrar productos\n"
             << "\t\t3. Modificar producto\n"
             << "\t\t4. Eliminar producto\n"
             << "\t\t5. Volver al menú principal\n"
             << "\t\t======================\n"
             << "\t\tSeleccione una opción: ";

        // Validación de entrada
        while (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\t\tEntrada inválida. Por favor ingrese un número: ";
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(opcion) {
            case 1:
                Producto::agregar(listaProductos, usuarioActual.getNombre());
                break;

            case 2:
                Producto::mostrar(listaProductos);
                break;

            case 3: {
                Producto::mostrar(listaProductos);
                if (!listaProductos.empty()) {
                    cout << "\n\t\tIngrese Código del producto a modificar: ";
                    getline(cin, input);

                    if (Producto::esCodigoValido(input)) {
                        Producto::modificar(listaProductos, usuarioActual.getNombre(), input);
                    } else {
                        cout << "\t\tCódigo no válido. Debe estar entre 3209 y 3259\n";
                        system("pause");
                    }
                }
                break;
            }

            case 4: {
                Producto::mostrar(listaProductos);
                if (!listaProductos.empty()) {
                    cout << "\n\t\tIngrese Código del producto a eliminar: ";
                    getline(cin, input);

                    if (Producto::esCodigoValido(input)) {
                        Producto::eliminar(listaProductos, usuarioActual.getNombre(), input);
                    } else {
                        cout << "\t\tCódigo no válido. Debe estar entre 3209 y 3259\n";
                        system("pause");
                    }
                }
                break;
            }

            case 5:
                Producto::guardarEnArchivoBin(listaProductos);
                return;

            default:
                cout << "\t\tOpción no válida. Intente nuevamente.\n";
                system("pause");
        }
    } while (true);
}
