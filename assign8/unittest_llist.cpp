// Author: Gladys Monagan
// CPSC 1160
// Do not post anywhere.

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

/*
to run only the test cases removeIth

on Windows
unittest_llist  -tc=removeIth

on Linux (MacOS)
./unittest_llist  -tc=removeIth

to exclude the BONUS tests cases 

on Windows
unittest_llist -tc="BONUS*"

on Linux (MacOS)
/unittest_llist -tc="BONUS*"

*/

#include <sstream>  // std::stringstream
#include <iostream>
#include <string>   // std::string
using std::stringstream, std::string;

#include "llist_utils.h"
#include "llist.h"

TEST_CASE("input operator >> ") {
   SUBCASE("empty list") {
      Node *p;
      stringstream ss_in("k");
      ss_in >> p;
      stringstream actual;
      actual << p;
      CHECK( actual.str() == "{ }" );
   }
   SUBCASE("one element and end-of-file or end-of-stream") {
      Node* p ;
      stringstream ss_in("  -1   \n");
      ss_in >> p;
      stringstream actual;
      actual << p;
      CHECK( actual.str() == "{ -1 }" );
   }
   SUBCASE("one element followed by a character") {
      Node* p;
      stringstream ss_in("  -777   k");
      ss_in >> p;
      stringstream actual;
      actual << p;
      CHECK( actual.str() == "{ -777 }" );
   }
   SUBCASE("three elements") {
      Node* p;
      stringstream ss_in("10 20 30");
      ss_in >> p;
      stringstream actual;
      actual << p;
      CHECK( actual.str() == "{ 10 20 30 }" );
   }
   SUBCASE("free formatted input and no more input") {
      Node *p;
      stringstream ss_in("13 14     15 16 17 18\n    19");
      ss_in >> p;
      stringstream actual;
      actual << p;
      CHECK( actual.str() == "{ 13 14 15 16 17 18 19 }" );
   }
   SUBCASE("free formatted input followed by a character") {
      Node* p;
      stringstream ss_in("13 14     15 16 17 18\n    19  k");
      ss_in >> p;
      stringstream actual;
      actual << p;
      CHECK( actual.str() == "{ 13 14 15 16 17 18 19 }" );
   }
}

TEST_CASE("copyList") {
   SUBCASE("empty lists") {
      CHECK_EQ(copyList(nullptr), nullptr);
   }
   SUBCASE("one empty list") {
      Node* p = cons(2021, nullptr);
      stringstream actual;
      actual << copyList(p);
      CHECK( actual.str() == "{ 2021 }" );
   }
   SUBCASE("3 elements") {
      Node* p = cons(7, cons(10, cons(9, nullptr)));
      stringstream actual;
      actual << copyList(p);
      CHECK( actual.str() == "{ 7 10 9 }" );
   }
   SUBCASE("4 elements") {
      Node* p = cons(0, cons(1, cons(2, cons(3, cons(4, nullptr)))));
      stringstream actual;
      actual << copyList(p);
      CHECK( actual.str() == "{ 0 1 2 3 4 }" );
   }
   SUBCASE("more elements") {
      Node * p = cons(0, cons(2, cons(-1, cons(1, cons(0, nullptr)))));
      stringstream actual;
      actual << copyList(p);
      CHECK( actual.str() == "{ 0 2 -1 1 0 }" );
   }
   SUBCASE("remove element from original") {
      Node * p = cons(0, cons(2, cons(-1, cons(1, cons(0, nullptr)))));
      stringstream p_ss, q_ss, qc_ss;
      Node* q = copyList(p);
      qc_ss << q;
      CHECK(qc_ss.str() == "{ 0 2 -1 1 0 }" );
      Node* r = p;
      while (cdr(cdr(r)) != nullptr) r = cdr(r);
      Node* discard = cdr(r);
      setcdr(r, nullptr);
      delete discard;
      p_ss << p;
      CHECK(p_ss.str() == "{ 0 2 -1 1 }" );
      q_ss << q;
      CHECK(q_ss.str() == "{ 0 2 -1 1 0 }" );
   }
   SUBCASE("remove element from copy") {
      Node * p = cons(0, cons(2, cons(-1, cons(1, cons(0, nullptr)))));
      stringstream p_ss, q_ss, qc_ss;
      Node* q = copyList(p);
      qc_ss << q;
      CHECK(qc_ss.str() == "{ 0 2 -1 1 0 }" );
      Node* r = q;
      while (cdr(cdr(r)) != nullptr) r = cdr(r);
      Node* discard = cdr(r);
      setcdr(r, nullptr);
      delete discard;
      p_ss << p;
      CHECK(p_ss.str() == "{ 0 2 -1 1 0 }" );
      q_ss << q;
      CHECK(q_ss.str() == "{ 0 2 -1 1 }" );
   }
}

