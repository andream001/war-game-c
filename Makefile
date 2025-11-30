# Professional Makefile for war-game-c
# Usage: make build | run | test | valgrind | clean | help

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2 -g
SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build
BIN = war-game

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
TEST_SRCS := $(wildcard $(TEST_DIR)/*.c)
TEST_BIN := $(BUILD_DIR)/test_runner

.PHONY: all build run test valgrind clean help

all: build

# Default build target: compile sources and link binary
build: $(BUILD_DIR)/$(BIN)

$(BUILD_DIR)/$(BIN): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@
	@echo "Built $@"

# Compile each source into object in build directory
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
	@printf "Compiled %-40s -> %s\n" "$<" "$@"

# Run the game (build first)
run: build
	@echo "Running $(BUILD_DIR)/$(BIN)..."
	./$(BUILD_DIR)/$(BIN)

# Build and run tests
test: CFLAGS += -I$(TEST_DIR)
test: $(TEST_BIN)
	@echo "Running tests..."
	./$(TEST_BIN)

$(TEST_BIN): $(TEST_SRCS) $(SRCS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(TEST_SRCS) $(SRCS) -o $(TEST_BIN)
	@echo "Built test runner: $(TEST_BIN)"

# Run valgrind for memory leak detection
valgrind: build
	@echo "Starting valgrind on $(BUILD_DIR)/$(BIN)..."
	valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=1 ./$(BUILD_DIR)/$(BIN)

# Clean build artifacts
clean:
	@echo "Cleaning build artifacts..."
	@rm -rf $(BUILD_DIR)
	@echo "Clean complete."

# Help target
help:
	@echo "Makefile targets:"
	@echo " - make build      - compile the project into $(BUILD_DIR)/$(BIN)"
	@echo " - make run        - build and run the game"
	@echo " - make test       - build and run tests"
	@echo " - make valgrind   - run under valgrind for memory checks"
	@echo " - make clean      - remove build artifacts"
	@echo " - make help       - show this help message"
