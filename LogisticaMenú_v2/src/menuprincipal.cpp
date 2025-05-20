#include "menuprincipal.h"
#include "menuarchivo.h"
#include "menucatalogos.h"
#include "menuprocesos.h"
#include "menuinformes.h"
#include "usuarios.h"
#include "bitacora.h"
#include <vector>
#include <iostream>
using namespace std;

//Creado JENNIFER ALBA DAYAMI BARRIOS FLORES
//9959-24-10016
//MAYO 2025
// Modificado por Camila Araujo

void MenuPrincipal::mostrar(std::vector<Clientes>& clientes,
                          std::vector<Proveedor>& proveedores,
                          std::vector<Producto>& productos,
                          std::vector<Almacen>& almacenes,
                          std::vector<Administracion>& administradores,
                          std::vector<Transportistas>& transportistas,
                          usuarios& usuarioActual) {
    int choice;
    do {
        system("cls");

        cout << "\t\t========================================\n"
             << "\t\t|     SISTEMA DE GESTION LOGISTICA     |\n"
             << "\t\t========================================\n"
             << "\t\t| Usuario: " << usuarioActual.getNombre() << "\n"
             << "\t\t================================================\n"
             << "\t\t 1. Archivo\n"
             << "\t\t 2. Catalogos\n"
             << "\t\t 3. Procesos\n"
             << "\t\t 4. Informes\n"
             << "\t\t 5. Bitacora\n"
             << "\t\t 6. Salir\n"
             << "\t\t========================================\n"
             << "\t\tIngresa tu opcion: ";

        cin >> choice;

        switch(choice) {
            case 1:
                MenuArchivo::mostrar();
                break;

            case 2:
                MenuCatalogos::mostrar(clientes, proveedores, productos,
                                     almacenes, administradores,
                                     transportistas, usuarioActual);
                break;

            case 3:
                // Llamada corregida pasando los vectores necesarios
                MenuProcesos menuProcesos;
                menuProcesos.mostrar(clientes, productos, almacenes);
                break;

            case 4:
                MenuInformes::mostrar();
                break;

            case 5: {
                bitacora b;
                b.menuBitacora();
                break;
            }

            case 6:
                return;

            default:
                cout << "\n\t\tOpcion invalida... Intenta de nuevo...";
        }
    } while(choice != 6);
}