TEST_CASE("reverse") {
   SUBCASE("special case empty list") {
      Node* p = nullptr;
      stringstream actual;
      actual << reverse(p);
      CHECK( actual.str() == "{ }" );
   }
   SUBCASE("one element") {
      Node* p = cons(2023, nullptr);
      stringstream actual;
      actual << reverse(p);
      CHECK( actual.str() == "{ 2023 }" );
   }
   SUBCASE("3 elements") {
      Node* p = cons(7, cons(10, cons(9, nullptr)));
      stringstream actual;
      actual << reverse(p);
      CHECK( actual.str() == "{ 9 10 7 }" );
   }
   SUBCASE("4 elements") {
      Node* p = cons(0, cons(1, cons(2, cons(3, nullptr))));
      stringstream actual;
      actual << reverse(p);
      CHECK( actual.str() == "{ 3 2 1 0 }" );
   }
   SUBCASE("more elements") {
      Node * p = cons(0, cons(2, cons(-1, cons(1, cons(0, nullptr)))));
      stringstream actual;
      actual << reverse(p);
      CHECK( actual.str() == "{ 0 1 -1 2 0 }" );
   }
}

TEST_CASE("output operator <<") {
   SUBCASE("empty list") {
      Node* p = nullptr;
      stringstream actual;
      actual << p;
      CHECK( actual.str() == "{ }" );
   }
   SUBCASE("one element") {
      Node* p = cons(2023, nullptr);
      stringstream actual;
      actual << p;
      CHECK( actual.str() == "{ 2023 }" );
   }
   SUBCASE("3 elements") {
      Node* p = cons(7, cons(10, cons(9, nullptr)));
      stringstream actual;
      actual << p;
      CHECK( actual.str() == "{ 7 10 9 }" );
   }
   SUBCASE("more elements") {
      Node * p = cons(1, cons(2, cons(3, cons(4, cons(5, cons(6, nullptr))))));
      stringstream actual;
      actual << p;
      CHECK( actual.str() == "{ 1 2 3 4 5 6 }" );
   }
}


TEST_CASE("append") {
   SUBCASE("from an empty list") {
      Node* p = nullptr;
      p = append(77, p);
      stringstream actual;
      actual << p;
      CHECK( actual.str() == "{ 77 }" );
   }
   SUBCASE("from a one element list") {
      Node* p = cons(88, nullptr);
      p = append(-999, p);
      stringstream actual;
      actual << p;
      CHECK( actual.str() == "{ 88 -999 }" );
   }
   SUBCASE("longer list") {
      Node * p = cons(0, cons(2, cons(-1, cons(1, cons(0, nullptr)))));
      p = append(-1, p);
      stringstream actual;
      actual << p;
      CHECK( actual.str() == "{ 0 2 -1 1 0 -1 }" );
   }
}

