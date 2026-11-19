#ifndef SISTEMAORQUESTA_H
#define SISTEMAORQUESTA_H

#include "Lista.h"
#include "Musico.h"
#include "Director.h"
#include "TurnoAudicion.h"
#include <string>

/**
 * @brief Controlador central del dominio.
 * Gestiona colecciones en memoria, orquesta la persistencia y aplica
 * de forma estricta las reglas de negocio y validaciones.
 */
class SistemaOrquesta {
private:
    Lista<Musico> musicos;
    Lista<Director> directores;
    Lista<TurnoAudicion> turnos;

    std::string rutaMusicos;
    std::string rutaDirectores;
    std::string rutaTurnos;

    int proximoIdMusico;
    int proximoIdDirector;
    int proximoIdTurno;

    void actualizarProximosIds();
    int obtenerIndiceMusico(int id) const;
    int obtenerIndiceDirector(int id) const;
    int obtenerIndiceTurno(int id) const;

public:
    SistemaOrquesta(const std::string& rutaM = "data/musicos.txt",
                    const std::string& rutaD = "data/directores.txt",
                    const std::string& rutaT = "data/turnos.txt");
    ~SistemaOrquesta();

    // Persistencia
    void cargarDatos();
    void guardarDatos();

    // ABML Musicos
    void registrarMusico(const std::string& nombre, const std::string& instrumento, const std::string& nivel);
    void bajaLogicaMusico(int id);
    void reactivarMusico(int id);
    void modificarMusico(int id, const std::string& nuevoNombre, const std::string& nuevoInst, const std::string& nuevoNivel);
    Musico buscarMusico(int id) const;
    void listarMusicos(bool soloActivos = false) const;

    // ABML Directores
    void registrarDirector(const std::string& nombre, const std::string& especialidad);
    void bajaDirector(int id);
    void modificarDirector(int id, const std::string& nuevoNombre, const std::string& nuevaEsp);
    Director buscarDirector(int id) const;
    void listarDirectores() const;

    // Gestion de Turnos y Reglas de Negocio
    void agendarTurno(int idMusico, int idDirector, const FechaHora& fechaHora, const std::string& sala);
    void cancelarTurno(int idTurno);
    void reprogramarTurno(int idTurno, const FechaHora& nuevaFecha);
    TurnoAudicion buscarTurno(int idTurno) const;
    void listarTurnos() const;
    void listarTurnosPorMusico(int idMusico) const;
    void listarTurnosPorDirector(int idDirector) const;
};

#endif // SISTEMAORQUESTA_H
