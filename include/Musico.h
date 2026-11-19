#ifndef MUSICO_H
#define MUSICO_H

#include <iostream>
#include <string>

/**
 * @brief Entidad principal 1: Musico / Aspirante de la orquesta virtual.
 * Posee baja logica (activo/inactivo), sobrecarga de operador y funcion friend.
 */
class Musico {
private:
    int id;
    std::string nombre;
    std::string instrumento;
    std::string nivel;
    bool activo;

public:
    Musico();
    Musico(int id, const std::string& nombre, const std::string& instrumento, const std::string& nivel, bool activo = true);
    ~Musico();

    int getId() const { return id; }
    std::string getNombre() const { return nombre; }
    std::string getInstrumento() const { return instrumento; }
    std::string getNivel() const { return nivel; }
    bool isActivo() const { return activo; }

    void setNombre(const std::string& nuevoNombre) { nombre = nuevoNombre; }
    void setInstrumento(const std::string& nuevoInstrumento) { instrumento = nuevoInstrumento; }
    void setNivel(const std::string& nuevoNivel) { nivel = nuevoNivel; }
    void setActivo(bool estado) { activo = estado; }

    void darDeBaja() { activo = false; }
    void reactivar() { activo = true; }

    // Sobrecarga de operador de igualdad (compara por ID)
    bool operator==(const Musico& otro) const;

    // Serializacion sencilla para archivo
    std::string toLineaArchivo() const;
    static Musico fromLineaArchivo(const std::string& linea);

    // Funcion friend justificada: impresion directa y controlada de la entidad
    friend std::ostream& operator<<(std::ostream& os, const Musico& m);
};

#endif // MUSICO_H
