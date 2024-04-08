#include <gtest/gtest.h>

int add(int a, int b) {
    return a + b;
}

TEST(AdditionTest, PositiveNumbers) {
    EXPECT_EQ(add(2, 3), 5);
}

TEST(AdditionTest, NegativeNumbers) {
    EXPECT_EQ(add(-2, -3), -5);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
