// 9959-24-11603 GABRIELA ESCOBAR
#include "Reportes.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <limits>

using namespace std;

// Lista estatica de reportes
vector<Reportes::DatosReporte> Reportes::listaReportes;

const int CODIGO_INICIAL = 3800;
const int CODIGO_FINAL = 3850;

// Constructor: carga los reportes desde el archivo binario al iniciar
Reportes::Reportes() {
    cargarDesdeArchivoBin(listaReportes);
}

// Genera un ID unico dentro del rango disponible
string Reportes::generarIdUnico(const vector<DatosReporte>& lista) {
    for (int i = CODIGO_INICIAL; i <= CODIGO_FINAL; ++i) {
        string id = to_string(i);
        if (idDisponible(lista, id)) {
            return id;
        }
    }
    return "";
}

// Verifica si un ID esta disponible en la lista
bool Reportes::idDisponible(const vector<DatosReporte>& lista, const string& id) {
    return none_of(lista.begin(), lista.end(),
        [&id](const DatosReporte& r) { return r.id == id; });
}

// Muestra un mensaje de "procesando..." con retardo visual
void Reportes::mostrarProcesando(const string& mensaje) {
    cout << "\n\t\t" << mensaje;
    for (int i = 0; i < 3; ++i) {
        cout << ".";
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    cout << "\n";
}

// Guarda los reportes en un archivo binario
void Reportes::guardarEnArchivoBin(const vector<DatosReporte>& lista) {
    ofstream archivo("reportes.bin", ios::binary | ios::out);
    if (!archivo.is_open()) {
        cerr << "\n\t\tError al abrir archivo de reportes!\n";
        return;
    }

    try {
        size_t cantidad = lista.size();
        archivo.write(reinterpret_cast<const char*>(&cantidad), sizeof(cantidad));

        for (const auto& reporte : lista) {
            size_t idSize = reporte.id.size();
            archivo.write(reinterpret_cast<const char*>(&idSize), sizeof(idSize));
            archivo.write(reporte.id.c_str(), idSize);

            size_t tipoSize = reporte.tipo.size();
            archivo.write(reinterpret_cast<const char*>(&tipoSize), sizeof(tipoSize));
            archivo.write(reporte.tipo.c_str(), tipoSize);

            archivo.write(reinterpret_cast<const char*>(&reporte.fechaGeneracion), sizeof(reporte.fechaGeneracion));

            size_t contenidoSize = reporte.contenido.size();
            archivo.write(reinterpret_cast<const char*>(&contenidoSize), sizeof(contenidoSize));
            archivo.write(reporte.contenido.c_str(), contenidoSize);
        }

        archivo.close();

        // Verifica si el archivo fue creado correctamente
        ifstream test("reportes.bin", ios::binary);
        if (!test) {
            cerr << "\n\t\tError: No se pudo verificar el archivo de reportes!\n";
            return;
        }
        test.close();

    } catch (const exception& e) {
        cerr << "\n\t\tError al guardar: " << e.what() << "\n";
        remove("reportes.bin");
    }
}

// Carga los reportes desde el archivo binario
void Reportes::cargarDesdeArchivoBin(vector<DatosReporte>& lista) {
    lista.clear();
    ifstream archivo("reportes.bin", ios::binary | ios::in);
    if (!archivo) {
        cout << "\n\t\tInfo: No existe archivo de reportes previo o no se pudo abrir\n";
        return;
    }

    try {
        archivo.seekg(0, ios::end);
        if (archivo.tellg() == 0) {
            cout << "\n\t\tInfo: Archivo de reportes existe pero esta vacio\n";
            archivo.close();
            return;
        }
        archivo.seekg(0, ios::beg);

        size_t cantidad;
        archivo.read(reinterpret_cast<char*>(&cantidad), sizeof(cantidad));

        for (size_t i = 0; i < cantidad; ++i) {
            DatosReporte reporte;

            size_t idSize;
            archivo.read(reinterpret_cast<char*>(&idSize), sizeof(idSize));
            reporte.id.resize(idSize);
            archivo.read(&reporte.id[0], idSize);

            size_t tipoSize;
            archivo.read(reinterpret_cast<char*>(&tipoSize), sizeof(tipoSize));
            reporte.tipo.resize(tipoSize);
            archivo.read(&reporte.tipo[0], tipoSize);

            archivo.read(reinterpret_cast<char*>(&reporte.fechaGeneracion), sizeof(reporte.fechaGeneracion));

            size_t contenidoSize;
            archivo.read(reinterpret_cast<char*>(&contenidoSize), sizeof(contenidoSize));
            reporte.contenido.resize(contenidoSize);
            archivo.read(&reporte.contenido[0], contenidoSize);

            lista.push_back(reporte);
        }

        cout << "\n\t\tSe cargaron " << lista.size() << " reportes desde archivo\n";

    } catch (const exception& e) {
        cerr << "\n\t\tError al cargar reportes: " << e.what() << "\n";
        lista.clear();
    }
    archivo.close();
}

// Metodo principal que llama al generador con parametros globales
void Reportes::generarReportes() {
    generarReportes(auditoria, usuarioRegistrado);
}

// Menu de seleccion de tipo de reporte
void Reportes::generarReportes(bitacora& auditoria, const usuarios& usuario) {
    int opcion;
    do {
        system("cls");
        cout << "\t\t========================================" << endl;
        cout << "\t\t| REPORTES Y ANALISIS - LOGISTICA      |" << endl;
        cout << "\t\t========================================" << endl;
        cout << "\t\t 1. Informe de ventas" << endl;
        cout << "\t\t 2. Analisis de tiempos de entrega" << endl;
        cout << "\t\t 3. Reporte de inventarios" << endl;
        cout << "\t\t 4. Evaluacion de proveedores" << endl;
        cout << "\t\t 5. Volver al menu anterior" << endl;
        cout << "\t\t========================================" << endl;
        cout << "\t\tOpcion a escoger: ";

        while (!(cin >> opcion) || opcion < 1 || opcion > 5) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\t\tOpcion invalida. Ingrese 1-5: ";
        }

        switch(opcion) {
            case 1: informeVentas(auditoria, usuario); break;
            case 2: analisisTiemposEntrega(auditoria, usuario); break;
            case 3: reporteInventarios(auditoria, usuario); break;
            case 4: evaluacionProveedores(auditoria, usuario); break;
            case 5: guardarEnArchivoBin(listaReportes); break;
        }
    } while(opcion != 5);
}

