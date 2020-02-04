#ifndef BANDADJUSTER_HH
#define BANDADJUSTER_HH

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <chrono>
#include <ctime>
#include <utility>
#include <memory>
#include <future>
#include <thread>

//This class contains a benchmark routine
//It performs a time measurement on construction->destruction process and returns the number of miliseconds
class TestApp
{
private:
    //time point that registers the initialization of the class object
    std::chrono::time_point<std::chrono::high_resolution_clock> startPoint;

public:
    TestApp();
    ~TestApp();

public:
    void RunApp();
    void Sleep(int);
    //method for measuring the duration until the object is destroyed
    void StopApp();
};

class Data_ENSDF
{
public:
    std::vector<double> spin1 = {7.5, 9.5, 11.5, 13.5, 15.5, 17.5, 19.5, 21.5, 23.5, 25.5};
    std::vector<double> spin2 = {8.5, 10.5, 12.5, 14.5, 16.5};
    std::vector<double> yrastExp = {0.37277, 1.03284, 1.88684, 2.88674, 3.96174, 4.80574, 5.63974,
                                    6.52174, 7.44474, 8.35794};
    std::vector<double> wobbExp = {1.07524, 1.80044, 2.64294, 3.59894, 4.71094};
    static constexpr double j_OddSpin = 5.5;
    static constexpr double PI = 3.14159265358979;
};

class BandAdjuster
{
public:
    BandAdjuster();
    ~BandAdjuster();

public:
    std::vector<double> dataExp;
    std::vector<double> dataTh;
    static std::vector<double> dataExp_Subtracted;
    //testing containers
public:
    //test container for yrast
    std::vector<double> band1Th_test = {0.708863, 1.44817, 2.21829, 3.01941, 3.85159, 4.71489, 5.60933, 6.53492, 7.49169, 8.47963};
    //test container for wobbling
    std::vector<double> band2Th_test = {1.07468, 1.82936, 2.61497, 3.43161, 4.27935};
    //methods for band calculus
public:
    template <typename T>
    static double RMS_Calculation(std::vector<T> &exp, std::vector<T> &th)
    {
        return 1;
    }

    template <typename T>
    static std::vector<T> DELTA_Calculation(std::vector<T> &exp, std::vector<T> &th)
    {
        if (exp.size() != th.size())
        {
            return {};
        }
        std::vector<T> deltas;
        auto delta = [](auto x, auto y) {
            return static_cast<double>(y - x);
        };
        for (int i = 0; i < exp.size(); ++i)
        {
            deltas.emplace_back(delta(exp.at(i), th.at(i)));
        }
        return deltas;
    }

public:
    static double BandSubtraction(std::vector<double> &, double);
    //store the average deviations from the experimental data (related to Delta terms)
    struct halfSize_tuple
    {
        double avg_Left;
        double avg_Right;
        int states_Left;
        int states_Right;
        bool side;
        halfSize_tuple()
        {
            avg_Left = 0.0;
            avg_Right = 0.0;
            states_Left = 0;
            states_Right = 0;
            side = 0;
        }
    };

    static halfSize_tuple averageDeviation(std::vector<double> &);
    template <typename T>
    static void tuplePrinter(T &tuple)
    {
        std::cout << tuple.avg_Left << " " << tuple.avg_Right << "\n";
    }

    //container for the adjusted bands
    //modify only the fist part of the energy container (1ST HALF ADJUST)
    static std::vector<double> joinLeft(std::vector<double> &, double);

    //container for the adjusted bands
    //modify only the second part of the energy container (2ND HALF ADJUST)
    static std::vector<double> joinRight(std::vector<double> &, double);

    //function which decides what side to modify and what adjuster to implement
    static int sidePicker(halfSize_tuple &);

    //the actual band adjuster
    static void adjuster(std::vector<double> &, halfSize_tuple &);
};

#endif // BANDADJUSTER_HH
