#pragma once
#include <iostream>
#include <fstream>

#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNING
#include <stdio.h>

#include <vector>
#include "math.h"

using namespace std;

class Disturbances
{
public:
	Disturbances()
	{}
	virtual void init(int) = 0;
	virtual double getValue(vector<double>, double) = 0;
	virtual void showParameters() = 0;
};

class Gaussian: public Disturbances
{
private:
	double ampl = 0.5;
	vector<double> R; //position 
	vector<double> L; //size of disturbance
	//double Ntid = 0;
public:
	Gaussian(){};

	void init(int);
	double getValue(vector<double>, double);
	void showParameters();
};