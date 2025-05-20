//JENNIFER BARRIOS COORD EQ:3 MAYO 2025
#include "Producto.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <limits>
#include "bitacora.h"

using namespace std;

//: Definición del rango válido de códigos de productos
const int CODIGO_INICIAL = 3209;
const int CODIGO_FINAL = 3259;

//: Constructor por defecto que inicializa los valores numéricos
Producto::Producto() : precio(0.0), stock(0), stockMinimo(0) {}

//: Métodos getter para acceder a los atributos del producto
string Producto::getId() const { return id; }
string Producto::getCodigo() const { return codigo; }
string Producto::getNombre() const { return nombre; }
string Producto::getDescripcion() const { return descripcion; }
double Producto::getPrecio() const { return precio; }
int Producto::getStock() const { return stock; }
int Producto::getStockMinimo() const { return stockMinimo; }

//: Métodos setter para modificar los atributos del producto
void Producto::setId(const string& id) { this->id = id; }
void Producto::setCodigo(const string& codigo) { this->codigo = codigo; }
void Producto::setNombre(const string& nombre) { this->nombre = nombre; }
void Producto::setDescripcion(const string& descripcion) { this->descripcion = descripcion; }
void Producto::setPrecio(double precio) { this->precio = precio; }
void Producto::setStock(int stock) { this->stock = stock; }
void Producto::setStockMinimo(int stockMinimo) { this->stockMinimo = stockMinimo; }

//: Genera un código único dentro del rango definido que no esté en uso
string Producto::generarCodigoUnico(const vector<Producto>& lista) {
    for (int i = CODIGO_INICIAL; i <= CODIGO_FINAL; ++i) {
        string codigo = to_string(i);
        if (codigoDisponible(lista, codigo)) {
            return codigo;
        }
    }
    return ""; //: Retorna cadena vacía si no hay códigos disponibles
}

//: Verifica si un código aún no ha sido asignado
bool Producto::codigoDisponible(const vector<Producto>& lista, const string& codigo) {
    return none_of(lista.begin(), lista.end(),
        [&codigo](const Producto& p) { return p.codigo == codigo; });
}

//: Valida si un código está dentro del rango permitido
bool Producto::esCodigoValido(const string& codigo) {
    try {
        int num = stoi(codigo);
        return (num >= CODIGO_INICIAL && num <= CODIGO_FINAL);
    } catch (...) {
        return false;
    }
}

//: Agrega un nuevo producto a la lista, solicitando datos por consola
void Producto::agregar(vector<Producto>& lista, const string& usuarioActual) {
    Producto nuevo;
    nuevo.codigo = generarCodigoUnico(lista);

    if (nuevo.codigo.empty()) {
        cerr << "\n\t\tError: No hay códigos disponibles\n";
        system("pause");
        return;
    }

    cout << "\n\t\t=== AGREGAR PRODUCTO (Código: " << nuevo.codigo << ") ===\n";
    cout << "\t\t(0 para cancelar)\n";

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    //: Solicita nombre
    cout << "\t\tNombre del producto: ";
    string nombre;
    getline(cin, nombre);

    if (nombre == "0") {
        cout << "\t\tOperación cancelada.\n";
        system("pause");
        return;
    }
    nuevo.setNombre(nombre);

    //: Solicita descripción
    cout << "\t\tDescripción: ";
    string descripcion;
    getline(cin, descripcion);
    nuevo.setDescripcion(descripcion);

    //: Solicita precio y valida entrada
    cout << "\t\tPrecio: ";
    double precio;
    while (!(cin >> precio) || precio < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\t\tEntrada inválida. Ingrese precio (0 para cancelar): ";
        string input;
        getline(cin, input);
        if (input == "0") {
            cout << "\t\tOperación cancelada.\n";
            system("pause");
            return;
        }
    }
    nuevo.setPrecio(precio);

    //: Solicita stock inicial
    cout << "\t\tStock inicial: ";
    int stock;
    while (!(cin >> stock)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\t\tEntrada inválida. Ingrese stock (0 para cancelar): ";
        string input;
        getline(cin, input);
        if (input == "0") {
            cout << "\t\tOperación cancelada.\n";
            system("pause");
            return;
        }
    }
    nuevo.setStock(stock);

    //: Solicita stock mínimo
    cout << "\t\tStock mínimo: ";
    int stockMin;
    while (!(cin >> stockMin)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\t\tEntrada inválida. Ingrese stock mínimo (0 para cancelar): ";
        string input;
        getline(cin, input);
        if (input == "0") {
            cout << "\t\tOperación cancelada.\n";
            system("pause");
            return;
        }
    }
    nuevo.setStockMinimo(stockMin);

    //: Guarda el nuevo producto
    lista.push_back(nuevo);
    guardarEnArchivoBin(lista);
    bitacora::registrar(usuarioActual, "PRODUCTOS", "Agregado: " + nuevo.codigo);
    cout << "\n\t\tProducto registrado!\n";
    system("pause");
}

