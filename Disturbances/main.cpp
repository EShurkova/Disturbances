#include "pch.h"
#include <iostream>
#include <fstream>

#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNING
#include <stdio.h>

#include <vector>
#include "math.h"

#include "Ionosphere.h"
#include "Disturbances.h"
#include "gnuplot.h"

using namespace std;

int main()
{
	cout << fixed;
	cout.precision(2);
	int DIM = 2; //dimension
		
	vector<double> range_min(DIM); // including Xmin, Ymin, Zmin
	vector<double> range_max(DIM); // including Xmax, Ymax, Zmax
	vector<int> range_number(DIM); // number of step
	vector<double> r_current(DIM); // including current vector r
	double Ne = 0;

	for (int i = 0; i < DIM; i++)
	{
		range_min[i] = 0;
		range_max[i] = 1000;
		range_number[i] = 50;
		r_current[i] = 0;
	}

	//range_max[DIM - 1] = 300;// user insert value
	
	vector<double> range_step(DIM); // including Xstep, Ystep, Zstep
	
	for (int i = 0; i < DIM; i++)
		range_step[i] = (range_max[i] - range_min[i]) / range_number[i];

	/*//=======================================================================

	double Xmin = 0;
	double Ymin = 0;

	double Xmax = 1000;
	double Ymax = 500;

	int s = 50; //number of step
	double Xstep = (Xmax - Xmin) / s;
	double Ystep = (Ymax - Ymin) / s;

	double X = 0;
	double Y = 0;


	//=======================================================================*/

	Ionosphere* ION = new ParabolicLayer;
	Disturbances* TID = new Gaussian;
	TID->init(DIM);

	vector<double> m(DIM);
	//m[0] = 3.5;
	//m[1] = 4.5;
	//m[2] = 200.;

	if (DIM == 2)
	{
		FILE *file = fopen("output.txt", "w");

		for (int i = 0; i <= range_number[0]; i++)
		{

			for (int j = 0; j <= range_number[1]; j++)
			{

				for (int k = 0; k < DIM; k++)
				{
					m[k] = r_current[k];
				}
				Ne = ION->get_Value(m);
				
				for (int k = 0; k < DIM; k++)
				{
					fprintf(file, " %10.4f", m[k]);
				}
				fprintf(file, " %10.4f \n", TID -> getValue(m, Ne));

				r_current[1] = r_current[1] + range_step[1];
				//cout << m[0] << " " << m[1] << " " << "\n";
			}
			fprintf(file, "\n");
			r_current[1] = range_min[1];
			r_current[0] = r_current[0] + range_step[0];
			
		}
		fclose(file);

	}

	Ne = ION->get_Value(m);
	cout << "Ntid = " << TID -> getValue(m, Ne) << "\n";
	cout << "TID: \n"; TID -> showParameters();
	cout << endl;

	Gnuplot Plot;
	Plot.plot();

	system("pause");

	return 0;
}