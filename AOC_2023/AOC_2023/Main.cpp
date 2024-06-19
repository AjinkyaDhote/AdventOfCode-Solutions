#include "Solutions.h"
#include <chrono>

int main()
{
    //Day 1 - Trebuchet
    //Solutions::SumOfCalibrationValues();
    //Solutions::SumOfRealCalibrationValues();

    std::cout << "\n";

    //Day 2 - Cube Conundrum
    //Solutions::CubeConundrum();
    //Solutions::CubeConundrumPartTwo();

    //Day 3 - Gear Ratios
    //Solutions::GearRatios();

    auto startTime = std::chrono::high_resolution_clock::now();

    //Day 4 - Never Tell Me The Odds
    Solutions::ScratchCards();

    auto stopTime = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stopTime - startTime);
    std::cout << "Time taken to execute " << duration.count() << " microseconds." << std::endl;

    return 0;
}
