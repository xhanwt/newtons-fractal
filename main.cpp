/*
 CMPT_1209 Lab Proj
 Group members:
 Chris gursche
 Sarah Vaily
 Han Win Tun
 Jaoquin

 */

#include "Fractal.hpp"
#include "Pixel.hpp"
#include "Complex.hpp"
using namespace std;

Fractal testMoveConstructor(unsigned int rows, unsigned int cols)
{
    Fractal&& temp = Fractal(rows, cols);
    
    return  temp;
}

int main()
{
	Fractal m1(2000U, 2000U), m2, m3;
	saveToPPM(m1, "newton1-Scrap.ppm");

	m2 = Fractal(m1);
	saveToPPM(m1, "newton2-Scrap.ppm");

	m3 = testMoveConstructor(600U, 800U);
	saveToPPM(m3, "newton3.ppm"); 

	return 0;
}
