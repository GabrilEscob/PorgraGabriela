//JENNIFER BARRIOS COORD EQ:3 MAYO 2025 9959-24-10016

// Inclusión de cabeceras necesarias
#include "pedidos.h"         // Definición de la clase Pedidos
#include "clientes.h"        // Para manejo de clientes
#include "producto.h"        // Para manejo de productos
#include "Almacen.h"         // Para manejo de almacenes
#include <iostream>          // Para entrada/salida estándar
#include <fstream>           // Para manejo de archivos
#include <sstream>           // Para manejo de strings como streams
#include <iomanip>           // Para formato de salida
#include <algorithm>         // Para funciones como find_if, any_of
#include <limits>            // Para límites de tipos numéricos
#include <ctime>             // Para manejo de fechas/horas
#include "envios.h"          // Para manejo de envíos
#include "transportistas.h"  // Para manejo de transportistas

using namespace std;

// Definición del vector estático que almacena todos los pedidos
std::vector<Pedidos> Pedidos::listaPedidos;

// Rango de IDs disponibles para nuevos pedidos
const int CODIGO_INICIAL = 3400;
const int CODIGO_FINAL = 3500;

// Constructor por defecto de Pedidos
// Inicializa la fecha con el tiempo actual y estado como "procesado"
Pedidos::Pedidos() : fechaPedido(time(nullptr)), estado("procesado") {}

// Función para generar un ID único para nuevos pedidos
// Recibe la lista de pedidos existentes para evitar duplicados
// Devuelve un string con el ID generado o string vacío si no hay disponibles
string Pedidos::generarIdUnico(const vector<Pedidos>& lista) {
    for (int i = CODIGO_INICIAL; i <= CODIGO_FINAL; ++i) {
        string id = to_string(i);
        if (idDisponible(lista, id)) {
            return id;
        }
    }
    return "";
}

// Función para verificar si un ID está disponible
// Recibe la lista de pedidos y el ID a verificar
// Devuelve true si el ID está disponible, false si ya existe
bool Pedidos::idDisponible(const vector<Pedidos>& lista, const string& id) {
    return none_of(lista.begin(), lista.end(),
        [&id](const Pedidos& p) { return p.id == id; });
}

// Función para validar si un cliente existe
// Recibe el ID del cliente y la lista de clientes
// Devuelve true si el cliente existe, false si no
bool Pedidos::validarCliente(const string& idCliente, const vector<Clientes>& clientes) {
    return any_of(clientes.begin(), clientes.end(),
        [&idCliente](const Clientes& c) { return c.getId() == idCliente; });
}

// Función para validar si un producto existe
// Recibe el código del producto y la lista de productos
// Devuelve true si el producto existe, false si no
bool Pedidos::validarProducto(const string& codigoProducto, const vector<Producto>& productos) {
    return any_of(productos.begin(), productos.end(),
        [&codigoProducto](const Producto& p) { return p.getCodigo() == codigoProducto; });
}

// Función para validar si un almacén existe
// Recibe el ID del almacén y la lista de almacenes
// Devuelve true si el almacén existe, false si no
bool Pedidos::validarAlmacen(const string& idAlmacen, const vector<Almacen>& almacenes) {
    return any_of(almacenes.begin(), almacenes.end(),
        [&idAlmacen](const Almacen& a) { return a.getId() == idAlmacen; });
}

// Función para obtener detalles básicos de un pedido
// Devuelve un string con información resumida del pedido
string Pedidos::getDetalles() const {
    stringstream ss;
    ss << "Pedido ID: " << id << " - Cliente: " << idCliente << " - Estado: " << estado;
    return ss.str();
}

