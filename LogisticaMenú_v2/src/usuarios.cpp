#include "usuarios.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <set>
#include "globals.h"

///KARINA ALEJANDRA ARRIAZA ORTIZ
//MAYO 2025

using namespace std;

const int CODIGO_INICIAL = 3100;
const int CODIGO_FINAL = 3149;

extern bitacora auditoria;

// Constructor
usuarios::usuarios() : id(""), nombre(""), contrasena(""), nivelAcceso(0) {}

// Implementación de métodos
string usuarios::generarCodigoUnico() {
    ifstream archivo("usuarios.txt");
    set<string> codigosExistentes;
    string linea;

    if (archivo.is_open()) {
        while (getline(archivo, linea)) {
            istringstream ss(linea);
            string idArchivo;
            if (ss >> idArchivo) {
                codigosExistentes.insert(idArchivo);
            }
        }
        archivo.close();
    }

    for (int i = CODIGO_INICIAL; i <= CODIGO_FINAL; ++i) {
        string codigo = to_string(i);
        if (codigosExistentes.find(codigo) == codigosExistentes.end()) {
            return codigo;
        }
    }

    throw runtime_error("No hay códigos disponibles en el rango.");
}

bool usuarios::esNumero(const string& str) {
    return !str.empty() && all_of(str.begin(), str.end(), ::isdigit);
}

bool usuarios::usuarioExiste(const string& nombreUsuario) {
    ifstream archivo("usuarios.bin", ios::binary);
    string linea;

    while (getline(archivo, linea)) {
        istringstream ss(linea);
        string idArchivo, nombreArchivo, passArchivo;
        int nivelArchivo;
        if (ss >> idArchivo >> nombreArchivo >> passArchivo >> nivelArchivo) {
            if (nombreArchivo == nombreUsuario) {
                return true;
            }
        }
    }
    return false;
}

string usuarios::leerPasswordSegura() {
    string pass;
    char ch;
    while ((ch = _getch()) != 13) {
        if (ch == 8 && !pass.empty()) {
            pass.pop_back();
            cout << "\b \b";
        } else if (ch != 8) {
            pass.push_back(ch);
            cout << '*';
        }
    }
    return pass;
}

bool usuarios::loginUsuarios() {
    string user, pass;
    int intentos = 0;
    bool autenticado = false; // Cambiado de 'acceso' a 'autenticado'

    do {
        system("cls");
        cout << "\t\t========================================" << endl;
        cout << "\t\t| AUTENTICACION DE USUARIOS - LOGISTICA |" << endl;
        cout << "\t\t========================================" << endl;
        cout << "\t\t1. Iniciar sesion" << endl;
        cout << "\t\t2. Registrarse (nuevo usuario)" << endl;
        cout << "\t\t3. Salir del Programa" << endl;
        cout << "\t\t========================================" << endl;
        cout << "\t\tOpcion: ";

        int opcion;
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                cout << "\t\tUsuario: ";
                getline(cin, user);
                cout << "\t\tContrasena: ";
                pass = leerPasswordSegura();

                if (buscarUsuario(user, pass)) {
                    autenticado = true;
                    nombre = user;
                    auditoria.insertar(nombre, "000", "LOGIN");
                    cout << "\n\t\tAutenticacion exitosa. Bienvenido!\n";
                    system("pause");
                    return true;
                } else {
                    intentos++;
                    auditoria.insertar(user, "000", "LOGIN-FAIL");
                    cout << "\n\t\tUsuario o contrasena incorrectos. Intentos restantes: " << (3 - intentos);
                    system("pause");
                }
                break;

            case 2:
                registrarUsuario();
                break;

            case 3:
                auditoria.insertar("Sistema", "000", "PROGRAMA CERRADO");
                cout << "\n\t\tSaliendo del programa...\n";
                system("pause");
                return false;

            default:
                cout << "\n\t\tOpcion invalida!\n";
                system("pause");
        }
    } while (intentos < 3 && !autenticado);

    return autenticado;
}

void usuarios::registrarUsuario() {
    system("cls");
    ofstream archivo("usuarios.bin", ios::binary);
    if (!archivo.is_open()) {
        cerr << "\n\t\tError al abrir archivo de usuarios!\n";
        return;
    }

    cout << "\t\t========================================" << endl;
    cout << "\t\t| REGISTRO DE NUEVO USUARIO            |" << endl;
    cout << "\t\t========================================" << endl;

    try {
        id = generarCodigoUnico();
        cout << "\t\tID generado automaticamente: " << id << endl;

        do {
            cout << "\t\tNombre de usuario (sin espacios): ";
            getline(cin, nombre);
            if (nombre.find(' ') != string::npos) {
                cout << "\t\tEl nombre no puede contener espacios!\n";
            } else if (usuarioExiste(nombre)) {
                cout << "\t\tEste nombre de usuario ya existe!\n";
            }
        } while (nombre.empty() || nombre.find(' ') != string::npos || usuarioExiste(nombre));

        string confirmacion;
        do {
            cout << "\t\tContrasena (minimo 8 caracteres): ";
            contrasena = leerPasswordSegura();
            while (contrasena.length() < 8) {
                cout << "\n\t\tDebe tener al menos 8 caracteres. Intente de nuevo.\n";
                cout << "\t\tContrasena: ";
                contrasena = leerPasswordSegura();
            }

            cout << "\n\t\tConfirmar contrasena: ";
            confirmacion = leerPasswordSegura();

            if (contrasena != confirmacion) {
                cout << "\n\t\tLas contrasenas no coinciden. Intente de nuevo.\n";
            }
        } while (contrasena != confirmacion);

        do {
            cout << "\n\t\tNivel de acceso (1-3): ";
            cin >> nivelAcceso;
            cin.ignore();
            if (nivelAcceso < 1 || nivelAcceso > 3) {
                cout << "\t\tNivel de acceso invalido!\n";
            }
        } while (nivelAcceso < 1 || nivelAcceso > 3);

        archivo << id << " " << nombre << " " << contrasena << " " << nivelAcceso << "\n";
        archivo.close();

        auditoria.insertar(nombre, "000", "REG-USER");
        cout << "\n\t\tUsuario registrado con exito con ID: " << id << "!\n";
    } catch (const runtime_error& e) {
        cerr << "\n\t\tError: " << e.what() << endl;
    }

    system("pause");
}

bool usuarios::buscarUsuario(const string& user, const string& pass) {
    ifstream archivo("usuarios.bin", ios::binary);
    if (!archivo.is_open()) {
        cerr << "\n\t\tError al abrir archivo de usuarios!\n";
        return false;
    }

    string linea;
    while (getline(archivo, linea)) {
        istringstream ss(linea);
        string idArchivo, nombreArchivo, passArchivo;
        int nivelArchivo;

        if (ss >> idArchivo >> nombreArchivo >> passArchivo >> nivelArchivo) {
            if (nombreArchivo == user && passArchivo == pass) {
                id = idArchivo;
                nombre = nombreArchivo;
                contrasena = passArchivo;
                nivelAcceso = nivelArchivo;
                return true;
            }
        }
    }
    return false;
}
