CC=gcc
CFLAGS=-Wall -Wextra -O2
SRC=src/note_app.c
BIN=note_app

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(BIN) ../../notes.db ../../notes.tmp
