#ifndef BACKUP_MANAGER_H
#define BACKUP_MANAGER_H
//CREADO POR: JENNIFER BARRIOS.
#include <string>
#include <vector>

class BackupManager {
public:
    // Menú principal de backup
    static void mostrarMenuBackup();
    static void mostrarMenuCreacion();  // Añadido

    // Funciones de creación de backups
    static void crearBackupCompleto();
    static void crearBackupClientes();
    static void crearBackupProductos();
    static void crearBackupPedidos();
    static void crearBackupEnvios();
    static void crearBackupAlmacenes();
    static void crearBackupBitacora();

    // Funciones de restauración
    static void mostrarMenuRestauracion();
    static void restaurarBackupCompleto();
    static void restaurarClientes();
    static void restaurarProductos();
    static void restaurarPedidos();
    static void restaurarEnvios();
    static void restaurarAlmacenes();
    static void restaurarBitacora();

private:
    static void crearBackupDeClase(const std::string& nombreClase);
    static void restaurarClase(const std::string& nombreClase);
};

#endif // BACKUP_MANAGER_H
