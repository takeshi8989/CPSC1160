

/*

g++ -pedantic -Wall -Wextra -std=c++17 calculator.cpp -o calculator

*/

// We are assuming that the user enters numeric data i.e. that the old price
// and that new price are numeric.

#include <iostream>
#include <string>
////////////////////////////////////////////////////////////////////////////////
//
// it is terrible programming style to #include an implementation cpp file
//      we are only doing this at the beginning of the course 
//
////////////////////////////////////////////////////////////////////////////////
#include "inflation.cpp"

using std::cout, std::cin, std::endl, std::string;

// Name: Takeshi Hashimoto

// ask a user to input an item's price both one year ago and now.
// calculate the inflation rate using a function inflation, then print it
// precondition:  
//    none
// 
// postcondition:
//    print the inflation rate as percentage
void calculateInflation(){
   double prev;
   double current;
   do {
      cout << "Enter price from a year ago: ";
      cin >> prev;
      // negative or zero is not viable
      if(prev <= 0){
         cout << "Negative and zero value is invalid." << endl;
      }
   } while (prev <= 0);
   do {
      cout << "Enter current price of the same item: ";
      cin >> current;
      // for the current price, zero is acceptable because it might happen.
      if(current <= 0){
         cout << "Negative value is invalid." << endl;
      }
   } while (current < 0);
   double percentage = inflation(prev, current);
   cout << "The inflation rate is: " << percentage << "%" << endl;
}

// ask a user to input y or n to coninue the program
// if a user input y, repeat a process. otherwise, stop the program
int main() {
   string answer = "y";
   while(answer.compare("y") == 0){
      answer = "";
      calculateInflation();
      while(answer != "y" && answer != "n"){
         cout << "Want to calculate inflation rate again? (y/n): ";
         cin >> answer;
      }
   }
   return 0;
}