TEST_CASE("append_it, iterative version of append") {
   SUBCASE("from an empty list") {
      Node* p = nullptr;
      p = append_it(77, p);
      stringstream actual;
      actual << p;
      CHECK( actual.str() == "{ 77 }" );
   }
   SUBCASE("from a one element list") {
      Node* p = cons(66666, nullptr);
      p = append_it(66666, p);
      stringstream actual;
      actual << p;
      CHECK( actual.str() == "{ 66666 66666 }" );
   }
   SUBCASE("longer list") {
      Node * p = cons(10, cons(12, cons(11, cons(11, cons(0, nullptr)))));
      p = append_it(-1, p);
      stringstream actual;
      actual << p;
      CHECK( actual.str() == "{ 10 12 11 11 0 -1 }" );
   }
}

TEST_CASE("searchInOrder") {
   SUBCASE("special case empty list") {
      CHECK_FALSE( searchInOrder(3, nullptr));
   }
   SUBCASE("one element") {
      Node* p = cons(4, nullptr);
      CHECK( searchInOrder(4, p) );
      CHECK_FALSE( searchInOrder(-5, p) );
   }
   SUBCASE("last element") {
      Node* p = cons(4, cons(5, cons(10, cons(11, nullptr))));
      CHECK( searchInOrder(11, p) );
      CHECK_FALSE( searchInOrder(6, p) );
   }
   SUBCASE("longer list") {
      Node * p = cons(11, cons(12, cons(13, cons(14, cons(15, nullptr)))));
      for (int i = 11; i <= 15; i++)
         CHECK( searchInOrder(i, p) );
      CHECK_FALSE( searchInOrder(-3, p) );
      CHECK_FALSE( searchInOrder(20, p) );
   }
}


TEST_CASE("searchInOrder_it iterative version") {
   SUBCASE("special case empty list") {
      CHECK_FALSE( searchInOrder_it(3, nullptr));
   }
   SUBCASE("one element") {
      Node* p = cons(14, nullptr);
      CHECK( searchInOrder_it(14, p) );
      CHECK_FALSE( searchInOrder_it(-15, p) );
   }
   SUBCASE("last element") {
      Node* p = cons(4, cons(5, cons(10, cons(11, nullptr))));
      CHECK( searchInOrder_it(11, p) );
      CHECK_FALSE( searchInOrder_it(-6, p) );
   }
   SUBCASE("longer list") {
      Node * p = cons(11, cons(12, cons(13, cons(14, cons(15, nullptr)))));
      for (int i = 11; i <= 15; i++)
         CHECK( searchInOrder_it(i, p) );
      CHECK_FALSE( searchInOrder_it(-3, p) );
      CHECK_FALSE( searchInOrder_it(20, p) );
   }
}

TEST_CASE("isLonger") {
   SUBCASE("first longer than empty list") {
      Node *p = cons(1, cons(3, cons(4, cons(5, nullptr))));
      CHECK( isLonger(p, nullptr) );
   }
   SUBCASE("empty list NOT longer than empty list") {
      CHECK_FALSE( isLonger(nullptr, nullptr) );
   }
   SUBCASE("empty list not longer than anything") {
      Node *p = cons(8, nullptr);
      CHECK_FALSE( isLonger(nullptr, p) );
   }
   SUBCASE("first longer than second") {
      Node *p = cons(1, cons(3, cons(4, cons(5, nullptr))));
      Node *q = cons(8, nullptr);
      CHECK( isLonger(p, q) );
      CHECK_FALSE( isLonger(q, p) );
   }
   SUBCASE("if lists are equal, first is not longer") {
      Node *p = cons(1, cons(3, cons(4, cons(5, nullptr))));
      Node *q = cons(1, cons(3, cons(4, cons(5, nullptr))));
      CHECK_FALSE( isLonger(p, q) );
   }
   SUBCASE("second longer than first so fail") {
      Node *p = cons(1, cons(2, nullptr));
      Node *q = cons(1, cons(3, cons(4, cons(5, nullptr))));
      CHECK_FALSE( isLonger(p, q) );
      CHECK( isLonger(q, p) );
   }
   SUBCASE("special case: both empty") {
      Node *p = nullptr;
      Node *q = nullptr;
      CHECK_FALSE( isLonger(p, q) );
   }
}


