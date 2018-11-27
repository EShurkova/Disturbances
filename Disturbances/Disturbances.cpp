// Disturbances.cpp : This file contains the 'main' function. Program execution begins and ends there.
// ПИВ

#include "pch.h"
#include <iostream>
#include <fstream>

#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNING
#include <stdio.h>

#include <vector>
#include "math.h"
#include "Ionosphere.h"

using namespace std;

class Disturbances
{
private:
    double ampl = 0.5;
	vector<double> R; //position 
	vector<double> L; //size of disturbance
	//double Ntid = 0;
public: 
	Disturbances(int n)
	{
		cout << "Constructor" << endl;
		/*for (int i = 0; i < n; i++)
		{
			//R.push_back(100);
			//L.push_back(100.);
		}*/
		R.push_back(500.);
		R.push_back(300.);
		L.push_back(100.);
		L.push_back(100.);
	}

	double getValue(vector<double> r, double Ne = 1)
	{
		double Ntid = 0;
		for (unsigned int i = 0; i < r.size(); i++)
		{
			Ntid += (0.5*pow((r[i]-R[i])/(L[i]),2));
		}
		Ntid = Ne*(ampl*exp(-Ntid) + 1);

		return (Ntid);
	}

	void showParameters()
	{
		cout << "Amplitude = " << ampl << "\n";
		cout << "R: ";
		for (unsigned int i = 0; i < R.size(); i++)
		{
			cout << R[i] << " ";
		}
		cout << endl;
		cout << "L: ";
		for (unsigned int i = 0; i < L.size(); i++)
		{
			cout << L[i] << " ";
		}
		cout << endl;
		//cout << "Ntid = " << Ntid;
	}
};

int main()
{
	cout << fixed;
	cout.precision(2);
	int DIM = 2; //dimension
	if (DIM == 2)
		vector<vector<double>> GRID;
	else if (DIM == 3)
		vector<vector<vector<double>>> GRID;
	double Xmin = 0;
	double Xmax = 1000;
	double Ymin = 0;
	double Ymax = 500;
	int s = 50; //number of step
	double Xstep = (Xmax - Xmin) / s;
	double Ystep = (Ymax - Ymin) / s;
	double X = 0;
	double Y = 0;
	double Ne = 0;

	Ionosphere* ION = new ParabolicLayer;
	Disturbances TID(DIM);

	vector<double> m(DIM);

	FILE *file = fopen("output.txt", "w");

	for (int i = 0; i <= s; i++)
	{
		for (int j = 0; j <= s; j++)
		{
			m[0] = X;
			m[1] = Y;
			//cout << m[0] << " " << m[1] << " " << TID.getValue(m, Ne) << "\n";

			Ne = ION->get_Value(m);

			fprintf(file, " %10.4f %10.4f %10.4f \n", m[0], m[1], TID.getValue(m, Ne));
			Y = Y + Ystep;
		}
		fprintf(file, "\n");
		Y = Ymin;
		X = X + Xstep;
	}

	fclose(file);

	cout << "Ntid = " << TID.getValue(m, 1) << "\n";
	cout << "TID: \n"; TID.showParameters();
	cout << endl;

	return 0;
}