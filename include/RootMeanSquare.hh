#ifndef ROOTMEANSQUARE_HH
#define ROOTMEANSQUARE_HH

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
#include <fstream>
#include "../include/bandAdjuster.hh"

class RootMeanSquare
{
private:
    /* data */
public:
    RootMeanSquare(/* args */);
    ~RootMeanSquare();

public:
    static constexpr double j_singleParticle = 5.5;
    static constexpr double PI = 3.14159265358979;

public:
    static double inertiaFactor(double);
    static double j_Component(int, double);
    static double omega(double, double, double, double, double);
    static double omegaPrime(double, double, double, double, double);
    static double minHamiltonian(double, double, double, double, double);
    static double energyExpression(int, double, double, double, double, double);

public:
    //the set of parameters
    struct minParamSet
    {
        double i1_min, i2_min, i3_min;
        double a1_min, a2_min, a3_min;
        double theta_min;
        double rms;
        auto transform(double x)
        {
            return static_cast<double>(1.0 / (2.0 * x));
        };
    };

    //the set of limits for fitting params (moments of inertia and the single particle angle)
    struct paramsLimits
    {
        const double i_left = 1.0;
        const double i_right = 120.0;
        const double i_step = 10.0;
        const double theta_left = 0.0;
        const double theta_right = 180.0;
        const double theta_step = 1.0;
    };
    std::vector<minParamSet> minimalParameters;

public:
    //search for the minimal set of parameters after the substraction of the bands with a fixed quantity.
    // static void searchMinimum(Data_ENSDF &object, minParamSet &bestParams)
    template <typename T>
    static void searchMinimum(std::vector<T> &spin1, std::vector<T> &spin2, std::vector<T> &energy1Exp, std::vector<T> &energy2Exp, RootMeanSquare::minParamSet &bestParams)
    {
        auto limits = std::make_unique<paramsLimits>();
        std::vector<minParamSet> minSetOfParams;
        std::vector<double> RMS_stack;
        int index = 0;
        for (auto I1 = limits->i_left; I1 < limits->i_right; I1 += limits->i_step)
        {
            for (auto I2 = limits->i_left; I2 < limits->i_right; I2 += limits->i_step)
            {
                for (auto I3 = limits->i_left; I3 < limits->i_right; I3 += limits->i_step)
                {
                    for (auto theta = limits->theta_left; theta < limits->theta_right; theta += limits->theta_step)
                    {
                        auto currentRMS = dataGeneration<T>(spin1, spin2, energy1Exp, energy2Exp, I1, I2, I3, theta);
                        // if (!isnan(currentRMS) && currentRMS != 6969)
                        {
                            minSetOfParams.emplace_back(minParamSet());
                            minSetOfParams.at(index).i1_min = I1;
                            minSetOfParams.at(index).i2_min = I2;
                            minSetOfParams.at(index).i3_min = I3;
                            minSetOfParams.at(index).theta_min = theta;
                            RMS_stack.emplace_back(currentRMS);
                            index++;
                        }
                    }
                }
            }
        }
        auto minIndex = std::distance(RMS_stack.begin(), std::min_element(RMS_stack.begin(), RMS_stack.end()));
        bestParams.i1_min = std::move(minSetOfParams.at(minIndex).i1_min);
        bestParams.a1_min = std::move(bestParams.transform(bestParams.i1_min));
        bestParams.i2_min = std::move(minSetOfParams.at(minIndex).i2_min);
        bestParams.a2_min = std::move(bestParams.transform(bestParams.i2_min));
        bestParams.i3_min = std::move(minSetOfParams.at(minIndex).i3_min);
        bestParams.a3_min = std::move(bestParams.transform(bestParams.i3_min));
        bestParams.theta_min = std::move(minSetOfParams.at(minIndex).theta_min);
        bestParams.rms = RMS_stack.at(minIndex);
    }

    template <typename T>
    static void paramPrinter(std::ofstream &out, T &params)
    {
        std::cout << "The best fit parameters are"
                  << "\n";
        out << "The best fit parameters are"
            << "\n";
        std::cout << "I1= " << params.i1_min << " I2= " << params.i2_min << " I3= " << params.i3_min << " th= " << params.theta_min << "\n";
        std::cout << "A1= " << params.a1_min << " A2= " << params.a2_min << " A3= " << params.a3_min << " th= " << params.theta_min << "\n";
        std::cout << "E_RMS= " << params.rms << "\n";
        out << "I1= " << params.i1_min << " I2= " << params.i2_min << " I3= " << params.i3_min << " th= " << params.theta_min << "\n";
        out << "A1= " << params.a1_min << " A2= " << params.a2_min << " A3= " << params.a3_min << " th= " << params.theta_min << "\n";
        out << "E_RMS= " << params.rms << "\n";
    }

