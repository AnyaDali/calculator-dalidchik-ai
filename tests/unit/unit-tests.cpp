#include <gtest/gtest.h>
#include "../../src/calculator.h"

TEST(Calculator, IsOp) {
    char available_symbols[] = {'-', '+', '*', '/', };
    for (size_t i = 0; i < sizeof(available_symbols) / sizeof(char); ++i) {
        EXPECT_TRUE(is_op(available_symbols[i]));
    }

    char another_symbols[] = {'\0', 'q', '%', '(', };
    for (size_t i = 0; i < sizeof(another_symbols) / sizeof(char); ++i) {
        EXPECT_FALSE(is_op(another_symbols[i]));
    }
}

TEST(Calculator, IsDigit) {
    char numbers[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', };
    for (size_t i = 0; i < sizeof(numbers) / sizeof(char); ++i) {
        EXPECT_TRUE(is_dig(numbers[i]));
    }

    char another_symbols[] = {'\0', 'o', '%', '(', '\n'};
    for (size_t i = 0; i < sizeof(another_symbols) / sizeof(char); ++i) {
        EXPECT_FALSE(is_dig(another_symbols[i]));
    }
}