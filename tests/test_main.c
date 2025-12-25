#include "unity.h"

void run_deck_tests(void);
void run_player_tests(void);
void run_shuffle_tests(void);

void setUp(void)
{
}

void tearDown(void)
{
}

int main(void)
{
    UNITY_BEGIN();

    run_deck_tests();
    run_player_tests();
    run_shuffle_tests();

    return UNITY_END();
}
