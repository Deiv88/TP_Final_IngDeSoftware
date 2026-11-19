#include "../include/SistemaOrquesta.h"
#include "../include/Excepciones.h"
#include <iostream>
#include <cassert>

void testSistemaCompleto() {
    std::cout << "[Test] Iniciando verificacion automatizada del sistema...\n";

    // Rutas de prueba aisladas
    std::string rutaM = "data/test_musicos.txt";
    std::string rutaD = "data/test_directores.txt";
    std::string rutaT = "data/test_turnos.txt";

    // Limpiamos archivos previos si existian
    std::remove(rutaM.c_str());
    std::remove(rutaD.c_str());
    std::remove(rutaT.c_str());

    SistemaOrquesta sistema(rutaM, rutaD, rutaT);

    // 1. Alta de entidades
    sistema.registrarMusico("Julian Gomez", "Violin", "Avanzado");
    sistema.registrarMusico("Clara Rodriguez", "Violonchelo", "Intermedio");
    sistema.registrarDirector("Maestro Daniel Barenboim", "Cuerdas");
    sistema.registrarDirector("Maestra Marta Argerich", "Direccion General");

    Musico m1 = sistema.buscarMusico(1);
    assert(m1.getNombre() == "Julian Gomez");
    assert(m1.isActivo() == true);

    Director d1 = sistema.buscarDirector(1);
    assert(d1.getNombre() == "Maestro Daniel Barenboim");

    std::cout << " -> Alta y busqueda de entidades: OK\n";

    // 2. Agendar Turno de Audicion
    FechaHora fh1(10, 12, 2026, 15, 30);
    sistema.agendarTurno(1, 1, fh1, "Sala-Virtual-1");

    TurnoAudicion t1 = sistema.buscarTurno(1);
    assert(t1.getIdMusico() == 1);
    assert(t1.getIdDirector() == 1);
    assert(t1.getEstado() == "PROGRAMADA");

    std::cout << " -> Agendado de turno normal: OK\n";

    // 3. Regla de negocio: No duplicar turno para el mismo musico en misma fecha/hora
    bool lanzoExcepcion = false;
    try {
        sistema.agendarTurno(1, 2, fh1, "Sala-Virtual-2"); // Mismo musico, otro director, misma fecha
    } catch (const TurnoOcupadoException& e) {
        lanzoExcepcion = true;
    }
    assert(lanzoExcepcion);
    std::cout << " -> Deteccion de conflicto de horario en musico: OK\n";

    // 4. Regla de negocio: No duplicar turno para el mismo director en misma fecha/hora
    lanzoExcepcion = false;
    try {
        sistema.agendarTurno(2, 1, fh1, "Sala-Virtual-2"); // Otro musico, mismo director, misma fecha
    } catch (const TurnoOcupadoException& e) {
        lanzoExcepcion = true;
    }
    assert(lanzoExcepcion);
    std::cout << " -> Deteccion de conflicto de horario en director: OK\n";

    // 5. Baja Logica y restriccion de turno
    sistema.bajaLogicaMusico(2);
    Musico m2 = sistema.buscarMusico(2);
    assert(m2.isActivo() == false);

    lanzoExcepcion = false;
    try {
        FechaHora fh2(11, 12, 2026, 16, 0);
        sistema.agendarTurno(2, 1, fh2, "Sala-Virtual-2");
    } catch (const ReglaNegocioException& e) {
        lanzoExcepcion = true;
    }
    assert(lanzoExcepcion);
    std::cout << " -> Baja logica y restriccion de asignacion: OK\n";

    // 6. Reprogramar turno
    FechaHora fhNueva(15, 12, 2026, 17, 0);
    sistema.reprogramarTurno(1, fhNueva);
    TurnoAudicion tReprog = sistema.buscarTurno(1);
    assert(tReprog.getEstado() == "REPROGRAMADA");
    assert(tReprog.getFechaHora() == fhNueva);
    std::cout << " -> Reprogramacion de turno: OK\n";

    // 7. Persistencia: creamos una nueva instancia y leemos desde disco
    SistemaOrquesta sistemaRecuperado(rutaM, rutaD, rutaT);
    Musico mRecup = sistemaRecuperado.buscarMusico(1);
    assert(mRecup.getNombre() == "Julian Gomez");
    TurnoAudicion tRecup = sistemaRecuperado.buscarTurno(1);
    assert(tRecup.getFechaHora() == fhNueva);
    assert(tRecup.getEstado() == "REPROGRAMADA");
    std::cout << " -> Persistencia y recuperacion desde archivos: OK\n";

    // Limpieza de archivos de test
    std::remove(rutaM.c_str());
    std::remove(rutaD.c_str());
    std::remove(rutaT.c_str());

    std::cout << "\n>>> TODAS LAS PRUEBAS DE ARQUITECTURA Y NEGOCIO PASARON EXITOSAMENTE <<<\n";
}

int main() {
    testSistemaCompleto();
    return 0;
}
