//LUIS ANGEL MENDEZ FUENTES
//9959-24-6845
#ifndef ENVIOS_H
#define ENVIOS_H

#include <string>
#include <vector>
#include "transportistas.h"

/**
 * @struct Envio
 * @brief Representa un envío realizado a un cliente.
 *
 * Esta estructura contiene los datos necesarios para realizar un envío,
 * como el ID del envío, pedido, transportista y cliente, además del estado del envío.
 */
struct Envio {
    std::string idEnvio;         ///< ID único del envío (formato numérico entre 3500 y 3599) */
    std::string idPedido;        ///< ID del pedido asociado al envío */
    std::string idTransportista; ///< ID del transportista asignado al envío */
    std::string idCliente;       ///< ID del cliente receptor del envío */
    std::string estado;          ///< Estado actual del envío (ej. "En camino", "Entregado") */
};

/**
 * @class Envios
 * @brief Clase que gestiona la creación, almacenamiento y consulta de envíos.
 *
 * Esta clase permite gestionar los envíos dentro del sistema, incluyendo
 * la generación automática de IDs, persistencia en archivos binarios,
 * y selección de transportistas disponibles.
 */
class Envios {
public:

    /**
     * @brief Muestra el menú principal del módulo de gestión de envíos.
     */
    void gestionEnvios();

    /**
     * @brief Crea un nuevo envío solicitando los datos al usuario.
     */
    void crearEnvioInteractivo();

    /**
     * @brief Crea un nuevo envío desde otro módulo (como pedidos).
     * @param idPedido ID del pedido asociado al envío.
     * @param transportistasDisponibles Lista de transportistas disponibles para asignar.
     */
    static void crearEnvio(const std::string& idPedido, const std::vector<Transportistas>& transportistasDisponibles);

    /**
     * @brief Muestra en consola todos los envíos registrados.
     */
    void mostrarEnvios();

    /**
     * @brief Carga todos los envíos desde el archivo binario "envios.dat".
     * @return Vector con todos los envíos cargados.
     */
    static std::vector<Envio> cargarEnviosDesdeArchivo();

    /**
     * @brief Guarda todos los envíos en el archivo binario "envios.dat".
     * @param envios Vector de envíos a guardar.
     */
    static void guardarEnviosEnArchivo(const std::vector<Envio>& envios);

    /**
     * @brief Genera automáticamente un ID único dentro del rango 3500–3599.
     * @return El ID numérico disponible convertido a entero.
     */
    static int generarIdEnvio();

    /**
     * @brief Variante de crearEnvioInteractivo con parámetros, útil para pruebas o llamadas desde otros módulos.
     * @param idPedido ID del pedido asociado.
     * @param listaTransportistas Lista de transportistas disponibles.
     */
    void crearEnvioInteractivo(const std::string& idPedido, const std::vector<Transportistas>& listaTransportistas);

private:
    /**
     * @brief Vector estático que contiene todos los envíos cargados en memoria.
     */
    static std::vector<Envio> envios;
};

#endif // ENVIOS_H
