#include "../include/SistemaOrquesta.h"
#include "../include/GestorArchivos.h"
#include "../include/Excepciones.h"
#include <iostream>

SistemaOrquesta::SistemaOrquesta(const std::string& rutaM,
                                 const std::string& rutaD,
                                 const std::string& rutaT)
    : rutaMusicos(rutaM), rutaDirectores(rutaD), rutaTurnos(rutaT),
      proximoIdMusico(1), proximoIdDirector(1), proximoIdTurno(1) {
    cargarDatos();
}

SistemaOrquesta::~SistemaOrquesta() {
    guardarDatos();
}

void SistemaOrquesta::actualizarProximosIds() {
    int maxM = 0;
    for (int i = 0; i < musicos.getTamanio(); ++i) {
        if (musicos[i].getId() > maxM) maxM = musicos[i].getId();
    }
    proximoIdMusico = maxM + 1;

    int maxD = 0;
    for (int i = 0; i < directores.getTamanio(); ++i) {
        if (directores[i].getId() > maxD) maxD = directores[i].getId();
    }
    proximoIdDirector = maxD + 1;

    int maxT = 0;
    for (int i = 0; i < turnos.getTamanio(); ++i) {
        if (turnos[i].getId() > maxT) maxT = turnos[i].getId();
    }
    proximoIdTurno = maxT + 1;
}

void SistemaOrquesta::cargarDatos() {
    GestorArchivos<Musico>::cargar(rutaMusicos, musicos);
    GestorArchivos<Director>::cargar(rutaDirectores, directores);
    GestorArchivos<TurnoAudicion>::cargar(rutaTurnos, turnos);
    actualizarProximosIds();
}

void SistemaOrquesta::guardarDatos() {
    GestorArchivos<Musico>::guardar(rutaMusicos, musicos);
    GestorArchivos<Director>::guardar(rutaDirectores, directores);
    GestorArchivos<TurnoAudicion>::guardar(rutaTurnos, turnos);
}

int SistemaOrquesta::obtenerIndiceMusico(int id) const {
    for (int i = 0; i < musicos.getTamanio(); ++i) {
        if (musicos[i].getId() == id) return i;
    }
    return -1;
}

int SistemaOrquesta::obtenerIndiceDirector(int id) const {
    for (int i = 0; i < directores.getTamanio(); ++i) {
        if (directores[i].getId() == id) return i;
    }
    return -1;
}

int SistemaOrquesta::obtenerIndiceTurno(int id) const {
    for (int i = 0; i < turnos.getTamanio(); ++i) {
        if (turnos[i].getId() == id) return i;
    }
    return -1;
}

// ==================== ABML MÚSICOS ====================

void SistemaOrquesta::registrarMusico(const std::string& nombre, const std::string& instrumento, const std::string& nivel) {
    Musico nuevo(proximoIdMusico++, nombre, instrumento, nivel, true);
    musicos.agregar(nuevo);
    guardarDatos();
}

void SistemaOrquesta::bajaLogicaMusico(int id) {
    int idx = obtenerIndiceMusico(id);
    if (idx == -1) {
        throw EntidadNoEncontradaException("No existe musico con ID " + std::to_string(id));
    }
    musicos[idx].darDeBaja();
    guardarDatos();
}

void SistemaOrquesta::reactivarMusico(int id) {
    int idx = obtenerIndiceMusico(id);
    if (idx == -1) {
        throw EntidadNoEncontradaException("No existe musico con ID " + std::to_string(id));
    }
    musicos[idx].reactivar();
    guardarDatos();
}

void SistemaOrquesta::modificarMusico(int id, const std::string& nuevoNombre, const std::string& nuevoInst, const std::string& nuevoNivel) {
    int idx = obtenerIndiceMusico(id);
    if (idx == -1) {
        throw EntidadNoEncontradaException("No existe musico con ID " + std::to_string(id));
    }
    musicos[idx].setNombre(nuevoNombre);
    musicos[idx].setInstrumento(nuevoInst);
    musicos[idx].setNivel(nuevoNivel);
    guardarDatos();
}

