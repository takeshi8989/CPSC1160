/* 
Author: Gladys Monagan 
DO NOT POST THIS ANYWHERE.
This code is copyrighted.
Use it exclusively for CPSC 1160 at Langara College in Vancouver


Program to use (test) sparse polynomials with a user interface. 
 Commands supported 
 -> input two sparse polynomials
 -> calculate their sum
 -> calculate their difference
 -> multiply a polynomial by a scalar
 -> print the polynomial
 -> get the coefficient of a term 
 -> get the degree of the polynomial
 -> possibly differentiate

usage: test_sparse
renders a command driver interactive session

usage: test_sparse -batch < cmds.txt 
will take the input from cmds.txt and will output to the console
cmds.txt is here the name of an input file

usage: test_sparse -batch < cmds.txt > outFile.txt
to run program non-interactively obtaining data from cmds.txt
cmds.txt is here the name of an input file
putting the output into outFile.txt
outFile.txt is here the name of an output file

*/

#include "sparse.h"
#include "sparse_utils.h"
#include <functional> // std::greater
#include <map>        // std::map
#include <iostream>   // std::cout std::cin
#include <string>     // std::string
using std::istream, std::ostream, std::cout, std::endl;
using std::string;

// we have the polynomial f and the polynomial g
// sometimes we have a third polynomial which results 
// from adding f + g or from subtracting f - g 
// how do we know if the third polynomial exists? 
// we lug around a variable called third: third is of SparseType
// when third is NEMO, rSparse does not exist
// when third is PLUS, rSparse results from f + g 
// when third is MINUS, rSparse results from f - g 
enum SparseType { NEMO, PLUS, MINUS };

// output a polynomial with its label
// precondition:
//    the operator << has been defined (overloaded) for Sparse
void printSparsePoly(const string& label,const Sparse& poly,ostream& out=cout) {
   out << label << " = " << poly << endl;
}

// output a polynomial with its label and depending on third,
// output it as an addition or subtraction (or do nothing if third is NEMO)
// precondition:
//    the operator << has been defined (overloaded) for Sparse
void printSparsePoly(const Sparse& poly,SparseType& third,ostream& out=cout) {
   if (third == PLUS) printSparsePoly("f + g", poly, out);
   if (third == MINUS) printSparsePoly("f - g", poly, out);
}

// output the polynomial's degree with its label
void printDegree(const string& label, const Sparse& poly,ostream& out=cout) {
   out << "degree of " << label << " = " << poly.degree() << endl;
}

// output the polynomials a and b
// precondition:
//    fSparse, gSparse are bona fide polynomials (including the zero polynomial)
void printSparsePolys(const Sparse& fSparse,const Sparse& gSparse, ostream& out=cout) {
   printSparsePoly("f", fSparse, out);
   printSparsePoly("g", gSparse, out);
}

// differentiate and print the differentiated polynomials
// the differentiated polynomials (the results) are destroyed after they
// are printed, they go out of scope
void differentiate(const Sparse& fSparse, const Sparse& gSparse, ostream& out=cout) {
   printSparsePoly("df/dx", fSparse.derivative(), out);
   printSparsePoly("dg/dx", gSparse.derivative(), out);
   // the destructors of the polynomials 
   // resulting from fSparse.derivative() and gSparse.derivative() are called
}

// print the coefficient and a blurb
void printCoeffDegree(string label, int coeff, int deg, ostream& out=cout) {
   out << "in " << label << ",\t" << coeff;
   out << " is the coefficient of the term of degree " << deg << endl;
}

// read in the info on the first sparse polynomial fSparse
// if successful, read in the info on the second sparse polynomial gSparse
// expected for each sparse polynomial is
// -> the number of terms
// -> pairs of numbers for the coefficient of the term and the degree
// precondition:
//    fSparse, gSparse, rSparse are the zero polynomials
//    the operator << has been defined for Sparse
//    reading into a polynomial consists of
//        an integer n for the number of terms
//        coefficient degree pairs n times    
// postcondition: 
//    fSparse, gSparse are bona fide sparse polynomials 
//    the input stream is cleared in case of having read non-numeric input
//    return true if the reading was successful, false otherwise
bool inputSparse(std::istream& in, Sparse& fSparse, Sparse& gSparse, 
                           ostream& out=cout) {
   bool successfulRead = true;
   out << "For polynomial f, enter # of terms, coeff degree, coeff, degree, ...\n";
   if (!(in >> fSparse)) {
      out << "ERROR in reading polynomial\n";
      successfulRead = false;
   }
   if (successfulRead) {
      out << "For polynomial g, enter # of terms, ";
      out << "coeff degree, coeff, degree, ...\n";

      if (!(in >> gSparse)) {
         out << "ERROR in reading polynomial\n";
         successfulRead = false;
      }
   }
   clearClean(in);
   return successfulRead;
}

