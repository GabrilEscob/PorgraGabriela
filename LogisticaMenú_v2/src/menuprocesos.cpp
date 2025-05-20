#include "MenuProcesos.h"
#include "usuarios.h"
#include <iostream>
#include "pedidos.h"
#include "inventario.h"
#include "envios.h"
#include "facturacion.h"
#include "reportes.h"
#include "globals.h"
#include "clientes.h"
#include "producto.h"
#include "Almacen.h"

///CREADO POR: JENNIFER BARRIOS EQ3

using namespace std;

// Declaración externa del usuario registrado actual
extern usuarios usuarioRegistrado;

// Muestra el menú principal de procesos y redirige según la opción elegida
void MenuProcesos::mostrar(std::vector<Clientes>& clientes,
                         std::vector<Producto>& productos,
                         std::vector<Almacen>& almacenes) {
    int choice;
    do {
        // Limpiar pantalla antes de mostrar el menú
        system("cls");

        // Mostrar encabezado del menú y nombre del usuario actual
        cout << "\t\t========================================\n"
             << "\t\t|          MENU DE PROCESOS            |\n"
             << "\t\t========================================\n"
             << "\t\t| Usuario: " << usuarioRegistrado.getNombre() << "\n"
             << "\t\t========================================\n"
             << "\t\t 1. Gestion de Pedidos\n"
             << "\t\t 2. Control de Inventario\n"
             << "\t\t 3. Envios y Transportes\n"
             << "\t\t 4. Facturacion\n"
             << "\t\t 5. Reportes\n"
             << "\t\t 6. Volver\n"
             << "\t\t========================================\n"
             << "\t\tIngresa tu opcion: ";

        cin >> choice;

        switch(choice) {
            case 1:
                {
                    Pedidos gestorPedidos;
                    gestorPedidos.gestionPedidos(clientes, productos, almacenes);
                }
                break;

            case 2:
                {
                    Inventario gestorInventario;
                    gestorInventario.controlInventario(); // Cambiado a controlInventario
                }
                break;

            case 3:
                {
                    Envios gestorEnvios;
                    gestorEnvios.gestionEnvios();
                }
                break;

            case 4:
                {
                    Facturacion gestorFacturacion;
                    gestorFacturacion.mostrarMenuFacturacion();
                }
                break;

            case 5:
                {
                    Reportes gestorReportes;
                    gestorReportes.generarReportes();
                }
                break;

            case 6:
                // Salir del menú de procesos
                return;

            default:
                // Manejar opción inválida
                cout << "\n\t\tOpcion invalida...";
        }

        // Esperar una tecla antes de volver a mostrar el menú
        cin.ignore(); // Limpiar buffer
        cin.get();    // Esperar entrada del usuario
    } while(choice != 6); // Repetir hasta que se seleccione salir
}
