// Name: Takeshi Hashimoto
// Student Number: 100398623
// CPSC 1160 Assignment #3

#include <iostream>
#include <string>

using namespace std;

// precondition: n > 0
// CPSC 1160: if no second argument is passed, the default argument 
// for the stream is std::cout
void writeBackwardForward(unsigned int n, std::ostream& out = std::cout);

// precondition:
//   1 <= n <= declared size of the array A
int maximum(const int A[], int n);

// precondition:
//   0 <= n <= declared size of the array A
bool isStrictlyDescending(const int A[], int n);

// precondition:
//   1 <= n <= declared size of the array A
void swapPairsLeftToRight(int A[], int n);

// precondition:
//  two strings
short goesFirst(const string& strA, const string& strB);

// BONUS
// precondition:
//   0 <= n <= declared size of the array A
int minPosNum(const int A[], int n);

//------------------------------------------------------------------------------
// fill your code below 
// remove the cerr statement every time that you implement the function
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Write a number backward and forward
// precondition: n > 0
void writeBackwardForward(unsigned int n, std::ostream& out) {
    if(n <= 0){
        out << endl;
        return;
    }
    out << n % 10;
    writeBackwardForward(n / 10, out);
    out << n % 10;
}

//------------------------------------------------------------------------------
// Find the maximum value in the array. 
// precondition:
//   1 <= n <= declared size of the array A
// postcondition:
//   return the maximum value in the first n elements of A
int maximum(const int A[], int n) {
   if(n <= 1) return A[n-1];
    int max = maximum(A, n-1);
    if(A[n-1] > max) max = A[n-1];
    return max;
}

//------------------------------------------------------------------------------
// Check if the array is sorted to strictly descending
// precondition:
//   0 <= n <= declared size of the array A
// postcondition:
//   return true if the array is ordered strictly descending. else, return false
bool isStrictlyDescending(const int A[], int n) {
   if(n < 2) return true;
    return A[n-1] < A[n-2] && isStrictlyDescending(A, n-1);
}

//------------------------------------------------------------------------------
// Helper function, swap each adjacent value
// precondition:
//   1 <= n <= declared size of the array A, m is left index of swapping two value
void swapPairsLeftToRight(int A[], int n, int m){
    if(m+1 >= n) return;
    int temp = A[m];
    A[m] = A[m+1];
    A[m+1] = temp;
    swapPairsLeftToRight(A, n, m+2);
}

//------------------------------------------------------------------------------
// Swap each adjacent value
// precondition:
//   1 <= n <= declared size of the array A
void swapPairsLeftToRight(int A[], int n) {
   swapPairsLeftToRight(A, n, 0);
}

//------------------------------------------------------------------------------
// Helper function, Check which string goes first in a dictionary
// precondition:
//  two strings, 0 <= index <= min(strA.length(), strB.length())
// postcondition:
//   return positive number if strA goes first, negative for strB goes first. return 0 when two strings are same
short goesFirst(const std::string& strA, const std::string& strB, int index){
    if((int)strA.length() <= index || (int)strB.length() <= index){
        return (int)strB.length() - (int)strA.length();
    }
    char a = strA[index];
    char b = strB[index];
    if(a > 'Z') a = a - 'a' + 'A';
    if(b > 'Z') b = b - 'a' + 'A';
    if(a == b) return goesFirst(strA, strB, index + 1);
    return b - a;
}

//------------------------------------------------------------------------------
// Check which string goes first in a dictionary
// precondition:
//  two strings
// postcondition:
//   return positive number if strA goes first, negative for strB goes first. return 0 when two strings are same
short goesFirst(const string& strA, const string& strB) {
   return goesFirst(strA, strB, 0);
}

//------------------------------------------------------------------------------
// Find positive and minimum value in the array.
// precondition:
//   1 <= n <= declared size of the array A
// postcondition:
//   return minimum and positive value of the array. if no positive value, return zero
int minPosNum(const int A[], int n) {
    if(n == 0) return 0;
    if(n == 1) return A[n-1] > 0 ? A[n-1] : 0;
    int min = minPosNum(A, n-1);
    int val = A[n-1];
    if(min <= 0 && val <= 0)
        return 0;
    else if(min <= 0 || val <= 0)
        return min <= 0 ? val : min;
    return min < val ? min : val;
}