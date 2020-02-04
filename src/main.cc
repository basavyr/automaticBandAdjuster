#include "../include/bandAdjuster.hh"

void YRAST()
{
    auto adjuster = std::make_unique<BandAdjuster>();
    auto data = std::make_unique<Data_ENSDF>();
    auto x = adjuster->DELTA_Calculation(data->yrastExp, adjuster->band1Th_test);
    for (auto &&n : x)
    {
        // std::cout << n << " , ";
    }
    auto xx = adjuster->averageDeviation(x);
    adjuster->tuplePrinter(xx);
    // adjuster->sidePicker(xx);
    adjuster->adjuster(adjuster->dataExp, xx);
}

void WOBBLING()
{
    auto adjuster = std::make_unique<BandAdjuster>();
    auto data = std::make_unique<Data_ENSDF>();
    auto x = adjuster->DELTA_Calculation(data->wobbExp, adjuster->band2Th_test);
    for (auto &&n : x)
    {
        // std::cout << n << " , ";
    }
    auto xx = adjuster->averageDeviation(x);
    adjuster->tuplePrinter(xx);
    adjuster->sidePicker(xx);
}

int main()
{
    YRAST();
    // WOBBLING();
}