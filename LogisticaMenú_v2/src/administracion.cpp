//Karina Alejandra Arriaza Ortiz 9959-24-14190
#include "administracion.h"
#include <iostream>
#include <vector>
#include "transportistas.h"
#include "globals.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <fstream>
#include "bitacora.h"
#include <sstream>
#include <iomanip>
#include <string>
#include <limits> // Para numeric_limits


using namespace std;

// Rango de c�digos para administradores
const int CODIGO_INICIAL_ADMIN = 3362;
const int CODIGO_FINAL_ADMIN = 3402;

std::string Administracion::generarIdUnico(const std::vector<Administracion>& lista) {
    for (int i = CODIGO_INICIAL_ADMIN; i <= CODIGO_FINAL_ADMIN; ++i) {
        std::string id = std::to_string(i);
        if (idDisponible(lista, id)) {
            return id;
        }
    }
    return ""; // Retorna cadena vacia si no hay codigos disponibles
}

bool Administracion::idDisponible(const std::vector<Administracion>& lista, const std::string& id) {
    return std::none_of(lista.begin(), lista.end(),
        [&id](const Administracion& a) { return a.id == id; });
}

bool Administracion::esIdValido(const std::string& id) {
    try {
        int num = std::stoi(id);
        return (num >= CODIGO_INICIAL_ADMIN && num <= CODIGO_FINAL_ADMIN);
    } catch (...) {
        return false;
    }
}

void Administracion::agregar(std::vector<Administracion>& lista, const std::string& usuarioActual) {
    Administracion nuevo;

    // Asignar ID automatico
    nuevo.id = generarIdUnico(lista);
    if (nuevo.id.empty()) {
        std::cerr << "\n\t\tError: No hay codigos disponibles para nuevos administradores (rango lleno)\n";
        system("pause");
        return;
    }

    std::cout << "\n\t\t=== AGREGAR ADMINISTRADOR (ID Auto-Asignado: " << nuevo.id << ") ===\n";

    // Limpiar buffer antes de getline()
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "\t\tNombre completo: ";
    std::getline(std::cin, nuevo.nombre);

    std::cout << "\t\tCargo: ";
    std::getline(std::cin, nuevo.cargo);

    std::cout << "\t\tDepartamento: ";
    std::getline(std::cin, nuevo.departamento);

    std::cout << "\t\tTelefono: ";
    std::getline(std::cin, nuevo.telefono);

    std::cout << "\t\tCorreo electronico: ";
    std::getline(std::cin, nuevo.email);

    std::cout << "\t\tNivel de acceso (1-3): ";
    while (!(std::cin >> nuevo.nivelAcceso) || nuevo.nivelAcceso < 1 || nuevo.nivelAcceso > 3) {
        std::cout << "\t\tPor favor ingrese un nivel valido (1-3): ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    lista.push_back(nuevo);
    guardarEnArchivo(lista);

    bitacora::registrar(usuarioActual, "ADMINISTRACION", "Administrador agregado - ID: " + nuevo.id);
    std::cout << "\n\t\tAdministrador registrado exitosamente con ID: " << nuevo.id << "\n";
    system("pause");
}

void Administracion::guardarEnArchivo(const std::vector<Administracion>& lista) {
    std::ofstream archivo("administradores.bin", ios::binary);

    for (const auto& admin : lista) {
        archivo << admin.id << ","
                << admin.nombre << ","
                << admin.cargo << ","
                << admin.departamento << ","
                << admin.telefono << ","
                << admin.email << ","
                << admin.nivelAcceso << "\n";
    }
}



void Administracion::mostrar(const std::vector<Administracion>& lista) {
    system("cls");
    std::cout << "\n\t\t=== LISTA DE ADMINISTRADORES ===\n";
    for (const auto& admin : lista) {
        std::cout << "\t\tID: " << admin.id
                  << " | Nombre: " << admin.nombre
                  << " | Cargo: " << admin.cargo
                  << " | Depto: " << admin.departamento
                  << " | Tel: " << admin.telefono
                  << " | Email: " << admin.email
                  << " | Nivel: " << admin.nivelAcceso << "\n";
    }
    system("pause");
}

void Administracion::modificar(std::vector<Administracion>& lista, const std::string& usuarioActual, const std::string& id) {
    auto it = std::find_if(lista.begin(), lista.end(),
        [&id](const Administracion& a) { return a.id == id; });

    if (it != lista.end()) {
        std::cout << "\n\t\t=== MODIFICAR ADMINISTRADOR (ID: " << id << ") ===\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "\t\tNuevo nombre (" << it->nombre << "): ";
        std::getline(std::cin, it->nombre);

        std::cout << "\t\tNuevo cargo (" << it->cargo << "): ";
        std::getline(std::cin, it->cargo);

        std::cout << "\t\tNuevo departamento (" << it->departamento << "): ";
        std::getline(std::cin, it->departamento);

        std::cout << "\t\tNuevo telofono (" << it->telefono << "): ";
        std::getline(std::cin, it->telefono);

        std::cout << "\t\tNuevo email (" << it->email << "): ";
        std::getline(std::cin, it->email);

        std::cout << "\t\tNuevo nivel de acceso (" << it->nivelAcceso << "): ";
        while (!(std::cin >> it->nivelAcceso) || it->nivelAcceso < 1 || it->nivelAcceso > 3) {
            std::cout << "\t\tPor favor ingrese un nivel valido (1-3): ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        guardarEnArchivo(lista);
        bitacora::registrar(usuarioActual, "ADMINISTRACION", "Administrador modificado - ID: " + id);
        std::cout << "\n\t\tAdministrador modificado exitosamente!\n";
    } else {
        std::cout << "\n\t\tAdministrador no encontrado!\n";
    }
    system("pause");
}

void Administracion::eliminar(std::vector<Administracion>& lista, const std::string& usuarioActual, const std::string& id) {
    auto it = std::find_if(lista.begin(), lista.end(),
        [&id](const Administracion& a) { return a.id == id; });

    if (it != lista.end()) {
        char confirmar;
        std::cout << "\n\t\t¿Esta seguro de eliminar al administrador ?" << it->nombre << "? (s/n): ";
        std::cin >> confirmar;

        if (tolower(confirmar) == 's') {
            lista.erase(it);
            guardarEnArchivo(lista);
            bitacora::registrar(usuarioActual, "ADMINISTRACION", "Administrador eliminado - ID: " + id);
            std::cout << "\n\t\tAdministrador eliminado exitosamente!\n";
        } else {
            std::cout << "\n\t\tOperacion cancelada\n";
        }
    } else {
        std::cout << "\n\t\tAdministrador no encontrado!\n";
    }
    system("pause");
}

void Administracion::cargarDesdeArchivo(std::vector<Administracion>& lista) {
    lista.clear();
    std::ifstream archivo("administradores.bin", ios::binary);

    if (!archivo.is_open()) {
        std::ofstream nuevoArchivo("administradores.bin", ios::binary);
        return;
    }

    std::string linea;
    while (std::getline(archivo, linea)) {
        std::istringstream ss(linea);
        Administracion admin;

        if (std::getline(ss, admin.id, ',') &&
            std::getline(ss, admin.nombre, ',') &&
            std::getline(ss, admin.cargo, ',') &&
            std::getline(ss, admin.departamento, ',') &&
            std::getline(ss, admin.telefono, ',') &&
            std::getline(ss, admin.email, ',') &&
            (ss >> admin.nivelAcceso)) {
            lista.push_back(admin);
        }
    }
}
