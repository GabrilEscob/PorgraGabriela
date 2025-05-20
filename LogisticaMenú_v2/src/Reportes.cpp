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
#include <ctime>

using namespace std;

vector<Reportes::DatosReporte> Reportes::listaReportes;

const int CODIGO_INICIAL = 3800;
const int CODIGO_FINAL = 3850;

Reportes::Reportes() {
    cargarDesdeArchivoBin(listaReportes);
}

string Reportes::generarIdUnico(const vector<DatosReporte>& lista) {
    for (int i = CODIGO_INICIAL; i <= CODIGO_FINAL; ++i) {
        string id = to_string(i);
        if (idDisponible(lista, id)) {
            return id;
        }
    }
    return "";
}

bool Reportes::idDisponible(const vector<DatosReporte>& lista, const string& id) {
    return none_of(lista.begin(), lista.end(),
        [&id](const DatosReporte& r) { return r.id == id; });
}

void Reportes::mostrarProcesando(const string& mensaje) {
    cout << "\n\t\t" << mensaje;
    for (int i = 0; i < 3; ++i) {
        cout << ".";
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    cout << "\n";
}

string Reportes::formatearFecha(time_t fecha) {
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&fecha));
    return string(buffer);
}

string Reportes::generarTabla(const vector<vector<string>>& datos) {
    if (datos.empty()) return "No hay datos para mostrar";

    stringstream tabla;
    vector<size_t> anchosColumnas(datos[0].size(), 0);

    // Calcular anchos máximos por columna
    for (const auto& fila : datos) {
        for (size_t i = 0; i < fila.size(); ++i) {
            anchosColumnas[i] = max(anchosColumnas[i], fila[i].size());
        }
    }

    // Generar la tabla
    for (const auto& fila : datos) {
        for (size_t i = 0; i < fila.size(); ++i) {
            tabla << left << setw(anchosColumnas[i] + 2) << fila[i];
        }
        tabla << "\n";
    }

    return tabla.str();
}

// Métodos CRUD
void Reportes::crearReporte(const string& tipo, const string& contenido) {
    DatosReporte nuevo;
    nuevo.id = generarIdUnico(listaReportes);
    nuevo.tipo = tipo;
    nuevo.fechaGeneracion = time(nullptr);
    nuevo.contenido = contenido;

    listaReportes.push_back(nuevo);
    guardarEnArchivoBin(listaReportes);

    auditoria.registrar(usuarioRegistrado.getNombre(), "REPORTES",
                       "Reporte creado - ID: " + nuevo.id + " Tipo: " + tipo);
}

void Reportes::consultarReportes() {
    system("cls");
    cout << "\n\t\t=== LISTA DE REPORTES ===\n";

    if (listaReportes.empty()) {
        cout << "\t\tNo hay reportes registrados.\n";
        system("pause");
        return;
    }

    vector<vector<string>> tabla;
    tabla.push_back({"ID", "Tipo", "Fecha", "Contenido (resumen)"});

    for (const auto& reporte : listaReportes) {
        string resumen = reporte.contenido.substr(0, 30);
        if (reporte.contenido.size() > 30) resumen += "...";

        tabla.push_back({
            reporte.id,
            reporte.tipo,
            formatearFecha(reporte.fechaGeneracion),
            resumen
        });
    }

    cout << generarTabla(tabla) << endl;
    system("pause");
}

void Reportes::modificarReporte(const string& id, const string& nuevoContenido) {
    auto it = find_if(listaReportes.begin(), listaReportes.end(),
        [&id](const DatosReporte& r) { return r.id == id; });

    if (it != listaReportes.end()) {
        it->contenido = nuevoContenido;
        it->fechaGeneracion = time(nullptr);
        guardarEnArchivoBin(listaReportes);

        auditoria.registrar(usuarioRegistrado.getNombre(), "REPORTES",
                          "Reporte modificado - ID: " + id);
        cout << "\n\t\tReporte modificado exitosamente!\n";
    } else {
        cout << "\n\t\tReporte no encontrado.\n";
    }
    system("pause");
}

