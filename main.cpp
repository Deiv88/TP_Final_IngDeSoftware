#include "include/SistemaOrquesta.h"
#include "include/InputHelper.h"
#include "include/Excepciones.h"
#include <iostream>

void subMenuMusicos(SistemaOrquesta& sistema) {
    int opcion = -1;
    while (opcion != 0) {
        InputHelper::limpiarPantalla();
        std::cout << "============================================\n"
                  << "        GESTION DE MUSICOS / ASPIRANTES     \n"
                  << "============================================\n"
                  << "1. Registrar Musico\n"
                  << "2. Baja Logica de Musico\n"
                  << "3. Reactivar Musico\n"
                  << "4. Modificar Musico\n"
                  << "5. Buscar Musico por ID\n"
                  << "6. Listar Musicos (Todos)\n"
                  << "7. Listar Musicos (Solo Activos)\n"
                  << "0. Volver al Menu Principal\n"
                  << "--------------------------------------------\n";
        opcion = InputHelper::leerEntero("Seleccione una opcion: ", 0, 7);

        if (opcion != 0) {
            InputHelper::limpiarPantalla();
        }

        try {
            switch (opcion) {
                case 1: {
                    std::cout << "--- Registrar Nuevo Musico ---\n\n";
                    std::string nombre = InputHelper::leerTextoNoVacio("Nombre y Apellido: ");
                    std::string instrumento = InputHelper::leerTextoNoVacio("Instrumento: ");
                    std::string nivel = InputHelper::leerTextoNoVacio("Nivel (Inicial/Intermedio/Avanzado): ");
                    sistema.registrarMusico(nombre, instrumento, nivel);
                    std::cout << "\n[Exito] Musico registrado correctamente en el sistema.\n";
                    break;
                }
                case 2: {
                    std::cout << "--- Baja Logica de Musico ---\n\n";
                    int id = InputHelper::leerEntero("Ingrese ID de Musico a dar de baja: ");
                    sistema.bajaLogicaMusico(id);
                    std::cout << "\n[Exito] Baja logica procesada con exito.\n";
                    break;
                }
                case 3: {
                    std::cout << "--- Reactivar Musico ---\n\n";
                    int id = InputHelper::leerEntero("Ingrese ID de Musico a reactivar: ");
                    sistema.reactivarMusico(id);
                    std::cout << "\n[Exito] Musico reactivado con exito.\n";
                    break;
                }
                case 4: {
                    std::cout << "--- Modificar Musico ---\n\n";
                    int id = InputHelper::leerEntero("Ingrese ID de Musico a modificar: ");
                    Musico actual = sistema.buscarMusico(id);
                    std::cout << "\nDatos actuales:\n" << actual << "\n\n";
                    std::string nombre = InputHelper::leerTextoNoVacio("Nuevo Nombre y Apellido: ");
                    std::string instrumento = InputHelper::leerTextoNoVacio("Nuevo Instrumento: ");
                    std::string nivel = InputHelper::leerTextoNoVacio("Nuevo Nivel: ");
                    sistema.modificarMusico(id, nombre, instrumento, nivel);
                    std::cout << "\n[Exito] Musico modificado correctamente.\n";
                    break;
                }
                case 5: {
                    std::cout << "--- Buscar Musico por ID ---\n\n";
                    int id = InputHelper::leerEntero("Ingrese ID de Musico: ");
                    Musico m = sistema.buscarMusico(id);
                    std::cout << "\nResultado:\n" << m << "\n";
                    break;
                }
                case 6:
                    std::cout << "--- Listado Completo de Musicos ---\n\n";
                    sistema.listarMusicos(false);
                    break;
                case 7:
                    std::cout << "--- Listado de Musicos Activos ---\n\n";
                    sistema.listarMusicos(true);
                    break;
            }
        } catch (const ExcepcionOrquesta& e) {
            std::cout << "\n[Error de Sistema] " << e.what() << "\n";
        } catch (const std::exception& e) {
            std::cout << "\n[Error Inesperado] " << e.what() << "\n";
        }

        if (opcion != 0) {
            InputHelper::pausar();
        }
    }
}

