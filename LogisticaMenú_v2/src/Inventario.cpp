//Karina Alejandra Arriaza Ortiz 9959-24-14190
//Modificaciones y ayuda con errores: Jennifer Barrios.
#include "Inventario.h"
#include "producto.h"
#include "almacen.h"
#include "proveedor.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <limits>
#include <iomanip>
#include <sstream>
#include <vector>
#include "usuarios.h"
#include "bitacora.h"
#include <algorithm>
#include <numeric>
#include <cstring> // Para strncpy

using namespace std;


extern usuarios usuarioRegistrado;
extern bitacora auditoria;
std::vector<Inventario> Inventario::listaInventario;

// ----------- Funciones de archivo para Productos ------------
vector<Producto> Inventario::cargarProductosDesdeArchivo() {
    vector<Producto> productos;

    try {
        ifstream archivo("productos.bin", ios::binary);
        if (!archivo) {
            throw runtime_error("Error al abrir el archivo de productos.");
        }

        size_t cantidad;
        archivo.read(reinterpret_cast<char*>(&cantidad), sizeof(cantidad));

        for (size_t i = 0; i < cantidad; ++i) {
            Producto p;
            size_t size;

            archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
            if (archivo.fail()) throw runtime_error("Error al leer tamaño del ID.");
            char* idBuffer = new char[size + 1];
            archivo.read(idBuffer, size);
            idBuffer[size] = '\0';
            p.setId(idBuffer);
            delete[] idBuffer;

            archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
            if (archivo.fail()) throw runtime_error("Error al leer tamaño del nombre.");
            char* nombreBuffer = new char[size + 1];
            archivo.read(nombreBuffer, size);
            nombreBuffer[size] = '\0';
            p.setNombre(nombreBuffer);
            delete[] nombreBuffer;

            int stock, stockMin;
            archivo.read(reinterpret_cast<char*>(&stock), sizeof(stock));
            archivo.read(reinterpret_cast<char*>(&stockMin), sizeof(stockMin));
            if (archivo.fail()) throw runtime_error("Error al leer stock o stock mínimo.");

            p.setStock(stock);
            p.setStockMinimo(stockMin);

            productos.push_back(p);
        }

        archivo.close();
    } catch (const exception& e) {
        cerr << "Excepción al cargar productos: " << e.what() << endl;
    }

    return productos;
}

void Inventario::guardarProductosEnArchivo(const vector<Producto>& productos) {
    try {
        ofstream archivo("productos.bin", ios::binary | ios::trunc);
        if (!archivo) {
            throw runtime_error("Error al abrir el archivo de productos para escritura.");
        }

        size_t cantidad = productos.size();
        archivo.write(reinterpret_cast<const char*>(&cantidad), sizeof(cantidad));

        for (const auto& p : productos) {
            string id = p.getId();
            size_t size = id.size();
            archivo.write(reinterpret_cast<const char*>(&size), sizeof(size));
            archivo.write(id.c_str(), size);

            string nombre = p.getNombre();
            size = nombre.size();
            archivo.write(reinterpret_cast<const char*>(&size), sizeof(size));
            archivo.write(nombre.c_str(), size);

            int stock = p.getStock();
            int stockMin = p.getStockMinimo();
            archivo.write(reinterpret_cast<const char*>(&stock), sizeof(stock));
            archivo.write(reinterpret_cast<const char*>(&stockMin), sizeof(stockMin));
        }

        archivo.close();
    } catch (const exception& e) {
        cerr << "Excepción al guardar productos: " << e.what() << endl;
    }
}