// Función principal para gestionar pedidos
// Muestra un menú con opciones para crear, consultar, modificar, cancelar y completar pedidos
// Recibe listas de clientes, productos y almacenes para validaciones
void Pedidos::gestionPedidos(const vector<Clientes>& clientes,
                           vector<Producto>& productos,
                           const vector<Almacen>& almacenes) {
    // Carga los pedidos desde archivo al iniciar
    cargarDesdeArchivoBin(listaPedidos);

    int opcion;
    do {
        system("cls");
        // Menú de opciones
        cout << "\t\t========================================" << endl;
        cout << "\t\t| SISTEMA DE GESTION DE PEDIDOS        |" << endl;
        cout << "\t\t========================================" << endl;
        cout << "\t\t 1. Crear nuevo pedido" << endl;
        cout << "\t\t 2. Consultar todos los pedidos" << endl;
        cout << "\t\t 3. Modificar pedido existente" << endl;
        cout << "\t\t 4. Cancelar pedido" << endl;
        cout << "\t\t 5. Completar pedido (envío)" << endl;
        cout << "\t\t 6. Volver al menú principal" << endl;
        cout << "\t\t========================================" << endl;
        cout << "\t\tOpcion a escoger: ";

        // Validación de entrada
        while (!(cin >> opcion) || opcion < 1 || opcion > 6) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\t\tEntrada inválida. Ingrese un número del 1 al 6: ";
        }

        // Switch para manejar las opciones del menú
        switch(opcion) {
            case 1:
                crearPedido(clientes, productos, almacenes);
                break;
            case 2:
                consultarPedidos();
                break;
            case 3:
                modificarPedido(clientes, productos, almacenes);
                break;
            case 4:
                cancelarPedido();
                break;
            case 5:
                completarPedido(productos);
                break;
            case 6:
                guardarEnArchivoBin(listaPedidos);
                auditoria.registrar(usuarioRegistrado.getNombre(),
                                  "PEDIDOS",
                                  "Salida de gestión de pedidos");
                break;
        }
    } while(opcion != 6);
}

