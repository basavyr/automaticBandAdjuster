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

//this class contains a benchmark routine
class TestApp
{
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startPoint;
    std::chrono::time_point<std::chrono::high_resolution_clock> endPoint;

public:
    TestApp();
    ~TestApp();

public:
    void RunApp();
    void StopApp();
};

class Data_ENSDF
{
};

#endif // BANDADJUSTER_HH
