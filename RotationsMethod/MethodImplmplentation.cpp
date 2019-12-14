#include <iostream>
#include <functional>
#include <vector>
#include <string>
#include <sstream>

#include "TestCases.h"

bool CheckTestCaseInputCheck(std::vector<std::vector<double>> Coefs, std::vector<double> Results)
{
	return Coefs.size() == Results.size() && Coefs[0].size() == Results.size();
}
void TestCasesFunction(std::vector<std::vector<double>> CheckCoefs, std::vector<double> CheckResults, std::string CheckString)
{
	std::cout << "Check function output" << std::endl;
	if (CheckTestCaseInputCheck(CheckCoefs, CheckResults))
	{
		std::cout << "Correct SLAE sizes" << std::endl;
	}
	else
	{
		std::cout << "Incorrect SLAE sizes" << std::endl;
	}
	std::cout << "Expected check function output" << std::endl;
	std::cout << CheckString << std::endl << std::endl;
}

#define OUT

double Power(double ValueToPow, int DegreeOfValue)
{
	double Result = 1;
	for (int32_t i = 0; i < abs(DegreeOfValue); i++)
	{
		Result *= ValueToPow;
	}
	return DegreeOfValue >= 0 ? Result : 1.0 / Result;
}

// Makes Triangle SLAE 
void StraightSolultion(std::vector<std::vector<double>>& Matrix OUT, std::vector<double>& Result OUT)
{
	double CosCoef;
	double SinCoef;

	int32_t SLAESize = Matrix.size();
	std::vector<double> TmpFirstEquation(SLAESize);
	std::vector<double> TmpOtherEquation(SLAESize);
	std::vector<double> TmpResult;

	for (int EquationsNumberInSystem = 0; EquationsNumberInSystem < SLAESize - 1; EquationsNumberInSystem++)
	{
		for (int32_t SystemRow = EquationsNumberInSystem + 1; SystemRow < SLAESize; SystemRow++)
		{
			TmpFirstEquation.clear();
			TmpOtherEquation.clear();
			TmpResult = Result;

			CosCoef = Matrix[EquationsNumberInSystem][EquationsNumberInSystem] / (sqrt(Power(Matrix[EquationsNumberInSystem][EquationsNumberInSystem], 2) + Power(Matrix[SystemRow][EquationsNumberInSystem], 2)));
			SinCoef = Matrix[SystemRow][EquationsNumberInSystem] / (sqrt(Power(Matrix[EquationsNumberInSystem][EquationsNumberInSystem], 2) + Power(Matrix[SystemRow][EquationsNumberInSystem], 2)));

			for (int32_t It = 0; It < SLAESize; It++)
			{
				TmpFirstEquation.push_back(CosCoef * Matrix[EquationsNumberInSystem][It] + SinCoef * Matrix[SystemRow][It]);
				TmpOtherEquation.push_back(-SinCoef * Matrix[EquationsNumberInSystem][It] + CosCoef * Matrix[SystemRow][It]);
			}

			TmpResult[EquationsNumberInSystem] = CosCoef * Result[EquationsNumberInSystem] + SinCoef * Result[SystemRow];
			TmpResult[SystemRow] = -SinCoef * Result[EquationsNumberInSystem] + CosCoef * Result[SystemRow];

			Matrix[EquationsNumberInSystem] = TmpFirstEquation;
			Matrix[SystemRow] = TmpOtherEquation;
			Result = TmpResult;
		}
	}
}

std::vector<double> BackwardSolution(const std::vector<std::vector<double>>& Matrix, const std::vector<double>& Result)
{
	int32_t SLAESize = Result.size();
	std::vector<double> UnitVectorOfSolutions(SLAESize);
	double LastElement;
	LastElement = Result.back() / Matrix.back().back();

	UnitVectorOfSolutions.back() = (UnitVectorOfSolutions.begin(), LastElement);

	for (int32_t Row = SLAESize - 2; Row >= 0; Row--)
	{
		double TmpSum{};
		for (int32_t Column = Row + 1; Column < SLAESize; Column++)
		{
			TmpSum += Matrix[Row][Column] * UnitVectorOfSolutions[Column];
		}
		UnitVectorOfSolutions[Row] = 1.0 / Matrix[Row][Row] * (Result[Row] - TmpSum);
	}
	return UnitVectorOfSolutions;
}

void PrintMatrix(const std::vector<std::vector<double>>& PrintNMatrix, const std::vector<double>& PrintUnitMatrix)
{
	std::cout << "Entry representation of SLAE" << std::endl;

	for (int32_t Row = 0; Row < PrintNMatrix.size(); Row++)
	{
		for (int32_t Column = 0; Column < PrintNMatrix.size(); Column++)
		{
			std::string AdditionalSymbol;
			if (PrintNMatrix[Row][Column] > 0)
			{
				AdditionalSymbol = "+";
			}
			std::cout << " " << AdditionalSymbol << PrintNMatrix[Row][Column] << "*";

			std::cout << "x" + Column;;
		}
		std::cout << " = " << PrintUnitMatrix[Row] << std::endl;
	}
}

