// Name:
// Student Number:
// Test the class Cash started by G. Monagan, with doctest
// CPSC 1160, Do not post anywhere

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <iostream>
#include <sstream>  // std::stringstream
#include <string>   // std::string
using std::stringstream, std::string;

#include "Cash.h"

TEST_CASE("constructors depend on == and the operator << ") {
   SUBCASE("no-arg constructor") {
      Cash m = Cash(); 
      stringstream ss;
      ss << m;
      CHECK(ss.str() == "$0.00");
   }
   SUBCASE("positive dollars, positive cents") {
      Cash m(7, 83);
      stringstream ss;
      ss << m;
      CHECK(ss.str() == "$7.83");
   }
   SUBCASE("0  dollars, negative cents") {
      Cash m(0, -32);
      stringstream ss;
      ss << m;
      CHECK(ss.str() == "-$0.32");
   }
   SUBCASE("0  dollars, positive cents") {
      Cash m(0, 99);
      stringstream ss;
      ss << m;
      CHECK(ss.str() == "$0.99");
   }
   SUBCASE("negative dollars, negative cents") {
      Cash m{-10, -21};
      stringstream ss;
      ss << m;
      CHECK(ss.str() == "-$10.21");
   }
   SUBCASE("negative dollars, positive cents") {
      Cash m{-10, 25};
      stringstream ss;
      ss << m;
      CHECK(ss.str() == "-$9.75");
   }
   SUBCASE("positive dollars, negative cents") {
      Cash m{8, -13};
      stringstream ss;
      ss << m;
      CHECK(ss.str() == "$7.87");
   }
   SUBCASE("negative dollars, positive cents") {
      Cash m(-2, 92); 
      stringstream ss;
      ss << m;
      CHECK(ss.str() == "-$1.08");
   }
   SUBCASE("one arg constructor, positive dollars") {
      Cash m(5);
      stringstream ss;
      ss << m;
      CHECK(ss.str() == "$5.00");
   }
   SUBCASE("one arg constructor, negative dollars") {
      Cash m(-12);
      stringstream ss;
      ss << m;
      CHECK(ss.str() == "-$12.00");
   }
}

TEST_CASE("output operator") {
   SUBCASE("only dollars") {
      Cash m(7);
      stringstream ss;
      ss << m;
      CHECK(ss.str() == "$7.00");
   }
   SUBCASE("positive dollars and positive cents") {
      Cash m(345, 67);
      stringstream ss;
      ss << m;
      CHECK(ss.str() == "$345.67");
   }
   SUBCASE("negative cents") {
      Cash m(0, -32);
      stringstream ss;
      ss << m;
      CHECK(ss.str() == "-$0.32");
   }
   SUBCASE("negative dollars and negative cents") {
      Cash m(-31, -32);
      stringstream ss;
      ss << m;
      CHECK(ss.str() == "-$31.32");
   }
   SUBCASE("negative dollars and negative cents") {
      Cash m(-10, -21);
      stringstream ss;
      ss << m;
      CHECK(ss.str() == "-$10.21");
   }
   SUBCASE("negative dollars and positive cents") {
      Cash m(-10, 25);
      stringstream ss;
      ss << m;
      CHECK(ss.str() == "-$9.75");
   }
}

TEST_CASE("input operator") {
   SUBCASE("positive dollars positive cents") {
      Cash m;
      stringstream ss_in("0 77");
      ss_in >> m;
      stringstream ss_out;
      ss_out << m;
      CHECK(ss_out.str() == "$0.77");
   }
   SUBCASE("negative dollars positive cents") {
      Cash m;
      stringstream ss_in("-56 21");
      ss_in >> m;
      stringstream ss_out;
      ss_out << m;
      CHECK(ss_out.str() == "-$55.79");
   }
   SUBCASE("negative dollars negative cents") {
      Cash m;
      stringstream ss_in("-17 -89");
      ss_in >> m;
      stringstream ss_out;
      ss_out << m;
      CHECK(ss_out.str() == "-$17.89");
   }
   SUBCASE("positive dollars negative cents") {
      Cash m;
      stringstream ss_in("43 -26");
      ss_in >> m;
      stringstream ss_out;
      ss_out << m;
      CHECK(ss_out.str() == "$42.74");
   }
}

