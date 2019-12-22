// Copyright 2018 Your Name <your_email>

#include <gtest/gtest.h>

TEST(Example, EmptyTest) {
	int*a = new int;
    a[0] = 42;
    int*b = new int;
    b[0] = 20;
	
    SharedPtr<int> link1(a);
	SharedPtr<int> link2(link1);
	SharedPtr<int> link3(b);
	
    EXPECT_EQ(static_cast<int>(link1.get()[0]), 42);
    EXPECT_EQ(static_cast<int>(link2.get()[0]), 42);
    link1.swap(link3);
    EXPECT_EQ(static_cast<int>(link1.get()[0]), 20);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}