CC = g++
CFLAGS = -g -Wall -lGLU -lglfw -lpthread -lGLEW -lGL -lglut

OBJECTS = Main.o Scene.o Score.o Shape.o Cube.o Board.o Utils.o
TARGET = game

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $^ $(CFLAGS) -o $(TARGET)

Main.o: Main.cpp
	$(CC) $(CFLAGS) -c $< -o $@

Scene.o: Scene.cpp Scene.h
	$(CC) $(CFLAGS) -c $< -o $@

Score.o: Score.cpp Score.h
	$(CC) $(CFLAGS) -c $< -o $@

Shape.o: Shapes/Shape.cpp Shapes/Shape.h
	$(CC) $(CFLAGS) -c $< -o $@

Cube.o: Shapes/Cube.cpp Shapes/Cube.h
	$(CC) $(CFLAGS) -c $< -o $@

Board.o: Shapes/Board.cpp Shapes/Board.h
	$(CC) $(CFLAGS) -c $< -o $@

Utils.o: Utils/Utils.cpp Utils/Utils.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)
	rm -f *.txt 

debug: $(TARGET)
	gdb $(TARGET)

.PHONY: all clean debug
