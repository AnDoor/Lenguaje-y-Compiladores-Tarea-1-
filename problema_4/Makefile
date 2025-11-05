CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = ejecutable
SRC = translator.c

all: $(TARGET) translator

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $<

translator: translator.c
	$(CC) $(CFLAGS) -O2 -o $@ translator.c

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) translator
