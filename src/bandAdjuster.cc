#include "../include/bandAdjuster.hh"
#include <iostream>

TestApp::TestApp()
{
    std::cout << "App is working fine..."
              << "\n";
    RunApp();
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

void TestApp::StopApp()
{
    auto now = std::chrono::system_clock::now();
    std::time_t date = std::chrono::system_clock::to_time_t(now);
    std::cout << std::ctime(&date);
}