Musico SistemaOrquesta::buscarMusico(int id) const {
    int idx = obtenerIndiceMusico(id);
    if (idx == -1) {
        throw EntidadNoEncontradaException("No existe musico con ID " + std::to_string(id));
    }
    return musicos[idx];
}

void SistemaOrquesta::listarMusicos(bool soloActivos) const {
    if (musicos.estaVacia()) {
        std::cout << "No hay musicos registrados en el sistema.\n";
        return;
    }
    int listados = 0;
    for (int i = 0; i < musicos.getTamanio(); ++i) {
        if (!soloActivos || musicos[i].isActivo()) {
            std::cout << musicos[i] << "\n";
            listados++;
        }
    }
    if (listados == 0) {
        std::cout << "No se encontraron musicos con el criterio solicitado.\n";
    }
}

// ==================== ABML DIRECTORES ====================

void SistemaOrquesta::registrarDirector(const std::string& nombre, const std::string& especialidad) {
    Director nuevo(proximoIdDirector++, nombre, especialidad);
    directores.agregar(nuevo);
    guardarDatos();
}

void SistemaOrquesta::bajaDirector(int id) {
    int idx = obtenerIndiceDirector(id);
    if (idx == -1) {
        throw EntidadNoEncontradaException("No existe director con ID " + std::to_string(id));
    }
    // Verificamos si tiene turnos activos asociados
    for (int i = 0; i < turnos.getTamanio(); ++i) {
        if (turnos[i].getIdDirector() == id && turnos[i].getEstado() == "PROGRAMADA") {
            throw ReglaNegocioException("No se puede eliminar el director: tiene turnos activos pendientes.");
        }
    }
    directores.eliminar(idx);
    guardarDatos();
}

void SistemaOrquesta::modificarDirector(int id, const std::string& nuevoNombre, const std::string& nuevaEsp) {
    int idx = obtenerIndiceDirector(id);
    if (idx == -1) {
        throw EntidadNoEncontradaException("No existe director con ID " + std::to_string(id));
    }
    directores[idx].setNombre(nuevoNombre);
    directores[idx].setEspecialidad(nuevaEsp);
    guardarDatos();
}

Director SistemaOrquesta::buscarDirector(int id) const {
    int idx = obtenerIndiceDirector(id);
    if (idx == -1) {
        throw EntidadNoEncontradaException("No existe director con ID " + std::to_string(id));
    }
    return directores[idx];
}

void SistemaOrquesta::listarDirectores() const {
    if (directores.estaVacia()) {
        std::cout << "No hay directores registrados en el sistema.\n";
        return;
    }
    for (int i = 0; i < directores.getTamanio(); ++i) {
        std::cout << directores[i] << "\n";
    }
}

// ==================== TURNOS Y REGLAS DE NEGOCIO ====================

void SistemaOrquesta::agendarTurno(int idMusico, int idDirector, const FechaHora& fechaHora, const std::string& sala) {
    // 1. Verificacion de existencia y estado del Musico
    int idxM = obtenerIndiceMusico(idMusico);
    if (idxM == -1) {
        throw EntidadNoEncontradaException("El musico ID " + std::to_string(idMusico) + " no existe.");
    }
    if (!musicos[idxM].isActivo()) {
        throw ReglaNegocioException("El musico tiene baja logica. No puede agendar audiciones.");
    }

    // 2. Verificacion de existencia del Director
    int idxD = obtenerIndiceDirector(idDirector);
    if (idxD == -1) {
        throw EntidadNoEncontradaException("El director ID " + std::to_string(idDirector) + " no existe.");
    }

    // 3. Reglas de colision de horarios
    for (int i = 0; i < turnos.getTamanio(); ++i) {
        const TurnoAudicion& t = turnos[i];
        if (t.getEstado() != "CANCELADA") {
            if (t.getIdMusico() == idMusico && t.getFechaHora() == fechaHora) {
                throw TurnoOcupadoException("El musico ya tiene una audicion programada en esa fecha y hora.");
            }
            if (t.getIdDirector() == idDirector && t.getFechaHora() == fechaHora) {
                throw TurnoOcupadoException("El director ya tiene una audicion asignada en esa fecha y hora.");
            }
        }
    }

    TurnoAudicion nuevo(proximoIdTurno++, idMusico, idDirector, fechaHora, sala, "PROGRAMADA");
    turnos.agregar(nuevo);
    guardarDatos();
}

