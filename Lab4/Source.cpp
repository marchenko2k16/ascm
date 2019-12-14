#pragma once 

#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <functional>


#include "UnitTests.h"

#include "vector2d.h"

float_t UniformRandom(float_t from, float_t to)
{
	std::random_device randomDevice;
	std::mt19937_64 mt(randomDevice());
	std::uniform_real_distribution<> distribution(from, to);
	return distribution(mt);
}

class NedlerMead 
{
private:
	std::vector<vector2d> ResultingSimplexVertices;
	std::function<float_t(float_t FirstParam, float_t SecondParam)> InitialFunction;

public:
	void RandomInit()
	{
		for (uint8_t Index = 0; Index < 3; Index++)
		{
			ResultingSimplexVertices.emplace(ResultingSimplexVertices.begin()+Index, UniformRandom(0, 10), UniformRandom(0, 10));
		}
	}
	
	void Init(std::initializer_list<vector2d> InitList) 
	{
		InitList.begin();
		for (auto Iterator = InitList.begin(); Iterator != InitList.end(); Iterator++)
		{
			ResultingSimplexVertices.push_back(*Iterator);
		}
	};

	void SetFunctor(std::function<float_t(float_t, float_t)> In) 
	{
		InitialFunction = In;
	}
	
	void Sort()
	{
		std::sort(ResultingSimplexVertices.begin(), ResultingSimplexVertices.end(), [this](const vector2d& First, const vector2d& Second)
			{return InitialFunction(First.x, First.y) < InitialFunction(Second.x, Second.y); }
		);
	}

	vector2d Solve()
	{
		// Defaults
		float_t alpha = 1, beta = 0.5, gamma = 2, maxiter = 1000;
		
		vector2d Best{};
		vector2d Good{};
		vector2d Worst{};
		for (uint16_t Iterator{}; Iterator < maxiter; Iterator++)
		{
			Sort();

			Best	= ResultingSimplexVertices[0];
			Good	= ResultingSimplexVertices[1];
			Worst	= ResultingSimplexVertices[2];

			vector2d mid = (Best + Good) / 2;

			// reflection
			vector2d xr = mid + alpha * (mid - Worst);
			if (InitialFunction(xr.x, xr.y) < InitialFunction(Good.x, Good.y))
			{
				Worst = xr;
			}
			else
			{
				if (InitialFunction(xr.x, xr.y) < InitialFunction(Worst.x, Worst.y))
				{
					Worst = xr;
				}

				vector2d c = (Worst + mid) / 2;	
				if (InitialFunction(c.x, c.y) < InitialFunction(Worst.x, Worst.y))
				{
					Worst = c;
				}
			}

			if (InitialFunction(xr.x, xr.y) < InitialFunction(Best.x, Best.y))
			{
				//expansion
				vector2d xe = mid + gamma * (xr - mid);
				if (InitialFunction(xe.x, xe.y) < InitialFunction(xr.x, xr.y))
				{
					Worst = xe;
				}
				else
				{
					Worst = xr;
				}	
			}
			
			if (InitialFunction(xr.x, xr.y) < InitialFunction(Good.x, Good.y))
			{
				// contraction
				vector2d xc = mid + beta * (Worst - mid);
				if (InitialFunction(xc.x, xc.y) < InitialFunction(Worst.x, Worst.y))
				{
					Worst = xc;
				}

			}			

			// update points
			ResultingSimplexVertices[0] = Worst;
			ResultingSimplexVertices[1] = Good;
			ResultingSimplexVertices[2] = Best;
		}
		return Best;
	}
};

void UnitTestBlock()
{
	std::cout << "Unit tests : " << std::endl << std::endl;

	NedlerMead SolvingSample4;
	SolvingSample4.RandomInit();
	SolvingSample4.SetFunctor(TestFunction4);
	auto ResultPoint4 = SolvingSample4.Solve();
	auto Result4 = TestFunction4(ResultPoint4.x, ResultPoint4.y);
	std::cout << "Expected Result4: " << ExpectedResult4 << "Expected Result Point4: " << ExpectedResultPoint4 << std::endl;
	std::cout << "Calculated Result4 : " << Result4 << "CalculatedPoint4: " << ResultPoint4 << std::endl;


	NedlerMead SolvingSample5;
	SolvingSample5.RandomInit();
	SolvingSample5.SetFunctor(TestFunction5);
	auto ResultPoint5 = SolvingSample5.Solve();
	auto Result5 = TestFunction5(ResultPoint5.x, ResultPoint5.y);
	std::cout << "Expected Result5: " << ExpectedResult5  << "Expected Result Point5: " << ExpectedResultPoint5 << std::endl;
	std::cout << "Calculated Result5 : " << Result5 << "CalculatedPoint5: " << ResultPoint5 << std::endl;
}

int main()
{
	NedlerMead SolvingSample;
	SolvingSample.Init({ vector2d(0,0), vector2d(1, 0), vector2d(0, 1) });
	SolvingSample.SetFunctor([](const float_t& FirstParam, const float_t& SecondParam)
	{
		return pow(FirstParam, 2) + FirstParam * SecondParam + pow(SecondParam, 2) - 6 * FirstParam - 9 * SecondParam;
	});
	auto Result = SolvingSample.Solve();

	UnitTestBlock();

	int DEBUG;
	return 0;
}