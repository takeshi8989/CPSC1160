// CPSC 1160 
// Author: Gladys Monagan
// Do not post anywhere nor give to anyone.

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <sstream>  // std::stringstream
#include <iostream>
#include <string> 
#include "Bag.h"

using std::stringstream, std::string;

TEST_CASE("default constructor") {
   SUBCASE("no-arg constructor") {
      Bag bag;
      stringstream ss;
      ss << bag;
      CHECK(ss.str() == Bag::START + Bag::END);
   }
}


TEST_CASE("add depends on the output operator") {
   SUBCASE("empty") {
      Bag bag;
      stringstream actual;
      actual << bag;
      stringstream expected;
      expected 
         << Bag::START 
         << Bag::END;
      CHECK(actual.str() == expected.str());
   }
   SUBCASE("one element") {
      Bag bag;
      bag.add(7);
      stringstream actual;
      actual << bag;
      stringstream expected;
      expected
         << Bag::START 
         << 7 << Bag::SEP 
         << Bag::END;
      CHECK(actual.str() == expected.str());
   }
   SUBCASE("two elements") {
      Bag bag;
      bag.add(3);
      bag.add(5);
      stringstream actual;
      actual << bag;
      stringstream expected;
      expected
         << Bag::START 
         << 3 << Bag::SEP 
         << 5 << Bag::SEP 
         << Bag::END;
      CHECK(actual.str() == expected.str());
   }
}

TEST_CASE("size depends on add") {
   SUBCASE("empty bag") {
      Bag bag;
      CHECK_EQ(bag.size(), 0);
   }
   SUBCASE("many elements") {
      Bag bag;
      int n = 127;
      for (int i = 0; i < n; i++) {
         CHECK_EQ(bag.size(), i);
         bag.add(i);
      }
   }
}

TEST_CASE("remove depends on the output & input operator") {
   SUBCASE("from an empty bag - nothing happens") {
      Bag bag;
      bag.remove(4);
      stringstream actual;
      actual << bag;
      stringstream expected;
      expected 
         << Bag::START 
         << Bag::END;
      CHECK(actual.str() == expected.str());
   }
   SUBCASE("add a single item and remove it") {
      Bag bag;
      bag.add(87654);
      bag.remove(87654);
      stringstream actual;
      actual << bag;
      stringstream expected;
      expected 
         << Bag::START
         << Bag::END;
      CHECK(actual.str() == expected.str());
   }
   SUBCASE("middle element") {
      Bag bag;
      stringstream ss_in("17 15 13");
      ss_in >> bag;
      bag.remove(15);
      stringstream actual;
      actual << bag;
      stringstream expected;
      expected 
          << Bag::START 
         << 13 << Bag::SEP
         << 17 << Bag::SEP
         << Bag::END;
      CHECK(actual.str() == expected.str());
   }
   SUBCASE("at the head") {
      Bag bag;
      stringstream ss_in("80 88 85 81 80 88 80");
      ss_in >> bag;
      bag.remove(80);
      stringstream actual;
      actual << bag;
      stringstream expected;
      expected 
         << Bag::START 
         << 80 << Bag::SEP
         << 80 << Bag::SEP
         << 81 << Bag::SEP
         << 85 << Bag::SEP
         << 88 << Bag::SEP
         << 88 << Bag::SEP
         << Bag::END;
      CHECK(actual.str() == expected.str());
   }
}

TEST_CASE("operator >> depends on the output operator") {
   Bag bag;
   stringstream ss_in("0 8 5 1 0 8 0");
   ss_in >> bag;
   stringstream actual;
   actual << bag;
   stringstream expected;
   expected 
      << Bag::START 
      << 0 << Bag::SEP
      << 0 << Bag::SEP
      << 0 << Bag::SEP
      << 1 << Bag::SEP
      << 5 << Bag::SEP
      << 8 << Bag::SEP
      << 8 << Bag::SEP
      << Bag::END;
   CHECK(actual.str() == expected.str());
}

TEST_CASE("operator < depends on the input operator") {
   SUBCASE("empty bag") {
      Bag bag;
      CHECK_FALSE(3 < bag);
   }
   Bag bag;
   stringstream ss_in("0 8 5 1 0 8 0");
   ss_in >> bag;
   SUBCASE("several inside items") {
      CHECK(0 < bag);
      CHECK(8 < bag);
      CHECK(5 < bag);
      CHECK(1 < bag);
   }
   SUBCASE("greater item fail") {
      Bag bag;
      stringstream ss_in("0 8 5 1 0 8 0");
      ss_in >> bag;
      CHECK_FALSE(9 < bag);
   }
   SUBCASE("smaller item fail") {
      CHECK_FALSE(-4 < bag);
   }
}