// Función para crear un nuevo pedido
// Recibe listas de clientes, productos y almacenes para validaciones
void Pedidos::crearPedido(const std::vector<Clientes>& clientes,
                        const std::vector<Producto>& productos,
                        const std::vector<Almacen>& almacenes) {
    system("cls");
    cout << "\n\t\t[CREANDO NUEVO PEDIDO...]" << endl;

    // Verificación de datos mínimos requeridos
    if (clientes.empty()) {
        cout << "\n\t\t¡ADVERTENCIA! No hay clientes registrados.\n";
        system("pause");
        return;
    }

    if (almacenes.empty()) {
        cout << "\n\t\t¡ADVERTENCIA! No hay almacenes registrados.\n";
        system("pause");
        return;
    }

    if (productos.empty()) {
        cout << "\n\t\t¡ADVERTENCIA! No hay productos registrados.\n";
        system("pause");
        return;
    }

    // Creación del nuevo pedido
    Pedidos nuevo;
    nuevo.id = generarIdUnico(listaPedidos);

    if (nuevo.id.empty()) {
        cerr << "\n\t\tError: No hay IDs disponibles para nuevos pedidos\n";
        system("pause");
        return;
    }

    // Mostrar información para nuevo pedido
    cout << "\n\t\t=== NUEVO PEDIDO (ID: " << nuevo.id << ") ===" << endl;

    // Selección de cliente
    cout << "\n\t\t--- CLIENTES DISPONIBLES ---\n";
    for (const auto& cliente : clientes) {
        cout << "\t\tID: " << cliente.getId() << " | Nombre: " << cliente.getNombre() << endl;
    }

    while (true) {
        cout << "\n\t\tIngrese ID del cliente: ";
        cin >> nuevo.idCliente;

        if (validarCliente(nuevo.idCliente, clientes)) break;
        cerr << "\t\tCliente no válido. Intente nuevamente.\n";
    }

    // Selección de almacén
    cout << "\n\t\t--- ALMACENES DISPONIBLES ---\n";
    for (const auto& almacen : almacenes) {
        cout << "\t\tID: " << almacen.getId() << " | Dirección: " << almacen.getDireccion()
             << " | Estado: " << almacen.getEstado() << endl;
    }

    while (true) {
        cout << "\n\t\tIngrese ID del almacén: ";
        cin >> nuevo.idAlmacen;

        if (validarAlmacen(nuevo.idAlmacen, almacenes)) break;
        cerr << "\t\tAlmacén no válido. Intente nuevamente.\n";
    }

    // Agregar productos al pedido
    char continuar;
    do {
        // Mostrar productos disponibles
        cout << "\n\t\t--- PRODUCTOS DISPONIBLES ---\n";
        for (const auto& producto : productos) {
            cout << "\t\tCódigo: " << producto.getCodigo()
                 << " | Nombre: " << producto.getNombre()
                 << " | Stock: " << producto.getStock() << endl;
        }

        DetallePedido detalle;
        cout << "\n\t\t--- Agregar producto ---" << endl;

        // Selección de producto
        const Producto* productoSeleccionado = nullptr;
        while (true) {
            cout << "\t\tIngrese código de producto: ";
            cin >> detalle.codigoProducto;

            auto it = find_if(productos.begin(), productos.end(),
                [&detalle](const Producto& p) { return p.getCodigo() == detalle.codigoProducto; });

            if (it != productos.end()) {
                productoSeleccionado = &(*it);
                detalle.precioUnitario = productoSeleccionado->getPrecio();
                break;
            }
            cerr << "\t\tProducto no válido. Intente nuevamente.\n";
        }

        // Manejo de cantidad del producto
        bool productoAgregado = false;
        while (!productoAgregado) {
            cout << "\t\tIngrese cantidad (Stock disponible: "
                 << productoSeleccionado->getStock() << "): ";

            if (cin >> detalle.cantidad && detalle.cantidad > 0) {
                if (detalle.cantidad <= productoSeleccionado->getStock()) {
                    nuevo.detalles.push_back(detalle);
                    productoAgregado = true;

                    // Actualizar stock
                    const_cast<Producto*>(productoSeleccionado)->setStock(
                        productoSeleccionado->getStock() - detalle.cantidad);

                    cout << "\t\tProducto agregado al pedido.\n";
                } else {
                    // Manejo de stock insuficiente
                    cout << "\t\tNo hay suficiente stock. Stock disponible: "
                         << productoSeleccionado->getStock() << "\n";
                    cout << "\t\t1. Ingresar otra cantidad\n";
                    cout << "\t\t2. Elegir otro producto\n";
                    cout << "\t\t3. Cancelar agregar producto\n";
                    cout << "\t\tOpción: ";

                    int opcion;
                    while (!(cin >> opcion) || opcion < 1 || opcion > 3) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "\t\tOpción inválida. Ingrese 1, 2 o 3: ";
                    }

                    if (opcion == 2) break;
                    if (opcion == 3) {
                        productoAgregado = true;
                        continuar = 'n';
                    }
                }
            } else {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cerr << "\t\tCantidad inválida. Ingrese un número positivo.\n";
            }
        }

        // Preguntar si desea agregar más productos
        if (productoAgregado && !nuevo.detalles.empty()) {
            cout << "\n\t\t¿Desea agregar otro producto? (s/n): ";
            cin >> continuar;
        } else if (!productoAgregado) {
            continuar = 'n';
        }
    } while (continuar == 's' || continuar == 'S');

    // Guardar el pedido si tiene productos
    if (!nuevo.detalles.empty()) {
        Producto::guardarEnArchivoBin(productos);

        nuevo.estado = "procesado";
        listaPedidos.push_back(nuevo);
        guardarEnArchivoBin(listaPedidos);

        auditoria.registrar(usuarioRegistrado.getNombre(), "PEDIDOS", "Pedido creado - ID: " + nuevo.id);
        cout << "\n\t\tPedido registrado exitosamente!" << endl;
    } else {
        cout << "\n\t\tNo se creó el pedido porque no contiene productos." << endl;
    }
    system("pause");
}

// Función para consultar todos los pedidos
// Muestra una lista detallada de todos los pedidos registrados
void Pedidos::consultarPedidos() {
    system("cls");
    Pedidos::cargarDesdeArchivoBin(listaPedidos);
    cout << "\n\t\t[CONSULTANDO PEDIDOS...]" << endl;

    if (listaPedidos.empty()) {
        cout << "\n\t\tNo hay pedidos registrados." << endl;
        system("pause");
        return;
    }

    // Mostrar detalles de cada pedido
    cout << "\n\t\t=== LISTA DE PEDIDOS ===" << endl;
    for (const auto& pedido : listaPedidos) {
        cout << "\t\tID: " << pedido.id << endl;
        cout << "\t\tCliente: " << pedido.idCliente << endl;
        cout << "\t\tAlmacén: " << pedido.idAlmacen << endl;

        // Formatear fecha
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&pedido.fechaPedido));
        cout << "\t\tFecha: " << buffer << endl;

        cout << "\t\tEstado: " << pedido.estado << endl;
        cout << "\t\tProductos:" << endl;

        // Calcular y mostrar total
        double total = 0.0;
        for (const auto& detalle : pedido.detalles) {
            cout << "\t\t  - " << detalle.codigoProducto
                 << " x" << detalle.cantidad
                 << " @ $" << detalle.precioUnitario << endl;
            total += detalle.cantidad * detalle.precioUnitario;
        }

        cout << "\t\tTotal: $" << fixed << setprecision(2) << total << endl;
        cout << "\t\t----------------------------" << endl;
    }

    auditoria.registrar(usuarioRegistrado.getNombre(), "PEDIDOS", "Consulta de pedidos");
    system("pause");
}

