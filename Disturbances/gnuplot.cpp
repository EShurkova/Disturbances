#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>

#include "gnuplot.h"

using namespace std;

int N = 0;

Gnuplot::Gnuplot()
{
	gstream = _popen("\"C://Program Files//gnuplot//bin//gnuplot.exe\"", "w");
}
Gnuplot::~Gnuplot()
{}
void Gnuplot::plot()
{
	fprintf(gstream, "set title 'My plot'\n");
	fprintf(gstream, "set pm3d\n");
	fprintf(gstream, "splot 'output.txt' with l \n");
	fflush(gstream);
};
