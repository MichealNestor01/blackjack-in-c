#include "unity.h"
#include "deck.h"

static void test_init_sorted_deck_single_deck(void)
{
    Deck deck = init_sorted_deck(1);
    TEST_ASSERT_EQUAL_UINT16(deck.head, 51);
    TEST_ASSERT_EQUAL_UINT16(deck.cards[0], 0);
    TEST_ASSERT_EQUAL_UINT16(deck.cards[12], 12);
    TEST_ASSERT_EQUAL_UINT16(deck.cards[25], 25);
    TEST_ASSERT_EQUAL_UINT16(deck.cards[51], 51);
}

static void test_init_sorted_deck_multiple_decks(void)
{
    Deck deck = init_sorted_deck(3);
    TEST_ASSERT_EQUAL_UINT16(deck.head, 155);
    TEST_ASSERT_EQUAL_UINT16(deck.cards[0], 0);
    TEST_ASSERT_EQUAL_UINT16(deck.cards[51], 51);
    TEST_ASSERT_EQUAL_UINT16(deck.cards[52], 0);
    TEST_ASSERT_EQUAL_UINT16(deck.cards[104], 0);
    TEST_ASSERT_EQUAL_UINT16(deck.cards[155], 51);
}

static void test_init_shuffled_deck(void)
{
    Deck deck = init_sorted_deck(1);
    TEST_ASSERT_EQUAL_UINT16(deck.head, 51);

    unsigned short i;
    for (i = 0; i <= deck.head; ++i)
        if (deck.cards[i] != i)
            break;

    TEST_ASSERT_NOT_EQUAL_UINT(deck.cards[i], deck.head);
}

static void test_init_shuffled_multiple_decks(void)
{
    Deck deck = init_sorted_deck(3);
    TEST_ASSERT_EQUAL_UINT16(deck.head, 155);

    unsigned short i;
    for (i = 0; i <= deck.head; ++i)
        if (deck.cards[i] != i)
            break;

    TEST_ASSERT_NOT_EQUAL_UINT(deck.cards[i], deck.head);
}

static void test_pop_card(void)
{
    Deck deck = init_sorted_deck(2);
    unsigned short kd = pop_card(&deck);
    TEST_ASSERT_EQUAL_UINT16(102, deck.head);
    TEST_ASSERT_EQUAL_UINT16(51, kd);
}

static void test_card_string_repr_all_cards(void)
{
    char actual[4];
    char expected[4];

    const char *suits[] = {"S", "H", "C", "D"};
    const char *ranks[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

    for (unsigned short i = 0; i < 52; ++i)
    {
        card_string_repr(i, actual);
        snprintf(expected, 4, "%s%s", ranks[i % 13], suits[i / 13]);
        TEST_ASSERT_EQUAL_STRING(actual, expected);
    }
}

static void test_card_string_repr_specific_cards(void)
{
    char AS[4] = "AS\0";
    char KD[4] = "KD\0";
    char AH[4] = "AH\0";
    char buff[4];

    card_string_repr(0, buff);
    TEST_ASSERT_EQUAL_STRING(buff, AS);
    card_string_repr(51, buff);
    TEST_ASSERT_EQUAL_STRING(buff, KD);
    card_string_repr(13, buff);
    TEST_ASSERT_EQUAL_STRING(buff, AH);
}

void run_deck_tests(void)
{
    RUN_TEST(test_init_sorted_deck_single_deck);
    RUN_TEST(test_init_sorted_deck_multiple_decks);
    RUN_TEST(test_init_shuffled_deck);
    RUN_TEST(test_init_shuffled_multiple_decks);
    RUN_TEST(test_pop_card);
    RUN_TEST(test_card_string_repr_all_cards);
    RUN_TEST(test_card_string_repr_specific_cards);
}