void subMenuDirectores(SistemaOrquesta& sistema) {
    int opcion = -1;
    while (opcion != 0) {
        InputHelper::limpiarPantalla();
        std::cout << "============================================\n"
                  << "   GESTION DE DIRECTORES / EVALUADORES      \n"
                  << "============================================\n"
                  << "1. Registrar Director\n"
                  << "2. Eliminar Director\n"
                  << "3. Modificar Director\n"
                  << "4. Buscar Director por ID\n"
                  << "5. Listar Directores\n"
                  << "0. Volver al Menu Principal\n"
                  << "--------------------------------------------\n";
        opcion = InputHelper::leerEntero("Seleccione una opcion: ", 0, 5);

        if (opcion != 0) {
            InputHelper::limpiarPantalla();
        }

        try {
            switch (opcion) {
                case 1: {
                    std::cout << "--- Registrar Nuevo Director ---\n\n";
                    std::string nombre = InputHelper::leerTextoNoVacio("Nombre y Apellido: ");
                    std::string especialidad = InputHelper::leerTextoNoVacio("Especialidad/Catedra: ");
                    sistema.registrarDirector(nombre, especialidad);
                    std::cout << "\n[Exito] Director registrado correctamente.\n";
                    break;
                }
                case 2: {
                    std::cout << "--- Eliminar Director ---\n\n";
                    int id = InputHelper::leerEntero("Ingrese ID de Director a eliminar: ");
                    sistema.bajaDirector(id);
                    std::cout << "\n[Exito] Director eliminado del sistema.\n";
                    break;
                }
                case 3: {
                    std::cout << "--- Modificar Director ---\n\n";
                    int id = InputHelper::leerEntero("Ingrese ID de Director a modificar: ");
                    Director actual = sistema.buscarDirector(id);
                    std::cout << "\nDatos actuales:\n" << actual << "\n\n";
                    std::string nombre = InputHelper::leerTextoNoVacio("Nuevo Nombre y Apellido: ");
                    std::string especialidad = InputHelper::leerTextoNoVacio("Nueva Especialidad/Catedra: ");
                    sistema.modificarDirector(id, nombre, especialidad);
                    std::cout << "\n[Exito] Director modificado correctamente.\n";
                    break;
                }
                case 4: {
                    std::cout << "--- Buscar Director por ID ---\n\n";
                    int id = InputHelper::leerEntero("Ingrese ID de Director: ");
                    Director d = sistema.buscarDirector(id);
                    std::cout << "\nResultado:\n" << d << "\n";
                    break;
                }
                case 5:
                    std::cout << "--- Listado de Directores / Evaluadores ---\n\n";
                    sistema.listarDirectores();
                    break;
            }
        } catch (const ExcepcionOrquesta& e) {
            std::cout << "\n[Error de Sistema] " << e.what() << "\n";
        } catch (const std::exception& e) {
            std::cout << "\n[Error Inesperado] " << e.what() << "\n";
        }

        if (opcion != 0) {
            InputHelper::pausar();
        }
    }
}

