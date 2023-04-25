// Name: Takeshi Hashimoto
// Do not post anywhere

/*
g++ -pedantic -Wall -Wextra -std=c++17 univariate.cpp -o univariate
*/ 

#include <iostream>
#include <string>   // std::string

using std::cout, std::cin, std::endl, std::string, std::stringstream;

struct Univariate {
   int deg;    // the degree of the polynomial
   int* cffs; // an array of deg+1 coefficients in ascending order
};

// reads first the degree and then (degree + 1) coefficients
// makes a new struct and modifies the pointer p as p is passed by reference 
// returns the input stream in
std::istream& operator >> (std::istream& in, Univariate* &p);

// outputs the univariate with the variable 'x'
// returns the output stream out
std::ostream& operator << (std::ostream& out, const Univariate* p);
// outputs the term in an expression
void outputTerm(std::ostream& out, int* &Cffs, int pow, int deg);
// outputs the operator in an expression
void outputOperator(std::ostream& out, int* &Cffs, int pow, int deg);

// adds two univariates
// returns a pointer to a new struct which is their sum
Univariate* add(const Univariate* a, const Univariate* b);
// fills the sum of a and b in the C which has length d+1
void fillSumCffs(int d, int* &C, const Univariate* &a, const Univariate* &b);

// multiplies two univariates
// returns a pointer to a new struct which is their product
Univariate* times(const Univariate* a, const Univariate* b);
// fills the product of a and b in the C which has length d+1
void fillProductCffs(int d, int* C, const Univariate* &a, const Univariate* &b);

// returns to the heap the memory that had been allocated for the polynomial 
// and sets p to the nullptr
// note that p is passed by reference
void deleteUnivariate(Univariate* &p);
// deletes pointer pointing integer
// and sets it to the nullptr
void deleteIntPtr(int* &p);

// returns new pointer to univariate by asking user input
Univariate* listenUnivariateInput();
// returns true if user wants to continue the program
bool askContinueProgram();

// reads into the univariate pointed to by p
// reads the degree and then reads its coefficients in increasing degree of x
// assumes that the input is error free i.e. only integer values are
// entered and there is exactly degree+1 of them 
std::istream& operator >> (std::istream& in, Univariate* &p) {
   // delete p;
   p = new Univariate;
   int d;
   int *C;
   C = new int[d+1];
   cin >> d;
   for (int i = 0; i <= d; i++){
      cin >> *(C+i);
   }
   while(d > 0 && C[d] == 0) d--;
   p->deg = d;
   p->cffs = C;
   return in;
}


// outputs the univariate using the character 'x' as variable
// outputs an end-of-line afterwards
// ignore terms that have a zero coefficient (for pretty printing)
// deals with the zero univariate polynomial properly
// precondition:
//   p is not the nullptr
std::ostream& operator << (std::ostream& out, const Univariate* p) {
   if(p->deg == 0 && p->cffs[0] == 0){
      out << "0";
      return out;
   }
   int d = p->deg; 
   int *C = p->cffs;
   for(int i = 0; i <= d; i++){
      outputTerm(out, C, i, d);
   }
   return out;
}

// outputs the term in an expression
// out in format `{cff}*x^{pow}`
// if following term is positive, print ` + `, otherwise, print ` - `
// do not print the term if cff is zero
// 1*x^{pow} will be printed as x^{pow}
// {cff}*x^1 will be printed as {cff}*x
void outputTerm(std::ostream& out, int* &Cffs, int pow, int deg){
   int cff = *(Cffs+pow);
   cff = cff > 0 ? cff : -cff;

   if( cff == 0 )             return;
   if( cff != 1 || pow == 0 ) out << cff;
   if( pow != 0 && cff != 1 ) out << "*";
   if( pow != 0 )             out << "x";
   if( pow != 1 && pow != 0 ) out << "^" << pow;

   outputOperator(out, Cffs, pow, deg);
}

// if following term is positive, print ` + `, otherwise, print ` - `
// if the term is the last one, do not print the operator
void outputOperator(std::ostream& out, int* &Cffs, int pow, int deg){
   char oper = *(Cffs+pow+1) > 0 ? '+' : '-';
   if( pow != deg ) out << " " << oper << " ";
}

