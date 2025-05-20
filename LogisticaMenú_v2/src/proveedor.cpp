// Angoly Araujo Mayo 2025
// 9959-24-17623

#include "proveedor.h"     // Cabecera que define la clase Proveedor
#include "bitacora.h"      // Cabecera para registrar operaciones en bitácora
#include <iostream>        // Entrada/salida estándar
#include <fstream>         // Manejo de archivos
#include <vector>          // Uso de vectores (listas dinámicas)
#include <algorithm>       // Funciones como find_if, none_of, etc.
#include <limits>          // Para numeric_limits
#include <cstring>         // Funciones para manejar cadenas de caracteres tipo C
#include <ctime>           // Manejo de tiempo (aunque no se usa aquí explícitamente)

using namespace std;

// Rango de códigos válidos para proveedores
const int CODIGO_INICIAL_PROV = 3158;
const int CODIGO_FINAL_PROV = 3208;

// Codifica una cadena con XOR para ocultar información
void Proveedor::codificar(char* data, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        data[i] ^= XOR_KEY;
    }
}

// Decodifica una cadena usando el mismo método XOR (es reversible)
void Proveedor::decodificar(char* data, size_t len) {
    codificar(data, len);
}

// Convierte un objeto Proveedor a su forma binaria codificada para almacenamiento
ProveedorRegistro Proveedor::toRegistro(const Proveedor& p) {
    ProveedorRegistro reg = {};
    strncpy(reg.id, p.id.c_str(), sizeof(reg.id) - 1);
    strncpy(reg.nombre, p.nombre.c_str(), sizeof(reg.nombre) - 1);
    strncpy(reg.telefono, p.telefono.c_str(), sizeof(reg.telefono) - 1);
    codificar(reg.id, sizeof(reg.id));
    codificar(reg.nombre, sizeof(reg.nombre));
    codificar(reg.telefono, sizeof(reg.telefono));
    return reg;
}

// Reconstruye un objeto Proveedor desde un registro codificado
Proveedor Proveedor::fromRegistro(const ProveedorRegistro& regCodificado) {
    ProveedorRegistro reg = regCodificado;
    decodificar(reg.id, sizeof(reg.id));
    decodificar(reg.nombre, sizeof(reg.nombre));
    decodificar(reg.telefono, sizeof(reg.telefono));
    Proveedor p;
    p.id = reg.id;
    p.nombre = reg.nombre;
    p.telefono = reg.telefono;
    return p;
}

// Genera un ID único disponible dentro del rango permitido
string Proveedor::generarIdUnico(const vector<Proveedor>& lista) {
    for (int i = CODIGO_INICIAL_PROV; i <= CODIGO_FINAL_PROV; ++i) {
        string id = to_string(i);
        if (idDisponible(lista, id)) return id;
    }
    return "";
}

// Verifica si un ID ya está siendo usado en la lista de proveedores
bool Proveedor::idDisponible(const vector<Proveedor>& lista, const string& id) {
    return none_of(lista.begin(), lista.end(), [&id](const Proveedor& p) { return p.id == id; });
}

// Verifica si un ID está dentro del rango permitido
bool Proveedor::esIdValido(const string& id) {
    try {
        int valor = stoi(id);
        return valor >= CODIGO_INICIAL_PROV && valor <= CODIGO_FINAL_PROV;
    } catch (...) {
        return false;
    }
}

// Guarda en bitácora una acción realizada sobre un proveedor
void Proveedor::guardarEnBitacora(const string& usuario, const string& operacion, const Proveedor& proveedor) {
    bitacora::registrar(usuario, "PROVEEDORES", operacion + " - ID: " + proveedor.getId());
}

// Agrega un nuevo proveedor a la lista
void Proveedor::agregar(vector<Proveedor>& lista, const string& usuarioActual) {
    int opcion;
    cout << "\n\t\tDesea volver al menu principal? (1: Si / 0: No): ";
    cin >> opcion;
    if (opcion == 1) return;

    Proveedor nuevo;
    nuevo.id = generarIdUnico(lista);

    if (nuevo.id.empty()) {
        cerr << "\n\t\tError: No hay codigos disponibles para nuevos proveedores.\n";
        system("pause");
        return;
    }

    cout << "\n\t\t=== AGREGAR PROVEEDOR (ID Auto-Asignado: " << nuevo.id << ") ===\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Solicita nombre hasta que no esté vacío
    do {
        cout << "\t\tNombre completo: ";
        getline(cin, nuevo.nombre);
    } while (nuevo.nombre.empty());

    // Solicita teléfono hasta que no esté vacío
    do {
        cout << "\t\tTelefono: ";
        getline(cin, nuevo.telefono);
    } while (nuevo.telefono.empty());

    lista.push_back(nuevo);
    guardarEnArchivoBinario(lista);
    guardarEnBitacora(usuarioActual, "Proveedor agregado", nuevo);
    cout << "\n\t\tProveedor registrado exitosamente.\n";
    system("pause");
}

