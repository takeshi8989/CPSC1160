// Author: Gladys Monagan
// Do not submit.
// Do not post anywhere.

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <sstream>  // std::stringstream
#include <iostream>
#include <string> 
#include "sparse.h"

using std::stringstream, std::string;

// returns the string in the stringstream without blanks 
string string_from_ss(stringstream& ss) {
   string str = ss.str();
   string res = string("");
   for (unsigned int i = 0; i < str.length(); i++)
      if (str[i] != ' ')
         res += str[i];
   return res;
}

TEST_CASE("zero polynomial") {
   Sparse f;
   SUBCASE("output") {
      stringstream actual;
      actual << f;
      CHECK( string_from_ss(actual) == "0" );
   }
   SUBCASE("isZeroPolynomial") {
      CHECK(f.isZeroPolynomial());
   }
   SUBCASE("degree") {
      CHECK_EQ(f.degree(), -1);
   }
   SUBCASE("coefficient") {
      CHECK_EQ(f.coefficient(5), 0);
   }
   SUBCASE("multiplication") {
      Sparse result = f * 7;
      CHECK(result.isZeroPolynomial());
   }
   SUBCASE("sum") {
      Sparse g;
      CHECK((f + g).isZeroPolynomial());
   }
   SUBCASE("sum") {
      Sparse g;
      CHECK((f - g).isZeroPolynomial());
   }
}

TEST_CASE("one term constructor") {
   Sparse f(3, 2);
   SUBCASE("output") {
      stringstream actual;
      actual << f;
      CHECK( string_from_ss(actual) == "3*x^2" );
   }
   SUBCASE("isZeroPolynomial") {
      CHECK_FALSE( f.isZeroPolynomial() );
   }
   SUBCASE("degree") {
      CHECK_EQ( f.degree(), 2 );
   }
   SUBCASE("coefficient") {
      CHECK_EQ( f.coefficient(2), 3 );
      CHECK_EQ( f.coefficient(5), 0 );
   }
   SUBCASE("multiply") {
      stringstream actual;
      actual << (f * -2);
      CHECK( string_from_ss(actual) == "-6*x^2" );
   }
   SUBCASE("variable name") {
      CHECK( f.getPrintVariable() == 'x' );
   }
   SUBCASE("multiply by 0") {
      stringstream actual;
      CHECK( (f * 0).isZeroPolynomial() );
   }
}

TEST_CASE("insert one term") {
   Sparse f;
   stringstream ss_in("1 3 2");
   ss_in >> f;
   SUBCASE("output") {
      stringstream actual;
      actual << f;
      CHECK( string_from_ss(actual) == "3*x^2" );
   }
   SUBCASE("isZeroPolynomial") {
      CHECK_FALSE( f.isZeroPolynomial() );
   }
   SUBCASE("degree") {
      CHECK_EQ( f.degree(), 2 );
   }
   SUBCASE("coefficient") {
      CHECK_EQ( f.coefficient(2), 3 );
      CHECK_EQ( f.coefficient(5), 0) ;
   }
   SUBCASE("multiply") {
      stringstream actual;
      actual << (f * -2);
      CHECK( string_from_ss(actual) == "-6*x^2" );
   }
   SUBCASE("multiply by 0") {
      stringstream actual;
      CHECK( (f * 0).isZeroPolynomial() );
   }
}

TEST_CASE("add, subtract with different degrees") {
   Sparse f;
   stringstream ss_in_f("1 -3 1");
   ss_in_f >> f;
   SUBCASE("output") {
      stringstream actual;
      actual << f;
      CHECK( string_from_ss(actual) == "-3*x^1" );
   }
   SUBCASE("isZeroPolynomial") {
      CHECK_FALSE( f.isZeroPolynomial() );
   }
   SUBCASE("degree") {
      CHECK_EQ( f.degree(), 1 );
   }
   SUBCASE("coefficient") {
      CHECK_EQ( f.coefficient(1), -3 );
   }
   Sparse g;
   stringstream ss_in_g("1 4 3");
   ss_in_g >> g;
   SUBCASE("output") {
      stringstream actual;
      actual << g;
      CHECK( string_from_ss(actual) == "4*x^3" );
   }
   SUBCASE("isZeroPolynomial") {
      CHECK_FALSE( g.isZeroPolynomial() );
   }
   SUBCASE("degree") {
      CHECK_EQ( g.degree(), 3 );
   }
   SUBCASE("coefficient") {
      CHECK_EQ( g.coefficient(3), 4 );
   }
   SUBCASE("sum f + g: always outputs in ascending order") {
      stringstream actual;
      actual << f + g;
      CHECK( string_from_ss(actual) == "-3*x^1+4*x^3" );
   }
   SUBCASE("sum g + f: always outputs in ascending order") {
      stringstream actual;
      actual << g + f;
      CHECK( string_from_ss(actual) == "-3*x^1+4*x^3" );
   }
   SUBCASE("subtract f - g") {
      stringstream actual;
      actual << f - g;
      CHECK( string_from_ss(actual) == "-3*x^1-4*x^3" );
   }
   SUBCASE("subtract g - f") {
      stringstream actual;
      actual << g - f;
      CHECK( string_from_ss(actual) == "3*x^1+4*x^3" );
   }
}

// bonus part

TEST_CASE("derivative") {
   Sparse f;
   stringstream ss_in_f("1 -3 1");
   ss_in_f >> f;
   SUBCASE("single term") {
      stringstream actual;
      actual << f.derivative();
      CHECK( string_from_ss(actual) == "-3" );
   }
   
   Sparse g;
   stringstream ss_in_g("2 2 2 4 3");
   ss_in_g >> g;
   SUBCASE("multiple terms") {
      stringstream actual;
      actual << g.derivative();
      CHECK( string_from_ss(actual) == "4*x^1+12*x^2" );
   }

   Sparse h;
   stringstream ss_in_h("1 3 0");
   ss_in_g >> h;
   SUBCASE("constant") {
      stringstream actual;
      actual << h.derivative();
      CHECK( string_from_ss(actual) == "0" );
   }
}

// copyright 2022 Gladys Monagan