void Reportes::eliminarReporte(const string& id) {
    auto it = find_if(listaReportes.begin(), listaReportes.end(),
        [&id](const DatosReporte& r) { return r.id == id; });

    if (it != listaReportes.end()) {
        listaReportes.erase(it);
        guardarEnArchivoBin(listaReportes);

        auditoria.registrar(usuarioRegistrado.getNombre(), "REPORTES",
                          "Reporte eliminado - ID: " + id);
        cout << "\n\t\tReporte eliminado exitosamente!\n";
    } else {
        cout << "\n\t\tReporte no encontrado.\n";
    }
    system("pause");
}

// Métodos de generación de reportes específicos
void Reportes::informeVentas(const vector<Pedidos>& pedidos,
                           const vector<Clientes>& clientes,
                           const vector<Producto>& productos) {
    mostrarProcesando("Generando informe de ventas");

    stringstream contenido;
    contenido << "\t\t=== INFORME DE VENTAS ===\n\n";

    // Resumen general
    double totalVentas = 0;
    int totalClientes = 0;
    map<string, int> productosVendidos; // código -> cantidad

    for (const auto& pedido : pedidos) {
        if (pedido.getEstado() == "entregado") {
            totalClientes++;

            const vector<Pedidos::getDetalles>& detalles = pedidos.getDetalles();
            for (const auto& detalle : detalles) {
                totalVentas += detalle.cantidad * detalle.precioUnitario;
                productosVendidos[detalle.codigoProducto] += detalle.cantidad;
            }
        }
    }

    contenido << "Total de ventas: Q" << fixed << setprecision(2) << totalVentas << "\n";
    contenido << "Clientes atendidos: " << totalClientes << "\n";
    contenido << "Pedidos completados: " << count_if(pedidos.begin(), pedidos.end(),
        [](const Pedidos& p) { return p.getEstado() == "entregado"; }) << "\n\n";

    // Productos más vendidos
    contenido << "=== PRODUCTOS MÁS VENDIDOS ===\n";
    vector<pair<string, int>> topProductos(productosVendidos.begin(), productosVendidos.end());
    sort(topProductos.begin(), topProductos.end(),
        [](const pair<string, int>& a, const pair<string, int>& b) { return a.second > b.second; });

    vector<vector<string>> tablaProductos;
    tablaProductos.push_back({"Producto", "Cantidad Vendida", "Nombre"});

    for (const auto& producto : topProductos) {
        string codigo = producto.first;
        int cantidad = producto.second;

        string nombre = "No encontrado";
        auto prod = find_if(productos.begin(), productos.end(),
            [&codigo](const Producto& p) { return p.getCodigo() == codigo; });
        if (prod != productos.end()) nombre = prod->getNombre();

        tablaProductos.push_back({codigo, to_string(cantidad), nombre});
    }

    contenido << generarTabla(tablaProductos) << "\n";

    // Crear el reporte
    DatosReporte nuevo;
    nuevo.id = generarIdUnico(listaReportes);
    nuevo.tipo = "VENTAS";
    nuevo.fechaGeneracion = time(nullptr);
    nuevo.contenido = contenido.str();

    listaReportes.push_back(nuevo);
    guardarEnArchivoBin(listaReportes);

    system("cls");
    cout << nuevo.contenido;
    cout << "\n\t\tReporte guardado con ID: " << nuevo.id << endl;

    auditoria.registrar(usuarioRegistrado.getNombre(), "REPORTES", "Informe de ventas - ID: " + nuevo.id);
    system("pause");
}

