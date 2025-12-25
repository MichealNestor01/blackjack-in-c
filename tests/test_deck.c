#include "unity.h"
#include "deck.h"

static void test_add_returns_sum(void)
{
    TEST_ASSERT_EQUAL_INT(5, add(2, 3));
}

void run_deck_tests(void)
{
    RUN_TEST(test_add_returns_sum);
}
