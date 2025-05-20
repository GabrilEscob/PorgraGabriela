//Karina Alejandra Arriaza Ortiz 9959-24-14190
#include "menuadministracion.h"
#include "Administracion.h"
#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm> // Para find_if

using namespace std;

const int CODIGO_INICIAL_ADMIN = 3362;
const int CODIGO_FINAL_ADMIN = 3402;

void MenuAdministracion::mostrar(vector<Administracion>& listaAdministradores, usuarios& usuarioActual) {
    int opcion;
    string input;

    do {
        system("cls");
        cout << "\t\t=== MENU ADMINISTRACION ===\n"
             << "\t\t| Usuario: " << usuarioActual.getNombre() << "\n"
             << "\t\t| Nivel de acceso: " << usuarioActual.getNivelAcceso() << "\n"
             << "\t\t1. Agregar administrador\n"
             << "\t\t2. Mostrar administradores\n"
             << "\t\t3. Modificar administrador\n"
             << "\t\t4. Eliminar administrador\n"
             << "\t\t5. Volver al menu principal\n"
             << "\t\t===========================\n"
             << "\t\tSeleccione una opcion: ";

        while (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\t\tEntrada invalida. Por favor ingrese un numero: ";
        }
        cin.ignore();

        switch(opcion) {
            case 1:
                if (usuarioActual.getNivelAcceso() >= 3) {
                    Administracion::agregar(listaAdministradores, usuarioActual.getNombre());
                } else {
                    cout << "\n\t\tAcceso denegado. Se requiere nivel 3 o superior.\n";
                    system("pause");
                }
                break;

            case 2:
                Administracion::mostrar(listaAdministradores);
                break;

            case 3:
                if (usuarioActual.getNivelAcceso() >= 2) {
                    Administracion::mostrar(listaAdministradores);
                    if (!listaAdministradores.empty()) {
                        cout << "\n\t\tIngrese ID del administrador a modificar: ";
                        getline(cin, input);

                        if (Administracion::esIdValido(input)) {
                            auto it = find_if(listaAdministradores.begin(), listaAdministradores.end(),
                                [&input](const Administracion& a) { return a.getId() == input; });

                            if (it != listaAdministradores.end() && it->getNivelAcceso() <= usuarioActual.getNivelAcceso()) {
                                Administracion::modificar(listaAdministradores, usuarioActual.getNombre(), input);
                            } else {
                                cout << "\t\tNo puedes modificar administradores con mayor nivel de acceso.\n";
                                system("pause");
                            }
                        } else {
                            cout << "\t\tID no valido. Debe estar entre " << CODIGO_INICIAL_ADMIN
                                 << " y " << CODIGO_FINAL_ADMIN << "\n";
                            system("pause");
                        }
                    }
                } else {
                    cout << "\n\t\tAcceso denegado. Se requiere nivel 2 o superior.\n";
                    system("pause");
                }
                break;

            case 4:
                if (usuarioActual.getNivelAcceso() >= 3) {
                    Administracion::mostrar(listaAdministradores);
                    if (!listaAdministradores.empty()) {
                        cout << "\n\t\tIngrese ID del administrador a eliminar: ";
                        getline(cin, input);

                        if (Administracion::esIdValido(input)) {
                            if (input != usuarioActual.getId()) {
                                auto it = find_if(listaAdministradores.begin(), listaAdministradores.end(),
                                    [&input](const Administracion& a) { return a.getId() == input; });

                                if (it != listaAdministradores.end() && it->getNivelAcceso() < usuarioActual.getNivelAcceso()) {
                                    Administracion::eliminar(listaAdministradores, usuarioActual.getNombre(), input);
                                } else {
                                    cout << "\t\tNo puedes eliminar este administrador.\n";
                                    system("pause");
                                }
                            } else {
                                cout << "\t\tNo puedes eliminarte a ti mismo.\n";
                                system("pause");
                            }
                        } else {
                            cout << "\t\tID no valido. Debe estar entre " << CODIGO_INICIAL_ADMIN
                                 << " y " << CODIGO_FINAL_ADMIN << "\n";
                            system("pause");
                        }
                    }
                } else {
                    cout << "\n\t\tAcceso denegado. Se requiere nivel 3 (Administrador Superior).\n";
                    system("pause");
                }
                break;

            case 5:
                Administracion::guardarEnArchivo(listaAdministradores);
                return;

            default:
                cout << "\t\tOpcion no valida. Intente nuevamente.\n";
                system("pause");
        }
    } while (true);
}
