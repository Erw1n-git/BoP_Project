CC = g++
CFLAGS = -g -Wall -lGLU -lglfw -lGLEW -lGL -lglut

TARGET = 2048

all: $(TARGET)

$(TARGET): Game2048.o
	$(CC) $(CFLAGS) $^ -o $(TARGET)

main.o: Game2048.cpp Game2048.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)

debug: $(TARGET)
	gdb $(TARGET)

.PHONY: all clean debug