void SistemaOrquesta::cancelarTurno(int idTurno) {
    int idx = obtenerIndiceTurno(idTurno);
    if (idx == -1) {
        throw EntidadNoEncontradaException("No existe turno con ID " + std::to_string(idTurno));
    }
    if (turnos[idx].getEstado() == "CANCELADA") {
        throw ReglaNegocioException("El turno ya se encuentra cancelado.");
    }
    turnos[idx].cancelar();
    guardarDatos();
}

void SistemaOrquesta::reprogramarTurno(int idTurno, const FechaHora& nuevaFecha) {
    int idx = obtenerIndiceTurno(idTurno);
    if (idx == -1) {
        throw EntidadNoEncontradaException("No existe turno con ID " + std::to_string(idTurno));
    }
    if (turnos[idx].getEstado() == "CANCELADA") {
        throw ReglaNegocioException("No se puede reprogramar un turno cancelado. Agende un nuevo turno.");
    }

    int idM = turnos[idx].getIdMusico();
    int idD = turnos[idx].getIdDirector();

    for (int i = 0; i < turnos.getTamanio(); ++i) {
        if (i == idx) continue;
        const TurnoAudicion& t = turnos[i];
        if (t.getEstado() != "CANCELADA") {
            if (t.getIdMusico() == idM && t.getFechaHora() == nuevaFecha) {
                throw TurnoOcupadoException("El musico ya tiene una audicion asignada en el nuevo horario solicitado.");
            }
            if (t.getIdDirector() == idD && t.getFechaHora() == nuevaFecha) {
                throw TurnoOcupadoException("El director ya tiene una audicion asignada en el nuevo horario solicitado.");
            }
        }
    }

    turnos[idx].reprogramar(nuevaFecha);
    guardarDatos();
}

TurnoAudicion SistemaOrquesta::buscarTurno(int idTurno) const {
    int idx = obtenerIndiceTurno(idTurno);
    if (idx == -1) {
        throw EntidadNoEncontradaException("No existe turno con ID " + std::to_string(idTurno));
    }
    return turnos[idx];
}

void SistemaOrquesta::listarTurnos() const {
    if (turnos.estaVacia()) {
        std::cout << "No hay turnos registrados en el sistema.\n";
        return;
    }
    for (int i = 0; i < turnos.getTamanio(); ++i) {
        std::cout << turnos[i] << "\n";
    }
}

void SistemaOrquesta::listarTurnosPorMusico(int idMusico) const {
    int encontrados = 0;
    for (int i = 0; i < turnos.getTamanio(); ++i) {
        if (turnos[i].getIdMusico() == idMusico) {
            std::cout << turnos[i] << "\n";
            encontrados++;
        }
    }
    if (encontrados == 0) {
        std::cout << "No se encontraron turnos para el musico con ID " << idMusico << ".\n";
    }
}

void SistemaOrquesta::listarTurnosPorDirector(int idDirector) const {
    int encontrados = 0;
    for (int i = 0; i < turnos.getTamanio(); ++i) {
        if (turnos[i].getIdDirector() == idDirector) {
            std::cout << turnos[i] << "\n";
            encontrados++;
        }
    }
    if (encontrados == 0) {
        std::cout << "No se encontraron turnos para el director con ID " << idDirector << ".\n";
    }
}
