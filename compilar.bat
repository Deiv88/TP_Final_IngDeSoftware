@echo off
echo Compilando Sistema de Turnos de la Orquesta Virtual...
g++ -std=c++17 -Wall -Wextra -Iinclude src/FechaHora.cpp src/Musico.cpp src/Director.cpp src/TurnoAudicion.cpp src/InputHelper.cpp src/SistemaOrquesta.cpp main.cpp -o sistema_orquesta.exe
if %ERRORLEVEL% EQU 0 (
    echo.
    echo Compilacion exitosa. Ejecutable generado: sistema_orquesta.exe
) else (
    echo.
    echo Error durante la compilacion.
)
pause
