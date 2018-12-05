#pragma once
#include <iostream>
#include <fstream>

#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNING
#include <stdio.h>

#include <vector>
#include "math.h"

using namespace std;

class Ionosphere
{
public:
	Ionosphere()
	{}
	virtual double get_Value(vector<double>) = 0;
};

class ParabolicLayer : public Ionosphere
{
public:
	ParabolicLayer()
	{}
	double get_Value(vector<double>);
	void print();
};