#include "MenuArchivo.h"
#include "usuarios.h"
#include <iostream>
#include "globals.h"
//#include "backup_manager.h"

//JENNIFER BARRIOS COORD: EQ3

using namespace std;

extern usuarios usuarioRegistrado;
extern bitacora auditoria;

void MenuArchivo::mostrar() {
    int opcion;
    do {
        system("cls");
        cout << "\t\t========================================\n"
             << "\t\t|          MENU ARCHIVO                |\n"
             << "\t\t========================================\n"
             << "\t\t| Usuario: " << usuarioRegistrado.getNombre() << "\n"
             << "\t\t========================================\n"
             << "\t\t 1. Cerrar sesion\n"
             << "\t\t 2. Backup\n"
             << "\t\t 3. Volver al menu principal\n"
             << "\t\t========================================\n"
             << "\t\tIngresa tu opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1: {
                if(cerrarSesion()) {
                    usuarios user;
                    user.loginUsuarios();
                    return;
                }
                break;
            }
            case 2:
               // BackupManager::mostrarMenuBackup();  // Llamar al menú de backup
                break;
            case 3:
                return;
            default:
                cout << "\n\t\tOpcion invalida...";
                system("pause");
        }
    } while(true);
}

bool MenuArchivo::cerrarSesion() {
    char confirmacion;
    cout << "\n\t\t ¿Esta seguro que desea cerrar sesion? (S/N): ";
    cin >> confirmacion;

    if(toupper(confirmacion) == 'S') {
        auditoria.insertar(usuarioRegistrado.getNombre(), "000", "LOGOUT");
        cout << "\n\t\tSesion cerrada correctamente.\n";
        system("pause");
        usuarioRegistrado = usuarios();
        return true;
    }
    cout << "\n\t\tOperacion cancelada.\n";
    system("pause");
    return false;
}
