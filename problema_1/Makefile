CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = ejecutable
SRC = main.c fen.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