void Reportes::analisisTiemposEntrega(const vector<Envios>& envios,
                                    const vector<Pedidos>& pedidos,
                                    const vector<Transportistas>& transportistas) {
    mostrarProcesando("Analizando tiempos de entrega");

    stringstream contenido;
    contenido << "\t\t=== ANÁLISIS DE TIEMPOS DE ENTREGA ===\n\n";

    // Calcular tiempos promedio
    double tiempoTotal = 0;
    int entregasCompletadas = 0;
    map<string, pair<double, int>> tiemposPorTransportista; // id -> (tiempo total, cantidad)

    for (const auto& envio : envios) {
        if (envio.getEstado() == "entregado") {
            auto pedidoIt = find_if(pedidos.begin(), pedidos.end(),
                [&envio](const Pedidos& p) { return p.getId() == envio.getIdPedido(); });

            if (pedidoIt != pedidos.end()) {
                double tiempoEntrega = difftime(envio.getFechaEntrega(), pedidoIt->getFechaPedido()) / (60 * 60 * 24); // en días
                tiempoTotal += tiempoEntrega;
                entregasCompletadas++;

                tiemposPorTransportista[envio.getIdTransportista()].first += tiempoEntrega;
                tiemposPorTransportista[envio.getIdTransportista()].second++;
            }
        }
    }

    if (entregasCompletadas > 0) {
        contenido << "Tiempo promedio de entrega: " << fixed << setprecision(2)
                 << (tiempoTotal / entregasCompletadas) << " días\n";
        contenido << "Entregas completadas: " << entregasCompletadas << "\n\n";

        // Rendimiento por transportista
        contenido << "=== RENDIMIENTO POR TRANSPORTISTA ===\n";
        vector<vector<string>> tablaTransportistas;
        tablaTransportistas.push_back({"ID", "Nombre", "Tiempo Promedio", "Entregas"});

        for (const auto& elemento : tiemposPorTransportista) {
            string id = elemento.first;
            auto datos = elemento.second;

            string nombre = "No encontrado";
            auto trans = find_if(transportistas.begin(), transportistas.end(),
                [&id](const Transportistas& t) { return t.getId() == id; });
            if (trans != transportistas.end()) nombre = trans->getNombre();

            double promedio = datos.first / datos.second;
            tablaTransportistas.push_back({
                id,
                nombre,
                to_string(promedio) + " días",
                to_string(datos.second)
            });
        }

        contenido << generarTabla(tablaTransportistas) << "\n";
    } else {
        contenido << "No hay entregas completadas para analizar.\n";
    }

    // Crear el reporte
    DatosReporte nuevo;
    nuevo.id = generarIdUnico(listaReportes);
    nuevo.tipo = "TIEMPOS_ENTREGA";
    nuevo.fechaGeneracion = time(nullptr);
    nuevo.contenido = contenido.str();

    listaReportes.push_back(nuevo);
    guardarEnArchivoBin(listaReportes);

    system("cls");
    cout << nuevo.contenido;
    cout << "\n\t\tReporte guardado con ID: " << nuevo.id << endl;

    auditoria.registrar(usuarioRegistrado.getNombre(), "REPORTES", "Análisis tiempos entrega - ID: " + nuevo.id);
    system("pause");
}

void Reportes::reporteInventarios(const vector<Producto>& productos,
                                const vector<Almacen>& almacenes) {
    mostrarProcesando("Generando reporte de inventario");

    stringstream contenido;
    contenido << "\t\t=== REPORTE DE INVENTARIO ===\n\n";

    // Resumen general
    int totalProductos = productos.size();
    int bajoInventario = count_if(productos.begin(), productos.end(),
        [](const Producto& p) { return p.getStock() < p.getStockMinimo(); });

    contenido << "Total de productos: " << totalProductos << "\n";
    contenido << "Productos bajo stock mínimo: " << bajoInventario << "\n\n";

    // Productos bajo stock
    contenido << "=== PRODUCTOS BAJO STOCK MÍNIMO ===\n";
    vector<vector<string>> tablaBajoStock;
    tablaBajoStock.push_back({"Código", "Nombre", "Stock Actual", "Stock Mínimo"});

    for (const auto& producto : productos) {
        if (producto.getStock() < producto.getStockMinimo()) {
            tablaBajoStock.push_back({
                producto.getCodigo(),
                producto.getNombre(),
                to_string(producto.getStock()),
                to_string(producto.getStockMinimo())
            });
        }
    }

    if (tablaBajoStock.size() > 1) {
        contenido << generarTabla(tablaBajoStock) << "\n";
    } else {
        contenido << "No hay productos bajo stock mínimo.\n";
    }

    // Distribución por almacén (si hay información de almacenes)
    if (!almacenes.empty()) {
        contenido << "\n=== DISTRIBUCIÓN POR ALMACÉN ===\n";
        for (const auto& almacen : almacenes) {
            contenido << "\nAlmacén: " << almacen.getId() << " - " << almacen.getDireccion() << "\n";
            contenido << "Capacidad: " << almacen.getCapacidad() << " m²\n";
            contenido << "Estado: " << almacen.getEstado() << "\n";
        }
    }

    // Crear el reporte
    DatosReporte nuevo;
    nuevo.id = generarIdUnico(listaReportes);
    nuevo.tipo = "INVENTARIO";
    nuevo.fechaGeneracion = time(nullptr);
    nuevo.contenido = contenido.str();

    listaReportes.push_back(nuevo);
    guardarEnArchivoBin(listaReportes);

    system("cls");
    cout << nuevo.contenido;
    cout << "\n\t\tReporte guardado con ID: " << nuevo.id << endl;

    auditoria.registrar(usuarioRegistrado.getNombre(), "REPORTES", "Reporte inventario - ID: " + nuevo.id);
    system("pause");
}