vector<Almacen> Inventario::cargarAlmacenesDesdeArchivo() {
    vector<Almacen> almacenes;

    try {
        ifstream archivo("Almacenes.bin", ios::binary);
        if (!archivo) {
            throw runtime_error("Error al abrir el archivo de almacenes.");
        }

        // Leer la cantidad de almacenes
        size_t cantidad;
        archivo.read(reinterpret_cast<char*>(&cantidad), sizeof(cantidad));
        if (archivo.fail()) throw runtime_error("Error al leer la cantidad de almacenes.");

        // Leer cada almacén
        for (size_t i = 0; i < cantidad; ++i) {
            Almacen a;
            size_t size;

            // Leer ID
            archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
            if (archivo.fail()) throw runtime_error("Error al leer tamaño del ID.");
            char* idBuffer = new char[size + 1];
            archivo.read(idBuffer, size);
            idBuffer[size] = '\0';
            a.setId(idBuffer);
            delete[] idBuffer;

            // Leer nombre
            archivo.read(reinterpret_cast<char*>(&size), sizeof(size));
            if (archivo.fail()) throw runtime_error("Error al leer tamaño del nombre.");
            char* nombreBuffer = new char[size + 1];
            archivo.read(nombreBuffer, size);
            nombreBuffer[size] = '\0';
            a.setNombre(nombreBuffer);
            delete[] nombreBuffer;

            // Leer capacidad y espacio disponible
            int capacidad, espacio;
            archivo.read(reinterpret_cast<char*>(&capacidad), sizeof(capacidad));
            archivo.read(reinterpret_cast<char*>(&espacio), sizeof(espacio));
            if (archivo.fail()) throw runtime_error("Error al leer capacidad o espacio disponible.");

            a.setCapacidad(capacidad);
            a.setEspacioDisponible(espacio);

            almacenes.push_back(a);
        }

        archivo.close();

    } catch (const exception& e) {
        cerr << "Excepción al cargar almacenes: " << e.what() << endl;
    }

    return almacenes;
}

void Inventario::guardarAlmacenesEnArchivo(const vector<Almacen>& almacenes) {
    try {
        ofstream archivo("Almacenes.bin", ios::binary | ios::trunc);
        if (!archivo) {
            throw runtime_error("Error al abrir el archivo de almacenes para escritura.");
        }

        size_t cantidad = almacenes.size();
        archivo.write(reinterpret_cast<const char*>(&cantidad), sizeof(cantidad));

        for (const auto& a : almacenes) {
            string id = a.getId();
            size_t size = id.size();
            archivo.write(reinterpret_cast<const char*>(&size), sizeof(size));
            archivo.write(id.c_str(), size);

            string nombre = a.getNombre();
            size = nombre.size();
            archivo.write(reinterpret_cast<const char*>(&size), sizeof(size));
            archivo.write(nombre.c_str(), size);

            int capacidad = a.getCapacidad();
            int espacio = a.getEspacioDisponible();
            archivo.write(reinterpret_cast<const char*>(&capacidad), sizeof(capacidad));
            archivo.write(reinterpret_cast<const char*>(&espacio), sizeof(espacio));
        }

        archivo.close();
    } catch (const exception& e) {
        cerr << "Excepción al guardar almacenes: " << e.what() << endl;
    }
}

vector<Proveedor> Inventario::cargarProveedoresDesdeArchivo() {
    vector<Proveedor> proveedores;

    try {
        ifstream archivo("Proveedores.bin", ios::binary);
        if (!archivo) {
            throw runtime_error("Error al abrir el archivo de proveedores.");
        }

        ProveedorRegistro reg;
        while (archivo.read(reinterpret_cast<char*>(&reg), sizeof(reg))) {
            Proveedor::decodificar(reg.id, sizeof(reg.id));
            Proveedor::decodificar(reg.nombre, sizeof(reg.nombre));
            Proveedor::decodificar(reg.telefono, sizeof(reg.telefono));

            Proveedor p;
            p.setId(reg.id);
            p.setNombre(reg.nombre);
            p.setTelefono(reg.telefono);

            proveedores.push_back(p);
        }

        archivo.close();
    } catch (const exception& e) {
        cerr << "Excepción al cargar proveedores: " << e.what() << endl;
    }

    return proveedores;
}

