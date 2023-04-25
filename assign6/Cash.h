// Name: Takeshi Hashimoto
// Student Number: 100398623
// A class to represent a cash amount with dollars and cents
// CPSC 1160, Do not post anywhere
#ifndef CASH_H 
#define CASH_H

#include <iostream>
#include <string>
class Cash {
   public:
      // creates an instance worth $d dollars (d may be positive, negative, or 0)
      // plus or minus c cents (depending on whether c is positive, negative, or 0)
      // precondition: |cents| < 100
      Cash(int dollars, int cents);
      // creates an instance worth dollars (-100 < d < 100)
      Cash(int dollars);
      // creates an instance with 0 dollars, 0 cents
      Cash();

      // read two integers the first integer corresponding to the dollars
      // and the second integer corresponding to the cents
      // assume that the user enters exactly two integers (no error checking needed)
      friend std::istream& operator >> (std::istream& in, Cash&);
      // output in the form    $ddd.cc     with Cash::DIGITS_OF_CENTS 
      // after the fixed decimal point
      // there could possibly a negative sign before the $ sign
      friend std::ostream& operator << (std::ostream&, const Cash&);
      // return true if both Cash objects have same amount of money
      friend bool operator == (const Cash&, const Cash&);
      // return true if left Cash object has less money
      friend bool operator < (const Cash&, const Cash&);
      // return true if right Cash object has less money
      friend bool operator > (const Cash&, const Cash&);
      // return new Cash that has the amount of money which is the sum of two objects' money
      friend const Cash operator + (const Cash&, const Cash&);
      // return new Cash that has the amount of money which is the difference of two objects' money
      friend const Cash operator - (const Cash&, const Cash&);
      // return new Cash that has the amount of money which is the product of two objects' money
      friend const Cash operator * (const Cash&, int);
      // return new Cash that has the amount of money which is the division of two objects' money
      friend const Cash operator * (int, const Cash&);
      // return new Cash that has the negative amount of money of the object' money
      friend const Cash operator - (const Cash&);
      // return new Cash that has the amount of money which is the division of two objects' money
      // if there is remainder, it round off
      // eg) 43 / 3 => 14
      // precondition n != 0
      friend const Cash operator / (const Cash&, int n);
      // returns the number of coins required to cover the cash
      // precondition cash >= 0
      friend int operator % (const Cash& cash, const Cash& coin);
                
      // number of decimal places after the decimal point
      // I don't need this variable
      static const int DIGITS_OF_CENTS = 2;

      // return the amount of money as dollar
      int getDollars() const;
      // return the amount of money as cents
      int getCents() const;
      // return the amount of money as dollar
      double getAmount() const;
      // setter method
      // set cents by converting dollar into cents
      void setDollarsCents(int d, int c);
      // set cents with double value representing like $12.34 by converting it into cents value
      void setDollarsCents(double amount);

   private:
      int cents;
      
};

const Cash LOONIE(1);
const Cash TOONIE(2);
const Cash QUARTER(0, 25);
const Cash DIME(0, 10);
const Cash NICKEL(0, 5);

#endif   // CASH_H