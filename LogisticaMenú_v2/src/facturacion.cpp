// Angoly Araujo Mayo 2025
#include "facturacion.h"
#include "pedidos.h"
#include "clientes.h"
#include "usuarios.h"
#include "bitacora.h"
#include <fstream>
#include <iomanip>
#include <cstring>
#include <limits>

extern usuarios usuarioRegistrado; // Usuario actualmente registrado
extern bitacora auditoria;         // Bitácora para registrar acciones

// --- Menu principal de facturacion ---
void Facturacion::mostrarMenuFacturacion() {
    int opcion;
    do {
        // Mostrar opciones del menú
        cout << "\n=========== MENU DE FACTURACION ===========\n";
        cout << "1. Crear Factura\n";
        cout << "2. Mostrar Facturas\n";
        cout << "3. Modificar Factura\n";
        cout << "4. Eliminar Factura\n";
        cout << "0. Salir\n";
        cout << "===========================================\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        // Ejecutar la opción seleccionada
        switch (opcion) {
            case 1: crearFactura(); break;
            case 2: mostrarFacturas(); break;
            case 3: modificarFactura(); break;
            case 4: eliminarFactura(); break;
            case 0: cout << "Saliendo del modulo de facturacion...\n"; break;
            default: cout << "Opcion invalida.\n"; break;
        }

    } while (opcion != 0);
}

// --- Genera un nuevo ID para la factura dentro del rango permitido ---
int Facturacion::generarIdFactura() {
    ifstream archivo(archivoFacturas, ios::binary);
    int ultimoId = 3555;
    Factura temp;

    // Leer el archivo para encontrar el último ID usado
    while (archivo.read(reinterpret_cast<char*>(&temp), sizeof(Factura))) {
        if (temp.idFactura >= ultimoId) {
            ultimoId = temp.idFactura + 1;
        }
    }

    archivo.close();

    // Validar que el ID no exceda el rango permitido
    if (ultimoId > 3606) {
        throw runtime_error("Se ha alcanzado el limite de IDs de facturas (3555 - 3606).");
    }

    return ultimoId;
}

// --- Guarda una factura en el archivo binario ---
void Facturacion::guardarEnArchivo(Factura factura) {
    ofstream archivo(archivoFacturas, ios::binary | ios::app);
    if (archivo) {
        archivo.write(reinterpret_cast<char*>(&factura), sizeof(Factura));
        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo para guardar la factura." << endl;
    }
}

// --- Registra una acción en la bitácora (falta completar escritura en bitácora) ---
void Facturacion::registrarBitacora(const Factura& factura, const string& accion, const string& usuario) {
    string descripcion = "Factura ID " + to_string(factura.idFactura) + " | Pedido: " + to_string(factura.idPedido) +
                         " | Cliente: " + to_string(factura.idCliente) +
                         " | Monto: " + to_string(factura.monto) +
                         " | Pagada: " + string(factura.pagada ? "Si" : "No");

    // Falta: auditoria.registrar(accion, usuario, descripcion);
}

// --- Crea una nueva factura ---
void Facturacion::crearFactura() {
    int volver;
    cout << "Desea regresar al menu principal? (1: Si / 0: No): ";
    cin >> volver;
    if (volver == 1) return;

    // Cargar pedidos disponibles
    vector<Pedidos> listaPedidos;
    Pedidos::cargarDesdeArchivoBin(listaPedidos);

    if (listaPedidos.empty()) {
        cout << "No hay pedidos registrados." << endl;
        return;
    }

    // Mostrar pedidos disponibles
    string idPedidoStr;
    cout << "\n--- Lista de pedidos disponibles ---\n";
    for (const auto& pedido : listaPedidos) {
        cout << "ID Pedido: " << pedido.getId()
             << " | ID Cliente: " << pedido.getIdCliente()
             << " | Estado: " << pedido.getEstado() << endl;
    }

    // Solicitar ID de pedido
    cout << "Ingrese el ID del pedido para facturar: ";
    cin >> idPedidoStr;

    // Buscar pedido por ID
    auto it = find_if(listaPedidos.begin(), listaPedidos.end(), [&idPedidoStr](const Pedidos& p) {
        return p.getId() == idPedidoStr;
    });

    if (it == listaPedidos.end()) {
        cout << "ID de pedido no encontrado." << endl;
        return;
    }

    // Crear nueva factura
    Factura nueva;
    nueva.idFactura = generarIdFactura();

    try {
        nueva.idPedido = stoi(it->getId());
        nueva.idCliente = stoi(it->getIdCliente());
    } catch (...) {
        cerr << "Error al convertir ID de pedido o cliente a entero. Revisa las estructuras." << endl;
        return;
    }

    nueva.monto = 0;
    nueva.pagada = false;
    memset(nueva.cliente, 0, sizeof(nueva.cliente)); // Inicializar nombre cliente

    // Calcular monto total desde los detalles del pedido
    string detalles = it->getDetalles();
    size_t pos = 0;
    while ((pos = detalles.find('\n')) != string::npos) {
        string linea = detalles.substr(0, pos);
        size_t precioPos = linea.find("Precio:");
        size_t cantPos = linea.find("Cantidad:");

        if (precioPos != string::npos && cantPos != string::npos) {
            double precio = stod(linea.substr(precioPos + 7));
            int cantidad = stoi(linea.substr(cantPos + 9, precioPos - cantPos - 9));
            nueva.monto += precio * cantidad;
        }

        detalles.erase(0, pos + 1);
    }

    // Guardar y registrar factura
    guardarEnArchivo(nueva);
    registrarBitacora(nueva, "Creacion", usuarioRegistrado.getNombre());

    // Mostrar diseño visual de la factura
    cout << "\n\n=====================================\n";
    cout << "              FACTURA                \n";
    cout << "=====================================\n";
    cout << "ID Factura : " << nueva.idFactura << endl;
    cout << "ID Cliente : " << nueva.idCliente << endl;
    cout << "ID Pedido  : " << nueva.idPedido << endl;
    cout << "Monto Total: $" << fixed << setprecision(2) << nueva.monto << endl;
    cout << "Estado     : " << (nueva.pagada ? "Pagada" : "No Pagada") << endl;
    cout << "=====================================\n";
    cout << "Factura creada exitosamente.\n";
}

