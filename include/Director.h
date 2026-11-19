#ifndef DIRECTOR_H
#define DIRECTOR_H

#include <iostream>
#include <string>

/**
 * @brief Entidad principal 2: Director / Evaluador de seccion.
 */
class Director {
private:
    int id;
    std::string nombre;
    std::string especialidad;

public:
    Director();
    Director(int id, const std::string& nombre, const std::string& especialidad);
    ~Director();

    int getId() const { return id; }
    std::string getNombre() const { return nombre; }
    std::string getEspecialidad() const { return especialidad; }

    void setNombre(const std::string& nuevoNombre) { nombre = nuevoNombre; }
    void setEspecialidad(const std::string& nuevaEspecialidad) { especialidad = nuevaEspecialidad; }

    // Sobrecarga de operador
    bool operator==(const Director& otro) const;

    // Persistencia
    std::string toLineaArchivo() const;
    static Director fromLineaArchivo(const std::string& linea);

    // Funcion friend justificada
    friend std::ostream& operator<<(std::ostream& os, const Director& d);
};

#endif // DIRECTOR_H
