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
    // test low ace and high ace together
    player.hand_head = 2;
    player.hand[0] = 13; // AH - 11
    player.hand[1] = 14; // 2H - 2
    player.hand[2] = 15; // 3H - 3
    score_hand(&player);
    TEST_ASSERT_EQUAL_UINT16(16, player.hand_score);
}

static void test_score_hand_ace_tests(void)
{
    // test low ace
    Player player = {0, 0, 3, {10, 0, 0, 0}};
    score_hand(&player);
    TEST_ASSERT_EQUAL_UINT16(13, player.hand_score);
    // test low ace and high ace together
    player.hand_head = 2;
    player.hand[0] = 0; // high ace - 11
    player.hand[1] = 0; // low ace - 1
    player.hand[2] = 8; //  8 - 9
    score_hand(&player);
    TEST_ASSERT_EQUAL_UINT16(21, player.hand_score);
}

static void test_init_player(void)
{
    Player player = init_player();
    TEST_ASSERT_EQUAL_INT16(0, player.score);
    TEST_ASSERT_EQUAL_UINT16(0, player.hand_score);
    TEST_ASSERT_EQUAL_INT16(-1, player.hand_head);
}

static void test_add_to_hand(void)
{
    Player player = init_player();
    add_to_hand(&player, 0);
    TEST_ASSERT_EQUAL_INT16(0, player.score);
    TEST_ASSERT_EQUAL_UINT16(11, player.hand_score);
    TEST_ASSERT_EQUAL_INT16(0, player.hand_head);
}

static void test_score_player_double_blackjack(void)
{
    Player player = init_player();
    Player dealer = init_player();
    add_to_hand(&player, 10); // Jack
    add_to_hand(&player, 0);  // Ace
    add_to_hand(&dealer, 10); // Jack
    add_to_hand(&dealer, 0);  // Ace
    score_player(&player, &dealer);
    TEST_ASSERT_EQUAL_INT16(0, player.score);
}

static void test_score_player_dealer_blackjack(void)
{
    Player player = init_player();
    Player dealer = init_player();
    add_to_hand(&player, 10); // Jack
    add_to_hand(&player, 0);  // Ace
    score_player(&player, &dealer);
    TEST_ASSERT_EQUAL_INT16(1, player.score);
}

static void test_score_player_player_blackjack(void)
{
    Player player = init_player();
    Player dealer = init_player();
    add_to_hand(&dealer, 10); // Jack
    add_to_hand(&dealer, 0);  // Ace
    score_player(&player, &dealer);
    TEST_ASSERT_EQUAL_INT16(-1, player.score);
}

static void test_score_player_player_bust(void)
{
    Player player = init_player();
    Player dealer = init_player();
    add_to_hand(&dealer, 10); // Jack
    add_to_hand(&dealer, 10); // Jack
    add_to_hand(&dealer, 1);  // 2
    score_player(&player, &dealer);
    TEST_ASSERT_EQUAL_INT16(-1, player.score);
}

static void test_score_player_player_wins(void)
{
    Player player = init_player();
    Player dealer = init_player();
    add_to_hand(&player, 10); // Jack
    add_to_hand(&player, 10); // Jack
    add_to_hand(&dealer, 10); // Jack
    score_player(&player, &dealer);
    TEST_ASSERT_EQUAL_INT16(1, player.score);
}

static void test_score_player_dealer_wins(void)
{
    Player player = init_player();
    Player dealer = init_player();
    add_to_hand(&player, 10); // Jack
    add_to_hand(&player, 10); // Jack
    add_to_hand(&dealer, 10); // Jack
    add_to_hand(&dealer, 10); // Jack
    add_to_hand(&dealer, 0);  // Ace
    score_player(&player, &dealer);
    TEST_ASSERT_EQUAL_INT16(-1, player.score);
}

static void test_score_player_player_wins_twice(void)
{
    Player player = init_player();
    Player dealer = init_player();
    add_to_hand(&player, 10); // Jack
    add_to_hand(&player, 10); // Jack
    add_to_hand(&dealer, 10); // Jack
    score_player(&player, &dealer);
    add_to_hand(&player, 10); // Jack
    add_to_hand(&player, 10); // Jack
    score_player(&player, &dealer);
    TEST_ASSERT_EQUAL_INT16(2, player.score);
}

void run_player_tests(void)
{
    RUN_TEST(test_score_hand_single_card);
    RUN_TEST(test_score_hand_set_hands);
    RUN_TEST(test_score_hand_ace_tests);
    RUN_TEST(test_init_player);
    RUN_TEST(test_add_to_hand);
    RUN_TEST(test_score_player_dealer_blackjack);
    RUN_TEST(test_score_player_player_blackjack);
    RUN_TEST(test_score_player_double_blackjack);
    RUN_TEST(test_score_player_player_bust);
    RUN_TEST(test_score_player_player_wins);
    RUN_TEST(test_score_player_dealer_wins);
    RUN_TEST(test_score_player_player_wins_twice);
}
