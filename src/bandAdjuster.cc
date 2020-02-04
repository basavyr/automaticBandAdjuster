#include "../include/bandAdjuster.hh"
#include <iostream>

TestApp::TestApp()
{
    std::cout << "App is working fine..."
              << "\n";
    startPoint = std::chrono::high_resolution_clock::now();
    // Sleep(1);
}
TestApp::~TestApp()
{
    std::cout << "Class container stopped with status OK"
              << "\n";
    StopApp();
    // std::cout << "Class container stopped with status FAIL"
    //   << "\n";
}

void TestApp::RunApp()
{
    auto now = std::chrono::system_clock::now();
    std::time_t date = std::chrono::system_clock::to_time_t(now);
    std::cout << std::ctime(&date);
}

void TestApp::Sleep(int seconds)
{
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

void TestApp::StopApp()
{
    auto endPoint = std::chrono::high_resolution_clock::now();
    auto start = std::chrono::time_point_cast<std::chrono::microseconds>(startPoint).time_since_epoch().count();
    auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endPoint).time_since_epoch().count();
    auto durationMS = (end - start) * 0.001;
    std::cout << "and was alive for " << durationMS << " ms..."
              << "\n";
}