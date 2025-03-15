CC=gcc
LIB_FLAGS=-lm

BIN_FOLDER=bin

MAIN_NAME=geometric_n_arithmetic_mean
MAIN_BIN=$(MAIN_NAME)
MAIN_SRC=$(MAIN_NAME).c

$(BIN_FOLDER)/$(MAIN_BIN): $(MAIN_SRC)
	mkdir -p $(BIN_FOLDER)
	$(CC) $^ -o $@ $(LIB_FLAGS)

clean:
	rm -rf $(BIN_FOLDER)