// Función para modificar un pedido existente
// Permite cambiar estado y productos de un pedido
// Recibe listas de clientes, productos y almacenes para validaciones
void Pedidos::modificarPedido(const vector<Clientes>& clientes,
                            const vector<Producto>& productos,
                            const vector<Almacen>& almacenes) {
    system("cls");
    cout << "\n\t\t[MODIFICANDO PEDIDO...]" << endl;

    if (listaPedidos.empty()) {
        cout << "\n\t\tNo hay pedidos para modificar." << endl;
        system("pause");
        return;
    }

    // Mostrar pedidos modificables (pendientes o procesados)
    cout << "\n\t\t=== PEDIDOS DISPONIBLES PARA MODIFICAR ===" << endl;
    for (const auto& pedido : listaPedidos) {
        if (pedido.estado == "pendiente" || pedido.estado == "procesado") {
            cout << "\t\tID: " << pedido.id << " - Estado: " << pedido.estado << endl;
        }
    }

    string id;
    cout << "\n\t\tIngrese ID del pedido a modificar (o 0 para volver): ";
    cin >> id;

    if (id == "0") return;

    // Buscar el pedido
    auto it = find_if(listaPedidos.begin(), listaPedidos.end(),
        [&id](const Pedidos& p) { return p.id == id; });

    if (it != listaPedidos.end()) {
        cout << "\n\t\t=== MODIFICAR PEDIDO (ID: " << id << ") ===" << endl;

        // Modificar estado
        cout << "\t\tNuevo estado (pendiente/procesado/enviado/cancelado): ";
        cin >> it->estado;

        // Opción para modificar productos
        char opcion;
        cout << "\t\t¿Desea modificar los productos? (s/n): ";
        cin >> opcion;

        if (opcion == 's' || opcion == 'S') {
            it->detalles.clear();
            char continuar;
            do {
                DetallePedido detalle;
                cout << "\n\t\t--- Agregar producto ---" << endl;

                // Selección de producto
                while (true) {
                    cout << "\t\tCódigo de producto: ";
                    cin >> detalle.codigoProducto;

                    if (validarProducto(detalle.codigoProducto, productos)) {
                        // Obtener precio del producto
                        auto prod = find_if(productos.begin(), productos.end(),
                        [&detalle](const Producto& p) { return p.getCodigo() == detalle.codigoProducto; });
                        detalle.precioUnitario = prod->getPrecio();
                        break;
                    }
                    cerr << "\t\tProducto no válido. Intente nuevamente.\n";
                }

                // Cantidad del producto
                cout << "\t\tCantidad: ";
                while (!(cin >> detalle.cantidad) || detalle.cantidad <= 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cerr << "\t\tCantidad inválida. Ingrese un número positivo: ";
                }

                it->detalles.push_back(detalle);

                cout << "\n\t\t¿Desea agregar otro producto? (s/n): ";
                cin >> continuar;
            } while (continuar == 's' || continuar == 'S');
        }

        // Guardar cambios
        guardarEnArchivoBin(listaPedidos);
        auditoria.registrar(usuarioRegistrado.getNombre(), "PEDIDOS", "Pedido modificado - ID: " + id);
        cout << "\n\t\tPedido modificado exitosamente!" << endl;
    } else {
        cout << "\t\tPedido no encontrado." << endl;
    }
    system("pause");
}

