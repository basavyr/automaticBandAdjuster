#include "../include/bandAdjuster.hh"
#include "../include/plotGraph.hh"

void YRAST()
{
    auto adjuster = std::make_unique<BandAdjuster>();
    auto data = std::make_unique<Data_ENSDF>();
    auto x = adjuster->DELTA_Calculation(data->yrastExp, adjuster->band1Th_test);
    auto xx = adjuster->averageDeviation(x);
    adjuster->tuplePrinter(xx);
    std::vector<double> test;
    adjuster->adjuster(data->yrastExp, xx, test);
    std::ofstream file("../output/plot1.dat");
    PlotGraphs::PopulateArrays(file, data->spin1, data->yrastExp, test);
}

void WOBBLING()
{
    auto adjuster = std::make_unique<BandAdjuster>();
    auto data = std::make_unique<Data_ENSDF>();
    auto x = adjuster->DELTA_Calculation(data->wobbExp, adjuster->band2Th_test);
    auto xx = adjuster->averageDeviation(x);
    adjuster->tuplePrinter(xx);
    std::vector<double> test;
    adjuster->adjuster(data->wobbExp, xx, test);
    std::ofstream file("../output/plot2.dat");
    PlotGraphs::PopulateArrays(file, data->spin2, data->wobbExp, test);
}

int main()
{
    YRAST();
    WOBBLING();
}