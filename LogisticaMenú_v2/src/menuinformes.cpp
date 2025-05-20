// Angoly Araujo Mayo 2025
#include "menuinformes.h"
#include <iostream>
#include <cstdlib> // Para system("cls")
using namespace std;

void MenuInformes::mostrar() {
    int opcion;
    do {
        system("cls");
        cout << "\t\t========================================\n"
             << "\t\t|          SUBMENÚ DE INFORMES         |\n"
             << "\t\t========================================\n"
             << "\t\t 1. Informe diario de operaciones\n"
             << "\t\t 2. Informe mensual de ventas\n"
             << "\t\t 3. Resumen de inventario\n"
             << "\t\t 4. Histórico de envíos\n"
             << "\t\t 5. Exportar datos maestros\n"
             << "\t\t 6. Volver al menú principal\n"
             << "\t\t========================================\n"
             << "\t\tIngresa tu opción: ";

        cin >> opcion;

        switch(opcion) {
            case 1:
                cout << "\n\t\t[Generando Informe Diario de Operaciones...]\n";
                // Lógica para generar informe diario
                break;

            case 2:
                cout << "\n\t\t[Generando Informe Mensual de Ventas...]\n";
                // Lógica para generar informe mensual
                break;

            case 3:
                cout << "\n\t\t[Generando Resumen de Inventario...]\n";
                // Lógica para generar resumen de inventario
                break;

            case 4:
                cout << "\n\t\t[Generando Histórico de Envíos...]\n";
                // Lógica para generar histórico de envíos
                break;

            case 5:
                cout << "\n\t\t[Exportando Datos Maestros...]\n";
                // Lógica para exportar datos
                break;

            case 6:
                cout << "\n\t\tVolviendo al menú principal...\n";
                break;

            default:
                cout << "\n\t\tOpción inválida... Intenta de nuevo.\n";
        }

        if (opcion != 6) {
            system("pause");
        }

    } while(opcion != 6);
}