TEST_CASE("equals operator") {
   SUBCASE("special case") {
      Cash x;
      Cash y;
      CHECK( x == y );
   }
   SUBCASE("special case different constructor") {
      Cash x;
      Cash y(0, 0);
      CHECK( x == y );
   }
   SUBCASE("different sign dollars fail") {
      Cash x(-8, -25);
      Cash y(8, -25);
      CHECK_FALSE( x == y );
   }
   SUBCASE("different sign cents fail") {
      Cash x(-3, -25);
      Cash y(3, -25);
      CHECK_FALSE( x == y );
   }
   SUBCASE("different signs fail") {
      Cash x(-3, -25);
      Cash y(3, -25);
      CHECK_FALSE( x == y );
   }
   SUBCASE("different constructor but same value") {
      Cash x(3);
      Cash y(3, 0);
      CHECK( x == y );
   }
}

TEST_CASE("constants depends on equals") {
   CHECK(LOONIE == Cash(1, 0));
   CHECK(LOONIE == Cash(1));
   CHECK(TOONIE == Cash(2));
   CHECK(TOONIE == Cash(2, 0));
   CHECK(QUARTER == Cash(0, 25));
   CHECK(DIME == Cash(0, 10));
   CHECK(NICKEL == Cash(0, 5));
}

TEST_CASE("less than operator") {
   SUBCASE("less than zero") {
      Cash x(0, -1);
      Cash y;
      CHECK( x < y );
      CHECK_FALSE( y < x);
   }
   SUBCASE("1 less cent but same dollars") {
      Cash x(10, 99);
      Cash y(10, 98);
      CHECK(y < x);
      CHECK_FALSE( x < y );
   }
   SUBCASE("negative amounts") {
      Cash x(-7, -22);
      Cash y(-7, -23);
      CHECK_FALSE( x < y );
      CHECK( y < x );
   }
   SUBCASE("positive amounts") {
      Cash x(17, 22);
      Cash y(17, 23);
      CHECK( x < y );
      CHECK_FALSE( y < x );
   }
   SUBCASE("equal amounts") {
      Cash x(57, 22);
      Cash y(57, 22);
      CHECK_FALSE( x < y );
      CHECK_FALSE( y < x );
   }
}

TEST_CASE("greater than operator") {
   SUBCASE("greater than zero") {
      Cash x(0, -1);
      Cash y;
      CHECK_FALSE( x > y );
      CHECK( y > x );
   }
   SUBCASE("1 less cent but same dollars") {
      Cash x(10, 99);
      Cash y(10, 98);
      CHECK( x > y );
      CHECK_FALSE(y > x);
   }
   SUBCASE("negative amounts") {
      Cash x(-7, -22);
      Cash y(-7, -23);
      CHECK( x > y );
      CHECK_FALSE( y > x );
   }
   SUBCASE("positive amounts") {
      Cash x(17, 22);
      Cash y(17, 23);
      CHECK_FALSE( x > y );
      CHECK( y > x );
   }
   SUBCASE("equal amounts") {
      Cash x(57, 22);
      Cash y(57, 22);
      CHECK_FALSE( x > y );
      CHECK_FALSE( y > x );
   }
}

TEST_CASE("addition operator") {
   SUBCASE("symmetric with conversion") {
      Cash m(12, 99);
      stringstream ssLeft;
      ssLeft << (m + 13);
      CHECK(ssLeft.str() == "$25.99");
      stringstream ssRight;
      ssRight << (13 + m);
      CHECK(ssRight.str() == "$25.99");
   }
   SUBCASE("starting with amount owed with conversion") {
      Cash m(-12, -99);
      stringstream ssLeft;
      ssLeft << (m + 13);
      CHECK(ssLeft.str() == "$0.01");
      stringstream ssRight;
      ssRight << (13 + m);
      CHECK(ssRight.str() == "$0.01");
   }
   SUBCASE("addtion with two object") {
      Cash m(-12, -99);
      Cash n(9, 82);
      stringstream ssLeft;
      ssLeft << (m + n);
      CHECK(ssLeft.str() == "-$3.17");
   }
}

TEST_CASE("subtraction operator") {
   SUBCASE("two positive amounts") {
      Cash a(8);
      Cash b(7, 99);
      stringstream ssLeft;
      ssLeft << (a - b);
      CHECK(ssLeft.str() == "$0.01");
   }
   SUBCASE("negative minus a negative amount") {
      Cash a(-9);
      Cash b(-1, -98);
      stringstream ssLeft;
      ssLeft << (a - b);
      CHECK(ssLeft.str() == "-$7.02");
   }
   SUBCASE("positive minus a negative amount") {
      Cash a(7, 45);
      Cash b(-2, -35);
      stringstream ssLeft;
      ssLeft << (a - b);
      CHECK(ssLeft.str() == "$9.80");
   }
}

