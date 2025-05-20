//9959 24 11603 GABRIELA ESCOBAR
#include "Almacen.h"
#include "bitacora.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <cstring>

using namespace std;

// Constantes para validacion de IDs
// Rango valido: 3260 a 3310
const int Almacen::CODIGO_INICIAL = 3260;
const int Almacen::CODIGO_FINAL = 3310;

// Aplica codificacion XOR a un bloque de datos
// data: Puntero a los datos a codificar
// len: Longitud de los datos
void Almacen::codificar(char* data, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        data[i] ^= XOR_KEY;
    }
}

// Decodifica datos codificados con XOR
// Reutiliza codificar porque XOR es reversible
void Almacen::decodificar(char* data, size_t len) {
    codificar(data, len);
}

// Convierte objeto Almacen a estructura AlmacenRegistro
// Devuelve estructura con los datos del almacen
AlmacenRegistro Almacen::toRegistro(const Almacen& a) {
    AlmacenRegistro reg = {};
    strncpy(reg.id, a.id.c_str(), sizeof(reg.id) - 1);
    strncpy(reg.direccion, a.direccion.c_str(), sizeof(reg.direccion) - 1);
    reg.capacidad = a.capacidad;
    strncpy(reg.responsable, a.responsable.c_str(), sizeof(reg.responsable) - 1);
    strncpy(reg.contacto, a.contacto.c_str(), sizeof(reg.contacto) - 1);
    strncpy(reg.estado, a.estado.c_str(), sizeof(reg.estado) - 1);
    return reg;
}

// Convierte estructura AlmacenRegistro a objeto Almacen
// Devuelve objeto Almacen con los datos
Almacen Almacen::fromRegistro(const AlmacenRegistro& reg) {
    Almacen a;
    a.id = string(reg.id);
    a.direccion = string(reg.direccion);
    a.capacidad = reg.capacidad;
    a.responsable = string(reg.responsable);
    a.contacto = string(reg.contacto);
    a.estado = string(reg.estado);
    return a;
}

// Genera un ID unico dentro del rango permitido
// lista: Lista actual de almacenes
// Devuelve string con ID o vacio si no hay disponibles
string Almacen::generarIdUnico(const vector<Almacen>& lista) {
    for (int i = CODIGO_INICIAL; i <= CODIGO_FINAL; ++i) {
        string id = to_string(i);
        if (idDisponible(lista, id)) {
            return id;
        }
    }
    return "";
}

// Verifica si un ID no esta en uso
// lista: Lista de almacenes
// id: ID a verificar
// Devuelve true si el ID esta disponible
bool Almacen::idDisponible(const vector<Almacen>& lista, const string& id) {
    return none_of(lista.begin(), lista.end(),
        [&id](const Almacen& a) { return a.id == id; });
}

// Valida que un ID este dentro del rango numerico permitido
// id: ID a validar
// Devuelve true si el ID es valido
bool Almacen::esIdValido(const string& id) {
    try {
        int num = stoi(id);
        return (num >= CODIGO_INICIAL && num <= CODIGO_FINAL);
    } catch (...) {
        return false;
    }
}

// Valida que el estado sea "operativo" o "en mantenimiento"
// estado: Estado a validar
// Devuelve true si el estado es valido
bool Almacen::validarEstado(const string& estado) {
    return (estado == "operativo" || estado == "en mantenimiento");
}

// Agrega un nuevo almacen a la lista
// lista: Referencia a la lista de almacenes
// usuarioActual: Usuario que realiza la operacion
void Almacen::agregar(vector<Almacen>& lista, const string& usuarioActual) {
    Almacen nuevo;
    nuevo.id = generarIdUnico(lista);

    if (nuevo.id.empty()) {
        cerr << "\nError: No hay IDs disponibles\n";
        system("pause");
        return;
    }

    cout << "\n=== AGREGAR ALMACEN (ID: " << nuevo.id << ") ===\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Direccion: ";
    getline(cin, nuevo.direccion);

    cout << "Capacidad (m²): ";
    while (!(cin >> nuevo.capacidad) || nuevo.capacidad <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Error: Ingrese un valor positivo: ";
    }

    cin.ignore();
    cout << "Responsable: ";
    getline(cin, nuevo.responsable);

    cout << "Contacto: ";
    getline(cin, nuevo.contacto);

    cout << "Estado (operativo/en mantenimiento): ";
    while (getline(cin, nuevo.estado) && !validarEstado(nuevo.estado)) {
        cout << "Estado invalido. Ingrese 'operativo' o 'en mantenimiento': ";
    }

    lista.push_back(nuevo);
    guardarEnArchivoBinario(lista);
    bitacora::registrar(usuarioActual, "ALMACEN", "Almacen creado - ID: " + nuevo.id);
    cout << "\nAlmacen registrado exitosamente!\n";
    system("pause");
}

// Muestra todos los almacenes en la lista
// lista: Lista de almacenes a mostrar
void Almacen::mostrar(const vector<Almacen>& lista) {
    cout << "\n=== LISTA DE ALMACENES ===\n";
    for (const auto& a : lista) {
        cout << "ID: " << a.id << "\n"
             << "Direccion: " << a.direccion << "\n"
             << "Capacidad: " << a.capacidad << " m²\n"
             << "Responsable: " << a.responsable << "\n"
             << "Contacto: " << a.contacto << "\n"
             << "Estado: " << a.estado << "\n"
             << "-----------------------\n";
    }
    system("pause");
}

