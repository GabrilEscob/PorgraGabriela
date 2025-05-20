//Karina Alejandra Arriaza Ortiz 9959-24-14190
#ifndef MENUTRANSPORTISTAS_H
#define MENUTRANSPORTISTAS_H

#include <vector>
#include "transportistas.h"
#include "usuarios.h"

class MenuTransportistas {
public:
    static void mostrar(std::vector<Transportistas>& lista, usuarios& usuarioActual);
};


#endif // MENUTRANSPORTISTAS_H
