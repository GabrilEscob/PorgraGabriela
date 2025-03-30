#include "Juego.h"
#include <fstream>
#include <unistd.h>
#include <ctime> // Para medir el tiempo
#include <iomanip> // Para formatear la salida

int Juego::aleatorio_en_rango(int minimo, int maximo)
{
    return minimo + rand() / (RAND_MAX / (maximo - minimo + 1) + 1);
}

int Juego::filaAleatoria()
{
    return this->aleatorio_en_rango(0, this->tablero.getAlturaTablero() - 1);
}

int Juego::columnaAleatoria()
{
    return this->aleatorio_en_rango(0, this->tablero.getAnchoTablero() - 1);
}

Juego::Juego(Tablero tablero, int cantidadMinas)
{
    this->tablero = tablero;
    this->cantidadMinas = cantidadMinas;
    this->colocarMinasAleatoriamente();
}

void Juego::colocarMinasAleatoriamente()
{
    int x, y, minasColocadas = 0;

    while (minasColocadas < this->cantidadMinas)
    {
        x = this->columnaAleatoria();
        y = this->filaAleatoria();
        if (this->tablero.colocarMina(x, y))
        {
            minasColocadas++;
        }
    }
}

int Juego::solicitarFilaUsuario()
{
    int fila = 0;
    cout << "Ingresa la FILA en la que desea jugar: ";
    cin >> fila;
    return fila - 1;
}

int Juego::solicitarColumnaUsuario()
{
    int columna = 0;
    cout << "Ingresa la COLUMNA en la que desea jugar: ";
    cin >> columna;
    return columna - 1;
}

bool Juego::jugadorGana()
{
    int conteo = this->tablero.contarCeldasSinMinasYSinDescubrir();
    return conteo == 0;
}

void Juego::iniciar()
{
    int fila, columna;
    time_t tiempoInicio = time(nullptr); // Guarda el tiempo de inicio

    while (true)
    {
        this->tablero.imprimir();
        fila = this->solicitarFilaUsuario();
        columna = this->solicitarColumnaUsuario();
        bool respuestaAUsuario = this->tablero.descubrirMina(columna, fila);

        if (!respuestaAUsuario)
        {
            cout << "Perdiste el Juego\n";
            this->tablero.setModoDesarrollador(true);
            this->tablero.imprimir();
            break;
        }

        if (this->jugadorGana())
        {
            cout << "Ganaste el Juego\n";
            this->tablero.setModoDesarrollador(true);
            this->tablero.imprimir();
            break;
        }
    }

    time_t tiempoFinal = time(nullptr); // Guarda el tiempo de finalización
    int tiempoTotal = difftime(tiempoFinal, tiempoInicio); // Calcula la diferencia en segundos

    // Convertimos a formato legible
    int horas = tiempoTotal / 3600;
    int minutos = (tiempoTotal % 3600) / 60;
    int segundos = tiempoTotal % 60;

    cout << "Tiempo total de juego: ";
    if (horas > 0) cout << horas << " horas, ";
    if (minutos > 0) cout << minutos << " minutos, ";
    cout << segundos << " segundos.\n";
}
