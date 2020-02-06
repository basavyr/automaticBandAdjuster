#include "../include/RootMeanSquare.hh"

RootMeanSquare::RootMeanSquare(/* args */)
{
}

RootMeanSquare::~RootMeanSquare()
{
}

double RootMeanSquare::inertiaFactor(double moi)
{
    return static_cast<double>(1.0 / (2.0 * moi));
}

double RootMeanSquare::j_Component(int k, double theta)
{
    if (k == 1)
        return RootMeanSquare::j_singleParticle * cos(theta * RootMeanSquare::PI / 180.0);
    return RootMeanSquare::j_singleParticle * sin(theta * RootMeanSquare::PI / 180.0);
}

double RootMeanSquare::omega(double spin, double i1, double i2, double i3, double theta)
{
    //generate the inertia factors
    auto a1 = inertiaFactor(i1);
    auto a2 = inertiaFactor(i2);
    auto a3 = inertiaFactor(i3);
    //generate the single particle a.m. components
    auto j1 = j_Component(1, theta);
    auto j2 = j_Component(2, theta);
    auto term1 = (2.0 * spin + 1.0) * (a2 - a1 - (a2 * j2 / spin)) - 2.0 * a1 * j1;
    auto term2 = (2.0 * spin + 1.0) * (a3 - a1) - 2.0 * a1 * j1;
    auto term3 = (a3 - a1) * (a2 - a1 - (a2 * j2 / spin));
    auto result = sqrt(term1 * term2 - term3);
    if (isnan(result))
        return 6969;
    return static_cast<double>(result);
}

double RootMeanSquare::omegaPrime(double spin, double i1, double i2, double i3, double theta)
{
    //generate the inertia factors
    auto a1 = inertiaFactor(i1);
    auto a2 = inertiaFactor(i2);
    auto a3 = inertiaFactor(i3);
    //generate the single particle a.m. components
    auto j1 = j_Component(1, theta);
    auto j2 = j_Component(2, theta);
    auto term1 = (2.0 * spin + 1.0) * (a2 - a1 - (a2 * j2 / spin)) + 2.0 * a1 * j1;
    auto term2 = (2.0 * spin + 1.0) * (a3 - a1) + 2.0 * a1 * j1;
    auto term3 = (a3 - a1) * (a2 - a1 - (a2 * j2 / spin));
    auto result = sqrt(term1 * term2 - term3);
    if (isnan(result))
        return 6969;
    return static_cast<double>(result);
}

double RootMeanSquare::minHamiltonian(double spin, double i1, double i2, double i3, double theta)
{
    //generate the inertia factors
    auto a1 = inertiaFactor(i1);
    auto a2 = inertiaFactor(i2);
    auto a3 = inertiaFactor(i3);
    //generate the single particle a.m. components
    auto j1 = j_Component(1, theta);
    auto j2 = j_Component(2, theta);

    auto singleParticleSum = a1 * (j1 * j1) + a2 * (j2 * j2);
    auto minTerm = a1 * spin * spin + (2.0 * spin + 1.0) * a1 * j1 - spin * a2 * j2;
    auto result = minTerm + singleParticleSum;
    if (isnan(result))
        return 6969;
    return static_cast<double>(result);
}

double RootMeanSquare::energyExpression(int N, double spin, double i1, double i2, double i3, double theta)
{
    auto omega = RootMeanSquare::omega(spin, i1, i2, i3, theta);
    //stop immediately if the wobbling frequency is not real
    if (omega == 6969)
        return 6969;

    //generate the first state (band head)
    auto spinZero = 5.5;
    auto e0 = static_cast<double>(minHamiltonian(spinZero, i1, i2, i3, theta) + 0.5 * RootMeanSquare::omega(spinZero, i1, i2, i3, theta));

    //generate the inertia factors
    auto a1 = inertiaFactor(i1);
    auto a2 = inertiaFactor(i2);
    auto a3 = inertiaFactor(i3);
    auto result = static_cast<double>(minHamiltonian(spin, i1, i2, i3, theta) + (N + 0.5) * RootMeanSquare::omega(spin, i1, i2, i3, theta) - e0);
    if (isnan(result))
        return 6969;
    return result;
}