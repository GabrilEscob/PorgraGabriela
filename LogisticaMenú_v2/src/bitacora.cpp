//LUIS ANGEL MENDEZ FUENTES
//9959-24-6845
#include "bitacora.h"
//LUIS ANGEL MENDEZ FUENTES
//9959-24-6845
#include "bitacora.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <unordered_map>
#include <chrono>
#include <cstring>
#include <set>
#include <cstring>

using namespace std;

/**
 * Mapa estático que almacena los rangos de códigos por módulo.
 * Utilizado para asignar códigos únicos a cada registro.
 */
std::unordered_map<std::string, int> CodigosBitacora::rangos = {
    {"AUTENTICACION", 3000}, {"USUARIOS", 3050}, {"PEDIDOS", 3100},
    {"CLIENTES", 3150}, {"PROVEEDORES", 3200}, {"PRODUCTOS", 3250},
    {"ALMACENES", 3300}, {"TRANSPORTISTAS", 3350}, {"FACTURACION", 3400},
    {"REPORTES", 3450}, {"INVENTARIO", 3500}, {"ENVIOS", 3550},
    {"SISTEMA", 3600}
};

/**
 * Obtiene el código actual para un módulo y lo incrementa para el próximo uso.
 * Si el módulo no existe en el mapa, se inicializa en 3000.
 * @param modulo Nombre del módulo.
 * @return Código actual asignado para el módulo.
 */
int CodigosBitacora::getCodigo(const std::string& modulo) {
    if (rangos.find(modulo) == rangos.end()) {
        rangos[modulo] = 3000;  // O puedes asignar otro rango por defecto
    }
    return rangos[modulo]++;
}

/**
 * Registra un nuevo evento en la bitácora.
 * Escribe la información en el archivo binario bitacora.bin.
 * @param usuario Nombre del usuario que realizó la acción.
 * @param modulo Módulo del sistema donde ocurrió el evento.
 * @param descripcion Breve explicación de lo que ocurrió.
 */
void bitacora::registrar(const std::string& usuario, const std::string& modulo, const std::string& descripcion) {
    std::ofstream file("bitacora.bin", std::ios::binary | std::ios::app);
    if (!file) {
        std::cerr << "No se pudo abrir bitacora.bin\n";
        return;
    }

    RegistroBitacora r;
    r.codigo = CodigosBitacora::getCodigo(modulo);
    strncpy(r.usuario, usuario.c_str(), sizeof(r.usuario));
    r.usuario[sizeof(r.usuario) - 1] = '\0';

    strncpy(r.modulo, modulo.c_str(), sizeof(r.modulo));
    r.modulo[sizeof(r.modulo) - 1] = '\0';

    strncpy(r.descripcion, descripcion.c_str(), sizeof(r.descripcion));
    r.descripcion[sizeof(r.descripcion) - 1] = '\0';

    std::time_t now = std::time(nullptr);
    std::strftime(r.fecha_hora, sizeof(r.fecha_hora), "%d/%m/%Y %H:%M:%S", std::localtime(&now));

    file.write(reinterpret_cast<char*>(&r), sizeof(RegistroBitacora));
    file.close();
}

/**
 * Obtiene la fecha actual del sistema en formato DD/MM/AAAA.
 * @return Fecha como cadena de texto.
 */
std::string bitacora::obtenerFechaActual() {
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&time);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%d/%m/%Y");
    return oss.str();
}

/**
 * Muestra todos los registros de la bitácora almacenados en el archivo binario.
 * Presenta los datos en formato tabular por consola.
 */

 void bitacora::insertar(const std::string& usuario, const std::string& modulo, const std::string& descripcion) {
    registrar(usuario, modulo, descripcion);
}

void bitacora::mostrarBitacora() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    std::ifstream file("bitacora.bin", std::ios::binary);

    if (!file) {
        std::cout << "\n\t\t\tNo hay registros en la bitacora.\n";
        return;
    }

    RegistroBitacora r;

    std::cout << "\n----------------------------- REPORTE DE BITACORA -----------------------------\n";
    std::cout << std::left << std::setw(10) << "ID"
              << std::setw(15) << "USUARIO"
              << std::setw(15) << "MODULO"
              << std::setw(35) << "DESCRIPCION"
              << std::setw(20) << "FECHA" << "\n";
    std::cout << "-------------------------------------------------------------------------------\n";

    while (file.read(reinterpret_cast<char*>(&r), sizeof(RegistroBitacora))) {
        std::cout << std::left << std::setw(10) << r.codigo
                  << std::setw(15) << r.usuario
                  << std::setw(15) << r.modulo
                  << std::setw(35) << r.descripcion
                  << std::setw(20) << r.fecha_hora << "\n";
    }

    std::cout << "-------------------------------------------------------------------------------\n";

    file.close();
    system("pause");
}

/**
 * Genera una copia de seguridad de la bitácora actual.
 * El archivo generado se nombra automáticamente con fecha y hora.
 */
void bitacora::generarBackup() {
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&time);

    std::ostringstream oss;
    oss << "backup_bitacora_" << std::put_time(&tm, "%Y%m%d_%H%M%S") << ".bin";

    std::ifstream src("bitacora.bin", std::ios::binary);
    std::ofstream dst(oss.str(), std::ios::binary);

    if (src && dst) {
        dst << src.rdbuf();
        registrar("SISTEMA", "SISTEMA", "Backup generado: " + oss.str());
        std::cout << "\n\t\tBackup generado exitosamente: " << oss.str() << "\n";
    } else {
        std::cerr << "\n\t\tError al generar backup!\n";
    }

    system("pause");
}

