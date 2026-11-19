CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude
TARGET = sistema_orquesta.exe
SRCS = src/FechaHora.cpp src/Musico.cpp src/Director.cpp src/TurnoAudicion.cpp src/InputHelper.cpp src/SistemaOrquesta.cpp main.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)