    //generate the containers of energy
    //the experimental containers are created from the already existing arrays
    //the theoretical containers are created from the set of parameters and the existing spins
    template <typename T>
    static T dataGeneration(std::vector<T> &spin1, std::vector<T> &spin2, std::vector<T> &energy1Exp, std::vector<T> &energy2Exp, double i1, double i2, double i3, double theta)
    {
        auto yrast = [&](auto spin) { return RootMeanSquare::energyExpression(0, spin, i1, i2, i3, theta); };
        auto wobbling = [&](auto spin) { return RootMeanSquare::energyExpression(0, spin, i1, i2, i3, theta); };
        std::vector<T> energyExp;
        std::vector<T> energyTh;
        for (int i = 0; i < spin1.size(); ++i)
        {
            energyExp.emplace_back(energy1Exp.at(i));
            auto currentValue = yrast(spin1.at(i));
            if (currentValue == 6969)
            {
                /* THIS IS NOT OK*/
                //should never fail!
            }
            else
            {
                energyTh.emplace_back(static_cast<double>(currentValue));
            }
        }
        for (int i = 0; i < spin2.size(); ++i)
        {
            energyExp.emplace_back(energy2Exp.at(i));
            auto currentValue = wobbling(spin2.at(i));
            if (currentValue == 6969)
            {
                /* THIS IS NOT OK*/
                //should never fail!
            }
            else
            {
                energyTh.emplace_back(static_cast<double>(currentValue));
            }
        }
        T result = BandAdjuster::RMS_Calculation<T>(energyExp, energyTh);
        return result;
    }
    template <typename T>
    static void generateExperimentalSet(T &object1, T &object2, std::vector<double> &outputArray)
    {
        //only do this for an empty and fresh output
        if (!outputArray.size())
        {
            for (auto i = 0; i < object1.size(); ++i)
            {
                outputArray.emplace_back(object1.at(i));
            }
            for (auto i = 0; i < object2.size(); ++i)
            {
                outputArray.emplace_back(object2.at(i));
            }
        }
        else
            outputArray.clear();
    }

    template <typename T>
    static void generateTheoreticalSet(T &object, std::vector<double> &outputArray, double i1, double i2, double i3, double theta)
    {
        //only do this for an empty and fresh output
        if (!outputArray.size())
        {
            auto yrast = [&](auto spin) { return RootMeanSquare::energyExpression(0, spin, i1, i2, i3, theta); };
            auto wobbling = [&](auto spin) { return RootMeanSquare::energyExpression(0, spin, i1, i2, i3, theta); };
            for (int i = 0; i < object.spin1.size(); ++i)
            {
                outputArray.emplace_back(yrast(object.spin1.at(i)));
            }
            for (int i = 0; i < object.spin2.size(); ++i)
            {
                outputArray.emplace_back(wobbling(object.spin2.at(i)));
            }
        }
        else
            outputArray.clear();
    }
    
    //obtain the experimental small data sets per each band
    template <typename T, typename T2>
    static void antiGenerationExperimental(T &object, T2 &data, std::vector<double> &yrastExp, std::vector<double> &wobbExp)
    {
        if (yrastExp.size() && wobbExp.size())
        {
            yrastExp.clear();
            wobbExp.clear();
        }
        else
        {
            for (int i = 0; i < data.spin1.size(); ++i)
            {
                yrastExp.emplace_back(object.dataExp.at(i));
            }
            for (int i = data.spin1.size(); i < object.dataExp.size(); ++i)
            {
                wobbExp.emplace_back(object.dataExp.at(i));
            }
        }
    }

    template <typename T, typename T2>
    static void antiGnerationTheoretical(T &object, T2 &data, std::vector<double> &yrastTh, std::vector<double> &wobbTh)
    {
        if (yrastTh.size() && wobbTh.size())
        {
            yrastTh.clear();
            wobbTh.clear();
        }
        else
        {
            for (int i = 0; i < data.spin1.size(); ++i)
            {
                yrastTh.emplace_back(object.dataTh.at(i));
            }
            for (int i = data.spin1.size(); i < object.dataTh.size(); ++i)
            {
                wobbTh.emplace_back(object.dataTh.at(i));
            }
        }
    }
};

#endif // ROOTMEANSQUARE_HH