// Función para cancelar un pedido
// Cambia el estado del pedido a "cancelado"
void Pedidos::cancelarPedido() {
    system("cls");
    cout << "\n\t\t[CANCELANDO PEDIDO...]" << endl;

    if (listaPedidos.empty()) {
        cout << "\n\t\tNo hay pedidos para cancelar." << endl;
        system("pause");
        return;
    }

    // Mostrar lista de pedidos disponibles para cancelar
    cout << "\n\t\t=== LISTA DE PEDIDOS DISPONIBLES PARA CANCELAR ===" << endl;
    cout << "\t\t" << string(70, '-') << endl;
    cout << "\t\t" << left << setw(10) << "ID" << setw(15) << "Cliente"
         << setw(15) << "Almacén" << setw(20) << "Fecha" << setw(15) << "Estado" << endl;
    cout << "\t\t" << string(70, '-') << endl;

    for (const auto& pedido : listaPedidos) {
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&pedido.fechaPedido));

        cout << "\t\t" << setw(10) << pedido.id
             << setw(15) << (pedido.idCliente.size() > 10 ? pedido.idCliente.substr(0, 10) + "..." : pedido.idCliente)
             << setw(15) << (pedido.idAlmacen.size() > 10 ? pedido.idAlmacen.substr(0, 10) + "..." : pedido.idAlmacen)
             << setw(20) << buffer
             << setw(15) << pedido.estado << endl;
    }
    cout << "\t\t" << string(70, '-') << endl;

    // Selección de pedido a cancelar
    string id;
    cout << "\n\t\tIngrese ID del pedido a cancelar (o 0 para volver): ";
    cin >> id;

    if (id == "0") return;

    // Buscar el pedido
    auto it = find_if(listaPedidos.begin(), listaPedidos.end(),
        [&id](const Pedidos& p) { return p.id == id; });

    if (it != listaPedidos.end()) {
        // Cambiar estado a cancelado
        it->estado = "cancelado";
        guardarEnArchivoBin(listaPedidos);
        auditoria.registrar(usuarioRegistrado.getNombre(), "PEDIDOS", "Pedido cancelado - ID: " + id);
        cout << "\n\t\tPedido cancelado exitosamente!" << endl;
    } else {
        cout << "\t\tPedido no encontrado." << endl;
    }
    system("pause");
}

// Función para guardar pedidos en archivo binario
// Recibe la lista de pedidos a guardar
void Pedidos::guardarEnArchivoBin(const vector<Pedidos>& lista) {
    ofstream archivo("pedidos.bin", ios::binary | ios::out);
    if (!archivo.is_open()) {
        cerr << "\n\t\tError crítico: No se pudo abrir archivo de pedidos!\n";
        return;
    }

    try {
        // Escribir cantidad de pedidos
        size_t cantidad = lista.size();
        archivo.write(reinterpret_cast<const char*>(&cantidad), sizeof(cantidad));

        // Escribir cada pedido
        for (const auto& pedido : lista) {
            // Escribir campos básicos
            size_t idSize = pedido.id.size();
            archivo.write(reinterpret_cast<const char*>(&idSize), sizeof(idSize));
            archivo.write(pedido.id.c_str(), idSize);

            size_t clienteSize = pedido.idCliente.size();
            archivo.write(reinterpret_cast<const char*>(&clienteSize), sizeof(clienteSize));
            archivo.write(pedido.idCliente.c_str(), clienteSize);

            size_t almacenSize = pedido.idAlmacen.size();
            archivo.write(reinterpret_cast<const char*>(&almacenSize), sizeof(almacenSize));
            archivo.write(pedido.idAlmacen.c_str(), almacenSize);

            archivo.write(reinterpret_cast<const char*>(&pedido.fechaPedido), sizeof(pedido.fechaPedido));

            size_t estadoSize = pedido.estado.size();
            archivo.write(reinterpret_cast<const char*>(&estadoSize), sizeof(estadoSize));
            archivo.write(pedido.estado.c_str(), estadoSize);

            // Escribir detalles del pedido
            size_t detallesSize = pedido.detalles.size();
            archivo.write(reinterpret_cast<const char*>(&detallesSize), sizeof(detallesSize));

            for (const auto& detalle : pedido.detalles) {
                size_t codigoSize = detalle.codigoProducto.size();
                archivo.write(reinterpret_cast<const char*>(&codigoSize), sizeof(codigoSize));
                archivo.write(detalle.codigoProducto.c_str(), codigoSize);

                archivo.write(reinterpret_cast<const char*>(&detalle.cantidad), sizeof(detalle.cantidad));
                archivo.write(reinterpret_cast<const char*>(&detalle.precioUnitario), sizeof(detalle.precioUnitario));
            }
        }

        archivo.flush();
        if (!archivo) {
            throw runtime_error("Error al escribir en archivo");
        }
    } catch (const exception& e) {
        cerr << "\n\t\tError al guardar pedidos: " << e.what() << "\n";
        archivo.close();
        remove("pedidos.bin");
        return;
    }

    archivo.close();
}

