// Name: Takeshi Hashimoto
// CPSC 1160 Assignment #2 

/*
g++ -pedantic -Wall -Wextra  -std=c++17 solver.cpp -o solver
*/

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// it is terrible programming style to #include an implementation cpp file    //
//      do not do this in general, only at the beginning of the course        //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
#include "equation.cpp"

#include <iostream>
#include <string>
using std::cout, std::cin, std::string, std::endl;

void printExpression(double a, double b, double c);

void printResult(double a, double b, double c, double root1, double root2, int numOfRoots);

// ask the user 
int main() {
   double a, b, c;
   double root1, root2;
   string answer = "y";
   while(answer.compare("y") == 0){
      answer = "";
      cout << "Enter a, b, c: ";
      cin >> a >> b >> c; 
      int numOfRoots = getRoots(a, b, c, root1, root2);

      printExpression(a, b, c);
      printResult(a, b, c, root1, root2, numOfRoots);

      // continue or not
      while(answer != "y" && answer != "n"){
         cout << "continue? (y/n): ";
         cin >> answer;
      }
      cout << "\n";
   }
   return 0;
}

// print an expression f(x) with given values a, b, and c
// precondition:
//   all real numbers for a, b, c
void printExpression(double a, double b, double c){
   if(!(a == 0 && b == 0 && c == 0)){
      cout << "f(x) = ";
   }
   if(a == 1) cout << "x^2";
   else if(a != 0) cout << a << "x^2";

   if(a != 0 && b != 0) cout << " + ";
   if(b == 1) cout << "x";
   else if(b != 0) cout << b << "x";

   if((a != 0 || b != 0) && c != 0) cout << " + ";
   if(c != 0) cout << c;
   cout << endl;
}

// print a result of equation f(x)
// precondition:
//   all real numbers for a, b, c. and its roots and number of roots
void printResult(double a, double b, double c, double root1, double root2, int numOfRoots){
   if(a == 0 && b == 0 && c == 0) cout << "invalid equation." << endl;
   // f(x) = bx + c
   else if(a == 0 && b != 0){
      cout << "liner function" << endl;
      cout << "x = " << root1 << endl;
   }
   // f(x) = c
   else if(a == 0){
      cout << "constant." << endl;
   }
   else if(numOfRoots == 1) cout << "x = " << root1 << endl;
   else if(numOfRoots > 0) cout << "x = " << root1 << ", " << root2 << endl;
   else cout << "no roots" << endl;
}
