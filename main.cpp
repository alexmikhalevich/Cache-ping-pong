#include <fstream>
#include <utility>
#include "ctest.hpp"
#include "gnuplot-iostream/gnuplot-iostream.h"

int main() {
	Gnuplot gp;
	const int max_dst = 100;
	std::vector<std::pair<int, double>> result;
	for(int i = 3; i < max_dst; ++i) 
		result.push_back(std::make_pair(i, CTest::get_avg_time(i)));
	gp << "set xlabel 'Distance between used memory cells'" << std::endl;
	gp << "set ylabel 'Average working time, seconds'" << std::endl;
	gp << "set title 'Cache ping-pong visualization'" << std::endl;
	gp << "plot" << gp.file1d(result) << "with lines notitle" << std::endl;
	return 0;
}
