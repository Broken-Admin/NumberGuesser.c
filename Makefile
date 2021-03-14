CC := gcc
LDFLAGS := -lm
.PHONY: all clean

all: NumberGuesser.elf

clean:
	rm NumberGuesser.elf

NumberGuesser.elf: main.c
	$(CC) -o $@ $^ $(LDFLAGS)