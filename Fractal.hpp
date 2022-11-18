//
//  Fractal.hpp
//  gp proj
//

#ifndef Fractal_hpp
#define Fractal_hpp

#include <stdio.h>

#include "Pixel.hpp"
#include "Complex.hpp"

class Fractal
{
private:
    unsigned int cols;
    unsigned int rows;
    const unsigned int maxIter = 30;
    Pixel** grid;
public:
    ~Fractal();
    Pixel determinePixelColor(Complex);
    Fractal();
    Fractal(const Fractal &);
    Fractal(Fractal &&);
    Fractal(unsigned int, unsigned int);
    void makeNewtonFractal();
    const Fractal& operator=(const Fractal&);
    Fractal& operator=(Fractal&&);
    
    friend void saveToPPM(Fractal&, string);
};

#endif /* Fractal_hpp */
