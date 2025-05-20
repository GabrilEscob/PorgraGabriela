#ifndef BITACORA_H
#define BITACORA_H
//CREADO POR: JENNIFER BARRIOS MAYO 2025
#include <string>
#include <unordered_map>

struct RegistroBitacora {
    int id_accion;              ///< ID único de la acción basada en el módulo
    int codigo;                 ///< Código del módulo al que pertenece la acción
    char usuario[30];           ///< Nombre del usuario que ejecutó la acción
    char modulo[30];            ///< Nombre del módulo donde se ejecutó la acción
    char descripcion[100];      ///< Descripción de la acción realizada
    char fecha_hora[20];        ///< Fecha y hora en que ocurrió la acción
};

/**
 * @class CodigosBitacora
 * @brief Administra los códigos únicos asignados a cada módulo para identificación en la bitácora.
 *
 * Esta clase permite obtener un ID específico por módulo, útil para clasificar
 * y rastrear acciones dentro del sistema.
 */
class CodigosBitacora {
private:
    static std::unordered_map<std::string, int> rangos;///< Mapa de modulos

public:
    /**
     * @brief Devuelve el código único asociado a un módulo.
     * @param modulo Nombre del módulo (ej. "Clientes", "Pedidos", etc.).
     * @return Código entero asociado al módulo.
     */
    static int getCodigo(const std::string& modulo);
};

/**
 * @class bitacora
 * @brief Clase encargada de registrar y administrar las acciones del sistema en una bitácora binaria.
 *
 * Proporciona funciones para registrar eventos, generar respaldos,
 * realizar búsquedas y mostrar el contenido de la bitácora.
 */
class bitacora {
public:

    /**
     * @brief Registra una acción en la bitácora.
     * @param usuario Nombre del usuario que realizó la acción.
     * @param modulo Nombre del módulo donde ocurrió la acción.
     * @param descripcion Breve descripción de la acción realizada.
     */
    static void registrar(const std::string& usuario, const std::string& modulo, const std::string& descripcion);

    /**
     * @brief Inserta un registro en la bitácora (alias de registrar).
     * @param usuario Nombre del usuario que realizó la acción.
     * @param modulo Nombre del módulo donde ocurrió la acción.
     * @param descripcion Breve descripción de la acción realizada.
     */
    static void insertar(const std::string& usuario, const std::string& modulo, const std::string& descripcion);

    /**
     * @brief Muestra en consola todos los registros almacenados en la bitácora.
     */
    static void mostrarBitacora();

    /**
     * @brief Genera una copia de seguridad del archivo de la bitácora.
     */
    static void generarBackup();

    /**
     * @brief Elimina todos los registros existentes en la bitácora.
     */
    static void reiniciarBitacora();

    /**
     * @brief Permite buscar registros por nombre de usuario.
     */
    static void buscarPorNombreUsuario();

    /**
     * @brief Permite buscar registros por fecha.
     */
    static void buscarPorFecha();

    /**
     * @brief Muestra el menú interactivo de gestión de la bitácora.
     */
    static void menuBitacora();

private:

    /**
     * @brief Obtiene la fecha y hora actual en formato de cadena.
     * @return Fecha y hora actual como string.
     */
    static std::string obtenerFechaActual();

};

#endif // BITACORA_H
