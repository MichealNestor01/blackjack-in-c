#include "unity.h"
#include "player.h"

static void test_add_2(void)
{
    TEST_ASSERT_EQUAL_INT(6, add_2(3, 3));
}

void run_player_tests(void)
{
    RUN_TEST(test_add_2);
}
