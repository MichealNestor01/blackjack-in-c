CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -g

SRC_DIR = src
TEST_DIR = tests
UNITY_DIR = third_party/unity

TARGET = blackjack
TEST_TARGET = test_runner


SRC = $(SRC_DIR)/blackjack.c $(SRC_DIR)/deck.c $(SRC_DIR)/player.c
TEST_SRC = $(TEST_DIR)/test_main.c $(TEST_DIR)/test_deck.c $(TEST_DIR)/test_player.c
OBJ = $(SRC:.c=.o)
TEST_OBJS = src/deck.c src/player.c third_party/unity/unity.c

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -I$(SRC_DIR) -c $< -o $@

$(TEST_TARGET): $(TEST_SRC) $(TEST_OBJS)
	$(CC) $(CFLAGS) -I$(SRC_DIR) -I$(UNITY_DIR) $^ -o $@

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -f $(OBJ) $(TARGET) $(TEST_TARGET)