void Inventario::guardarProveedoresEnArchivo(const vector<Proveedor>& proveedores) {
    try {
        ofstream archivo("Proveedores.bin", ios::binary | ios::trunc);
        if (!archivo) {
            throw runtime_error("Error al abrir el archivo de proveedores para escritura.");
        }

        for (const auto& p : proveedores) {
            ProveedorRegistro reg;

            strncpy(reg.id, p.getId().c_str(), sizeof(reg.id) - 1);
            reg.id[sizeof(reg.id) - 1] = '\0';

            strncpy(reg.nombre, p.getNombre().c_str(), sizeof(reg.nombre) - 1);
            reg.nombre[sizeof(reg.nombre) - 1] = '\0';

            strncpy(reg.telefono, p.getTelefono().c_str(), sizeof(reg.telefono) - 1);
            reg.telefono[sizeof(reg.telefono) - 1] = '\0';

            Proveedor::codificar(reg.id, sizeof(reg.id));
            Proveedor::codificar(reg.nombre, sizeof(reg.nombre));
            Proveedor::codificar(reg.telefono, sizeof(reg.telefono));

            archivo.write(reinterpret_cast<const char*>(&reg), sizeof(reg));
        }

        archivo.close();
    } catch (const exception& e) {
        cerr << "Excepción al guardar proveedores: " << e.what() << endl;
    }
}

