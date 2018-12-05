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

double ParabolicLayer::get_Value(vector<double> r)
{
	double No = 1e12; //максимум F2 в [cm-3] по умолчанию
	double z_m1 = 150; // полутолщина F2 в [km] 140 по умолчанию
	double z_01 = 300; // высота F2 в [km] 300 по умолчанию
	double z_m2 = 30; // полутолщина E в [km] 40 по умолчанию (50)
	double z_02 = 110; // высота E в [km] 110 по умолчанию
	double beta = 0.2; //0.11
	double ksi = 0;

	double teta = (r[r.size() - 1] - z_01) / (z_m1 / 2);

	double Ne = No * (exp(0.5*(1 - teta - (exp(-teta) / cos(ksi)))) + beta * exp(-(((r[r.size() - 1] - z_02) / z_m2)*((r[r.size() - 1] - z_02) / z_m2))));
	Ne = Ne / 1e12;
	return (Ne);
}

void ParabolicLayer::print()
{
	cout << "test" << endl;
}