TEST_CASE("multiplication operator by a factor") {
   SUBCASE("money owed and then paid") {
      Cash x(-3, -27);
      stringstream ss;
      ss << (x * -1);
      CHECK(ss.str() == "$3.27");
   }
   SUBCASE("money owed and then doubled") {
      Cash x(-3, -27);
      stringstream ss;
      ss << (x * 2);
      CHECK(ss.str() == "-$6.54");
   }
   SUBCASE("money paid by 10 people") {
      Cash x(1000);
      stringstream ss;
      ss << (10 * x);
      CHECK(ss.str() == "$10000.00");
   }
}

TEST_CASE("multiplication operator factor by an object") {
   SUBCASE("money owed and then paid") {
      Cash x(-3, -27);
      stringstream ss;
      ss << (-1 * x);
      CHECK(ss.str() == "$3.27");
   }
   SUBCASE("money owed and then doubled") {
      Cash x(-3, -27);
      stringstream ss;
      ss << (2 * x);
      CHECK(ss.str() == "-$6.54");
   }
   SUBCASE("money paid by 10 people") {
      Cash x(1000);
      stringstream ss;
      ss << (x * 10);
      CHECK(ss.str() == "$10000.00");
   }
}

TEST_CASE("multiple multiplications") {
   SUBCASE("back to original price") {
      Cash x(4, 99);
      stringstream ss;
      ss << (-1 * x * -1);
      CHECK(ss.str() == "$4.99");
   }
   SUBCASE("several factors first") {
      Cash x(-8, 1);
      stringstream ss;
      ss << (2 * 5 * x);
      CHECK(ss.str() == "-$79.90");
   }
   SUBCASE("factors after") {
      Cash x(1000);
      stringstream ss;
      ss << (x * 10 * 5);
      CHECK(ss.str() == "$50000.00");
   }
}


TEST_CASE("BONUS unary negative") {
   SUBCASE("from positive to negative") {
      Cash m(12345, 67);
      stringstream ss;
      ss << -m;
      CHECK(ss.str() == "-$12345.67");
   }
   SUBCASE("negative plus position equals 0") {
      Cash m(33, 81);
      stringstream ss;
      ss << (-m + m);
      CHECK(ss.str() == "$0.00");
   }
   SUBCASE("negative plus negative equals twice negative") {
      Cash m(33, 81);
      stringstream ss;
      ss << (-m + -m);
      CHECK(ss.str() == "-$67.62");
   }
   SUBCASE("negative to begin with") {
      Cash m(-22, -77);
      stringstream ss;
      ss << -m;
      CHECK(ss.str() == "$22.77");
   }
}


//---------------------------------------------------------------------
// add your tests below including the missing functions (methods)
// for the accessor functions and mutator functions
//----------------------------------------------------------------------

TEST_CASE("getDollars accessor method") {
   SUBCASE("no arg constructor value 0") {
      Cash x = Cash();
      CHECK( x.getDollars() == 0 );
   }
   SUBCASE("one arg constructor positive value") {
      Cash x(5);
      CHECK( x.getDollars() == 5 );
   }
   SUBCASE("one arg constructor negative value") {
      Cash x(-4);
      CHECK( x.getDollars() == -4 );
   }
   SUBCASE("two arg constructor positive value") {
      Cash x(10, 99);
      CHECK( x.getDollars() == 10 );
   }
   SUBCASE("two arg constructor negative value") {
      Cash x(-43, -1);
      CHECK( x.getDollars() == -43 );
   }
}

TEST_CASE("getCents accessor method") {
   SUBCASE("no arg constructor value 0") {
      Cash x = Cash();
      CHECK( x.getCents() == 0 );
   }
   SUBCASE("one arg constructor positive value") {
      Cash x(5);
      CHECK( x.getCents() == 0 );
   }
   SUBCASE("one arg constructor negative value") {
      Cash x(-4);
      CHECK( x.getCents() == 0 );
   }
   SUBCASE("two arg constructor positive value") {
      Cash x(10, 99);
      CHECK( x.getCents() == 99 );
   }
   SUBCASE("two arg constructor negative value") {
      Cash x(-43, -1);
      CHECK( x.getCents() == -1 );
   }
}

TEST_CASE("getAmount accessor method") {
   SUBCASE("no arg constructor value 0") {
      Cash x = Cash();
      CHECK( x.getAmount() == 0 );
   }
   SUBCASE("one arg constructor positive value") {
      Cash x(5);
      CHECK( x.getAmount() == 5 );
   }
   SUBCASE("one arg constructor negative value") {
      Cash x(-4);
      CHECK( x.getAmount() == -4 );
   }
   SUBCASE("two arg constructor positive value") {
      Cash x(10, 99);
      CHECK( x.getAmount() == 10.99 );
   }
   SUBCASE("two arg constructor negative value") {
      Cash x(-43, -1);
      CHECK( x.getAmount() == -43.01 );
   }
   SUBCASE("two arg constructor no cents") {
      Cash x(10, 0);
      CHECK( x.getAmount() == 10 );
   }
   SUBCASE("two arg constructor no dollars") {
      Cash x(0, 92);
      CHECK( x.getAmount() == 0.92 );
   }
}

