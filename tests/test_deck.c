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

void run_deck_tests(void)
{
    RUN_TEST(test_init_sorted_deck_single_deck);
    RUN_TEST(test_init_sorted_deck_multiple_decks);
}