TEST_CASE("equal") {
   SUBCASE("empty lists") {
      CHECK( equal(nullptr, nullptr) );
   }
   SUBCASE("one empty so fail") {
      Node* p = nullptr;
      Node* q = cons(4, nullptr);
      CHECK_FALSE( equal(p, q) );
      CHECK_FALSE( equal(q, p) );
   }
   SUBCASE("left longer list but equal values at head") {
      Node* left = cons(0, cons(1, cons(5, cons(7, nullptr))));
      Node* right = cons(0, cons(1, cons(5, nullptr)));
      CHECK_FALSE( equal(left, right) );
   }
   SUBCASE("right longer list but equal values up at head") {
      Node* left = cons(10, cons(11, cons(15, nullptr)));
      Node* right = cons(10, cons(11, cons(15, cons(17, nullptr))));
      CHECK_FALSE( equal(left, right) );
   }
   SUBCASE("same length different values") {
      Node* left = cons(0, cons(1, cons(5, cons(7, nullptr))));
      Node* right = cons(-1, cons(-2, cons(-3, cons(-4, nullptr))));
      CHECK_FALSE( equal(left, right) );
   }
   SUBCASE("1 element equal") {
      Node* p = cons(4, nullptr);
      Node* q = cons(4, nullptr);
      CHECK( equal(p, q) );
   }
   SUBCASE("2 elements equal") {
      Node* p = cons(4, cons(-4, nullptr));
      Node* q = cons(4, cons(-4, nullptr));
      CHECK( equal(p, q) );
   }
   SUBCASE("more elements equal") {
      Node* p = cons(-1, cons(-2, cons(-3, cons(-4, nullptr))));
      Node* q = cons(-1, cons(-2, cons(-3, cons(-4, nullptr))));
      CHECK( equal(p, q) );
   }
}


TEST_CASE("makeDuplicates") {
   SUBCASE("empty lists") {
      CHECK( equal(nullptr, nullptr) );
   }
   SUBCASE("one element") {
      Node* p = cons(-1, nullptr);
      stringstream actual;
      actual << makeDuplicates(p);
      CHECK( actual.str() == "{ -1 -1 }" );
   }
   SUBCASE("odd number of elements in list") {
      Node *p = cons(-3, cons(-2, cons(-1, nullptr)));
      stringstream actual;
      actual << makeDuplicates(p);
      CHECK( actual.str() == "{ -3 -3 -2 -2 -1 -1 }" );
   }
   SUBCASE("typical") {
      Node *p = cons(0, cons(1, cons(2, cons(3, nullptr))));
      stringstream actual;
      actual << makeDuplicates(p);
      CHECK( actual.str() == "{ 0 0 1 1 2 2 3 3 }" );
   }
   SUBCASE("test independence (without using remove)") {
      Node* dups;
      {
         Node *p = cons(0, cons(1, cons(2, cons(3, nullptr))));
         dups = makeDuplicates(p);
         stringstream actual;
         actual << p;
         CHECK( actual.str() == "{ 0 1 2 3 }" );
         actual = stringstream();
         actual << dups;
         CHECK( actual.str() == "{ 0 0 1 1 2 2 3 3 }" );
      }
      stringstream actual;
      actual << dups;
      CHECK( actual.str() == "{ 0 0 1 1 2 2 3 3 }" );
   }
}


TEST_CASE("removeList") {
   SUBCASE("empty lists") {
      CHECK_EQ(removeList(nullptr), nullptr);
   }
   SUBCASE("one element") {
      Node* p = cons(4, nullptr);
      CHECK_EQ(removeList(p), nullptr);
   }
   SUBCASE("typical") {
      Node *p = cons(0, cons(1, cons(2, cons(3, nullptr))));
      CHECK_EQ(removeList(p), nullptr);
   }
}


