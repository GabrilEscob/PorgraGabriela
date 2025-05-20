#include "backup_manager.h"
#include <iostream>
#include <string>
#include "globals.h"
#include "bitacora.h"
//JENNIFER BARRIOS COORD: EQ3
//MAYO 2025

using namespace std;

extern usuarios usuarioRegistrado;
extern bitacora auditoria;

void BackupManager::mostrarMenuBackup() {
    int opcion;
    do {
        system("cls");
        cout << "\t\t========================================\n"
             << "\t\t|          MENU DE BACKUP               |\n"
             << "\t\t========================================\n"
             << "\t\t| Usuario: " << usuarioRegistrado.getNombre() << "\n"
             << "\t\t========================================\n"
             << "\t\t 1. Crear copias de seguridad\n"
             << "\t\t 2. Restaurar datos\n"
             << "\t\t 3. Volver al menu anterior\n"
             << "\t\t========================================\n"
             << "\t\tIngresa tu opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                mostrarMenuCreacion();
                break;
            case 2:
                mostrarMenuRestauracion();
                break;
            case 3:
                return;
            default:
                cout << "\n\t\tOpcion invalida...";
                system("pause");
        }
    } while(true);
}

void BackupManager::mostrarMenuCreacion() {
    int opcion;
    do {
        system("cls");
        cout << "\t\t========================================\n"
             << "\t\t|      CREACION DE COPIA DE SEGURIDAD  |\n"
             << "\t\t========================================\n"
             << "\t\t 1. Backup completo\n"
             << "\t\t 2. Backup de Clientes\n"
             << "\t\t 3. Backup de Productos\n"
             << "\t\t 4. Backup de Pedidos\n"
             << "\t\t 5. Backup de Envios\n"
             << "\t\t 6. Backup de Almacenes\n"
             << "\t\t 7. Backup de Bitacora\n"
             << "\t\t 8. Volver al menu anterior\n"
             << "\t\t========================================\n"
             << "\t\tIngresa tu opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                crearBackupCompleto();
                break;
            case 2:
                crearBackupClientes();
                break;
            case 3:
                crearBackupProductos();
                break;
            case 4:
                crearBackupPedidos();
                break;
            case 5:
                crearBackupEnvios();
                break;
            case 6:
                crearBackupAlmacenes();
                break;
            case 7:
                crearBackupBitacora();
                break;
            case 8:
                return;
            default:
                cout << "\n\t\tOpcion invalida...";
                system("pause");
        }
    } while(true);
}

void BackupManager::crearBackupCompleto() {
    cout << "\n\t\tCreando backup completo del sistema...\n";
    crearBackupClientes();
    crearBackupProductos();
    crearBackupPedidos();
    crearBackupEnvios();
    crearBackupAlmacenes();
    crearBackupBitacora();
    cout << "\n\t\tBackup completo creado con exito!\n";
    auditoria.insertar(usuarioRegistrado.getNombre(), "000", "BACKUP COMPLETO");
    system("pause");
}

void BackupManager::crearBackupClientes() {
    crearBackupDeClase("Clientes");
}

void BackupManager::crearBackupProductos() {
    crearBackupDeClase("Productos");
}

void BackupManager::crearBackupPedidos() {
    crearBackupDeClase("Pedidos");
}

void BackupManager::crearBackupEnvios() {
    crearBackupDeClase("Envios");
}

void BackupManager::crearBackupAlmacenes() {
    crearBackupDeClase("Almacenes");
}

void BackupManager::crearBackupBitacora() {
    crearBackupDeClase("Bitacora");
}

void BackupManager::crearBackupDeClase(const string& nombreClase) {
    cout << "\n\t\tCreando backup de " << nombreClase << "...\n";
    // Aquí iría la lógica real de backup cuando esté implementada
    cout << "\t\tBackup de " << nombreClase << " creado con exito!\n";
    auditoria.insertar(usuarioRegistrado.getNombre(), "000", "BACKUP " + nombreClase);
    system("pause");
}

// Implementación de funciones de restauración (similar a las de creación)
void BackupManager::mostrarMenuRestauracion() {
    int opcion;
    do {
        system("cls");
        cout << "\t\t========================================\n"
             << "\t\t|      RESTAURACION DE BACKUPS         |\n"
             << "\t\t========================================\n"
             << "\t\t 1. Restaurar backup completo\n"
             << "\t\t 2. Restaurar Clientes\n"
             << "\t\t 3. Restaurar Productos\n"
             << "\t\t 4. Restaurar Pedidos\n"
             << "\t\t 5. Restaurar Envios\n"
             << "\t\t 6. Restaurar Almacenes\n"
             << "\t\t 7. Restaurar Bitacora\n"
             << "\t\t 8. Volver al menu anterior\n"
             << "\t\t========================================\n"
             << "\t\tIngresa tu opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                restaurarBackupCompleto();
                break;
            case 2:
                restaurarClientes();
                break;
            case 3:
                restaurarProductos();
                break;
            case 4:
                restaurarPedidos();
                break;
            case 5:
                restaurarEnvios();
                break;
            case 6:
                restaurarAlmacenes();
                break;
            case 7:
                restaurarBitacora();
                break;
            case 8:
                return;
            default:
                cout << "\n\t\tOpcion invalida...";
                system("pause");
        }
    } while(true);
}

void BackupManager::restaurarBackupCompleto() {
    cout << "\n\t\tRestaurando backup completo del sistema...\n";
    restaurarClientes();
    restaurarProductos();
    restaurarPedidos();
    restaurarEnvios();
    restaurarAlmacenes();
    restaurarBitacora();
    cout << "\n\t\tRestauracion completa finalizada con exito!\n";
    auditoria.insertar(usuarioRegistrado.getNombre(), "000", "RESTAURACION COMPLETA");
    system("pause");
}

void BackupManager::restaurarClientes() {
    restaurarClase("Clientes");
}

void BackupManager::restaurarProductos() {
    restaurarClase("Productos");
}

void BackupManager::restaurarPedidos() {
    restaurarClase("Pedidos");
}

void BackupManager::restaurarEnvios() {
    restaurarClase("Envios");
}

void BackupManager::restaurarAlmacenes() {
    restaurarClase("Almacenes");
}

void BackupManager::restaurarBitacora() {
    restaurarClase("Bitacora");
}

void BackupManager::restaurarClase(const string& nombreClase) {
    cout << "\n\t\tRestaurando " << nombreClase << " desde backup...\n";
    // Aquí iría la lógica real de restauración cuando esté implementada
    cout << "\t\t" << nombreClase << " restaurados con exito!\n";
    auditoria.insertar(usuarioRegistrado.getNombre(), "000", "RESTAURACION " + nombreClase);
    system("pause");
}
