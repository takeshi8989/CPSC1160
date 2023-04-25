// Assignment #9, CPSC 1160
// Author: Gladys Monagan
// Do not post anywhere

#include <iostream>
#include <cstdlib>
#include <string>
#include "Bag.h"
using std::string, std::cout, std::endl;

void test_isEmpty_size(Bag& bag) {
   cout << "empty bag actual: " <<  bag << endl; 
   cout << "expecting:        " << Bag::START << Bag::END << endl;
   cout << "actual    bag size = " << bag.size() << endl;
   cout << "expecting bag size = 0\n";
}

void test_insert(Bag& bag) {
   cout << endl;
   cout << "before insert \n";
   cout << "bag     = " << bag << endl; 
   bag.add(3);
   bag.add(1);
   bag.add(9); 
   bag.add(3);
   bag.add(7);
   bag.add(5);
   cout << "after insert\n";
   cout << "actual   = " << bag << endl; 
   string expected = 
      Bag::START 
      + "1" + Bag::SEP
      + "3" + Bag::SEP
      + "3" + Bag::SEP
      + "5" + Bag::SEP
      + "7" + Bag::SEP
      + "9" + Bag::SEP
      + Bag::END;
   cout << "expected = " << bag << endl;
}

void test_in(Bag& bag) {
   cout << endl;
   if (!(2 < bag)) 
      cout << "2 is not in the bag " << bag << " as expected\n";
   else
      cout << "ERROR: 2 is in the bag " << bag << endl;
   if (7 < bag)
      cout << "7 is in the bag " << bag << " as expected\n";
   else
      cout << "ERROR: 7 is NOT in the bag " << bag << endl;
}

void test_size(Bag& bag) {
   cout << endl;
   cout << "bag size = " << bag.size() << endl;
   cout << "expecting bag size =  6\n";
}

void test_remove(Bag& bag) {
   cout << endl;
   cout << "before remove\n";
   cout << "bag     = " << bag << endl; 
   bag.remove(7);
   bag.remove(1);
   bag.remove(9);
   bag.remove(10);
   cout << "after remove\n";
   cout << "actual   = " << bag << endl; 
   string expected = 
      Bag::START 
      + "3" + Bag::SEP
      + "3" + Bag::SEP
      + "5" + Bag::SEP
      + Bag::END;
   cout << "expected = " << expected << endl; 
}

void test_insert(Bag& bag, Bag& other) {
   cout << endl;
   cout << "before insert of bag\n";
   cout << "bag      = " << bag << endl; 
   bag.add(1);
   bag.add(7);
   bag.add(3);
   cout << "after insert into bag\n";
   cout << "actual   = " << bag << endl; 
   string expected = 
      Bag::START 
      + "1" + Bag::SEP
      + "3" + Bag::SEP
      + "7" + Bag::SEP
      + Bag::END;
   cout << "expected = " << bag << endl;

   cout << "before insert of other \n";
   cout << "other   = " << other << endl; 
   other.add(3);
   other.add(5);
   other.add(4);
   cout << "after insert of other \n";
   cout << "other    = " << other << endl; 
   expected = 
      Bag::START 
      + "3" + Bag::SEP
      + "5" + Bag::SEP
      + "4" + Bag::SEP
      + Bag::END;
   cout << "expected = " << other << endl;
   cout << "after insert into bag\n";
   cout << "actual   = " << bag << endl; 
   expected = 
      Bag::START 
      + "1" + Bag::SEP
      + "3" + Bag::SEP
      + "3" + Bag::SEP
      + "5" + Bag::SEP
      + "7" + Bag::SEP
      + "9" + Bag::SEP
      + Bag::END;
   cout << "expected = " << bag << endl;
}

// 19 should be inserted into the local copy
void test_copy_constructor_pass_by_value(Bag copy) {
   copy.add(0);
   cout << "local copy when passed by value\n";
   cout << "actual   = " << copy << endl; 
   string expected = 
      Bag::START 
      + "0" + Bag::SEP
      + "1160" + Bag::SEP
      + "2150" + Bag::SEP
      + Bag::END;
   cout << "expected = " << expected << endl;
}

void test_destructor() {
   cout << endl;
   Bag local;
   local.add(-77);
   local.add(-88);
   std::cout << "a local bag has values " << local << "\n";
   string expected = 
      Bag::START 
      + "-88" + Bag::SEP
      + "-77" + Bag::SEP
      + Bag::END;
   cout << "expected = " << expected << endl; 
   // the destructor of local is called
}

void test_equal() {
   Bag a;
   Bag b;
   if (a == b)
      cout << a << " is equal to " << b << " as expected" << endl;
   else
      cout << "ERROR " << a << "SHOULD HAVE BEEN equal to " << b << endl;
   b.add(3);
   a.add(3);
   if (a == b)
      cout << a << " is equal to " << b << " as expected" << endl;
   else
      cout << "ERROR " << a << "SHOULD HAVE BEEN equal to " << b << endl;
   b.add(5);
   a.add(5);
   if (a == b)
      cout << a << " is equal to " << b << " as expected" << endl;
   else
      cout << "ERROR " << a << "SHOULD HAVE BEEN equal to " << b << endl;
   if (a == a)
      cout << a << " is equal to " << a << " as expected" << endl;
   else
      cout << "ERROR " << a << "SHOULD HAVE BEEN equal to " << a << endl;
   cout << endl;
}

int main() {
   // passing bag by reference to prevent calling the destructor
   // BUT it makes it hard to debug to keep track of what happened in the
   // previous functions: the order of the function calls is significant
   
   Bag bag;
   test_isEmpty_size(bag);
   test_insert(bag);
   test_in(bag);
   test_size(bag);
   test_remove(bag);
   Bag other;
   test_insert(bag, other);
   test_destructor();
   cout << endl;
   Bag d;
   d.add(1160);
   d.add(2150);
   cout << "before calling the function = " << d << endl;
   test_copy_constructor_pass_by_value(d);
   cout << "after calling the function  = " << d << endl;
   cout << "which is the same as before calling the function\n" << endl;

   test_equal();
  
   return 0;
}

// copyright 2023 Gladys Monagan
