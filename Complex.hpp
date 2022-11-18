//
//  Complex.hpp
//  gp proj
//


#ifndef Complex_hpp
#define Complex_hpp

#include <stdio.h>
#include <iostream>
using namespace std;

class Complex // complex number
{
private:
    double imag; // imaginary value of point
    double real; // real value of point

public:
    ~Complex();
    Complex();
    Complex(const Complex&);
    Complex(double);
    Complex(double, double);
    double& operator[](const char*);

    friend const Complex operator*(const Complex&, const Complex&);
    friend const Complex operator/(const Complex&, const Complex&);
    friend const Complex operator+(const Complex&, const Complex&);
    friend const Complex operator-(const Complex&, const Complex&);
   
    friend double getMagnitude(const Complex&);
    friend ostream& operator << (ostream&, Complex&);

    class InputOutOfBoundsException
    {
    private:
        const char* errorMessage;
        const char* offendingIndex;

    public:
        InputOutOfBoundsException(const char *, const char *);
        const char* returnError();
        const char* returnOffendingIndex();
    };
};

#endif /* Complex_hpp */