void PrintResult(const std::vector<double>& PrintResult)
{
	std::cout << std::endl << "The result of Rotation Method calculation: " << std::endl;
	for (int32_t i = 0; i < PrintResult.size(); i++)
	{
		std::cout << "X" << i << " " << " = " << PrintResult[i] << std::endl;;
	}
}


template <typename T>
void SafeInput(T& CheckParam OUT, std::function<bool(T)> Predicate)
{
	do
	{
		std::stringstream ss;
		std::string InputString;
		std::getline(std::cin, InputString);
		ss << InputString;

		ss >> CheckParam;
		if (Predicate(CheckParam))
		{
			break;
		}
		else
		{
			std::cout << "Incorrect input, try again :" << std::endl;
			continue;
		}
	} while (true);
}

template<typename TT, typename T>
void FillSLAE(TT& SlaeCoef OUT, T& SlaeSolve OUT)
{
	std::cout << "Attention, if you will input garbage, the value automatically set's to Zero!!!" << std::endl;
	int32_t SLAESize = SlaeCoef.size();

	std::function<bool(double)> Lambda = [](double InputValue) {return abs(InputValue) < 1'000'000'000'000; };

	for (int32_t it1 = 0; it1 < SLAESize; it1++)
	{
		std::cout << "Input coef of equation number " << it1 + 1 << std::endl;
		for (int32_t it2 = 0; it2 <= SLAESize; it2++)
		{
			double InputValue;

			if (it2 < SLAESize)
			{
				std::cout << "Input x" << it2 + 1 << " coef: " << std::endl;

				SafeInput(InputValue, Lambda);
				SlaeCoef[it1][it2] = InputValue;
			}
			else
			{
				std::cout << "Input equation result: " << std::endl;
				SafeInput(InputValue, Lambda);
				SlaeSolve[it1] = InputValue;
			}
		}
	}
}

void WaitAndCls()
{
	std::cout << "Press enter to continue checking my labwork... \n";
	std::string EmpyString;
	std::getline(std::cin, EmpyString);
	std::cin.clear();
	system("cls");
}

int main()
{
	{
		std::vector<std::vector<double>> StartingMatrix
		{ {7,1,7},
		{-1,7,1},
		{7,-1,7} };
		std::vector<double> ResultingMatrix{ 15,5,13 }; /*TransMatrix*/

		std::cout << "Default values from student variant : \n";
		PrintMatrix(StartingMatrix, ResultingMatrix);

		StraightSolultion(StartingMatrix, ResultingMatrix);
		std::vector<double> XValues = BackwardSolution(StartingMatrix, ResultingMatrix);

		PrintResult(XValues);

		WaitAndCls();

		// Input data part

		std::cout << "Now you can manually input SLAE raw by raw...\n";
		std::cout << "Be careful to input your number in a right way...\n";
	}
	
	while (true)
	{
		std::cout << "Input size of Matrix, it should be N*N and bigger than 1 \n";
		int32_t Size;
		std::function<bool(int32_t)> Lambda1 = [](int32_t Size) {return Size > 1; };
		SafeInput(Size, Lambda1);
	
		std::vector<std::vector<double>> SlaeCoefficient(Size, std::vector<double>(Size, 0.0));
		std::vector<double> SLAESolve(Size);

		FillSLAE(SlaeCoefficient, SLAESolve);
		PrintMatrix(SlaeCoefficient, SLAESolve);

		StraightSolultion(SlaeCoefficient, SLAESolve);
		std::vector<double> ResultXValues = BackwardSolution(SlaeCoefficient, SLAESolve);
		PrintResult(ResultXValues);

		std::cout << "Input 'y' to continue or 'n' to exit from the programm : \n";
		std::string CheckOutContidionString;
		std::function<bool(std::string)> Lambda2 = [](std::string CheckOutContidionString)
		{
			return CheckOutContidionString == "y" || CheckOutContidionString == "n";
		};
		SafeInput(CheckOutContidionString, Lambda2);
		
		if (CheckOutContidionString == "n")
		{
			break;
		}
		else
		{
			continue;
		}
	}

	system("cls");
	std::cout << "Result of test cases :" << std::endl;

	TestCasesFunction(TestCoef1, TestResult1, ExpectedCheckResult1);
	TestCasesFunction(TestCoef2, TestResult2, ExpectedCheckResult2);
	TestCasesFunction(TestCoef3, TestResult3, ExpectedCheckResult3);
	TestCasesFunction(TestCoef4, TestResult4, ExpectedCheckResult4);
}
