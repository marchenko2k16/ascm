#pragma once
// Rotations Method

#include <vector>
#include <string>

std::vector<std::vector<double>> TestCoef1
{ {1,2,3},
{1,2,3} };
std::vector<double> TestResult1{ 1,2 };
std::string ExpectedCheckResult1 = "Incorrect SLAE sizes.";

std::vector<std::vector<double>> TestCoef2
{ {1,2,3},
{1,2,3} };
std::vector<double> TestResult2{ 1,2,3,4 };
std::string ExpectedCheckResult2 = "Incorrect SLAE sizes.";

std::vector<std::vector<double>> TestCoef3
{ {1,2,3},
{1,2,3} };
std::vector<double> TestResult3{ 1 };
std::string ExpectedCheckResult3 = "Incorrect SLAE sizes.";

std::vector<std::vector<double>> TestCoef4
{ {1, 0, 0},
{1,2,3},
{3,0,2} };
std::vector<double> TestResult4{ 1 , 0 , 13 };
std::string ExpectedCheckResult4 = "Correct SLAE sizes.";