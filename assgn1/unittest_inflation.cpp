// Name: Takeshi Hashimoto

/*

g++ -pedantic -Wall -Wextra  -std=c++17 unittest_inflation.cpp -o unittest_inflation

*/

// the function inflation has some precondition
// so don't pass as arguments to inflation values that would violate 
// the precondition(s) of inflation

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

////////////////////////////////////////////////////////////////////////////////
//
// it is terrible programming style to #include an implementation cpp file
//      we are only doing this at the beginning of the course 
//
////////////////////////////////////////////////////////////////////////////////
#include "inflation.cpp"

TEST_CASE("inflation that is a whole number") {
   CHECK(inflation(25, 30) == 20);
}

TEST_CASE("exact inflation that is double the number") {
   CHECK(inflation(77, 154) == 100);
}

TEST_CASE("special case no inflation") {
   CHECK(inflation(9412.451253, 9412.451253) == 0);
}

// https://thekrazycouponlady.com/tips/money/starbucks-prices
// Starbucks coffee
TEST_CASE("inflation that is not exact") {
   CHECK(inflation(2.45, 2.95) == 20.41);
}

TEST_CASE("exact inflation that is triple the number") {
   CHECK(inflation(8.76, 26.28) == 200);
}

TEST_CASE("deflation that returns negative inflation percentage") {
   CHECK(inflation(50, 40) == -20);
}

TEST_CASE("the item became priceles ($0) meaning inflation rate is -100%") {
   CHECK(inflation(42.429, 0) == -100);
}

TEST_CASE("return big double values") {
   CHECK(inflation(8.5328742, 944.429842) == 10968.13);
}