// --- Muestra todas las facturas almacenadas ---
void Facturacion::mostrarFacturas() {
    ifstream archivo(archivoFacturas, ios::binary);
    if (!archivo) {
        cerr << "No se pudo abrir el archivo de facturas." << endl;
        return;
    }

    Factura temp;
    cout << "\n--- Listado de Facturas ---\n";
    while (archivo.read(reinterpret_cast<char*>(&temp), sizeof(Factura))) {
        cout << "ID Factura: " << temp.idFactura
             << " | ID Cliente: " << temp.idCliente
             << " | ID Pedido: " << temp.idPedido
             << " | Monto: $" << fixed << setprecision(2) << temp.monto
             << " | Pagada: " << (temp.pagada ? "Si" : "No") << endl;
    }

    archivo.close();
}

// --- Permite modificar el estado de pago de una factura ---
void Facturacion::modificarFactura() {
    int volver;
    cout << "Desea regresar al menu principal? (1: Si / 0: No): ";
    cin >> volver;
    if (volver == 1) return;

    mostrarFacturas();

    int idMod;
    cout << "\nIngrese el ID de la factura a modificar: ";
    cin >> idMod;

    fstream archivo(archivoFacturas, ios::binary | ios::in | ios::out);
    if (!archivo) {
        cerr << "No se pudo abrir el archivo." << endl;
        return;
    }

    Factura temp;
    bool encontrado = false;

    // Buscar factura por ID y modificar
    while (archivo.read(reinterpret_cast<char*>(&temp), sizeof(Factura))) {
        if (temp.idFactura == idMod) {
            encontrado = true;
            cout << "Factura encontrada. Modifique los campos:\n";
            cout << "Estado actual de pago: " << (temp.pagada ? "Si" : "No") << endl;
            cout << "Desea marcar como pagada? (1: Si / 0: No): ";
            int opcion;
            cin >> opcion;
            temp.pagada = (opcion == 1);

            archivo.seekp(-static_cast<int>(sizeof(Factura)), ios::cur);
            archivo.write(reinterpret_cast<char*>(&temp), sizeof(Factura));

            registrarBitacora(temp, "Modificacion", usuarioRegistrado.getNombre());
            cout << "Factura modificada correctamente.\n";
            break;
        }
    }

    if (!encontrado) {
        cout << "Factura no encontrada.\n";
    }

    archivo.close();
}

// --- Elimina una factura por ID ---
void Facturacion::eliminarFactura() {
    int volver;
    cout << "Desea regresar al menu principal? (1: Si / 0: No): ";
    cin >> volver;
    if (volver == 1) return;

    mostrarFacturas();

    int idDel;
    cout << "\nIngrese el ID de la factura a eliminar: ";
    cin >> idDel;

    ifstream archivo(archivoFacturas, ios::binary);
    ofstream temp("tempFacturas.bin", ios::binary);
    bool eliminado = false;
    Factura tempFactura;

    // Copiar todas las facturas excepto la que se va a eliminar
    while (archivo.read(reinterpret_cast<char*>(&tempFactura), sizeof(Factura))) {
        if (tempFactura.idFactura == idDel) {
            eliminado = true;
            registrarBitacora(tempFactura, "Eliminacion", usuarioRegistrado.getNombre());
            continue;
        }
        temp.write(reinterpret_cast<char*>(&tempFactura), sizeof(Factura));
    }

    archivo.close();
    temp.close();

    // Reemplazar archivo original por el temporal
    remove(archivoFacturas);
    rename("tempFacturas.bin", archivoFacturas);

    if (eliminado) {
        cout << "Factura eliminada correctamente.\n";
    } else {
        cout << "Factura no encontrada.\n";
    }
}
