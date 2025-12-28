#include "unity.h"
#include "player.h"

static void test_score_hand_single_card(void)
{
    Player player = {0, 0, 0, {}};
    // number cards
    for (int i = 1; i < 10; ++i)
    {
        player.hand[0] = i;
        score_hand(&player);
        TEST_ASSERT_EQUAL_UINT16(i + 1, player.hand_score);
        return;
    }
    // test face cards
    for (int i = 10; i < 13; ++i)
    {
        player.hand[0] = i;
        score_hand(&player);
        TEST_ASSERT_EQUAL_UINT16(10, player.hand_score);
    }
    // test non spades card (and high ace)
    player.hand[0] = 13;
    score_hand(&player);
    TEST_ASSERT_EQUAL_UINT16(11, player.hand_score);
}

static void test_score_hand_set_hands(void)
{
    // test high ace
    Player player = {0, 0, 1, {10, 0}};
    score_hand(&player);
    TEST_ASSERT_EQUAL_UINT16(21, player.hand_score);
    // test low ace and high ace together
    player.hand_head = 2;
    player.hand[0] = 0; // high ace - 11
    player.hand[1] = 0; // low ace - 1
    player.hand[2] = 1; //  2 - 2
    score_hand(&player);
    TEST_ASSERT_EQUAL_UINT16(14, player.hand_score);
}

static void test_init_player(void)
{
    Player player = init_player();
    TEST_ASSERT_EQUAL_UINT16(0, player.score);
    TEST_ASSERT_EQUAL_UINT16(0, player.hand_score);
    TEST_ASSERT_EQUAL_INT16(-1, player.hand_head);
}

static void test_add_to_hand(void)
{
    Player player = init_player();
    add_to_hand(&player, 0);
    TEST_ASSERT_EQUAL_UINT16(0, player.score);
    TEST_ASSERT_EQUAL_UINT16(11, player.hand_score);
    TEST_ASSERT_EQUAL_INT16(0, player.hand_head);
}

void run_player_tests(void)
{
    RUN_TEST(test_score_hand_single_card);
    RUN_TEST(test_score_hand_set_hands);
    RUN_TEST(test_init_player);
    RUN_TEST(test_add_to_hand);
}