// ----------- Métodos de Productos ------------
void crearProductoInteractivo() {
    system("cls");
    cout << "------------------------------------------------------------\n";
    cout << "                    CREAR NUEVO PRODUCTO                     \n";
    cout << "------------------------------------------------------------\n";

    Producto nuevo;
    vector<Producto> productos;

    try {
        productos = Inventario::cargarProductosDesdeArchivo();
    } catch (const exception& e) {
        cerr << "Error al cargar productos: " << e.what() << endl;
        system("pause");
        return;
    }

    // Generar ID único
    string nuevoId = "PROD";
    int maxNum = 0;
    for (const auto& p : productos) {
        string numStr = p.getId().substr(4);
        try {
            int num = stoi(numStr);
            if (num > maxNum) maxNum = num;
        } catch (...) {
            continue;
        }
    }
    ostringstream oss;
    oss << setw(3) << setfill('0') << (maxNum + 1);
    nuevoId += oss.str();
    nuevo.setId(nuevoId);

    // Nombre
    cout << "Ingrese nombre del producto: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string nombre;
    getline(cin, nombre);
    nuevo.setNombre(nombre);

    // Descripción
    cout << "Ingrese descripcion: ";
    string descripcion;
    getline(cin, descripcion);
    nuevo.setDescripcion(descripcion);

    // Precio
    double precio;
    while (true) {
        cout << "Ingrese precio: ";
        if (cin >> precio && precio >= 0) break;
        cout << "Entrada inválida. Ingrese un número válido.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    nuevo.setPrecio(precio);

    // Stock
    int stock;
    while (true) {
        cout << "Ingrese stock inicial: ";
        if (cin >> stock && stock >= 0) break;
        cout << "Entrada inválida. Ingrese un entero positivo.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    nuevo.setStock(stock);

    // Stock mínimo
    int stockMin;
    while (true) {
        cout << "Ingrese stock minimo: ";
        if (cin >> stockMin && stockMin >= 0) break;
        cout << "Entrada inválida. Ingrese un entero positivo.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    nuevo.setStockMinimo(stockMin);

    // Guardar y registrar
    productos.push_back(nuevo);
    try {
        Inventario::guardarProductosEnArchivo(productos);
        auditoria.registrar(usuarioRegistrado.getNombre(), "PRODUCTOS", "Creado producto " + nuevo.getId());
        cout << "\n\tProducto creado exitosamente.\n";
    } catch (const exception& e) {
        cerr << "Error al guardar producto: " << e.what() << endl;
    }

    system("pause");
}

void mostrarProductos() {
    system("cls");
    cout << "---------------------------------------------------------------\n";
    cout << "                      LISTA DE PRODUCTOS                        \n";
    cout << "---------------------------------------------------------------\n";

    vector<Producto> productos;
    try {
        productos = Inventario::cargarProductosDesdeArchivo();
    } catch (const exception& e) {
        cerr << "Error al cargar productos: " << e.what() << endl;
        system("pause");
        return;
    }

    if (productos.empty()) {
        cout << "\n\tNo hay productos registrados.\n";
        system("pause");
        return;
    }

    cout << "----------------------------------------------------------------------------------------\n";
    cout << "ID       | Nombre           | Descripcion       | Precio   | Stock  | Stock Minimo\n";
    cout << "----------------------------------------------------------------------------------------\n";

    for (const auto& producto : productos) {
        string descCorta = producto.getDescripcion().substr(0, 16);
        if (producto.getDescripcion().length() > 16) descCorta += "...";

        cout << setw(8) << left << producto.getId() << " | "
             << setw(16) << left << producto.getNombre() << " | "
             << setw(18) << left << descCorta << " | "
             << setw(8) << left << fixed << setprecision(2) << producto.getPrecio() << " | "
             << setw(6) << left << producto.getStock() << " | "
             << setw(11) << left << producto.getStockMinimo() << "\n";
    }
    cout << "----------------------------------------------------------------------------------------\n";
    system("pause");
}

// ----------- Métodos de Almacenes ------------
void crearAlmacenInteractivo() {
    system("cls");
    cout << "------------------------------------------------------------\n";
    cout << "                    CREAR NUEVO ALMACEN                      \n";
    cout << "------------------------------------------------------------\n";

    Almacen nuevo;
    vector<Almacen> almacenes = Inventario::cargarAlmacenesDesdeArchivo();

    // Generar ID único
    string nuevoId = "ALM";
    if (!almacenes.empty()) {
        int maxNum = 0;
        for (const auto& a : almacenes) {
            string numStr = a.getId().substr(3);
            try {
                int num = stoi(numStr);
                if (num > maxNum) maxNum = num;
            } catch (...) {
                continue;
            }
        }
        ostringstream oss;
        oss << setw(3) << setfill('0') << (maxNum + 1);
        nuevoId += oss.str();
    } else {
        nuevoId += "001";
    }
    nuevo.setId(nuevoId);

    cout << "Ingrese nombre del almacen: ";
    cin.ignore();
    string nombre;
    getline(cin, nombre);
    nuevo.setNombre(nombre);

    cout << "Ingrese direccion: ";
    string direccion;
    getline(cin, direccion);
    nuevo.setDireccion(direccion);

    cout << "Ingrese capacidad total: ";
    int capacidad;
    cin >> capacidad;
    nuevo.setCapacidad(capacidad);
    nuevo.setEspacioDisponible(capacidad);

    almacenes.push_back(nuevo);
    Inventario::guardarAlmacenesEnArchivo(almacenes);

    auditoria.registrar(usuarioRegistrado.getNombre(), "ALMACENES", "Creado almacen " + nuevo.getId());
    cout << "\n\tAlmacen creado exitosamente.\n";
    system("pause");
}

void mostrarAlmacenes() {
    system("cls");
    cout << "---------------------------------------------------------------\n";
    cout << "                      LISTA DE ALMACENES                       \n";
    cout << "---------------------------------------------------------------\n";

    vector<Almacen> almacenes = Inventario::cargarAlmacenesDesdeArchivo();
    if (almacenes.empty()) {
        cout << "\n\tNo hay almacenes registrados.\n";
        system("pause");
        return;
    }

    cout << "---------------------------------------------------------------------\n";
    cout << "ID      | Nombre           | Direccion          | Capacidad | Disponible\n";
    cout << "---------------------------------------------------------------------\n";

    for (const auto& almacen : almacenes) {
        string dirCorta = almacen.getDireccion().substr(0, 17);
        if (almacen.getDireccion().length() > 17) dirCorta += "...";

        cout << setw(7) << left << almacen.getId() << " | "
             << setw(16) << left << almacen.getNombre() << " | "
             << setw(19) << left << dirCorta << " | "
             << setw(9) << left << almacen.getCapacidad() << " | "
             << setw(10) << left << almacen.getEspacioDisponible() << "\n";
    }
    cout << "---------------------------------------------------------------------\n";
    system("pause");
}

// ----------- Métodos de Inventario ------------
void Inventario::controlInventario() {
    int opcion;
    do {
        system("cls");
        cout << "\t\t========================================" << endl;
        cout << "\t\t| CONTROL DE INVENTARIO - LOGISTICA     |" << endl;
        cout << "\t\t========================================" << endl;
        cout << "\t\t 1. Consultar stock" << endl;
        cout << "\t\t 2. Registrar mercancia" << endl;
        cout << "\t\t 3. Ajustar inventario" << endl;
        cout << "\t\t 4. Reporte de existencias" << endl;
        cout << "\t\t 5. Volver al menu anterior" << endl;
        cout << "\t\t========================================" << endl;
        cout << "\t\tOpcion a escoger: ";
        cin >> opcion;

        switch(opcion) {
            case 1: consultarStockCompleto(); break;
            case 2: registrarMercancias(); break;
            case 3: ajustarInventario(); break;
            case 4: reporteExistencias(); break;
            case 5: break;
            default:
                cout << "\n\t\tOpcion invalida!";
                cin.ignore();
                cin.get();
        }
    } while(opcion != 5);
}

#include "Inventario.h"
#include "Producto.h"
#include <algorithm>
#include <iomanip>

void Inventario::consultarStockCompleto() {
    // Cargar productos desde su archivo
    vector<Producto> productos;
    Producto::cargarDesdeArchivoBin(productos);

    // Cargar información de inventario
    vector<ItemInventario> inventario = cargarInventarioDesdeArchivo();

    if (productos.empty() && inventario.empty()) {
        cout << "\n\t\tNo hay productos registrados en el sistema.\n";
        system("pause");
        return;
    }

    system("cls");
    cout << "\n\t\t=== CONSULTA COMPLETA DE STOCK ===\n";
    cout << "\t\t" << left << setw(10) << "Codigo" << setw(25) << "Nombre"
         << setw(10) << "Stock" << setw(15) << "Stock Min"
         << setw(15) << "En Almacen" << setw(10) << "Estado" << "\n";
    cout << "\t\t" << string(85, '-') << "\n";

    for (const auto& producto : productos) {
        int enAlmacen = 0;
        auto it = find_if(inventario.begin(), inventario.end(),
            [&](const ItemInventario& item) {
                return item.idProducto == producto.getCodigo();
            });

        if (it != inventario.end()) {
            enAlmacen = it->cantidad;
        }

        string estado = (producto.getStock() >= producto.getStockMinimo()) ? "OK" : "BAJO";

        cout << "\t\t" << setw(10) << producto.getCodigo()
             << setw(25) << producto.getNombre().substr(0, 24)
             << setw(10) << producto.getStock()
             << setw(15) << producto.getStockMinimo()
             << setw(15) << enAlmacen
             << setw(10) << estado << "\n";
    }

    // Mostrar resumen
    int totalSistema = accumulate(productos.begin(), productos.end(), 0,
        [](int total, const Producto& p) { return total + p.getStock(); });

    int totalAlmacen = accumulate(inventario.begin(), inventario.end(), 0,
        [](int total, const ItemInventario& item) { return total + item.cantidad; });

    cout << "\n\t\tTOTAL EN SISTEMA: " << totalSistema
         << " | TOTAL EN ALMACEN: " << totalAlmacen
         << " | DIFERENCIA: " << (totalSistema - totalAlmacen) << "\n";

    cout << "\n\t\tPresione cualquier tecla para volver...";
    cin.ignore();
    cin.get();
}

vector<Inventario::ItemInventario> Inventario::cargarInventarioDesdeArchivo() {
    vector<ItemInventario> inventario;
    ifstream archivo("inventario.bin", ios::binary);

    if (!archivo.is_open()) {
        return inventario;
    }

    try {
        size_t numItems;
        archivo.read(reinterpret_cast<char*>(&numItems), sizeof(numItems));

        inventario.resize(numItems);

        for (size_t i = 0; i < numItems; ++i) {
            // Leer idProducto
            size_t len;
            archivo.read(reinterpret_cast<char*>(&len), sizeof(len));
            inventario[i].idProducto.resize(len);
            archivo.read(&inventario[i].idProducto[0], len);

            // Leer cantidad
            archivo.read(reinterpret_cast<char*>(&inventario[i].cantidad), sizeof(inventario[i].cantidad));

            // Leer idAlmacen
            archivo.read(reinterpret_cast<char*>(&len), sizeof(len));
            inventario[i].idAlmacen.resize(len);
            archivo.read(&inventario[i].idAlmacen[0], len);
        }
    } catch (...) {
        cerr << "Error al leer archivo de inventario\n";
        inventario.clear();
    }

    return inventario;
}

void Inventario::registrarMercancias() {
    system("cls");
    cout << "\t\t========================================" << endl;
    cout << "\t\t| REGISTRAR MERCANCIA NUEVA            |" << endl;
    cout << "\t\t========================================" << endl;

    // Cargar datos actualizados
    vector<Producto> productos = cargarProductosDesdeArchivo();
    vector<Almacen> almacenes = cargarAlmacenesDesdeArchivo();
    vector<Proveedor> proveedores = cargarProveedoresDesdeArchivo();

    // Validar datos mínimos requeridos
    if (productos.empty()) {
        cout << "\t\tNo hay productos registrados. Debe registrar productos primero." << endl;
        system("pause");
        return;
    }

    if (almacenes.empty()) {
        cout << "\t\tNo hay almacenes registrados. Debe registrar almacenes primero." << endl;
        system("pause");
        return;
    }

    // Mostrar productos disponibles
    cout << "\n\t\tPRODUCTOS DISPONIBLES:\n";
    for (const auto& p : productos) {
        cout << "\t\tID: " << p.getId() << " | Nombre: " << p.getNombre() << endl;
    }

    // Selección de producto
    string idProducto;
    cout << "\t\tID del producto a registrar: ";
    cin >> idProducto;

    // Buscar producto
    auto productoIt = find_if(productos.begin(), productos.end(),
        [&idProducto](const Producto& p) { return p.getId() == idProducto; });

    if (productoIt == productos.end()) {
        cout << "\n\t\tError: Producto no encontrado." << endl;
        system("pause");
        return;
    }

    // Mostrar almacenes disponibles
    cout << "\n\t\tALMACENES DISPONIBLES:\n";
    for (const auto& a : almacenes) {
        cout << "\t\tID: " << a.getId() << " | Nombre: " << a.getNombre() << endl;
    }

    // Selección de almacén
    string idAlmacen;
    cout << "\t\tID del almacén destino: ";
    cin >> idAlmacen;

    // Buscar almacén
    auto almacenIt = find_if(almacenes.begin(), almacenes.end(),
        [&idAlmacen](const Almacen& a) { return a.getId() == idAlmacen; });

    if (almacenIt == almacenes.end()) {
        cout << "\n\t\tError: Almacén no encontrado." << endl;
        system("pause");
        return;
    }

    // Ingresar cantidad con validación
    int cantidad;
    cout << "\t\tCantidad a registrar: ";
    while (!(cin >> cantidad) || cantidad <= 0) {
        cout << "\t\tCantidad inválida. Ingrese un número positivo: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Verificar espacio disponible
    if (almacenIt->getEspacioDisponible() < cantidad) {
        cout << "\n\t\tError: Espacio insuficiente en el almacén." << endl;
        cout << "\t\tEspacio disponible: " << almacenIt->getEspacioDisponible() << endl;
        system("pause");
        return;
    }

    // Crear nuevo registro de inventario
    ItemInventario nuevoRegistro;
    nuevoRegistro.idProducto = idProducto;
    nuevoRegistro.idAlmacen = idAlmacen;
    nuevoRegistro.cantidad = cantidad;

    // Actualizar registros
    productoIt->setStock(productoIt->getStock() + cantidad);
    almacenIt->setEspacioDisponible(almacenIt->getEspacioDisponible() - cantidad);

    // Guardar cambios
    guardarProductosEnArchivo(productos);
    guardarAlmacenesEnArchivo(almacenes);

    // Aquí deberías implementar guardarInventarioEnArchivo(nuevoRegistro);

    // Mostrar resumen de la operación
    cout << "\n\t\tREGISTRO EXITOSO:" << endl;
    cout << "\t\tProducto: " << productoIt->getNombre() << " (ID: " << productoIt->getId() << ")" << endl;
    cout << "\t\tCantidad registrada: " << cantidad << endl;
    cout << "\t\tAlmacén destino: " << almacenIt->getNombre() << endl;

    system("pause");
}


void Inventario::ajustarInventario() {
    system("cls");
    cout << "\t\t========================================" << endl;
    cout << "\t\t| AJUSTAR INVENTARIO EXISTENTE         |" << endl;
    cout << "\t\t========================================" << endl;

    vector<Producto> productos = cargarProductosDesdeArchivo();
    if (productos.empty()) {
        cout << "\t\tNo hay productos registrados." << endl;
        system("pause");
        return;
    }

    // Mostrar productos
    for (const auto& p : productos) {
        cout << "\t" << p.getId() << " - " << p.getNombre()
             << " (Stock: " << p.getStock() << ")" << endl;
    }

    string idProducto;
    cout << "\t\tID del producto a ajustar: ";
    cin >> idProducto;

    auto it = find_if(productos.begin(), productos.end(),
        [&](const Producto& p) { return p.getId() == idProducto; });

    if (it == productos.end()) {
        cout << "\t\tProducto no encontrado." << endl;
        system("pause");
        return;
    }

    int nuevaCantidad;
    cout << "\t\tNueva cantidad: ";
    cin >> nuevaCantidad;

    if (nuevaCantidad < 0) {
        cout << "\t\tCantidad invalida." << endl;
        system("pause");
        return;
    }

    it->setStock(nuevaCantidad);
    guardarProductosEnArchivo(productos);

    auditoria.insertar(usuarioRegistrado.getNombre(), "200", "AJUSTE-INV");
    cout << "\n\t\tInventario ajustado correctamente." << endl;
    system("pause");
}

void Inventario::reporteExistencias() {
    system("cls");
    cout << "\t\t========================================" << endl;
    cout << "\t\t| REPORTE DE EXISTENCIAS               |" << endl;
    cout << "\t\t========================================" << endl;

    vector<Producto> productos = cargarProductosDesdeArchivo();
    if (productos.empty()) {
        cout << "\t\tNo hay productos registrados." << endl;
        system("pause");
        return;
    }

    cout << "\t\t" << left << setw(10) << "ID"
         << setw(20) << "NOMBRE"
         << setw(10) << "STOCK"
         << setw(15) << "STOCK MIN" << endl;
    cout << "\t\t" << string(55, '-') << endl;

    for (const auto& producto : productos) {
        cout << "\t\t" << setw(10) << producto.getId()
             << setw(20) << producto.getNombre()
             << setw(10) << producto.getStock()
             << setw(15) << producto.getStockMinimo() << endl;
    }

    // Calcular totales
    int totalStock = 0;
    for (const auto& p : productos) {
        totalStock += p.getStock();
    }

    cout << "\t\t" << string(55, '-') << endl;
    cout << "\t\t" << setw(30) << "TOTAL STOCK:"
         << setw(10) << totalStock << endl;

    auditoria.insertar(usuarioRegistrado.getNombre(), "200", "REPORTE-INV");
    system("pause");
}
