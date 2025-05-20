//Karina Alejandra Arriaza Ortiz 9959-24-14190
#include "menutransportistas.h"
#include <iostream>
#include <limits> // Para limpieza del buffer
#include <vector>
#include "globals.h"
#include "transportistas.h"

using namespace std;

void MenuTransportistas::mostrar(std::vector<Transportistas>& listaTransportistas, usuarios& usuarioActual) {
    int opcion;
    string input;

    do {
        system("cls");
        cout << "\t\t=== MEN� TRANSPORTISTAS ===\n"
             << "\t\t| Usuario: " << usuarioActual.getNombre() << "\n"
             << "\t\t1. Agregar transportista\n"
             << "\t\t2. Mostrar transportistas\n"
             << "\t\t3. Modificar transportista\n"
             << "\t\t4. Eliminar transportista\n"
             << "\t\t5. Volver al men� principal\n"
             << "\t\t===========================\n"
             << "\t\tSeleccione una opci�n: ";

        // Validaci�n de entrada
        while (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\t\tEntrada inv�lida. Por favor ingrese un n�mero: ";
        }
        cin.ignore(); // Limpiar el buffer

        switch(opcion) {
            case 1: {
                Transportistas nuevoTransportista;
                nuevoTransportista.agregar(listaTransportistas, usuarioActual.getNombre());
                break;
            }

            case 2:
                Transportistas().mostrar(listaTransportistas);
                break;

            case 3: {
                Transportistas().mostrar(listaTransportistas);
                if (!listaTransportistas.empty()) {
                    cout << "\n\t\tIngrese ID del transportista a modificar: ";
                    getline(cin, input);

                    if (Transportistas::esIdValido(input)) {
                        Transportistas().modificar(listaTransportistas, usuarioActual.getNombre(), input);
                    } else {
                        cout << "\t\tID no v�lido. Debe estar entre 4100 y 4199.\n";
                        system("pause");
                    }
                }
                break;
            }

            case 4: {
                Transportistas().mostrar(listaTransportistas);
                if (!listaTransportistas.empty()) {
                    cout << "\n\t\tIngrese ID del transportista a eliminar: ";
                    getline(cin, input);

                    if (Transportistas::esIdValido(input)) {
                        Transportistas().eliminar(listaTransportistas, usuarioActual.getNombre(), input);
                    } else {
                        cout << "\t\tID no v�lido. Debe estar entre 4100 y 4199.\n";
                        system("pause");
                    }
                }
                break;
            }

            case 5:
                // Guardar cambios al salir
                Transportistas().guardarEnArchivo(listaTransportistas);
                return;

            default:
                cout << "\t\tOpci�n no v�lida. Intente nuevamente.\n";
                system("pause");
        }
    } while (true);
}