TEST_CASE("array2List") {
   SUBCASE("one element array") {
      int A[1] = {7};
      int n = 1;
      Node* q = array2List(A, n);
      stringstream actual;
      actual << q;
      CHECK( actual.str() == "{ 7 }" );
   }
   SUBCASE("even number of elements") {
      int A[3] = {2, 4, 6};
      int n = 2;  // only TWO elements
      Node* q = array2List(A, n);
      stringstream actual;
      actual << q;
      CHECK( actual.str() == "{ 2 4 }" );
   }
   SUBCASE("typical") {
      int A[4] = {1, 3, 5, 7};
      Node* q = array2List(A, 4);
      stringstream actual;
      actual << q;
      CHECK( actual.str() == "{ 1 3 5 7 }" );
   }
   SUBCASE("special case empty array") {
      int A[1] = {7};
      int n = 0;
      Node* q = array2List(A, n);
      stringstream actual;
      actual << q;
      CHECK( actual.str() == "{ }" );
   }
}


TEST_CASE("mergeTwoOrderedLists") {
   SUBCASE("first longer") {
      Node* p = cons(1, cons(3, cons(5, cons(7, cons(8, cons(9, nullptr))))));
      Node* q = cons(2, cons(4, cons(6, nullptr)));
      stringstream actual;
      actual << mergeTwoOrderedLists(p, q);
      CHECK( actual.str() == "{ 1 2 3 4 5 6 7 8 9 }" );
   }
   SUBCASE("second longer") {
      Node* p = cons(0, cons(1, cons(5, nullptr)));
      Node* q = cons(0, cons(1, cons(5, cons(7, nullptr))));
      stringstream actual;
      actual << mergeTwoOrderedLists(q, p);
      CHECK( actual.str() == "{ 0 0 1 1 5 5 7 }" );
   }
   SUBCASE("equal length different values") {
      Node* p = cons(1, cons(3, cons(5, cons(8, cons(10, cons(11, nullptr))))));
      Node* q = cons(2, cons(4, cons(6, cons(7, cons(9, cons(12, nullptr))))));
      stringstream actual;
      actual << mergeTwoOrderedLists(q, p);
      CHECK( actual.str() == "{ 1 2 3 4 5 6 7 8 9 10 11 12 }" );
   }
   SUBCASE("the same") {
      Node* p = cons(0, cons(1, cons(2, cons(3, nullptr))));
      Node* q = cons(0, cons(1, cons(2, cons(3, nullptr))));
      stringstream actual;
      actual << mergeTwoOrderedLists(q, p);
      CHECK( actual.str() == "{ 0 0 1 1 2 2 3 3 }" );
   }
   SUBCASE("second empty") {
      Node* p = cons(0, cons(1, cons(5, cons(7, nullptr))));
      Node* q = nullptr;
      stringstream actual;
      actual << mergeTwoOrderedLists(p, q);
      CHECK( actual.str() == "{ 0 1 5 7 }" );
   }
   SUBCASE("first empty") {
      Node* p =  nullptr;
      Node* q = cons(0, cons(1, cons(5, cons(7, nullptr))));
      stringstream actual;
      actual << mergeTwoOrderedLists(p, q);
      CHECK( actual.str() == "{ 0 1 5 7 }" );
   }
}