TEST_CASE("setDollarsCent accessor method with two arguments") {
   SUBCASE("set zero dollar and zero cents") {
      Cash x(4, 32);
      x.setDollarsCents(0,0);
      stringstream ssLeft;
      ssLeft << x;
      CHECK(ssLeft.str() == "$0.00");
   }
   SUBCASE("set negative values") {
      Cash x(5);
      x.setDollarsCents(-32, -99);
      stringstream ssLeft;
      ssLeft << x;
      CHECK(ssLeft.str() == "-$32.99");
   }
   SUBCASE("set negative dollars and positive cents") {
      Cash x(5);
      x.setDollarsCents(-58, 99);
      stringstream ssLeft;
      ssLeft << x;
      CHECK(ssLeft.str() == "-$57.01");
   }
   SUBCASE("set positive dollars and negative cents") {
      Cash x(5);
      x.setDollarsCents(43, -79);
      stringstream ssLeft;
      ssLeft << x;
      CHECK(ssLeft.str() == "$42.21");
   }
}

// depends on accessor methods
TEST_CASE("setDollarsCent accessor method with one double value") {
   SUBCASE("set zero dollar and zero cents") {
      Cash x(4, 32);
      x.setDollarsCents(0);
      stringstream ssLeft;
      ssLeft << x;
      CHECK(ssLeft.str() == "$0.00");
   }
   SUBCASE("set positive values") {
      Cash x(5);
      x.setDollarsCents(45.23);
      stringstream ssLeft;
      ssLeft << x;
      CHECK(ssLeft.str() == "$45.23");
   }
   SUBCASE("set negative values") {
      Cash x(5);
      x.setDollarsCents(-32.5);
      stringstream ssLeft;
      ssLeft << x;
      CHECK(ssLeft.str() == "-$32.50");
   }
   SUBCASE("set less than 1 dollar") {
      Cash x(5);
      x.setDollarsCents(0.35);
      stringstream ssLeft;
      ssLeft << x;
      CHECK(ssLeft.str() == "$0.35");
   }
}

// BONUS TESTS
// friend const Cash operator / (const Cash&, int n);
TEST_CASE("division operator") {
   SUBCASE("no remainder") {
      Cash a(9, 30);
      int n = 3;
      stringstream ssLeft;
      ssLeft << (a / n);
      CHECK(ssLeft.str() == "$3.10");
   }
   SUBCASE("no remainder, negative devisor") {
      Cash a(3, 20);
      int n = -4;
      stringstream ssLeft;
      ssLeft << (a / n);
      CHECK(ssLeft.str() == "-$0.80");
   }
   SUBCASE("no remainder, negative cash and negative devisor") {
      Cash a(-1, -21);
      int n = -11;
      stringstream ssLeft;
      ssLeft << (a / n);
      CHECK(ssLeft.str() == "$0.11");
   }
   SUBCASE("includes remainder") {
      Cash a(5, 12);
      int n = 3;
      stringstream ssLeft;
      ssLeft << (a / n);
      CHECK(ssLeft.str() == "$1.70");
   }
   SUBCASE("includes remainder, negative devisor") {
      Cash a(13, 29);
      int n = -4;
      stringstream ssLeft;
      ssLeft << (a / n);
      CHECK(ssLeft.str() == "-$3.32");
   }
   SUBCASE("includes remainder, negative cash and negative devisor") {
      Cash a(-93, -21);
      int n = -32;
      stringstream ssLeft;
      ssLeft << (a / n);
      CHECK(ssLeft.str() == "$2.91");
   }
}


TEST_CASE("number of coins operator") {
   SUBCASE("loonie") {
      Cash a(3, 42);
      CHECK(a % LOONIE == 4);
   }
   SUBCASE("loonie and zero") {
      Cash a(0);
      CHECK(a % LOONIE == 0);
   }
   SUBCASE("toonie and positive value") {
      Cash a(34, 63);
      CHECK(a % TOONIE == 18);
   }
   SUBCASE("toonie and no remainder") {
      Cash a(34);
      CHECK(a % TOONIE == 17);
   }
   SUBCASE("quarter") {
      Cash a(99, 14);
      CHECK(a % QUARTER == 397);
   }
   SUBCASE("dime") {
      Cash a(21, 0);
      CHECK(a % DIME == 210);
   }
   SUBCASE("nickel") {
      Cash a(54, 91);
      CHECK(a % NICKEL == 1099);
   }
}