// Función para cargar pedidos desde archivo binario
// Recibe la lista de pedidos donde se cargarán los datos
void Pedidos::cargarDesdeArchivoBin(vector<Pedidos>& lista) {
    lista.clear();
    ifstream archivo("pedidos.bin", ios::binary | ios::in);

    if (!archivo) {
        // Si el archivo no existe, no es un error (primera ejecución)
        return;
    }

    try {
        // Leer cantidad de pedidos
        size_t cantidad;
        archivo.read(reinterpret_cast<char*>(&cantidad), sizeof(cantidad));

        for (size_t i = 0; i < cantidad; ++i) {
            Pedidos pedido;

            // Leer campos básicos
            size_t idSize;
            archivo.read(reinterpret_cast<char*>(&idSize), sizeof(idSize));
            pedido.id.resize(idSize);
            archivo.read(&pedido.id[0], idSize);

            size_t clienteSize;
            archivo.read(reinterpret_cast<char*>(&clienteSize), sizeof(clienteSize));
            pedido.idCliente.resize(clienteSize);
            archivo.read(&pedido.idCliente[0], clienteSize);

            size_t almacenSize;
            archivo.read(reinterpret_cast<char*>(&almacenSize), sizeof(almacenSize));
            pedido.idAlmacen.resize(almacenSize);
            archivo.read(&pedido.idAlmacen[0], almacenSize);

            archivo.read(reinterpret_cast<char*>(&pedido.fechaPedido), sizeof(pedido.fechaPedido));

            size_t estadoSize;
            archivo.read(reinterpret_cast<char*>(&estadoSize), sizeof(estadoSize));
            pedido.estado.resize(estadoSize);
            archivo.read(&pedido.estado[0], estadoSize);

            // Leer detalles del pedido
            size_t detallesSize;
            archivo.read(reinterpret_cast<char*>(&detallesSize), sizeof(detallesSize));

            for (size_t j = 0; j < detallesSize; ++j) {
                DetallePedido detalle;

                size_t codigoSize;
                archivo.read(reinterpret_cast<char*>(&codigoSize), sizeof(codigoSize));
                detalle.codigoProducto.resize(codigoSize);
                archivo.read(&detalle.codigoProducto[0], codigoSize);

                archivo.read(reinterpret_cast<char*>(&detalle.cantidad), sizeof(detalle.cantidad));
                archivo.read(reinterpret_cast<char*>(&detalle.precioUnitario), sizeof(detalle.precioUnitario));

                pedido.detalles.push_back(detalle);
            }

            lista.push_back(pedido);
        }

        if (archivo.bad()) {
            throw runtime_error("Error de lectura del archivo");
        }
    } catch (const exception& e) {
        cerr << "\n\t\tError al cargar pedidos: " << e.what() << "\n";
        lista.clear(); // Limpiar lista parcialmente cargada
    }

    archivo.close();
}

