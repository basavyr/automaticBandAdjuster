#ifndef PLOTGRAPH_HH
#define PLOTGRAPH_HH

#include <iostream>
#include <vector>
#include <fstream>

class PlotGraphs
{
public:
    PlotGraphs();
    ~PlotGraphs();
    static void PopulateArrays(std::ofstream &, std::vector<double> &, std::vector<double> &, std::vector<double> &);
};

#endif // PLOTGRAPH_HH