/**
 * Elimina todos los registros de la bitácora, dejando el archivo binario vacío.
 * Esta operación no se puede deshacer.
 */
void bitacora::reiniciarBitacora() {
    std::ofstream file("bitacora.bin", std::ios::binary | std::ios::trunc);
    if (file.is_open()) {
        file.close();
        std::cout << "Bitacora reiniciada con éxito.\n";
    } else {
        std::cout << "Error al reiniciar la bitacora.\n";
    }
    system("pause");
}

/**
 * Busca y muestra todos los registros asociados a un nombre de usuario específico.
 * Presenta primero una lista de usuarios únicos para ayudar al usuario a elegir.
 */
void bitacora::buscarPorNombreUsuario() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    std::ifstream file("bitacora.bin", std::ios::binary);
    if (!file) {
        std::cout << "\t\tNo se pudo abrir la bitácora.\n";
        return;
    }

    // Paso 1: Mostrar todos los nombres de usuario únicos
    std::set<std::string> usuariosUnicos;
    RegistroBitacora temp;

    while (file.read(reinterpret_cast<char*>(&temp), sizeof(RegistroBitacora))) {
        usuariosUnicos.insert(temp.usuario);
    }

    file.clear();  // Limpia banderas de EOF
    file.seekg(0); // Regresa al inicio para nueva lectura

    std::cout << "\n\t\tUSUARIOS DISPONIBLES EN LA BITACORA:\n";
    std::cout << "\t\t-------------------------------------\n";
    for (const auto& nombre : usuariosUnicos) {
        std::cout << "\t\t" << nombre << "\n";
    }

    std::string usuarioBuscar;
    std::cout << "\n\t\tIngrese el nombre del usuario a buscar exactamente como aparece (0 para salir): ";
    std::cin >> usuarioBuscar;

    if (usuarioBuscar == "0") {
        // Salir si el usuario ingresa 0
        file.close();
        return;
    }

    // Paso 2: Buscar registros por usuario
    RegistroBitacora r;
    bool encontrado = false;
    std::cout << "\n\t\tRegistros encontrados:\n";
    std::cout << "\t\t-------------------------------------------------------------\n";
    std::cout << std::left << std::setw(10) << "ID"
              << std::setw(15) << "MODULO"
              << std::setw(35) << "DESCRIPCION"
              << std::setw(20) << "FECHA" << "\n";
    std::cout << "\t\t-------------------------------------------------------------\n";

    while (file.read(reinterpret_cast<char*>(&r), sizeof(RegistroBitacora))) {
        if (usuarioBuscar == r.usuario) {
            std::cout << std::left << std::setw(10) << r.codigo
                      << std::setw(15) << r.modulo
                      << std::setw(35) << r.descripcion
                      << std::setw(20) << r.fecha_hora << "\n";
            encontrado = true;
        }
    }

    if (!encontrado) {
        std::cout << "\n\t\tNo se encontraron registros para ese usuario.\n";
    }

    file.close();
    system("pause");
}

/**
 * Busca y muestra todos los registros asociados a una fecha específica.
 * La búsqueda se hace por coincidencia exacta con el formato "DD/MM/AAAA".
 */
void bitacora::buscarPorFecha() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    std::string fechaBuscar;
    std::cout << "\n\t\tIngrese la fecha a buscar (formato DD/MM/AAAA) (0 para salir): ";
    std::cin >> fechaBuscar;

    if (fechaBuscar == "0") {
        // Salir si el usuario ingresa 0
        return;
    }

    std::ifstream file("bitacora.bin", std::ios::binary);
    if (!file) {
        std::cout << "\t\tNo se pudo abrir la bitacora.\n";
        return;
    }

    RegistroBitacora r;
    bool encontrado = false;
    std::cout << "\n\t\tRegistros encontrados:\n";
    while (file.read(reinterpret_cast<char*>(&r), sizeof(RegistroBitacora))) {
        if (std::string(r.fecha_hora).substr(0, 10) == fechaBuscar) {
            std::cout << "\t\t" << r.codigo << " | " << r.usuario << " | " << r.modulo << " | " << r.descripcion << " | " << r.fecha_hora << "\n";
            encontrado = true;
        }
    }

    if (!encontrado) {
        std::cout << "\t\tNo se encontraron registros para esa fecha.\n";
    }

    file.close();
    system("pause");
}

/**
 * Busca y muestra todos los registros asociados a una fecha específica.
 * La búsqueda se hace por coincidencia exacta con el formato "DD/MM/AAAA".
 */
void bitacora::menuBitacora() {
    int opcion = 0;
    do {
        system("cls");
        cout << "\n--------------------------------------------------------------------------------\n";
        cout << "                          SISTEMA DE BITACORA DEL SISTEMA                       \n";
        cout << "--------------------------------------------------------------------------------\n";
        cout << "   [1] Mostrar bitacora completa\n";
        cout << "   [2] Buscar por nombre de usuario\n";
        cout << "   [3] Buscar por fecha\n";
        cout << "   [4] Generar respaldo de la bitacora\n";
        cout << "   [5] Reiniciar bitacora\n";
        cout << "   [6] Volver al menu principal\n";
        cout << "--------------------------------------------------------------------------------\n";
        cout << "                     Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                mostrarBitacora();
                break;
            case 2:
                buscarPorNombreUsuario();
                break;
            case 3:
                buscarPorFecha();
                break;
            case 4:
                generarBackup();
                break;
            case 5:
                reiniciarBitacora();
                break;
            case 6:
                cout << "\n\tSaliendo al menu principal...\n";
                break;
            default:
                cout << "\n\tOpcion invalida.\n";
                system("pause");
                break;
        }
    } while (opcion != 6);
}
