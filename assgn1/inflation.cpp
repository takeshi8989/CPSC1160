// Name: Takeshi Hashimoto

// calculate the inflation given the oldPrice from a year ago and the newPrice
// precondition:  
// 
// postcondition:
//    returns double value: the calculated inflation rate as a percentage with 2 significant digits after the decimal point
#include<cmath>

double inflation(double oldPrice, double newPrice){
    const int decimalPlace = 2;
    double diff = newPrice - oldPrice;
    // as percentage
    double rate = 100 * diff / oldPrice;
    // 2 significant digits after the decimal point
    double roundPoint = pow(10, decimalPlace);
    rate = round(rate * roundPoint) / roundPoint;
    return rate;
}

