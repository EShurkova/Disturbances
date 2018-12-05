#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#ifndef GNUPLOT_H
#define GNUPLOT_H
class Gnuplot
{
	FILE* gstream;
public:
	Gnuplot();
	~Gnuplot();
	void plot();
};
#endif