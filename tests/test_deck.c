#include "unity.h"
#include "deck.h"

static void test_init_sorted_deck_single_deck(void)
{
    Deck deck = init_sorted_deck(1);
    TEST_ASSERT_EQUAL_UINT(deck.head, 51);
    TEST_ASSERT_EQUAL_UINT(deck.cards[0], 0);
    TEST_ASSERT_EQUAL_UINT(deck.cards[12], 12);
    TEST_ASSERT_EQUAL_UINT(deck.cards[25], 25);
    TEST_ASSERT_EQUAL_UINT(deck.cards[51], 51);
}

static void test_init_sorted_deck_multiple_decks(void)
{
    Deck deck = init_sorted_deck(3);
    TEST_ASSERT_EQUAL_UINT(deck.head, 155);
    TEST_ASSERT_EQUAL_UINT(deck.cards[0], 0);
    TEST_ASSERT_EQUAL_UINT(deck.cards[51], 51);
    TEST_ASSERT_EQUAL_UINT(deck.cards[52], 0);
    TEST_ASSERT_EQUAL_UINT(deck.cards[104], 0);
    TEST_ASSERT_EQUAL_UINT(deck.cards[155], 51);
}

static void test_init_shuffled_deck(void)
{
    Deck deck = init_sorted_deck(1);
    TEST_ASSERT_EQUAL_UINT(deck.head, 51);

    unsigned int i;
    for (i = 0; i <= deck.head; ++i)
        if (deck.cards[i] != i)
            break;

    TEST_ASSERT_NOT_EQUAL_UINT(deck.cards[i], deck.head);
}

static void test_init_shuffled_multiple_decks(void)
{
    Deck deck = init_sorted_deck(3);
    TEST_ASSERT_EQUAL_UINT(deck.head, 155);

    unsigned int i;
    for (i = 0; i <= deck.head; ++i)
        if (deck.cards[i] != i)
            break;

    TEST_ASSERT_NOT_EQUAL_UINT(deck.cards[i], deck.head);
}

void run_deck_tests(void)
{
    RUN_TEST(test_init_sorted_deck_single_deck);
    RUN_TEST(test_init_sorted_deck_multiple_decks);
    RUN_TEST(test_init_shuffled_deck);
    RUN_TEST(test_init_shuffled_multiple_decks);
}