//: Muestra la lista completa de productos en consola con formato de tabla
void Producto::mostrar(const vector<Producto>& lista) {
    system("cls");
    cout << "\n\t\t=== INVENTARIO ===\n";
    cout << "\t\t" << left << setw(10) << "Código" << setw(25) << "Nombre"
         << setw(15) << "Precio" << setw(10) << "Stock" << setw(15) << "Stock Mín" << "\n";
    cout << "\t\t" << string(75, '-') << "\n";

    if (lista.empty()) {
        cout << "\t\tNo hay productos registrados.\n";
    } else {
        for (const auto& producto : lista) {
            cout << "\t\t" << left << setw(10) << producto.codigo
                 << setw(25) << producto.nombre.substr(0, 24)
                 << "$" << setw(14) << fixed << setprecision(2) << producto.precio
                 << setw(10) << producto.stock
                 << setw(15) << producto.stockMinimo << "\n";
        }
    }
    cout << "\n\t\tPresione cualquier tecla para continuar...";
    cin.ignore();
    cin.get();
}

//: Modifica los datos de un producto a partir de su código
void Producto::modificar(vector<Producto>& lista, const string& usuarioActual, const string& codigo) {
    auto it = find_if(lista.begin(), lista.end(),
        [&codigo](const Producto& p) { return p.codigo == codigo; });

    if (it != lista.end()) {
        cout << "\n\t\t=== MODIFICAR PRODUCTO (Código: " << codigo << ") ===\n";
        cout << "\t\t(Deje en blanco para mantener el valor actual)\n";

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        //: Modificación nombre
        cout << "\t\tNuevo nombre (" << it->nombre << "): ";
        string nuevoNombre;
        getline(cin, nuevoNombre);
        if (!nuevoNombre.empty()) it->setNombre(nuevoNombre);

        //: Modificación descripción
        cout << "\t\tNueva descripción (" << it->descripcion << "): ";
        string nuevaDesc;
        getline(cin, nuevaDesc);
        if (!nuevaDesc.empty()) it->setDescripcion(nuevaDesc);

        //: Modificación precio
        cout << "\t\tNuevo precio (" << it->precio << "): ";
        string precioStr;
        getline(cin, precioStr);
        if (!precioStr.empty()) {
            try {
                double nuevoPrecio = stod(precioStr);
                it->setPrecio(nuevoPrecio);
            } catch (...) {
                cout << "\t\tPrecio no válido. Se mantiene el actual.\n";
            }
        }

        //: Modificación stock
        cout << "\t\tNuevo stock (" << it->stock << "): ";
        string stockStr;
        getline(cin, stockStr);
        if (!stockStr.empty()) {
            try {
                int nuevoStock = stoi(stockStr);
                it->setStock(nuevoStock);
            } catch (...) {
                cout << "\t\tStock no válido. Se mantiene el actual.\n";
            }
        }

        //: Modificación stock mínimo
        cout << "\t\tNuevo stock mínimo (" << it->stockMinimo << "): ";
        string stockMinStr;
        getline(cin, stockMinStr);
        if (!stockMinStr.empty()) {
            try {
                int nuevoStockMin = stoi(stockMinStr);
                it->setStockMinimo(nuevoStockMin);
            } catch (...) {
                cout << "\t\tStock mínimo no válido. Se mantiene el actual.\n";
            }
        }

        guardarEnArchivoBin(lista);
        bitacora::registrar(usuarioActual, "PRODUCTOS", "Modificado: " + codigo);
        cout << "\n\t\tProducto modificado exitosamente!\n";
    } else {
        cout << "\t\tProducto no encontrado.\n";
    }
    system("pause");
}

