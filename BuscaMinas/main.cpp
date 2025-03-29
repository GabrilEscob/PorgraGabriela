#include <iostream>   // Biblioteca estándar para entrada y salida
#include <unistd.h>   // Biblioteca para getpid() (Unix/Linux)
#include "Juego.h"    // Archivo de encabezado que contiene la clase Juego
#include "Config.h"   // Archivo de encabezado que contiene la clase Config

using namespace std;

int main()
{
    // Definición de constantes para la configuración inicial del juego
    const int FILASTABLERO = 5;       // Número de filas del tablero
    const int COLUMNASTABLERO = 5;    // Número de columnas del tablero
    const int MINASENTABLERO = 3;     // Número de minas en el tablero
    const bool MODODESARROLLADOR = true; // Activa el modo desarrollador (muestra las minas)
    const int VIDASTABLERO = 3;       // Número de vidas del jugador

    // Se crea un objeto de la clase Config para almacenar la configuración del juego
    Config configuracionJuego(FILASTABLERO, COLUMNASTABLERO, MINASENTABLERO, MODODESARROLLADOR, VIDASTABLERO);

    // Se inicializa el juego con un tablero basado en la configuración establecida
    Juego juego(Tablero(configuracionJuego.getfilasTablero(),
                        configuracionJuego.getcolumnasTablero(),
                        configuracionJuego.getmodoDesarrolladorTablero()),
                configuracionJuego.getminasTablero());

    // Inicializa la semilla de números aleatorios usando el ID del proceso
    srand(getpid());

    int opciones;        // Variable para almacenar la opción elegida en el menú
    bool repetir = true; // Variable de control para mantener el menú activo

    // Bucle que mantiene activo el menú del juego hasta que el usuario decida salir
    do
    {
        system("cls"); // Limpia la pantalla (en Windows)

        // Muestra el menú principal del juego
        cout << "\n\n\t\tBUSCA MINAS -Menu-" << endl;
        cout << "\t\t-------------------" << endl;
        cout << "\t\t1. Configuracion del Juego" << endl;
        cout << "\t\t2. Iniciar el Juego" << endl;
        cout << "\t\t3. Salir del Juego" << endl;
        cout << "\n\t\tIngrese una opcion: ";
        cin >> opciones; // Captura la opción ingresada por el usuario

        // Estructura switch para manejar las opciones del menú
        switch (opciones)
        {
            case 1:
                // Llama al menú de configuración para modificar los parámetros del juego
                configuracionJuego.menuConfiguracion();
                break;

            case 2:
            {
                // Se crea un objeto Juego temporal con la configuración actualizada
                Juego juegoTemporal(Tablero(configuracionJuego.getfilasTablero(),
                                            configuracionJuego.getcolumnasTablero(),
                                            configuracionJuego.getmodoDesarrolladorTablero()),
                                    configuracionJuego.getminasTablero());
                // Se inicia el juego
                juegoTemporal.iniciar();

                // Pausa la ejecución para que el usuario pueda ver el resultado antes de continuar
                system("pause");
                break;
            }

            case 3:
                // Cambia la variable de control para salir del bucle y terminar el programa
                repetir = false;
                break;
        }
    } while (repetir); // El bucle se repite mientras 'repetir' sea verdadero

    system("cls"); // Limpia la pantalla antes de salir del programa
    return 0;      // Finaliza la ejecución correctamente
}