// Muestra todos los proveedores en pantalla
void Proveedor::mostrar(const vector<Proveedor>& lista) {
    cout << "\n\t\t--- LISTA DE PROVEEDORES ---\n";
    for (const auto& p : lista) {
        cout << "\t\tID: " << p.getId()
             << " | Nombre: " << p.getNombre()
             << " | Telefono: " << p.getTelefono() << '\n';
    }
    system("pause");
}

// Permite modificar nombre y teléfono de un proveedor existente
void Proveedor::modificar(vector<Proveedor>& lista, const string& usuarioActual, const string& /*idDummy*/) {
    int opcion;
    cout << "\n\t\tDesea volver al menu principal? (1: Si / 0: No): ";
    cin >> opcion;
    if (opcion == 1) return;

    mostrar(lista);
    string id;
    cout << "\n\t\tIngrese el ID del proveedor a modificar: ";
    cin >> id;

    auto it = find_if(lista.begin(), lista.end(), [&id](const Proveedor& p) { return p.getId() == id; });

    if (it != lista.end()) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\n\t\t--- MODIFICAR PROVEEDOR (ID: " << id << ") ---\n";

        string nuevoNombre, nuevoTelefono;

        // Pide nuevo nombre (opcional)
        cout << "\t\tNuevo nombre (" << it->getNombre() << "): ";
        getline(cin, nuevoNombre);
        if (!nuevoNombre.empty()) it->setNombre(nuevoNombre);

        // Pide nuevo teléfono (opcional)
        cout << "\t\tNuevo telefono (" << it->getTelefono() << "): ";
        getline(cin, nuevoTelefono);
        if (!nuevoTelefono.empty()) it->setTelefono(nuevoTelefono);

        guardarEnArchivoBinario(lista);
        guardarEnBitacora(usuarioActual, "Proveedor modificado", *it);
        cout << "\n\t\tProveedor modificado correctamente.\n";
    } else {
        cout << "\n\t\tProveedor no encontrado.\n";
    }
    system("pause");
}

// Elimina un proveedor de la lista si existe
void Proveedor::eliminar(vector<Proveedor>& lista, const string& usuarioActual, const string& /*idDummy*/) {
    int opcion;
    cout << "\n\t\tDesea volver al menu principal? (1: Si / 0: No): ";
    cin >> opcion;
    if (opcion == 1) return;

    mostrar(lista);
    string id;
    cout << "\n\t\tIngrese el ID del proveedor a eliminar: ";
    cin >> id;

    auto it = find_if(lista.begin(), lista.end(), [&id](const Proveedor& p) { return p.getId() == id; });

    if (it != lista.end()) {
        guardarEnBitacora(usuarioActual, "Proveedor eliminado", *it);
        lista.erase(it);
        guardarEnArchivoBinario(lista);
        cout << "\n\t\tProveedor eliminado correctamente.\n";
    } else {
        cout << "\n\t\tProveedor no encontrado.\n";
    }
    system("pause");
}

// Guarda la lista de proveedores en un archivo binario, codificados
void Proveedor::guardarEnArchivoBinario(const vector<Proveedor>& lista) {
    ofstream archivo("Proveedores.bin", ios::binary | ios::trunc);
    if (!archivo) {
        cerr << "\n\t\tError: No se pudo abrir Proveedores.bin para escritura.\n";
        return;
    }

    for (const auto& p : lista) {
        ProveedorRegistro reg = toRegistro(p);
        archivo.write(reinterpret_cast<const char*>(&reg), sizeof(reg));
    }

    archivo.close();
}

// Carga los proveedores desde el archivo binario y los decodifica
void Proveedor::cargarDesdeArchivoBinario(vector<Proveedor>& lista) {
    lista.clear();
    ifstream archivo("Proveedores.bin", ios::binary);
    if (!archivo) return;

    ProveedorRegistro reg;
    while (archivo.read(reinterpret_cast<char*>(&reg), sizeof(reg))) {
        lista.push_back(fromRegistro(reg));
    }

    archivo.close();
}

// Funciones auxiliares que permiten usar la clase desde main.cpp
void Proveedor::guardarEnArchivo(vector<Proveedor>& lista) {
    guardarEnArchivoBinario(lista);
}
void Proveedor::cargarDesdeArchivo(vector<Proveedor>& lista) {
    cargarDesdeArchivoBinario(lista);
}