// Genera un informe de ventas simulado
void Reportes::informeVentas(bitacora& auditoria, const usuarios& usuario) {
    mostrarProcesando("Generando informe de ventas");

    DatosReporte nuevoReporte;
    nuevoReporte.id = generarIdUnico(listaReportes);
    nuevoReporte.tipo = "VENTAS";
    nuevoReporte.fechaGeneracion = time(nullptr);

    stringstream contenido;
    contenido << "\t\t=== INFORME DE VENTAS ===\n";
    contenido << "\t\tID: " << nuevoReporte.id << "\n";
    contenido << "\t\tFecha: " << ctime(&nuevoReporte.fechaGeneracion);
    contenido << "\t\tVentas totales: Q125,300.00\n";
    contenido << "\t\tClientes atendidos: 230\n";

    nuevoReporte.contenido = contenido.str();
    listaReportes.push_back(nuevoReporte);

    system("cls");
    cout << nuevoReporte.contenido;
    cout << "\n\t\tReporte guardado con ID: " << nuevoReporte.id << endl;

    auditoria.registrar(usuario.getNombre(), "REPORTES", "Informe de ventas - ID: " + nuevoReporte.id);
    system("pause");
}

// Genera un analisis de tiempos de entrega
void Reportes::analisisTiemposEntrega(bitacora& auditoria, const usuarios& usuario) {
    mostrarProcesando("Analizando tiempos de entrega");

    DatosReporte nuevoReporte;
    nuevoReporte.id = generarIdUnico(listaReportes);
    nuevoReporte.tipo = "TIEMPOS_ENTREGA";
    nuevoReporte.fechaGeneracion = time(nullptr);

    stringstream contenido;
    contenido << "\t\t=== ANALISIS DE TIEMPOS ===\n";
    contenido << "\t\tID: " << nuevoReporte.id << "\n";
    contenido << "\t\tTiempo promedio: 2.3 dias\n";
    contenido << "\t\tRetrasos: 5\n";

    nuevoReporte.contenido = contenido.str();
    listaReportes.push_back(nuevoReporte);

    system("cls");
    cout << nuevoReporte.contenido;
    cout << "\n\t\tReporte guardado con ID: " << nuevoReporte.id << endl;

    auditoria.registrar(usuario.getNombre(), "REPORTES", "Analisis tiempos - ID: " + nuevoReporte.id);
    system("pause");
}

// Genera un reporte de inventarios
void Reportes::reporteInventarios(bitacora& auditoria, const usuarios& usuario) {
    mostrarProcesando("Generando reporte de inventario");

    DatosReporte nuevoReporte;
    nuevoReporte.id = generarIdUnico(listaReportes);
    nuevoReporte.tipo = "INVENTARIO";
    nuevoReporte.fechaGeneracion = time(nullptr);

    stringstream contenido;
    contenido << "\t\t=== REPORTE INVENTARIO ===\n";
    contenido << "\t\tID: " << nuevoReporte.id << "\n";
    contenido << "\t\tProductos en stock: 750\n";
    contenido << "\t\tBajo inventario: 12\n";

    nuevoReporte.contenido = contenido.str();
    listaReportes.push_back(nuevoReporte);

    system("cls");
    cout << nuevoReporte.contenido;
    cout << "\n\t\tReporte guardado con ID: " << nuevoReporte.id << endl;

    auditoria.registrar(usuario.getNombre(), "REPORTES", "Reporte inventario - ID: " + nuevoReporte.id);
    system("pause");
}

// Genera una evaluacion de proveedores
void Reportes::evaluacionProveedores(bitacora& auditoria, const usuarios& usuario) {
    mostrarProcesando("Evaluando proveedores");

    DatosReporte nuevoReporte;
    nuevoReporte.id = generarIdUnico(listaReportes);
    nuevoReporte.tipo = "EVALUACION_PROVEEDORES";
    nuevoReporte.fechaGeneracion = time(nullptr);

    stringstream contenido;
    contenido << "\t\t=== EVALUACION PROVEEDORES ===\n";
    contenido << "\t\tID: " << nuevoReporte.id << "\n";
    contenido << "\t\tProveedor A: 98% a tiempo\n";
    contenido << "\t\tProveedor B: 75% a tiempo\n";

    nuevoReporte.contenido = contenido.str();
    listaReportes.push_back(nuevoReporte);

    system("cls");
    cout << nuevoReporte.contenido;
    cout << "\n\t\tReporte guardado con ID: " << nuevoReporte.id << endl;

    auditoria.registrar(usuario.getNombre(), "REPORTES", "Evaluacion proveedores - ID: " + nuevoReporte.id);
    system("pause");
}
