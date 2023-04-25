/* 
Author: Gladys Monagan 
DO NOT POST THIS ANYWHERE.
This code is copyrighted.
Use it exclusively for CPSC 1160 at Langara College in Vancouver
*/

#include "sparse_utils.h"
#include <sstream>    // std::stringstream
#include <map>        // map
#include <string>     // std::string
#include <iostream>   // std::cout std::cin
#include <fstream>    // std::ifstream std::ofstream
#include <limits>     // std::numeric_limits<std::streamsize>::max()

using std::istream, std::ostream, std::string, std::pair;

// output the commands available
void printCommandMenu(ostream& out) {
   out << "\n";
   out << "      ------------- choose a command --------------------------\n";
   out << "(i) - input the sparse polynomials f and g\n";
   out << "(a) - add the sparse polynomials f and g, namely, f + g\n";
   out << "(s) - subtract g from f  namely f - g \n";
   out << "(t) - times or multiply a scalar by f and another scalar by g\n";
   out << "(p) - print the sparse polynomials\n";
   out << "(c) - coefficients of terms when the degree is supplied\n";
   out << "(d) - degree of the sparse polynomial\n";
   out << "(r) - reset or restart the process with two new polynomials\n";
   out << "(g) - get the derivative of the polynomials i.e. differentiate\n";
   out << "(m) - mention or comment: the subsequent line is ignored\n";
   out << "(q) - quit the program\n";
   out << "      ---------------------------------------------------------\n"; 
}

// make an associative array of the character (that will be obtained from input)
// and its associated command
void buildCommands(std::map<char, Commands>& commands) {
   commands.insert(pair('i', INPUT));
   commands.insert(pair('a', SUM));
   commands.insert(pair('s', SUBTRACT));
   commands.insert(pair('t', MULTIPLY));
   commands.insert(pair('p', PRINT));
   commands.insert(pair('c', GET_COEFF));
   commands.insert(pair('d', DEGREE));
   commands.insert(pair('r', RESET));
   commands.insert(pair('m', MENTION));
   commands.insert(pair('g', DIFFERENTIATE));
   commands.insert(pair('q', QUIT));
}

// read from the input stream a string
// using the first letter of that string,
// retrieve the corresponding pair value which is of the enum type Commands
// if echo is true, the command string read is echoed out
// postcondition:
//    returns a command from Commands (including INVALID)
Commands getCommand(std::map<char, Commands>& commands, 
                    istream& in, bool echo, ostream& out) {
   out << "\ncommand: ";
   string commandStr;
   in >> commandStr;
   std::stringstream ss(commandStr);
   char ch;
   ss >> ch;
   if (echo) out << commandStr << "\n";  // echo what was read
   Commands cmd = INVALID;
   if (commands.find(ch) != commands.end()) cmd = commands[ch];
   return cmd;
}

// return true if the first letter of the string read matches 'y' or 'Y'
bool yesAnswer(istream &in, bool echo, ostream& out) {
   string answerStr;
   in >> answerStr;
   if (echo) out << answerStr << "\n";
   return (answerStr[0] == 'Y' || answerStr[0] == 'y');
}

// reset the input stream (possibly out of its fail state) and clear the buffer
// postcondition:
//    in is ready to read again
void clearClean(istream &in) {
   in.clear();
   in.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
}


// consume the end-of-line of the input stream
// read a line
// output the line if echo is true
void getLineOutputLine(istream& in, bool echo, ostream& out) {
   string line;
   std::getline(in, line); // consume the end-of-line
   std::getline(in, line);
   if (echo) out << line << "\n";
}

// copyright 2023 Gladys Monagan