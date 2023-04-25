// Name: Takeshi Hashimoto
//

/*

g++ -pedantic -Wall -Wextra -std=c++17 unittest_equation.cpp -o unittest_equation

*/

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"


////////////////////////////////////////////////////////////////////////////////
//
// it is terrible programming style to #include an implementation cpp file
//      we are only doing this at the beginning of the course 
//
////////////////////////////////////////////////////////////////////////////////
#include "equation.cpp"


TEST_CASE("two real roots that are integers") {
   double root1, root2;
   CHECK_EQ(getRoots(1, -5, 6, root1, root2), 2);
   if (root1 < root2) {
      CHECK_EQ(root1, 2);
      CHECK_EQ(root2, 3);
   }
   else {
      CHECK_EQ(root2, 2);
      CHECK_EQ(root1, 3);
   }
}
TEST_CASE("special cases: b and c are 0 but not a") {
   double root1, root2;
   CHECK_EQ(getRoots(5, 0, 0, root1, root2), 1);
   CHECK_EQ(root1, doctest::Approx(0));
   CHECK_EQ(root2, doctest::Approx(0));
}
TEST_CASE("one real root, ignoring the value in root2") {
   double root1, root2;
   CHECK_EQ(getRoots(16, 8, 1, root1, root2), 1);
   CHECK_EQ(root1, -0.25);
}