// Función para completar un pedido (marcar como enviado)
// Recibe la lista de productos para actualizar stocks
void Pedidos::completarPedido(std::vector<Producto>& productos) {
    system("cls");
    cout << "\n\t\t========================================" << endl;
    cout << "\t\t|      COMPLETAR PEDIDO (ENVÍO)       |" << endl;
    cout << "\t\t========================================\n" << endl;

    // Verificar si hay pedidos
    if (listaPedidos.empty()) {
        cout << "\t\tNo hay pedidos registrados en el sistema.\n" << endl;
        system("pause");
        return;
    }

    // Mostrar todos los pedidos
    cout << "\t\t=== LISTA COMPLETA DE PEDIDOS ===" << endl;
    cout << "\t\t" << string(70, '-') << endl;
    cout << "\t\t" << left << setw(5) << "No." << setw(10) << "ID"
         << setw(15) << "Cliente" << setw(15) << "Almacén"
         << setw(20) << "Fecha" << setw(15) << "Estado" << endl;
    cout << "\t\t" << string(70, '-') << endl;

    for (size_t i = 0; i < listaPedidos.size(); i++) {
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&listaPedidos[i].fechaPedido));

        cout << "\t\t" << setw(5) << i+1
             << setw(10) << listaPedidos[i].id
             << setw(15) << (listaPedidos[i].idCliente.size() > 10 ?
                            listaPedidos[i].idCliente.substr(0, 10) + "..." : listaPedidos[i].idCliente)
             << setw(15) << (listaPedidos[i].idAlmacen.size() > 10 ?
                            listaPedidos[i].idAlmacen.substr(0, 10) + "..." : listaPedidos[i].idAlmacen)
             << setw(20) << buffer
             << setw(15) << listaPedidos[i].estado << endl;
    }
    cout << "\t\t" << string(70, '-') << endl;

    // Selección de pedido a completar
    string idPedido;
    cout << "\n\t\tIngrese ID del pedido a completar (o 0 para cancelar): ";
    cin >> idPedido;

    if (idPedido == "0") {
        cout << "\n\t\tOperación cancelada por el usuario.\n";
        system("pause");
        return;
    }

    // Buscar el pedido
    auto it = find_if(listaPedidos.begin(), listaPedidos.end(),
        [&idPedido](const Pedidos& p) { return p.id == idPedido; });

    if (it == listaPedidos.end()) {
        cout << "\t\tPedido no encontrado." << endl;
        system("pause");
        return;
    }

    Pedidos& pedidoSeleccionado = *it;

    // Verificar estado válido para completar
    if (pedidoSeleccionado.estado != "pendiente" && pedidoSeleccionado.estado != "procesado") {
        cout << "\n\t\tEl pedido no puede ser completado. Estado actual: " << pedidoSeleccionado.estado << endl;
        system("pause");
        return;
    }

    // Mostrar detalles del pedido
    system("cls");
    cout << "\n\t\t=== DETALLES DEL PEDIDO SELECCIONADO ===" << endl;
    cout << "\t\tID: " << pedidoSeleccionado.id << endl;
    cout << "\t\tCliente: " << pedidoSeleccionado.idCliente << endl;
    cout << "\t\tAlmacén: " << pedidoSeleccionado.idAlmacen << endl;

    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&pedidoSeleccionado.fechaPedido));
    cout << "\t\tFecha: " << buffer << endl;
    cout << "\t\tEstado actual: " << pedidoSeleccionado.estado << endl;

    // Mostrar productos y calcular total
    cout << "\n\t\tPRODUCTOS INCLUIDOS:" << endl;
    cout << "\t\t" << string(40, '-') << endl;
    double total = 0.0;
    for (const auto& detalle : pedidoSeleccionado.detalles) {
        cout << "\t\t- Código: " << detalle.codigoProducto
             << " | Cantidad: " << detalle.cantidad
             << " | Precio unitario: $" << fixed << setprecision(2) << detalle.precioUnitario << endl;
        total += detalle.cantidad * detalle.precioUnitario;
    }
    cout << "\t\t" << string(40, '-') << endl;
    cout << "\t\tTOTAL DEL PEDIDO: $" << fixed << setprecision(2) << total << endl;

    // Confirmación final
    cout << "\n\t\t¿Desea completar y enviar este pedido? (s/n): ";
    char confirmacion;
    cin >> confirmacion;

    if (tolower(confirmacion) == 's') {
        // Actualizar estado
        pedidoSeleccionado.estado = "completado";

        // Registrar envío
        cout << "\n\t\tRegistrando envío para el pedido " << pedidoSeleccionado.id << "..." << endl;
        Envios::crearEnvio(pedidoSeleccionado.id, Transportistas::getTransportistasDisponibles());

        // Guardar cambios
        guardarEnArchivoBin(listaPedidos);
        Producto::guardarEnArchivoBin(productos);

        // Registrar en bitácora
        auditoria.registrar(usuarioRegistrado.getNombre(),
                          "PEDIDOS",
                          "Pedido completado - ID: " + pedidoSeleccionado.id);

        cout << "\n\t\t¡Pedido completado y enviado exitosamente!\n";
    } else {
        cout << "\n\t\tOperación cancelada. El pedido no fue completado.\n";
    }

    system("pause");
}
