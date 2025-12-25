CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -g
TARGET  = blackjack

SRC     = src/blackjack.c
OBJ     = $(SRC:.c=.o)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)