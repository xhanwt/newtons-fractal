#include <iostream>
#include "Pixel.hpp"

using namespace std;

Pixel::Pixel() : red(0U), green(0U), blue(0U)
	{
		//cout << "Default Pixel constructor" << endl;
	}

Pixel::Pixel(const Pixel& p) : red(p.red), green(p.green), blue(p.blue)
	{
		//cout << "> Pixel Copy constructor" << endl;

	}

Pixel::Pixel(unsigned int r, unsigned int g, unsigned int b) : red(r), green(g), blue(b)
	{
		//cout << "> Pixel 3-args constructor" << endl;

	}

	//destructor
Pixel::~Pixel()
	{
		//cout << "> Pixel Destructor" << endl;

	}


	const unsigned int& Pixel::operator[](const char* i)
	{
		if (strcmp(i, "red") == 0)
		{
			return red;
		}
		else if (strcmp(i, "blue") == 0)
		{
			return blue;
		}
		else if (strcmp(i, "green") == 0)
		{
			return green;
		}
		{
			throw InputOutOfBoundsException("> Error: Index out of bound", i);
		}
	}





Pixel::InputOutOfBoundsException::InputOutOfBoundsException(const char* a, const char* b) : errorMessage(a), offendingIndex(b)
        {
            cout << errorMessage << ": " << b;
        }
const char* Pixel::InputOutOfBoundsException::returnError() {
            return errorMessage;
        }
const char* Pixel::InputOutOfBoundsException::returnOffendingIndex() {
            return offendingIndex;

        }
