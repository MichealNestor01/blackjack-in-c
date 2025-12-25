#include "unity.h"
#include "shuffle.h"

static void test_shuffle_uint_array(void)
{
    unsigned int max = 100000;
    unsigned int *arr = malloc(max * sizeof(unsigned int));
    for (unsigned int i = 0; i < max; ++i)
        arr[i] = i;
    shuffle_uint_array(arr, max);
    // check for a number in the wrong place, and that min and max val are present.
    // very very unlikely that this test fails because the shuffle randomly orders the array
    unsigned int includes_min = 0;
    unsigned int includes_max = 0;
    unsigned int inorder = 1;
    for (unsigned int i = 0; i < max; ++i)
    {
        if (arr[i] == 0)
            includes_min = 1;
        else if (arr[i] == max - 1)
            includes_max = 1;
        if (inorder && arr[i] != i)
            inorder = 0;
    }
    TEST_ASSERT_EQUAL_UINT(includes_min, 1);
    TEST_ASSERT_EQUAL_UINT(includes_max, 1);
    TEST_ASSERT_EQUAL_UINT(inorder, 0);
}

void run_shuffle_tests(void)
{
    RUN_TEST(test_shuffle_uint_array);
}
