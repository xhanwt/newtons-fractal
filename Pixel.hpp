//
//  Pixel.hpp
//  gp proj
//


#ifndef Pixel_hpp
#define Pixel_hpp

#include <stdio.h>
#include <iostream>

using namespace std;

class Pixel
{
private:
    unsigned int blue;
    unsigned int green;
    unsigned int red;

public:
    ~Pixel();
    const unsigned int& operator[](const char*);
    Pixel();
    Pixel(const Pixel&);
    Pixel(unsigned int, unsigned int, unsigned int);
    class InputOutOfBoundsException
    {
    private:
        const char* errorMessage;
        const char* offendingIndex;

    public:
        InputOutOfBoundsException(const char *, const char *);
        const char* returnError();
        const char* returnOffendingIndex();
        friend ostream& operator<<(ostream&, Pixel&);
    };
};

#endif /* Pixel_hpp */
