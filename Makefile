CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -O2

BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = include

SOURCES = $(SRC_DIR)/main.c $(SRC_DIR)/game.c $(SRC_DIR)/territory.c
OBJECTS = $(BUILD_DIR)/main.o $(BUILD_DIR)/game.o $(BUILD_DIR)/territory.o
EXECUTABLE = $(BUILD_DIR)/war-game

.PHONY: build run test valgrind clean help

build: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) | $(BUILD_DIR)
	$(CC) $(OBJECTS) -o $@

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -I$(INCLUDE_DIR) $< -o $@

$(BUILD_DIR)/game.o: $(SRC_DIR)/game.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -I$(INCLUDE_DIR) $< -o $@

$(BUILD_DIR)/territory.o: $(SRC_DIR)/territory.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -I$(INCLUDE_DIR) $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

run: build
	./$(EXECUTABLE)

test: build
	echo "Testes: A implementar"

valgrind: build
	valgrind --leak-check=full ./$(EXECUTABLE)

clean:
	rm -rf $(BUILD_DIR)

help:
	echo "make build   - Compilar"
	echo "make run     - Compilar e executar"
	echo "make valgrind- Testar memória"
	echo "make clean   - Limpar artifacts"
