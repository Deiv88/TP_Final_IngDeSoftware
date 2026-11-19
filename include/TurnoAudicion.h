#ifndef TURNOAUDICION_H
#define TURNOAUDICION_H

#include "FechaHora.h"
#include <iostream>
#include <string>

/**
 * @brief Clase asociativa / Relacion: Turno de Audicion.
 * Vincula a un Musico con un Director en una FechaHora especifica.
 */
class TurnoAudicion {
private:
    int id;
    int idMusico;
    int idDirector;
    FechaHora fechaHora;
    std::string salaVirtual;
    std::string estado; // "PROGRAMADA", "CANCELADA", "REPROGRAMADA", "FINALIZADA"

public:
    TurnoAudicion();
    TurnoAudicion(int id, int idMusico, int idDirector, const FechaHora& fechaHora, 
                  const std::string& salaVirtual = "Sala-A", const std::string& estado = "PROGRAMADA");
    ~TurnoAudicion();

    int getId() const { return id; }
    int getIdMusico() const { return idMusico; }
    int getIdDirector() const { return idDirector; }
    FechaHora getFechaHora() const { return fechaHora; }
    std::string getSalaVirtual() const { return salaVirtual; }
    std::string getEstado() const { return estado; }

    void setFechaHora(const FechaHora& nuevaFecha) { fechaHora = nuevaFecha; }
    void setSalaVirtual(const std::string& nuevaSala) { salaVirtual = nuevaSala; }
    void setEstado(const std::string& nuevoEstado) { estado = nuevoEstado; }

    void cancelar();
    void reprogramar(const FechaHora& nuevaFecha);
    void finalizar();

    // Sobrecarga de operador
    bool operator==(const TurnoAudicion& otro) const;

    // Persistencia
    std::string toLineaArchivo() const;
    static TurnoAudicion fromLineaArchivo(const std::string& linea);

    // Funcion friend justificada
    friend std::ostream& operator<<(std::ostream& os, const TurnoAudicion& t);
};

#endif // TURNOAUDICION_H
