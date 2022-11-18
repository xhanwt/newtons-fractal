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
		double tol = 1E-6;
        double diff = 1.0;
        double test = sqrt(3.0) / 2.0;
		unsigned int iter = 0U;
        unsigned int color = 0U;
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
		cout << "> Destructor called... " << endl;
		//delete the first pointer
		for (int i = 0; i < rows; i++)
			delete[] grid[i];
		//delete the pointer to pointer
		delete[] grid;
	}

Fractal::Fractal() : cols(0), rows(0), grid(nullptr), maxIter(30)
	{
		cout << "> Default constructor called... " << endl;
	}

Fractal::Fractal(const Fractal& f) : maxIter(30)
	{
		cout << "> Copy constructor called... " << endl;
        
      
        
      
        cols = f.cols;
        rows = f.rows;

		grid = new Pixel * [rows];

		for (int i = 0; i < rows; i++)
		{
			grid[i] = new Pixel[cols];
		}
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				grid[i][j] = f.grid[i][j];
        
        
	}

Fractal::Fractal(Fractal&& f): cols(f.cols), rows(f.rows), maxIter(30)
	{
		cout << "> Move constructor called..." << endl;
        
       
        
        grid = new Pixel * [rows];

        for (int i = 0; i < rows; i++)
        {
            grid[i] = new Pixel[cols];
        }
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                grid[i][j] = f.grid[i][j];
        
        
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
        
		cout << "> Two-arg constructor called... " << endl;
        
        // clean
        if (grid != nullptr)
        {
            for (int i = 0; i < rows; i++)
                delete[] grid[i];
            delete[] grid;
        }
        
		//dynamically allocate mem for grid
		grid = new Pixel * [rows];
        
		for (int i = 0; i < rows; i++)
		{
			grid[i] = new Pixel[cols];
		}
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
				grid[j][k] = determinePixelColor(Z);
           
                
			}
		}
	}

	const Fractal& Fractal::operator=(const Fractal& f)
	{
		cout << "> Assignment operator called... " << endl;

		if (this != &f)
		{
			cols = f.cols;
			rows = f.rows;
			
			// clean
			if (grid != nullptr)
			{
				for (int i = 0; i < rows; i++)
					delete[] grid[i];
				delete[] grid;
			}
			//dynamically allocate mem for grid
			grid = new Pixel * [rows];
			for (int i = 0; i < rows; i++)
			{
				grid[i] = new Pixel[cols];
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
        
		cout << "> Move assignment operator called..." << endl;
		if (this != &f)
		{
            swap(rows, f.rows);
            swap(cols, f.cols);
            swap(grid, f.grid);
		}
        
		return *this;
        
      
	}


ostream& operator<<(ostream& os, Pixel& p) {
    try
    {
        os << p["red"] << " " << p["green"] << " " << p["blue"] << " ";
    }
    catch (Pixel::InputOutOfBoundsException err){
        throw;
    }
    return os;
}


	void saveToPPM(Fractal& f, string n)
	{
		f.makeNewtonFractal();
		fstream file(n, ios::out);

		if (!file)
		{
			cout << "Error: Output file can not be opened. " << endl;
			exit(1);
		}
		cout << "> Saving Fractal object to PPM file.. " << endl;
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