//: Elimina un producto de la lista, solicitando confirmación al usuario
void Producto::eliminar(vector<Producto>& lista, const string& usuarioActual, const string& codigo) {
    auto it = find_if(lista.begin(), lista.end(),
        [&codigo](const Producto& p) { return p.codigo == codigo; });

    if (it != lista.end()) {
        cout << "\n\t\t¿Está seguro que desea eliminar el producto " << it->nombre << "? (s/n): ";
        char confirmacion;
        cin >> confirmacion;

        if (tolower(confirmacion) == 's') {
            lista.erase(it);
            guardarEnArchivoBin(lista);
            bitacora::registrar(usuarioActual, "PRODUCTOS", "Eliminado: " + codigo);
            cout << "\n\t\tProducto eliminado exitosamente!\n";
        } else {
            cout << "\n\t\tOperación cancelada.\n";
        }
    } else {
        cout << "\t\tProducto no encontrado.\n";
    }
    system("pause");
}

//: Guarda todos los productos en un archivo binario para persistencia
void Producto::guardarEnArchivoBin(const vector<Producto>& productos) {
    ofstream archivo("productos.bin", ios::binary | ios::out);

    if (!archivo.is_open()) {
        cerr << "\n\t\tError crítico: No se pudo abrir archivo de productos!\n";
        return;
    }

    try {
        size_t cantidad = productos.size();
        archivo.write(reinterpret_cast<const char*>(&cantidad), sizeof(cantidad));

        for (const auto& producto : productos) {
            size_t idSize = producto.id.size();
            archivo.write(reinterpret_cast<const char*>(&idSize), sizeof(idSize));
            archivo.write(producto.id.c_str(), idSize);

            size_t codigoSize = producto.codigo.size();
            archivo.write(reinterpret_cast<const char*>(&codigoSize), sizeof(codigoSize));
            archivo.write(producto.codigo.c_str(), codigoSize);

            size_t nombreSize = producto.nombre.size();
            archivo.write(reinterpret_cast<const char*>(&nombreSize), sizeof(nombreSize));
            archivo.write(producto.nombre.c_str(), nombreSize);

            size_t descSize = producto.descripcion.size();
            archivo.write(reinterpret_cast<const char*>(&descSize), sizeof(descSize));
            archivo.write(producto.descripcion.c_str(), descSize);

            archivo.write(reinterpret_cast<const char*>(&producto.precio), sizeof(producto.precio));
            archivo.write(reinterpret_cast<const char*>(&producto.stock), sizeof(producto.stock));
            archivo.write(reinterpret_cast<const char*>(&producto.stockMinimo), sizeof(producto.stockMinimo));
        }

        archivo.flush();
        if (!archivo) {
            throw runtime_error("Error al escribir en archivo");
        }
    } catch (const exception& e) {
        cerr << "\n\t\tError al guardar productos: " << e.what() << "\n";
        archivo.close();
        remove("productos.bin");
        return;
    }

    archivo.close();
}

//: Carga productos desde un archivo binario al vector en memoria
void Producto::cargarDesdeArchivoBin(vector<Producto>& productos) {
    productos.clear();
    ifstream archivo("productos.bin", ios::binary | ios::in);

    if (!archivo) {
        return;
    }

    try {
        size_t cantidad;
        archivo.read(reinterpret_cast<char*>(&cantidad), sizeof(cantidad));

        for (size_t i = 0; i < cantidad; ++i) {
            Producto producto;

            size_t idSize;
            archivo.read(reinterpret_cast<char*>(&idSize), sizeof(idSize));
            producto.id.resize(idSize);
            archivo.read(&producto.id[0], idSize);

            size_t codigoSize;
            archivo.read(reinterpret_cast<char*>(&codigoSize), sizeof(codigoSize));
            producto.codigo.resize(codigoSize);
            archivo.read(&producto.codigo[0], codigoSize);

            size_t nombreSize;
            archivo.read(reinterpret_cast<char*>(&nombreSize), sizeof(nombreSize));
            producto.nombre.resize(nombreSize);
            archivo.read(&producto.nombre[0], nombreSize);

            size_t descSize;
            archivo.read(reinterpret_cast<char*>(&descSize), sizeof(descSize));
            producto.descripcion.resize(descSize);
            archivo.read(&producto.descripcion[0], descSize);

            archivo.read(reinterpret_cast<char*>(&producto.precio), sizeof(producto.precio));
            archivo.read(reinterpret_cast<char*>(&producto.stock), sizeof(producto.stock));
            archivo.read(reinterpret_cast<char*>(&producto.stockMinimo), sizeof(producto.stockMinimo));

            productos.push_back(producto);
        }

        if (archivo.bad()) {
            throw runtime_error("Error de lectura del archivo");
        }
    } catch (const exception& e) {
        cerr << "\n\t\tError al cargar productos: " << e.what() << "\n";
        productos.clear();
    }

    archivo.close();
}
