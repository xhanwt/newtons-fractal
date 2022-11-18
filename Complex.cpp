#include <iostream>
#include <cmath>
#include "Complex.hpp"
using namespace std;

    Complex::Complex() : real(0.0), imag(0.0) {
		//cout << "Default complex constructor" << endl;
	}

    Complex::Complex(const Complex& c) : real(c.real), imag(c.imag)
	{
		//cout << "Copy complex constructor" << endl;
	}


	//HOW DO I CONVERT A DOUBLE INTO A COMPLEX NUMBER? 
	//example, passing in a sqrt(-9)
    Complex::Complex(double a) : real(a), imag(0.0)//PROBLEM 1: HOW TO IMPLEMENT THIS ?
	{
	}

    Complex::Complex(double a, double b) : real(b), imag(a)
	{
	}

    Complex::~Complex() {}

    Complex::InputOutOfBoundsException::InputOutOfBoundsException(const char* a, const char* b) : errorMessage(a), offendingIndex(b)
		{
			cout << errorMessage << ": " << b;
		}
		const char* Complex::InputOutOfBoundsException::returnError() {
			return errorMessage;
		}
		const char* Complex::InputOutOfBoundsException::returnOffendingIndex() {
			return offendingIndex;

		}

	double& Complex::operator[](const char* index)
	{
		if (strcmp(index, "real") == 0)
		{
			return real;
		}
		else if (strcmp(index, "imag") == 0)
		{
			return imag;
		}
		else
		{
			throw InputOutOfBoundsException("> Error: Input out of bound", index);
            
        }
	}


	const Complex operator*(const Complex& a, const Complex& b)
	{
		double i = (a.real * b.imag) + (a.imag * b.real);
		double r = (a.real * b.real) - (a.imag * b.imag);
		//return Complex(r, i);
		return Complex(i, r);
	}
	const Complex operator/(const Complex& a, const Complex& b)
	{
		double i = ((b.real * a.imag - a.real * b.imag) /
			(b.real * b.real + b.imag * b.imag));
		double r = ((a.real * b.real + a.imag * b.imag) /
			(b.real * b.real + b.imag * b.imag));
		return Complex(i, r);
		//    temp.image = image * c2.real+c2.image*real;

	}
	const Complex operator-(const Complex& a, const Complex& b)
	{
		double i = a.imag - b.imag;
		double r = a.real - b.real;
		return Complex(i, r);
	}
	const Complex operator+(const Complex& a, const Complex& b)
	{
		double i = a.imag + b.imag;
		double r = a.real + b.real;
		return Complex(i, r);
	}




	double getMagnitude(const Complex& c)
	{
		//Problem might lie here

		return abs(sqrt((c.real * c.real) + (c.imag * c.imag)));
	}
	ostream& operator <<(ostream& os, Complex& c)
	{
		return os << "real " << c.real << " - " << "imag " << c.imag;
	}