// adds two univariates pointed to by a and b
// precondition: 
//   a and b are well built polynomials
//   neither a nor b are the nullptr
// postcondition: 
//    returns a well built (newly created) polynomial which is the sum of a and b
Univariate* add(const Univariate* a, const Univariate* b) {
   int d = (a->deg > b->deg) ? a->deg : b->deg;

   int *C = new int[d+1];
   fillSumCffs(d, C, a, b);
   while(d > 0 && C[d] == 0) d--;

   Univariate *p = new Univariate();
   p->deg = d;
   p->cffs = C;
   return p;
}

// fills the sum of a and b in the C which has length d+1
// fill in the array C by adding two cffs which have same power of x
void fillSumCffs(int d, int* &C, const Univariate* &a, const Univariate* &b){
   for (int i = 0; i <= d; i++){
      int val = 0;
      if(i <= a->deg) val += a->cffs[i];
      if(i <= b->deg) val += b->cffs[i];
      *(C+i) = val;
   }
}

   
// multiply two univariates pointed to by a and by b 
// precondition: 
//   a and b are well built polynomials
//   neither a nor b are the nullptr
// postcondition: 
//    returns a well built polynomial which is the product of a and b
Univariate* times(const Univariate* a, const Univariate* b) {
   int d = a->deg + b->deg;
   int *C = new int[d+1];
   fillProductCffs(d, C, a, b);

   while(d > 0 && C[d] == 0) d--;
   Univariate *p = new Univariate();
   p->deg = d;
   p->cffs = C;
   return p;
}

// fills the product of a and b in the C which has length d+1
// by using nested for loop, multiply all combination of two univariates
// add the product to a proper position which is the addition of two powers
// x^2 * x^3 = x^5 because 2 + 3 = 5
void fillProductCffs(int d, int* C, const Univariate* &a, const Univariate* &b){
   for(int i = 0; i <= d; i++){
      *(C+i) = 0;
   }
   for(int i = 0; i <= a->deg; i++){
      for(int j = 0; j <= b->deg; j++){
         *(C+i+j) += a->cffs[i] * b->cffs[j];
      }
   }
}


// returns the memory allocated for the polynomial to the heap
// and set p to the nullptr
// precondition: 
//   p is a well built polynomial
// postcondition: 
//   p is set to nullptr
void deleteUnivariate(Univariate* &p) {
   deleteIntPtr(p->cffs);
   delete p;
   p = nullptr;
}

// returns the memory allocated for the polynomial to the heap
// and set p to the nullptr
// precondition: 
//   p is a well built polynomial
// postcondition: 
//   p is set to nullptr
void deleteIntPtr(int* &p){
   delete []p;
   p = nullptr;
}

// ask user to input the degree and coefficients
// return the pointer of univariate
Univariate* listenUnivariateInput(){
   cout << "Enter Degree, and coefficients of each degree from 0 to degree+1 separated by a space: ";
   Univariate *p1;
   p1 = new Univariate();
   cin >> p1;
   return p1;
}

// ask if user want to continue the program
// if user's input is not y or n, ask again recursively
bool askContinueProgram(){
   cout << "Do you want to continue this Program? (y/n): ";
   char x;
   cin >> x;
   if(x == 'y' || x == 'Y') return true;
   if(x == 'n' || x == 'N') return false;
   cout << "Enter y or n" << endl;
   return askContinueProgram();
}

// main method
int main () {
   bool isRunning = true;
   while(isRunning){
      Univariate* p1 = listenUnivariateInput();
      cout << p1 << endl;
      Univariate* p2 = listenUnivariateInput();
      cout << p2 << endl;

      cout << endl;
      cout << "Addition: " << add(p1, p2) << endl;
      cout << "Multiplication: " << times(p1, p2) << endl;
      cout << endl;

      deleteUnivariate(p1);
      deleteUnivariate(p2);

      isRunning = askContinueProgram();
   }
   
   return 0;
}

// copyright 2023 Gladys Monagan