void subMenuTurnos(SistemaOrquesta& sistema) {
    int opcion = -1;
    while (opcion != 0) {
        InputHelper::limpiarPantalla();
        std::cout << "============================================\n"
                  << "        GESTION DE TURNOS DE AUDICION       \n"
                  << "============================================\n"
                  << "1. Agendar Nuevo Turno de Audicion\n"
                  << "2. Cancelar Turno\n"
                  << "3. Reprogramar Turno\n"
                  << "4. Buscar Turno por ID\n"
                  << "5. Listar Todos los Turnos\n"
                  << "6. Listar Turnos por Musico\n"
                  << "7. Listar Turnos por Director\n"
                  << "0. Volver al Menu Principal\n"
                  << "--------------------------------------------\n";
        opcion = InputHelper::leerEntero("Seleccione una opcion: ", 0, 7);

        if (opcion != 0) {
            InputHelper::limpiarPantalla();
        }

        try {
            switch (opcion) {
                case 1: {
                    std::cout << "--- Agendar Turno de Audicion ---\n\n";
                    int idMusico = InputHelper::leerEntero("ID del Musico: ");
                    int idDirector = InputHelper::leerEntero("ID del Director/Evaluador: ");
                    FechaHora fecha = InputHelper::leerFechaHora();
                    std::string sala = InputHelper::leerTextoNoVacio("Nombre de Sala Virtual (ej. Sala-Violines-1): ");
                    sistema.agendarTurno(idMusico, idDirector, fecha, sala);
                    std::cout << "\n[Exito] Turno de audicion agendado correctamente.\n";
                    break;
                }
                case 2: {
                    std::cout << "--- Cancelar Turno de Audicion ---\n\n";
                    int id = InputHelper::leerEntero("Ingrese ID del Turno a cancelar: ");
                    sistema.cancelarTurno(id);
                    std::cout << "\n[Exito] Turno cancelado correctamente.\n";
                    break;
                }
                case 3: {
                    std::cout << "--- Reprogramar Turno de Audicion ---\n\n";
                    int id = InputHelper::leerEntero("Ingrese ID del Turno a reprogramar: ");
                    TurnoAudicion actual = sistema.buscarTurno(id);
                    std::cout << "\nTurno actual:\n" << actual << "\n\n";
                    std::cout << "Ingrese la nueva fecha y horario:\n";
                    FechaHora nuevaFecha = InputHelper::leerFechaHora();
                    sistema.reprogramarTurno(id, nuevaFecha);
                    std::cout << "\n[Exito] Turno reprogramado correctamente.\n";
                    break;
                }
                case 4: {
                    std::cout << "--- Buscar Turno por ID ---\n\n";
                    int id = InputHelper::leerEntero("Ingrese ID del Turno: ");
                    TurnoAudicion t = sistema.buscarTurno(id);
                    std::cout << "\nResultado:\n" << t << "\n";
                    break;
                }
                case 5:
                    std::cout << "--- Listado de Todos los Turnos ---\n\n";
                    sistema.listarTurnos();
                    break;
                case 6: {
                    std::cout << "--- Listar Turnos por Musico ---\n\n";
                    int idMusico = InputHelper::leerEntero("ID del Musico: ");
                    sistema.listarTurnosPorMusico(idMusico);
                    break;
                }
                case 7: {
                    std::cout << "--- Listar Turnos por Director ---\n\n";
                    int idDirector = InputHelper::leerEntero("ID del Director: ");
                    sistema.listarTurnosPorDirector(idDirector);
                    break;
                }
            }
        } catch (const ExcepcionOrquesta& e) {
            std::cout << "\n[Error de Sistema] " << e.what() << "\n";
        } catch (const std::exception& e) {
            std::cout << "\n[Error Inesperado] " << e.what() << "\n";
        }

        if (opcion != 0) {
            InputHelper::pausar();
        }
    }
}

int main() {
    SistemaOrquesta sistema;
    int opcionPrincipal = -1;

    while (opcionPrincipal != 0) {
        InputHelper::limpiarPantalla();
        std::cout << "============================================\n"
                  << "    SISTEMA DE TURNOS - ORQUESTA VIRTUAL    \n"
                  << "          Ingenieria de Software I          \n"
                  << "============================================\n"
                  << "1. Administracion de Musicos\n"
                  << "2. Administracion de Directores / Evaluadores\n"
                  << "3. Administracion de Turnos y Audiciones\n"
                  << "0. Salir\n"
                  << "--------------------------------------------\n";
        opcionPrincipal = InputHelper::leerEntero("Seleccione una opcion: ", 0, 3);

        switch (opcionPrincipal) {
            case 1:
                subMenuMusicos(sistema);
                break;
            case 2:
                subMenuDirectores(sistema);
                break;
            case 3:
                subMenuTurnos(sistema);
                break;
            case 0:
                InputHelper::limpiarPantalla();
                std::cout << "============================================\n";
                std::cout << " Guardando estado y saliendo del sistema... \n";
                std::cout << "============================================\n";
                break;
        }
    }

    return 0;
}
