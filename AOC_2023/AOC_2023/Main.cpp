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

    //Day 4 - Never Tell Me The Odds
    //Solutions::ScratchCards();

    //Day 5 - Day 5: If You Give A Seed A Fertilizer
    //Solutions::IfYouGiveASeedAFertilizer();

    //Day 6 - Wait For It
    //Solutions::WaitForIt();

    //Day 7 - CamelCards
    //Solutions::CamelCards();

    //Day 8 - HauntedWastelands
    //Solutions::HauntedWastelands();

    //Day 9 - Mirage Maintenance
    //Solutions::MirageMaintenance();

    //Day 10 - Pipe Maze 
    //Solutions::PipeMaze();

    //Day 11 - Cosmic Expolsion 
    //Solutions::CosmicExplosion();
    
    //Day 12 -
    auto startTime = std::chrono::high_resolution_clock::now();
    Solutions::Day12();

    auto stopTime = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stopTime - startTime);
    std::cout << "Time taken to execute " << duration.count() << " ms." << std::endl;

    return 0;
}
