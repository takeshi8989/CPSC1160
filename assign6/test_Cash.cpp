// Test the class Cash by Gladys Monagan
// Because the names of the accessor functions were not given in the 
// assignment, this test file would need to be expanded instead of having to
// "eyeball" the answer: better to do doctest
// CpSc 1160

#include "Cash.h"
#include <iostream>
#include <string>
using std::cout, std::cin, std::endl;
using std::string;

// equal tests to see if x and y are equal
// the minus operator needs to have been implemented correctly
bool equal(const Cash& x, const Cash& y){
   return (x-y) == Cash();
}

void testEqual(const std::string& str, const Cash& x, const Cash& y) {
   cout <<  "\ncompare " << x << " with " << y;
   if (!equal(x,y))
      cout << "ERROR:" << x << " should be equal to " << y << endl;
   else
      cout << " with expected value of " << str << endl;
}

// compare dollars and cents with expected values
void compareValues(int dollars, int cents, int expected_dollars, int expected_cents){
   cout <<  "\ncompare " << " dollar and cents" << endl;
   if (dollars != expected_dollars)
      cout << "ERROR:" << dollars << " should be equal to " << expected_dollars << endl;
   else
      cout << " with expected value of dollars: " << expected_dollars << endl;
   if (cents != expected_cents)
      cout << "ERROR:" << cents << " should be equal to " << expected_cents << endl;
   else
      cout << " with expected value of centes: " << expected_cents << endl;
}

// test the constructors and the output operator
// compareValues would presumably use the accessor functions
void testConstructors() {   
   // test the no-arg constructor
   Cash m = Cash(); 
   cout << endl;
   cout << "Cash()   \t" << m << endl;
   cout << "expecting \t" << "$0.00" << endl;
   int expected_dollars = 0;
   int expected_cents = 0;
   compareValues(m.getDollars(), m.getCents(), expected_dollars, expected_cents);
   cout << endl;
   
   // positive dollars, positive cents
   Cash a(7, 83);
   cout << "Cash(7, 83) \t" << a << endl;
   cout << "expecting    \t" << "$7.83" << endl;
   expected_dollars = 7;
   expected_cents = 83;
   compareValues(a.getDollars(), a.getCents(), expected_dollars, expected_cents);
   cout << endl;
   
   // 0  dollars, negative cents
   Cash b(0, -32);
   cout << "Cash(0, -32)\t" << b << endl;
   cout << "expecting    \t" << "-$0.32" << endl;
   expected_dollars = 0;
   expected_cents = -32;
   compareValues(b.getDollars(), b.getCents(), expected_dollars, expected_cents);
   cout << endl;
   
   // 0  dollars, positive cents
   Cash c(0, 99);
   cout << "Cash(0, 99)\t" << c << endl;
   cout << "expecting   \t" << "$0.99" << endl;
   expected_dollars = 0;
   expected_cents = 99;
   compareValues(c.getDollars(), c.getCents(), expected_dollars, expected_cents);
   cout << endl;
   
   // negative dollars, negative cents
   Cash d{-10, -21};
   cout << "Cash d{-10, -21}\t" << d << endl;
   cout << "expecting        \t" << "-$10.21" << endl;
   expected_dollars = -10;
   expected_cents = -21;
   compareValues(d.getDollars(), d.getCents(), expected_dollars, expected_cents);
   cout << endl;
   
   // negative dollars, positive cents
   Cash e = Cash{-10, 25};
   cout << "Cash{-10, 25}\t" << e << endl;
   cout << "expecting     \t" << "-$9.75" << endl;
   expected_dollars = -9;
   expected_cents = -75;
   compareValues(e.getDollars(), e.getCents(), expected_dollars, expected_cents);
   cout << endl;
   
   // positive dollars, negative cents
   Cash f{8, -13};
   cout << "Cash f{8, -13}\t" << f << endl;
   cout << "expecting     \t" << "$7.87" << endl;
   expected_dollars = 7;
   expected_cents = 87;
   compareValues(f.getDollars(), f.getCents(), expected_dollars, expected_cents);
   cout << endl;
   
   // negative dollars, positive cents
   Cash g(-2, 92); 
   cout << "Cash g(-2, 92)\t" << g << endl;
   cout << "expecting     \t" << "-$1.08" << endl;
   expected_dollars = -1;
   expected_cents = -8;
   compareValues(g.getDollars(), g.getCents(), expected_dollars, expected_cents);
   cout << endl;
}

// note the symmetry expected
void testAddition() {
   cout << "\ntesting addition..........";
   Cash m = Cash(12, 99);
   testEqual("25.99", m + 13, 13 + m);
   m.setDollarsCents(-12, 0);
   testEqual("1.00", m + 13, 13 + m);
}

// note the symmetry expected
void testSubtraction() {
   cout << "\ntesting subtraction..........";
   Cash m = Cash(12, 1);
   testEqual("-$0.99", m - 13, Cash(0, -99));
   
   m.setDollarsCents(-9, 99);
   testEqual("-$17.01", m - 9, Cash(-17,-1));

   m = Cash(12, 1);
   testEqual("-$5.01", (7 - m), Cash(-6, 99));
}

void testMultiplication() {
   cout << "\ntesting multiplication..........";
   Cash m(-3, -27);
   testEqual("$3.27", m * -1, Cash() - m);
   testEqual("$3.27", -1 * m, Cash() - m);

   testEqual("-$6.54", m * 2, Cash(-6, -54));
   m = Cash(0, 3);
   testEqual("$3.00", Cash(3, 0), m * 100);
   testEqual("$3.00", Cash(3, 0), 100 * m);
   m = m * 2 * 5;
   testEqual("$30.00", Cash(30), m * 100);
}


int main() {
   // from assignment sheet
   Cash m0(0, -32) ;
   cout << m0 << "\texpecting -$0.32 " << endl;
   Cash m1(-10, -21);
   cout << m1 << "\texpecting -$10.21 " << endl;
   Cash m2(-10, 25); 
   cout << m2 << "\texpecting -$9.75 " << endl;

   testConstructors();
   testAddition();
   testSubtraction();

   return 0;
}

// copyright 2023 Gladys Monagan 

