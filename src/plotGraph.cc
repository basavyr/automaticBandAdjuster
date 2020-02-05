#include "../include/plotGraph.hh"

void PlotGraphs::PopulateArrays(std::ofstream &out, std::vector<double> &x, std::vector<double> &v1, std::vector<double> &v2)
{
    bool ok = 0;
    if (v1.size() != v2.size() || x.size() != v2.size())
    {
        std::cout << "Cannot plot this set";
        std::cout << "\n";
        ok = 1;
        return;
    }
    for (int i = 0; i < v1.size() && !ok; ++i)
    {
        out << x.at(i) << " " << v1.at(i) << " " << v2.at(i);
        out << "\n";
    }
}