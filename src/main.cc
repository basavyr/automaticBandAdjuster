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

    std::ofstream params("../output/params.dat");
    std::ofstream file1("../output/plot1.dat");
    std::ofstream file2("../output/plot2.dat");

    RootMeanSquare::generateExperimentalSet(data->yrastExp, data->wobbExp, adjuster->dataExp);
    RootMeanSquare::searchMinimum(data->spin1, data->spin2, data->yrastExp, data->wobbExp, *bestParams);
    RootMeanSquare::paramPrinter<RootMeanSquare::minParamSet>(params, *bestParams);

    RootMeanSquare::generateTheoreticalSet(*data, adjuster->dataTh, bestParams->i1_min, bestParams->i3_min, bestParams->i3_min, bestParams->theta_min);
    RootMeanSquare::antiGenerationTheoretical(*adjuster, *data, adjuster->yrastTh, adjuster->wobbTh);
    RootMeanSquare::antiGenerationExperimental(*adjuster, *data, adjuster->yrastExp, adjuster->wobbExp);
    arrayPrinter(adjuster->dataExp);

    auto deltasYrast = adjuster->DELTA_Calculation(data->yrastExp, adjuster->yrastTh);
    auto weightYrast = adjuster->averageDeviation(deltasYrast);
    // arrayPrinter(deltasYrast);
    adjuster->tuplePrinter(weightYrast);
    std::vector<double> newArrayYrast;
    adjuster->adjuster(data->yrastExp, weightYrast, newArrayYrast);

    auto deltasWobb = adjuster->DELTA_Calculation(data->wobbExp, adjuster->wobbTh);
    auto weightWobb = adjuster->averageDeviation(deltasWobb);
    // arrayPrinter(deltasWobb);
    adjuster->tuplePrinter(weightWobb);
    std::vector<double> newArrayWobb;
    adjuster->adjuster(data->wobbExp, weightWobb, newArrayWobb);
    arrayPrinter(adjuster->dataExp);
    std::cout << adjuster->dataExp.size() << "\n";
    arrayPrinter(newArrayYrast);
    arrayPrinter(newArrayWobb);
    RootMeanSquare::generateAnySet(newArrayYrast, newArrayWobb, adjuster->dataExp);
    // RootMeanSquare::generateAnySet(newArrayYrast, newArrayWobb, adjuster->dataExp);
    arrayPrinter(adjuster->dataExp);
    std::cout << adjuster->dataExp.size() << "\n";
    std::cout << adjuster->RMS_Calculation(adjuster->dataExp, adjuster->dataTh) << "\n";
    RootMeanSquare::searchMinimum(data->spin1, data->spin2, adjuster->yrastExp, adjuster->wobbExp, *bestParams);
    PlotGraphs::PopulateArrays(file1, data->spin1, data->yrastExp, adjuster->yrastExp);
    arrayPrinter(data->yrastExp);
    arrayPrinter(adjuster->yrastExp);
    RootMeanSquare::paramPrinter<RootMeanSquare::minParamSet>(params, *bestParams);

    // arrayPrinter(newArray);
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