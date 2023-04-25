// Name:
// Student Number:
// A class to represent money with dollars and cents
// CPSC 1160, Do not post anywhere
#include "Cash.h"
#include <iostream>
#include <iomanip>
#include <string>

// create an object with d dollars and c cents
// precondition: |c| < 100
Cash::Cash(int d, int c) : cents(d * 100 + c){
}

// create an object with d dollars
// precondition: |d| < 100
Cash::Cash(int d): cents(d * 100){
}

// create an object with 0 dollars and 0 cents
Cash::Cash(): cents(0){
}

// getter method
// return the amount of money in the object as dollar
// 234 cents = 2.34 dollars
int Cash::getDollars() const{
   return cents / 100;
}

// getter method
// return the amount of cents of the object
int Cash::getCents() const {
   return cents % 100;
}

// return the amount of money of the object as double
// 432 cents = 4.32 
double Cash::getAmount() const {
   return cents / 100.0;
}

// setter method
// set cents by converting dollar into cents
void Cash::setDollarsCents(int d, int c) {
   cents = d * 100 + c;
}

// set cents with double value representing like $12.34 by converting it into cents value
void Cash::setDollarsCents(double amount) {
   cents = (int)(amount * 100);
}

// output with a decimal point (forced) and Cash::DIGITS_OF_CENTS digits for the cents
std::ostream& operator << (std::ostream& out, const Cash& cash) {
   int c = cash.getCents();
   int d = cash.getDollars();
   if(cash.cents < 0){
      out << "-";
      c *= -1;
      d *= -1;
   }
   out << "$" << d << ".";
   if (c < 10) out << "0";
   out << c;

   return out;
}

// if non numeric input is given, the istream enters a fail state
// assume that the user enters two integers
std::istream& operator >> (std::istream& in, Cash& cash) {
   int d, c;
   in >> d >> c;
   cash.setDollarsCents(d, c);
   return in;
}

// return true if both Cash objects have same amount of money
bool operator == (const Cash& cash1, const Cash& cash2) {
   return cash1.cents == cash2.cents;
}

// return true if left Cash object has less money
bool operator < (const Cash& cash1, const Cash& cash2) {
   return cash1.cents < cash2.cents;
}

// return true if right Cash object has less money
bool operator > (const Cash& cash1, const Cash& cash2) {
   return cash1.cents > cash2.cents;
}

// return new Cash that has the amount of money which is the sum of two objects's money
const Cash operator + (const Cash& cash1, const Cash& cash2) {
   int total = cash1.cents + cash2.cents;
   return Cash(0, total);
}

// return new Cash that has the amount of money which is the difference of two objects's money
const Cash operator - (const Cash& cash1, const Cash& cash2) {
   int total = cash1.cents - cash2.cents;
   return Cash(0, total);
}

// return new Cash that has the amount of money which is the product of two objects' money
const Cash operator * (const Cash& cash, int n) {
   int total = cash.cents * n;
   return Cash(0, total);
}

// return new Cash that has the amount of money which is the division of two objects' money
const Cash operator * (int n, const Cash& cash) {
   return cash * n;
}

//Bonus

// return new Cash that has the negative amount of money of the object' money
const Cash operator - (const Cash& cash){
   return 0 - cash;
}

// return new Cash that has the amount of money which is the division of two objects' money
// precondition n != 0
const Cash operator / (const Cash& cash, int n){
   int amount = cash.cents / n;
   return Cash(0, amount);
}

// returns the number of coins required to cover the cash
// precondition cash >= 0
int operator % (const Cash& cash, const Cash& coin){
   int numCoins = cash.cents / coin.cents;
   if(cash.cents % coin.cents != 0) numCoins++;
   return numCoins;
}