// Name: Takeshi Hashimoto
// CPSC 1160 Assignment #2

#include <cmath>

// compute how many real roots there are given the quadratic equation a*x^2 + b*x + c
// and solve for these roots if possible
// precondition:
//   all real numbers for a, b, c. and reference for root1 and root2
// postcondition:
//    returns 0 for no real roots
//    returns 1 for one real root (the two real roots are equal)
//              the computed root is returned in root1
//    returns 2 for two real roots
//              the computed roots are returned in root1 and root2
const double EPSILON = 0.00001;
int getRoots(double a, double b, double c, double &root1, double &root2) {
    int d = pow(b, 2) - 4 * a * c;
    int numOfRoots;
    // liner expression
    if(a == 0 && b != 0){
        root1 = c / b;
        return 1;
    }
    // no roots
    if(abs(d) < EPSILON){
        numOfRoots = 1;
    } else if(d > 0){
        numOfRoots = 2;
    } else{
        return 0;
    }
    root1 = (-b + sqrt(d)) / (2 * a);
    root2 = (-b - sqrt(d)) / (2 * a);
    return numOfRoots;
}

