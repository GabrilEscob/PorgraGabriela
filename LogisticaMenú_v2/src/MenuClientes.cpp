//LUIS ANGEL MENDEZ FUENTES
//9959-24-6845
// Inclusión de encabezados propios
#include "MenuClientes.h"
#include "Clientes.h"

// Inclusión de librerías estándar
#include <iostream>
#include <vector>
#include <string>
#include <limits> // Para manejar entradas inválidas y limpiar el buffer de entrada

using namespace std;

// Definición de rangos válidos para los ID de clientes
const int CODIGO_INICIAL = 3107; /**< ID mínimo válido para los clientes */
const int CODIGO_FINAL = 3157;   /**< ID máximo válido para los clientes */

/**
 * @brief Muestra el menú interactivo de gestión de clientes.
 *
 * Permite al usuario realizar operaciones como agregar, mostrar, modificar
 * o eliminar clientes. Al finalizar, guarda automáticamente los datos.
 *
 * @param listaClientes Vector que contiene la lista actual de clientes registrados.
 * @param usuarioActual Objeto que representa al usuario que está utilizando el sistema.
 */
void MenuClientes::mostrar(vector<Clientes>& listaClientes, usuarios& usuarioActual) {
    int opcion;
    string input;

    do {
        system("cls");
        cout << "\n--------------------------------------------------------------------------------\n";
        cout << "                        SISTEMA DE GESTION DE CLIENTES                          \n";
        cout << "--------------------------------------------------------------------------------\n";
        cout << "   Usuario actual: " << usuarioActual.getNombre() << "\n";
        cout << "--------------------------------------------------------------------------------\n";
        cout << "   [1] Agregar cliente\n";
        cout << "   [2] Mostrar clientes\n";
        cout << "   [3] Modificar cliente\n";
        cout << "   [4] Eliminar cliente\n";
        cout << "   [5] Volver al menu principal\n";
        cout << "--------------------------------------------------------------------------------\n";
        cout << "                     Seleccione una opcion: ";

        // Validación de entrada
        while (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n   Entrada invalida. Ingrese un numero valido: ";
        }
        cin.ignore();

        switch (opcion) {
            case 1:
                // Agregar nuevo cliente
                Clientes::agregar(listaClientes, usuarioActual.getNombre());
                break;

            case 2:
                // Mostrar lista de clientes
                Clientes::mostrar(listaClientes);
                break;

            case 3: {
                // Modificar cliente existente
                Clientes::mostrar(listaClientes);
                if (!listaClientes.empty()) {
                    cout << "\n   Ingrese ID del cliente a modificar: ";
                    getline(cin, input);
                    if (Clientes::esIdValido(input)) {
                        Clientes::modificar(listaClientes, usuarioActual.getNombre(), input);
                    } else {
                        cout << "   ID no valido. Debe estar entre " << CODIGO_INICIAL
                             << " y " << CODIGO_FINAL << "\n";
                        system("pause");
                    }
                }
                break;
            }

            case 4: {
                // Eliminar cliente existente
                Clientes::mostrar(listaClientes);
                if (!listaClientes.empty()) {
                    cout << "\n   Ingrese ID del cliente a eliminar: ";
                    getline(cin, input);
                    if (Clientes::esIdValido(input)) {
                        Clientes::eliminar(listaClientes, usuarioActual.getNombre(), input);
                    } else {
                        cout << "   ID no valido. Debe estar entre " << CODIGO_INICIAL
                             << " y " << CODIGO_FINAL << "\n";
                        system("pause");
                    }
                }
                break;
            }

            case 5:
                // Guardar cambios y salir del menú
                Clientes::guardarEnArchivo(listaClientes);
                cout << "\n   Regresando al menu principal...\n";
                break;

            default:
                // Opción no válida
                cout << "\n   Opcion invalida.\n";
                system("pause");
                break;
        }

    } while (opcion != 5);
}
