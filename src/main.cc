#include "../include/bandAdjuster.hh"
#include "../include/plotGraph.hh"
#include "../include/RootMeanSquare.hh"

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

template <typename T>
void arrayPrinter(std::vector<T> &vec)
{
    for (int i = 0; i < vec.size(); ++i)
    {
        if (i == vec.size() - 1)
        {
            std::cout << vec.at(i);
        }
        else
        {
            std::cout << vec.at(i) << " , ";
        }
    }
    std::cout << "\n";
}

void Bands()
{
    auto adjuster = std::make_unique<BandAdjuster>();
    auto data = std::make_unique<Data_ENSDF>();
    auto bestParams = std::make_unique<RootMeanSquare::minParamSet>();

    RootMeanSquare::generateExperimentalSet(data->yrastExp, data->wobbExp, adjuster->dataExp);
    RootMeanSquare::searchMinimum(data->spin1, data->spin2, data->yrastExp, data->wobbExp, *bestParams);
    RootMeanSquare::generateTheoreticalSet(*data, adjuster->dataTh, bestParams->i1_min, bestParams->i3_min, bestParams->i3_min, bestParams->theta_min);
    RootMeanSquare::antiGenerationExperimental(*adjuster, *data, adjuster->yrastExp, adjuster->wobbExp);
    RootMeanSquare::antiGnerationTheoretical(*adjuster, *data, adjuster->yrastTh, adjuster->wobbTh);
}

int main()
{
    auto timer = std::make_unique<TestApp>();
    // auto adjuster = std::make_unique<BandAdjuster>();
    // auto data = std::make_unique<Data_ENSDF>();
    // auto bestParams = std::make_unique<RootMeanSquare::minParamSet>();
    // std::ofstream params("../output/params.dat");

    // RootMeanSquare::searchMinimum<double>(data->spin1, data->spin2, data->yrastExp, data->wobbExp, *bestParams);
    // RootMeanSquare::paramPrinter<RootMeanSquare::minParamSet>(params, *bestParams);
    // std::cout << "Exp energy before the adjustment\n";
    // RootMeanSquare::generateExperimentalSet(data->yrastExp, data->wobbExp, adjuster->dataExp_Subtracted);
    // arrayPrinter(adjuster->dataExp_Subtracted);

    // YRAST();
    // WOBBLING();

    Bands();
}