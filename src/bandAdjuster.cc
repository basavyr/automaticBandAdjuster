#include "../include/bandAdjuster.hh"
#include <iostream>

//BENCHMARK TOOL
TestApp::TestApp()
{
    std::cout << "App is working fine..."
              << "\n";
    startPoint = std::chrono::high_resolution_clock::now();
    // Sleep(1);
}
TestApp::~TestApp()
{
    //if the creation failed...stop measuring time
    if (!std::chrono::time_point_cast<std::chrono::microseconds>(startPoint).time_since_epoch().count())
    {
        std::cout << "Class container stopped with status FAIL"
                  << "\n";
        return;
    }
    std::cout << "Class container stopped with status OK"
              << "\n";
    //calls the method for getting the duration
    StopApp();
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

BandAdjuster::BandAdjuster()
{
    const std::string message = "The class container for adjusting experimental band has been CREATED...\n";
    std::cout << message;
}

BandAdjuster::~BandAdjuster()
{
    const std::string message = "The class container for adjusting experimental band has been DESTROYED...\n";
    std::cout << message;
}

double BandAdjuster::BandSubtraction(std::vector<double> &array, double subtractor)
{
    return 0;
}

BandAdjuster::halfSize_tuple BandAdjuster::averageDeviation(std::vector<double> &array)
{
    auto avg_result = new halfSize_tuple();
    auto halfSize = static_cast<size_t>(array.size() / 2);

    std::cout << "full size" << array.size() << "\n";
    std::cout << "half size" << halfSize << "\n";
    for (int i = 0; i < halfSize; ++i)
    {
        avg_result->avg_Left += array.at(i);
        avg_result->states_Left++;
    }
    avg_result->avg_Left = static_cast<double>(avg_result->avg_Left / avg_result->states_Left);
    for (int i = halfSize; i < array.size(); ++i)
    {
        avg_result->avg_Right += array.at(i);
        avg_result->states_Right++;
    }
    if (halfSize % 2 == 0)
        avg_result->states_Right = avg_result->states_Right - 1;
    std::cout << "states left " << avg_result->states_Left << "\n";
    std::cout << "states right " << avg_result->states_Right << "\n";
    avg_result->avg_Right = static_cast<double>(avg_result->avg_Right / avg_result->states_Right);
    return *avg_result;
}