TEST_CASE("removeIth") {
   SUBCASE("first element") {
      Node* p = cons(10, cons(11, cons(12, cons(13, nullptr))));
      stringstream actual;
      actual << removeIth(0, p);
      CHECK( actual.str() == "{ 11 12 13 }" );
   }
   SUBCASE("last element") {
      Node* p = cons(30, cons(31, cons(32, cons(33, cons(34, cons(35, nullptr))))));
      stringstream actual;
      actual << removeIth(5, p);
      CHECK( actual.str() == "{ 30 31 32 33 34 }" );
   }
   SUBCASE("remove only element") {
      Node* p = cons(2150, nullptr);
      stringstream actual;
      actual << removeIth(0, p);
      CHECK( actual.str() == "{ }" );
   }
   SUBCASE("middle elements") {
      Node* p = cons(40, cons(41, cons(42, cons(43, cons(44, cons(45, nullptr))))));
      stringstream actual;
      actual << removeIth(1, p);
      CHECK( actual.str() == "{ 40 42 43 44 45 }" );
      actual = stringstream();
      actual << removeIth(1, p);
      CHECK( actual.str() == "{ 40 43 44 45 }" );
      actual = stringstream();
      actual << removeIth(2, p);
      CHECK( actual.str() == "{ 40 43 45 }" );
      actual = stringstream();
      actual << removeIth(2, p); // does nothing
      CHECK( actual.str() == "{ 40 43 }" );
      actual = stringstream();
      actual << removeIth(1, p);
      CHECK( actual.str() == "{ 40 }" );
      actual = stringstream();
      actual << removeIth(0, p);
      CHECK( actual.str() == "{ }" );
   }
   SUBCASE("not in list since index i is >= length of list") {
      Node *p = cons(20, cons(21, cons(22, cons(23, cons(24, nullptr)))));
      stringstream actual;
      actual << removeIth(5, p);
      CHECK( actual.str() == "{ 20 21 22 23 24 }" );
   }
   SUBCASE("special case empty list") {
      Node* p = nullptr;
      stringstream actual;
      actual << removeIth(0, p);
      CHECK( actual.str() == "{ }" );
   }
}

TEST_CASE("removeOccurrences") {
   SUBCASE("first element") {
      Node* p = cons(0, cons(1, cons(5, cons(6, nullptr))));
      stringstream actual;
      actual << removeOccurrences(0, p);
      CHECK( actual.str() == "{ 1 5 6 }" );
   }
   SUBCASE("last elements") {
      Node* p = cons(0, cons(1, cons(5, cons(7, cons(0, nullptr)))));
      stringstream actual;
      actual << removeOccurrences(0, p);
      CHECK( actual.str() == "{ 1 5 7 }" );
   }
   SUBCASE("not in list") {
      Node *p = cons(9, cons(7, cons(2, cons(5, cons(7, nullptr)))));
      stringstream actual;
      actual << removeOccurrences(-8, p);
      CHECK( actual.str() == "{ 9 7 2 5 7 }" );
   }
   SUBCASE("sprinkled repeats") {
      Node *p = cons(9, cons(7, cons(2, cons(5, cons(7, nullptr)))));
      stringstream actual;
      actual << removeOccurrences(7, p);
      CHECK( actual.str() == "{ 9 2 5 }" );
   }
   SUBCASE("special case empty list") {
      Node* p = nullptr;
      stringstream actual;
      actual << removeOccurrences(-98765, p);
      CHECK( actual.str() == "{ }" );
   }
   SUBCASE("many repeats at the head of the list") {
      Node* p = cons(9, cons(9, cons(9, cons(1, cons(2, nullptr)))));
      stringstream actual;
      actual << removeOccurrences(9, p);
      CHECK( actual.str() == "{ 1 2 }" );
   }
   SUBCASE("many repeats at the head of the list and last") {
      Node* p = cons(9, cons(9, cons(9, cons(1, cons(2, cons(9, nullptr))))));
      stringstream actual;
      actual << removeOccurrences(9, p);
      CHECK( actual.str() == "{ 1 2 }" );
   }
   SUBCASE("results in an empty list") {
      Node* p = cons(7, cons(7, cons(7, nullptr)));
      stringstream actual;
      actual << removeOccurrences(7, p);
      CHECK( actual.str() == "{ }" );
   }
}

