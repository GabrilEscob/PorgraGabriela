#ifndef JUEGO_H
#define JUEGO_H
#include "Tablero.h"

class Juego
{
private:
    Tablero tablero;
    int cantidadMinas;

    int aleatorio_en_rango(int minimo, int maximo);
    int filaAleatoria();
    int columnaAleatoria();
public:
    Juego(Tablero tablero, int cantidadMinas);
    void colocarMinasAleatoriamente();
    int solicitarFilaUsuario();
    int solicitarColumnaUsuario();
    bool jugadorGana();
    void iniciar();  // Asegúrate de que esté declarado
    void dibujarPortada(string nombreArchivo);
};

#endif // JUEGO_H
