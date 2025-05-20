// JENNIFER ALBA DAYAMI BARRIOS FLORES 9959-24-10016
// COORD EQUIPO 3
// MAYO 2025
// modificado por // 9959-24-11603 GE
#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <vector>
#include <string>
#include <fstream>  // Para ifstream/ofstream
#include <iostream> // Para cerr
#include "bitacora.h"

class Producto {
private:
    std::string id;
    std::string codigo;
    std::string nombre;
    std::string descripcion;
    double precio;
    int stock;
    int stockMinimo;

public:
    Producto();

    // Getters
    std::string getId() const;
    std::string getCodigo() const;
    std::string getNombre() const;
    std::string getDescripcion() const;
    double getPrecio() const;
    int getStock() const;
    int getStockMinimo() const;

    // Setters
    void setId(const std::string& id);
    void setCodigo(const std::string& codigo);
    void setNombre(const std::string& nombre);
    void setDescripcion(const std::string& descripcion);
    void setPrecio(double precio);
    void setStock(int stock);
    void setStockMinimo(int stockMinimo);

    // Métodos estáticos para gestión de archivos
    static void cargarDesdeArchivoBin(std::vector<Producto>& lista);
    static void guardarEnArchivoBin(const std::vector<Producto>& lista);

    // Métodos estáticos para operaciones
    static std::string generarCodigoUnico(const std::vector<Producto>& lista);
    static bool esCodigoValido(const std::string& codigo);
    static bool codigoDisponible(const std::vector<Producto>& productos, const std::string& codigo);
    static void agregar(std::vector<Producto>& productos, const std::string& usuario);
    static void mostrar(const std::vector<Producto>& productos);
    static void modificar(std::vector<Producto>& productos, const std::string& usuario, const std::string& codigo);
    static void eliminar(std::vector<Producto>& productos, const std::string& usuario, const std::string& codigo);
};

#endif // PRODUCTO_H
