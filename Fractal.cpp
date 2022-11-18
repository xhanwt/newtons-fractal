#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <cmath>
#include <algorithm>
#include "Fractal.hpp"
#include "Pixel.hpp"

using namespace std;




	Pixel Fractal::determinePixelColor(Complex Z)
	{
		Complex Znew;
		float tol = 1E-6;
		float diff = 1.0;
		float test = sqrt(3.0) / 2.0;
		unsigned int iter = 0U;
		int color = 0;
		while (iter < 512)
		{
			iter++;
			Znew = (Z - (((Z * Z * Z) - 1.0) / (3 * (Z * Z))));

			diff = getMagnitude(Z - Znew);
			Z = Znew;
			if (diff < tol)
			{

				color = maxIter - min(maxIter, iter);
				if (abs(Znew["imag"]) < tol)
				{
					return Pixel(color, 0, 0);
				}
				else if (abs(Znew["imag"] - test) < tol)
				{
					return Pixel(0, color, 0);
				}
				else if (abs(Znew["imag"] + test) < tol)
				{
					return Pixel(0, 0, color);
				}
			}
		}
		return Pixel(0, 0, 0);
	}

	void Fractal::makeNewtonFractal()
	{
        Complex Z;
		double step_height = 4.0 / rows;
		double step_width = 4.0 / cols;

		for (int j = 0; j < rows; j++)
		{
			for (int k = 0; k < cols; k++)
			{
				Z["imag"] = 2.0 - (j * step_height);
				Z["real"] = (k * step_width) - 2.0;
				grid[j][k] = determinePixelColor(Z);
			
			}
		}

	}

Fractal::~Fractal()
	{
		cout << "> Fractal destructor " << endl;
		//delete the first pointer
		for (int i = 0; i < rows; i++)
			delete[] grid[i];
		//delete the pointer to pointer
		delete[] grid;
	}

Fractal::Fractal() : cols(0), rows(0), grid(nullptr), maxIter(30)
	{
		cout << "> Fractal default constructor " << endl;
	}

Fractal::Fractal(const Fractal& f) : cols(f.cols), rows(f.rows), grid(nullptr), maxIter(f.maxIter)
	{
		cout << "> Fractal Copy constructor " << endl;
		if (grid != nullptr)
			for (int i = 0; i < rows; i++)
				delete[] grid[i];

		grid = new Pixel * [rows];

		for (int i = 0; i < rows; i++)
		{
			grid[i] = new Pixel[cols];
		}
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				grid[i][j] = f.grid[i][j];
	}

Fractal::Fractal(Fractal&& f): cols(f.cols), rows(f.rows), grid(nullptr), maxIter(30)
	{
		cout << "> Fractal Move constructor " << endl;
		//dynamically allocate mem for grid
		grid = f.grid;
		for (int i = 0; i < rows; i++)
		{
			f.grid[i] = nullptr;
		}
		f.grid = nullptr;
		f.cols = 0;
		f.rows = 0;

	}


Fractal::Fractal(unsigned int r, unsigned int c) : rows(r), cols(c), grid(nullptr), maxIter(30)
	{
        
		cout << "> Fractal 2-args constructor " << endl;
		//dynamically allocate mem for grid
		grid = new Pixel * [rows];//grid - ** Pixel, 
		//each row point to a col
		for (int i = 0; i < rows; i++)
		{
			grid[i] = new Pixel[cols];//grid[i] = new Pixel[columns]
			//each Pixel element of array columns will be assigned with Pixel object from determinePixelValue()
		}
		//makeNewtonFractals;
		cout << "> Now creating the Newton Fractal.." << endl;
		Complex Z;
		double step_height = 4.0 / rows;
		double step_width = 4.0 / cols;
 
		for (int j = 0; j < rows; j++)
		{
			for (int k = 0; k < cols; k++)
			{
				Z["imag"] = 2.0 - (j * step_height);
				Z["real"] = (k * step_width) - 2.0;
				//cout << "debug in makeNewtonFractal - Z value " << Z << endl;
				grid[j][k] = determinePixelColor(Z);//grid[j][k] = Pixel(a,b,c) - 3 arg constructor
           
                
			}
		}
	}

	const Fractal& Fractal::operator=(const Fractal& f)
	{
		cout << "> Fractal Assignment operator " << endl;

		if (this != &f)
		{
			cols = f.cols;
			rows = f.rows;
			
			//if grid is not pointing to null, point it to null
			if (grid != nullptr)
			{
				for (int i = 0; i < rows; i++)
					delete[] grid[i];
				delete[] grid;
			}
			//dynamically allocate mem for grid
			grid = new Pixel * [rows]; //cols is width and row is height
			for (int i = 0; i < rows; i++)
			{
				grid[i] = new Pixel[cols];//an array of cols Pixel object that carries r g b values
			}
			//deep copy 
			for (int i = 0; i < rows; i++)
				for (int j = 0; j < cols; j++)
					grid[i][j] = f.grid[i][j];

		}
		return *this;
	}

	Fractal& Fractal::operator=(Fractal&& f)
	{
        
		cout << "> Fractal Move assignment operator" << endl;
		if (this != &f)
		{
            swap(rows, f.rows);
            swap(cols, f.cols);
            swap(grid, f.grid);
		}
        
		return *this;
        
      
	}


ostream& operator<<(ostream& os, Pixel& p) {
    os << p["red"] << " " << p["green"] << " " << p["blue"] << " ";
    return os;
}


	void saveToPPM(Fractal& f, string n)
	{
		f.makeNewtonFractal();
		fstream file(n, ios::out);

		if (!file)
		{
			cout << "Error: Output file can not be open" << endl;
			exit(1);
		}
		cout << "Saving Fractal object to PPM file.." << endl;
		//Output header
		file << "P3" << endl << "# Newton Fractal project\n" << f.cols << " " << f.rows << endl << f.maxIter << endl;
        
		//output pixel to file forr each row and colum
        for (int i = 0; i < f.rows; i++){
			for (int j = 0; j < f.cols; j++)
            {
               
                file << f.grid[i][j];
            }
			}
		file.close();
	}