// read in the degree of the term whose coefficients will be printed
// for fSparse, gSparse and possibly the third poly 
// do not output anything if third == NEMO
// if echo is true, the degree read is echoed out
// postcondition:
//    the input stream is cleared in case of having read non-numeric input
void getCoeffs(istream &in, const Sparse& fSparse, const Sparse& gSparse, 
               const Sparse& rSparse, SparseType third, bool echo, ostream& out=cout) {
   do {
      int degree;
      out << "Enter the degree of term whose coefficient you want ";
      in >> degree;
      if (echo) out << degree << endl;
      printCoeffDegree("f", fSparse.coefficient(degree), degree);
      printCoeffDegree("g", gSparse.coefficient(degree), degree);
      if (third == PLUS) 
         printCoeffDegree("f+g", rSparse.coefficient(degree), degree);
      if (third == MINUS) 
         printCoeffDegree("f-g", rSparse.coefficient(degree), degree);
      out << "continue getting coefficients? (y/n): ";
   } while (yesAnswer(in, echo, out));
   clearClean(in);
}

// read in the scalar values used to multiply fSparse and gSparse 
// if echo is true, the constant read is echoed out
// postcondition:
//    fSparse is multiplied by the scalar value read
//    gSparse is multiplied by the scalar value read
//    the input stream is cleared in case of having read non-numeric input
void multiplyPolys(istream &in, Sparse& fSparse, Sparse& gSparse, 
                   bool echo, ostream& out=cout) {
   int k;
   out << "enter the constant (scalar) to multiply f by: ";
   in >> k; if (echo) out << k << endl;
   int c;
   out << "enter the constant (scalar) to multiply g by: ";
   in >> c; if (echo) out << c << endl;

   fSparse = fSparse * k;
   printSparsePoly("f = " + std::to_string(k) + " * f", fSparse, out);
   gSparse = gSparse * c;
   printSparsePoly("g = " + std::to_string(c) + " * g", gSparse, out);
   clearClean(in);
}

// process the command 
//   read in fSparse and gSparse 
//   compute the polynomial which is the sum of fSparse and gSparse
//   print fSparse, gSparse and rSparse
//   get the coefficients of terms in fSparse, gSparse and rSparse 
//   print if an error was made
// precondition:
//   the input operator >> has been over for Sparse
//   the output operator << has been over for Sparse
// postcondition:
//   return true when the command is RESET or QUIT, returns false otherwise
//   third is set to PLUS or MINUS depending on whether an 
//   addition or subtraction else it stays as NEMO
bool process(istream& in, Commands command, Sparse& fSparse,  Sparse& gSparse, 
             Sparse& rSparse, SparseType& third, bool echo, ostream& out=cout) {
   bool doneProcessing = false;
   switch (command) {
      case INPUT:
         // using the overloaded operator << of Sparse
         if (inputSparse(in, fSparse, gSparse, out)) 
            printSparsePolys(fSparse, gSparse, out);
         break;
      case SUM:
         third = PLUS;
         printSparsePolys(fSparse, gSparse, out);
         rSparse = fSparse + gSparse;
         printSparsePoly(rSparse, third, out);
         break;
      case SUBTRACT:
         third = MINUS;
         printSparsePolys(fSparse, gSparse, out);
         rSparse = fSparse - gSparse;
         printSparsePoly(rSparse, third, out);
         break;
      case MULTIPLY:
         third = NEMO; // because fSparse and gSparse are modified
         multiplyPolys(in, fSparse, gSparse, echo, out);
         break;
      case PRINT:
         printSparsePolys(fSparse, gSparse, out);
         printSparsePoly(rSparse, third, out);
         break;
      case GET_COEFF:
         // ask for the degree of the term whose coefficient will be returned
         getCoeffs(in, fSparse, gSparse, rSparse, third, echo, out);
         break;
      case DEGREE:
         printDegree("f", fSparse, out);
         printDegree("g", gSparse, out);
         if (third == PLUS) printDegree("f + g", rSparse, out);
         if (third == MINUS) printDegree("f - g", rSparse, out); 
         break;
      case RESET:
         // will be used to restart the process eliminating the polynomials
         doneProcessing = true;
         break;
      case MENTION:
         getLineOutputLine(in, echo, out);
         break;
      case DIFFERENTIATE:
         differentiate(fSparse, gSparse, out);
         break;
      case QUIT:
         // the task is done
         doneProcessing = true;
         break;
      case INVALID:
         out << "invalid command, please input again!\n";
         break;
      default:
         std::cerr << "**** ERROR in the switch of process ***\n";
         break;
   }
   return doneProcessing;
}

// determine if the "-batch" option was entered meaning that the
// session is NOT interactive and the input will be echoed
// return true if the string matches -batch, false otherwise
bool echoOption(string option) {
   return option == "-batch";
} 

// if the session is interactive, echo the input
// for each pair of polynomials read, process the command and
// finish once the command is quit
// right now input is from std::cin and output from std::out
int main(int argc, char* argv[]) {
   bool echo = false;
   if (argc > 1) echo = echoOption(argv[1]);
   std::map<char, Commands> commands;
   buildCommands(commands);

   istream& in = std::cin;
   ostream& out = std::cout;
   Commands cmd;
   do {
      if (!echo) printCommandMenu(out);

      // process two polynomials (and their sum, difference, multiplication)
      bool doneWithSparses = false;
      Sparse f, g, sum;
      SparseType third = NEMO;
      do {
         cmd = getCommand(commands, in, echo, out);
         doneWithSparses = process(in, cmd, f, g, sum, third, echo, out);
      } while (!doneWithSparses); // calls the destructors
   } while (cmd != QUIT); 
   return 0;
}

// copyright 2023 Gladys Monagan