TEST_CASE("mergeTwoOrderedLists removeOccurrences") {
   SUBCASE("first longer") {
      Node* p = cons(1, cons(3, cons(5, cons(6, cons(8, cons(9, nullptr))))));
      Node* q = cons(2, cons(4, cons(6, nullptr)));
      Node* merged = mergeTwoOrderedLists(p, q);
      stringstream p_ss, q_ss, merged_ss;
      p_ss << p;
      CHECK( p_ss.str() == "{ 1 3 5 6 8 9 }" );
      q_ss << q;
      CHECK( q_ss.str() == "{ 2 4 6 }" );
      merged_ss << merged;
      CHECK( merged_ss.str() == "{ 1 2 3 4 5 6 6 8 9 }" );
      // remove 6 ONLY from merged
      merged = removeOccurrences(6, merged);
      merged_ss = stringstream();
      merged_ss << merged;
      CHECK( p_ss.str() == "{ 1 3 5 6 8 9 }" );
      CHECK( q_ss.str() == "{ 2 4 6 }" );
      CHECK( merged_ss.str() == "{ 1 2 3 4 5 8 9 }" );
   }
   SUBCASE("second longer") {
      Node* p = cons(0, cons(1, cons(5, nullptr)));
      Node* q = cons(0, cons(1, cons(5, cons(7, nullptr))));
      Node* merged = mergeTwoOrderedLists(p, q);
      stringstream p_ss, q_ss, merged_ss;
      p_ss << p;
      CHECK( p_ss.str() == "{ 0 1 5 }" );
      q_ss << q;
      CHECK( q_ss.str() == "{ 0 1 5 7 }" );
      merged_ss << merged;
      CHECK( merged_ss.str() == "{ 0 0 1 1 5 5 7 }" );
      // remove 6 ONLY from merged
      merged = removeOccurrences(1, merged);
      merged_ss = stringstream();
      merged_ss << merged;
      CHECK( p_ss.str() == "{ 0 1 5 }" );
      CHECK( q_ss.str() == "{ 0 1 5 7 }" );
      CHECK( merged_ss.str() == "{ 0 0 5 5 7 }" );
   }
}


TEST_CASE("BONUS odds") {
   SUBCASE("typical length 5") {
      Node* p = cons(11, cons(22, cons(33, cons(44, cons(55, nullptr)))));
      stringstream actual;
      actual << odds(p);
      CHECK( actual.str() == "{ 11 33 55 }" );
   }
   SUBCASE("bordeline case one element") {
      Node* p = cons(-123456, nullptr);
      stringstream actual;
      actual << odds(p);
      CHECK( actual.str() == "{ -123456 }" );
   }
   SUBCASE("two elements") {
      Node* p = cons(-5, cons(-7, nullptr));
      stringstream actual;
      actual << odds(p);
      CHECK( actual.str() == "{ -5 }" );
   }
   SUBCASE("special case empty list") {
      Node* p = nullptr;
      stringstream actual;
      actual << odds(p);
      CHECK( actual.str() == "{ }" );
   }
}


TEST_CASE("BONUS evens") {
   SUBCASE("typical length 6") {
      Node* p = cons(11, cons(22, cons(33, cons(44, 
                cons(55, cons(66, cons(77, nullptr)))))));
      stringstream actual;
      actual << evens(p);
      CHECK( actual.str() == "{ 22 44 66 }" );
   }
   SUBCASE("bordeline case one element") {
      Node* p = cons(123456, nullptr);
      stringstream actual;
      actual << evens(p);
      CHECK( actual.str() == "{ }" );
   }
   SUBCASE("two element") {
      Node* p = cons(30, cons(40, nullptr));
      stringstream actual;
      actual << evens(p);
      CHECK( actual.str() == "{ 40 }" );
   }
   SUBCASE("special case empty list") {
      Node* p = nullptr;
      stringstream actual;
      actual << evens(p);
      CHECK( actual.str() == "{ }" );
   }
}


// copyright 2023 Gladys Monagan


