CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -O2

BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = include

SOURCES = $(SRC_DIR)/main.c $(SRC_DIR)/game.c $(SRC_DIR)/territory.c $(SRC_DIR)/mission.c $(SRC_DIR)/game_engine.c
OBJECTS = $(BUILD_DIR)/main.o $(BUILD_DIR)/game.o $(BUILD_DIR)/territory.o $(BUILD_DIR)/mission.o $(BUILD_DIR)/game_engine.o
EXECUTABLE = $(BUILD_DIR)/war-game

TEST_SRC = $(SRC_DIR)/test_game.c
TEST_OBJ = $(BUILD_DIR)/test_game.o
TEST_OBJECTS = $(TEST_OBJ) $(BUILD_DIR)/game.o $(BUILD_DIR)/territory.o $(BUILD_DIR)/mission.o $(BUILD_DIR)/game_engine.o
TEST_EXEC = $(BUILD_DIR)/test-war-game

.PHONY: build run test valgrind clean help

build: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -I$(INCLUDE_DIR) $< -o $@

$(BUILD_DIR)/game.o: $(SRC_DIR)/game.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -I$(INCLUDE_DIR) $< -o $@

$(BUILD_DIR)/territory.o: $(SRC_DIR)/territory.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -I$(INCLUDE_DIR) $< -o $@

$(BUILD_DIR)/mission.o: $(SRC_DIR)/mission.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -I$(INCLUDE_DIR) $< -o $@

$(BUILD_DIR)/game_engine.o: $(SRC_DIR)/game_engine.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -I$(INCLUDE_DIR) $< -o $@

$(BUILD_DIR)/test_game.o: $(SRC_DIR)/test_game.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -I$(INCLUDE_DIR) $< -o $@

$(TEST_EXEC): $(TEST_OBJECTS)
	$(CC) $(TEST_OBJECTS) -o $@

run: build
	./$(EXECUTABLE)

test: $(TEST_EXEC)
	./$(TEST_EXEC)

valgrind: build
	valgrind --leak-check=full ./$(EXECUTABLE)

clean:
	rm -rf $(BUILD_DIR)

help:
	@echo "make build   - Compilar"
	@echo "make run     - Compilar e executar"
	@echo "make test    - Compilar e executar testes"
	@echo "make valgrind- Testar memoria"
	@echo "make clean   - Limpar artifacts"