// Modifica un almacen existente
// lista: Referencia a la lista de almacenes
// usuarioActual: Usuario que realiza la operacion
// id: ID del almacen a modificar
void Almacen::modificar(vector<Almacen>& lista, const string& usuarioActual, const string& id) {
    auto it = find_if(lista.begin(), lista.end(),
        [&id](const Almacen& a) { return a.id == id; });

    if (it != lista.end()) {
        cout << "\n=== MODIFICAR ALMACEN (ID: " << id << ") ===\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Nueva direccion (" << it->direccion << "): ";
        getline(cin, it->direccion);

        cout << "Nueva capacidad (" << it->capacidad << " m²): ";
        while (!(cin >> it->capacidad) || it->capacidad <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error: Ingrese un valor positivo: ";
        }

        cin.ignore();
        cout << "Nuevo responsable (" << it->responsable << "): ";
        getline(cin, it->responsable);

        cout << "Nuevo contacto (" << it->contacto << "): ";
        getline(cin, it->contacto);

        cout << "Nuevo estado (" << it->estado << "): ";
        while (getline(cin, it->estado) && !validarEstado(it->estado)) {
            cout << "Estado invalido. Ingrese 'operativo' o 'en mantenimiento': ";
        }

        guardarEnArchivoBinario(lista);
        bitacora::registrar(usuarioActual, "ALMACEN", "Almacen modificado - ID: " + id);
        cout << "\nAlmacen modificado exitosamente!\n";
    } else {
        cerr << "\nError: Almacen no encontrado\n";
    }
    system("pause");
}

// Elimina un almacen de la lista
// lista: Referencia a la lista de almacenes
// usuarioActual: Usuario que realiza la operacion
// id: ID del almacen a eliminar
void Almacen::eliminar(vector<Almacen>& lista, const string& usuarioActual, const string& id) {
    auto it = find_if(lista.begin(), lista.end(),
        [&id](const Almacen& a) { return a.id == id; });

    if (it != lista.end()) {
        lista.erase(it);
        guardarEnArchivoBinario(lista);
        bitacora::registrar(usuarioActual, "ALMACEN", "Almacen eliminado - ID: " + id);
        cout << "\nAlmacen eliminado exitosamente!\n";
    } else {
        cerr << "\nError: Almacen no encontrado\n";
    }
    system("pause");
}

// Guarda todos los almacenes en archivo binario con codificacion XOR
// lista: Lista de almacenes a guardar
void Almacen::guardarEnArchivoBinario(const vector<Almacen>& lista) {
    ofstream archivo("Almacenes.bin", ios::binary | ios::out | ios::trunc);
    if (!archivo) {
        cerr << "\nError critico: No se pudo abrir Almacenes.bin\n";
        return;
    }

    for (const auto& a : lista) {
        AlmacenRegistro reg = toRegistro(a);
        codificar(reg.id, sizeof(reg.id));
        codificar(reg.direccion, sizeof(reg.direccion));
        codificar(reinterpret_cast<char*>(&reg.capacidad), sizeof(reg.capacidad));
        codificar(reg.responsable, sizeof(reg.responsable));
        codificar(reg.contacto, sizeof(reg.contacto));
        codificar(reg.estado, sizeof(reg.estado));

        archivo.write(reinterpret_cast<const char*>(&reg), sizeof(reg));
    }
    archivo.close();
}

// Carga almacenes desde archivo binario con decodificacion XOR
// lista: Lista donde se cargaran los almacenes
void Almacen::cargarDesdeArchivoBinario(vector<Almacen>& lista) {
    lista.clear();
    ifstream archivo("Almacenes.bin", ios::binary);
    if (!archivo) {
        cerr << "\nArchivo Almacenes.bin no encontrado. Se creara al guardar.\n";
        return;
    }

    AlmacenRegistro reg;
    while (archivo.read(reinterpret_cast<char*>(&reg), sizeof(reg))) {
        decodificar(reg.id, sizeof(reg.id));
        decodificar(reg.direccion, sizeof(reg.direccion));
        decodificar(reinterpret_cast<char*>(&reg.capacidad), sizeof(reg.capacidad));
        decodificar(reg.responsable, sizeof(reg.responsable));
        decodificar(reg.contacto, sizeof(reg.contacto));
        decodificar(reg.estado, sizeof(reg.estado));

        Almacen a = fromRegistro(reg);

        if (!esIdValido(a.id)) continue;
        if (!validarEstado(a.estado)) continue;
        if (!idDisponible(lista, a.id)) continue;

        lista.push_back(a);
    }
}

// Guarda la lista de almacenes en archivo (alias de guardarEnArchivoBinario)
// lista: Lista de almacenes a guardar
void Almacen::guardarEnArchivo(vector<Almacen>& lista) {
    guardarEnArchivoBinario(lista);
}

// Carga la lista de almacenes desde archivo (alias de cargarDesdeArchivoBinario)
// lista: Lista donde se cargaran los almacenes
void Almacen::cargarDesdeArchivo(vector<Almacen>& lista) {
    cargarDesdeArchivoBinario(lista);
}
