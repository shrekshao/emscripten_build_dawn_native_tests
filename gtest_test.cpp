#include <gtest/gtest.h>
// #include "out/web/_deps/googletest-src/googletest/include/gtest/gtest.h"  // temp

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
  // EXPECT_EQ(41, 42);
}



// #include <stdio.h>

// int main() {
//   printf("hello, world!\n");
//   return 0;
// }