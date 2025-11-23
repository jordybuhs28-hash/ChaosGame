CXX = g++
CXXFLAGS = -std=c++17 -I"C:/Users/jordy/OneDrive/SFML-2.4.0-built/include"
LDFLAGS = -L"C:/Users/jordy/OneDrive/SFML-2.4.0-built/lib" -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SRC = main.cpp
TARGET = ChaosGame.exe

$(TARGET): $(SRC)
	$(CXX) $(SRC) -o $(TARGET) $(CXXFLAGS) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)