void Reportes::evaluacionProveedores(const vector<Proveedor>& proveedores,
                                   const vector<Producto>& productos) {
    mostrarProcesando("Evaluando proveedores");

    stringstream contenido;
    contenido << "\t\t=== EVALUACIÓN DE PROVEEDORES ===\n\n";

    // Resumen general
    contenido << "Total de proveedores: " << proveedores.size() << "\n";
    contenido << "Total de productos: " << productos.size() << "\n\n";

    // Listado de proveedores
    contenido << "=== LISTADO DE PROVEEDORES ===\n";
    vector<vector<string>> tablaProveedores;
    tablaProveedores.push_back({"ID", "Nombre", "Teléfono"});

    for (const auto& proveedor : proveedores) {
        tablaProveedores.push_back({
            proveedor.getId(),
            proveedor.getNombre(),
            proveedor.getTelefono()
        });
    }

    contenido << generarTabla(tablaProveedores) << "\n";

    // Crear el reporte
    DatosReporte nuevo;
    nuevo.id = generarIdUnico(listaReportes);
    nuevo.tipo = "EVALUACION_PROVEEDORES";
    nuevo.fechaGeneracion = time(nullptr);
    nuevo.contenido = contenido.str();

    listaReportes.push_back(nuevo);
    guardarEnArchivoBin(listaReportes);

    system("cls");
    cout << nuevo.contenido;
    cout << "\n\t\tReporte guardado con ID: " << nuevo.id << endl;

    auditoria.registrar(usuarioRegistrado.getNombre(), "REPORTES", "Evaluación proveedores - ID: " + nuevo.id);
    system("pause");
}

// Métodos de persistencia
void Reportes::guardarEnArchivoBin(const vector<DatosReporte>& lista) {
    ofstream archivo("reportes.bin", ios::binary | ios::out);
    if (!archivo.is_open()) {
        cerr << "\n\t\tError al abrir archivo de reportes!\n";
        return;
    }

    try {
        // 1. Escribir cantidad de reportes
        size_t cantidad = lista.size();
        archivo.write(reinterpret_cast<const char*>(&cantidad), sizeof(cantidad));

        // 2. Escribir cada reporte
        for (const auto& reporte : lista) {
            // Escribir id (string)
            size_t idSize = reporte.id.size();
            archivo.write(reinterpret_cast<const char*>(&idSize), sizeof(idSize));
            archivo.write(reporte.id.c_str(), idSize);

            // Escribir tipo (string)
            size_t tipoSize = reporte.tipo.size();
            archivo.write(reinterpret_cast<const char*>(&tipoSize), sizeof(tipoSize));
            archivo.write(reporte.tipo.c_str(), tipoSize);

            // Escribir fecha (time_t)
            archivo.write(reinterpret_cast<const char*>(&reporte.fechaGeneracion), sizeof(reporte.fechaGeneracion));

            // Escribir contenido (string)
            size_t contenidoSize = reporte.contenido.size();
            archivo.write(reinterpret_cast<const char*>(&contenidoSize), sizeof(contenidoSize));
            archivo.write(reporte.contenido.c_str(), contenidoSize);
        }

        archivo.close();

        // Comprobar que el archivo se creó correctamente
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