TEST_CASE("operator ==") {
   Bag s, t;
   SUBCASE("empty bags") {
      CHECK(s == t);
   }
   s.add(3);
   t.add(5);
   SUBCASE("one element fail") {
      CHECK_FALSE(s == t);
   }
   t.add(3);
   s.add(5);
   SUBCASE("two elements") {
      CHECK(s == t);
   }
   t.remove(3);
   s.remove(5);
   SUBCASE("one different element fail") {
      CHECK_FALSE(s == t);
   }
   t.remove(5);
   s.remove(3);
   SUBCASE("two elements") {
      CHECK(s == t);
   }
   SUBCASE("empty again") {
      CHECK(s == t);
   }
}

TEST_CASE("operator +") {
   SUBCASE("intermingled") {
      Bag a;
      stringstream ss_in("2 4 6 7 8");
      ss_in >> a;
      a.remove(90);
      stringstream actual;
      actual << a;
      stringstream expected;
      expected 
         << Bag::START 
         << 2 << Bag::SEP
         << 4 << Bag::SEP
         << 6 << Bag::SEP
         << 7 << Bag::SEP
         << 8 << Bag::SEP
         << Bag::END;
      CHECK(actual.str() == expected.str());
      Bag b;
      b.add(1);
      b.add(3);
      b.add(5);
      actual = stringstream();
      actual << (a + b);
      expected = stringstream();
      expected 
         << Bag::START 
         << 1 << Bag::SEP
         << 2 << Bag::SEP
         << 3 << Bag::SEP
         << 4 << Bag::SEP
         << 5 << Bag::SEP
         << 6 << Bag::SEP
         << 7 << Bag::SEP
         << 8 << Bag::SEP
         << Bag::END;
      CHECK(actual.str() == expected.str());
      actual = stringstream();
      actual << (b + a);
      expected = stringstream();
      expected 
         << Bag::START 
         << 1 << Bag::SEP
         << 2 << Bag::SEP
         << 3 << Bag::SEP
         << 4 << Bag::SEP
         << 5 << Bag::SEP
         << 6 << Bag::SEP
         << 7 << Bag::SEP
         << 8 << Bag::SEP
         << Bag::END;
      CHECK(actual.str() == expected.str());
   }
   SUBCASE("with duplicates in lists a and b") {
      Bag a;
      stringstream ss_in("90 99 95 91 90 99 90");
      ss_in >> a;
      a.remove(90);
      stringstream actual;
      actual << a;
      stringstream expected;
      expected 
         << Bag::START 
         << 90 << Bag::SEP
         << 90 << Bag::SEP
         << 91 << Bag::SEP
         << 95 << Bag::SEP
         << 99 << Bag::SEP
         << 99 << Bag::SEP
         << Bag::END;
      CHECK(actual.str() == expected.str());
      Bag b;
      b.add(93);
      b.add(90);
      b.add(90);
      actual = stringstream();
      actual << (a + b);
      expected = stringstream();
      expected 
         << Bag::START 
         << 90 << Bag::SEP
         << 90 << Bag::SEP
         << 90 << Bag::SEP
         << 90 << Bag::SEP
         << 91 << Bag::SEP
         << 93 << Bag::SEP
         << 95 << Bag::SEP
         << 99 << Bag::SEP
         << 99 << Bag::SEP
         << Bag::END;
      CHECK(actual.str() == expected.str());
   }
   SUBCASE("with an empty bag") {
      Bag bag;
      bag.add(999);
      Bag empty;
      stringstream actual;
      actual << (empty + bag);
      stringstream expected;
      expected 
         << Bag::START 
         << 999 << Bag::SEP
         << Bag::END;
      CHECK(actual.str() == expected.str());
      actual = stringstream();
      actual << (bag + empty);
      CHECK(actual.str() == expected.str());
   }
   SUBCASE("two empty bags") {
      Bag empty;
      stringstream actual;
      actual << (empty + empty);
      stringstream expected;
      expected 
         << Bag::START 
         << Bag::END;
      CHECK(actual.str() == expected.str());
   }
}


// BONUS

TEST_CASE("operator *") {
   SUBCASE("with duplicates in lists a and b") {
      Bag a;
      stringstream ss_in("99 95 91 90 99 90");
      ss_in >> a;
      stringstream actual;
      actual << a;
      stringstream expected;
      expected 
         << Bag::START 
         << 90 << Bag::SEP
         << 90 << Bag::SEP
         << 91 << Bag::SEP
         << 95 << Bag::SEP
         << 99 << Bag::SEP
         << 99 << Bag::SEP
         << Bag::END;
      CHECK(actual.str() == expected.str());
      Bag b;
      b.add(93);
      b.add(90);
      b.add(90);
      actual = stringstream();
      actual << (a * b);
      expected = stringstream();
      expected 
         << Bag::START 
         << 90 << Bag::SEP
         << 91 << Bag::SEP
         << 93 << Bag::SEP
         << 95 << Bag::SEP
         << 99 << Bag::SEP
         << Bag::END;
      CHECK(actual.str() == expected.str());
      actual = stringstream();
      actual << (b * a);
      CHECK(actual.str() == expected.str());
   }
}




// copyright 2023 Gladys Monagan

