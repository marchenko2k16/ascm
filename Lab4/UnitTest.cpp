#pragma once

#include "UnitTests.h"

// rozenbrok
float_t TestFunction4(const float_t& FirstParam, const float_t& SecondParam)
{
	return pow((1 - FirstParam), 2) + 100 * pow(SecondParam - pow(FirstParam, 2), 2);
}
vector2d ExpectedResultPoint4{ 1,1 };
float_t ExpectedResult4 = 0.f;

float_t TestFunction5(const float_t& FirstParam, const float_t& SecondParam)
{
	return pow(FirstParam, 2) + FirstParam * SecondParam + pow(SecondParam, 2) - 6 * FirstParam - 9 * SecondParam;
}

vector2d ExpectedResultPoint5{ 1,4 };
float_t ExpectedResult5 = -21.f;