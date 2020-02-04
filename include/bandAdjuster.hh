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

public:
    TestApp();
    ~TestApp();

public:
    void RunApp();
    void Sleep(int);
    void StopApp();
};

class Data_ENSDF
{
};

#endif // BANDADJUSTER_HH
