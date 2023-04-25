#include "Point.h"
#include <iostream>
using namespace std;

int main(){
    Point p(1,2);
    cout << p.coordX;
    return 0;
}

// g++ -Wall -c Point.cpp -o Point.o
// g++ -Wall -std=c++17 -c triangle.cpp -o triangle.o