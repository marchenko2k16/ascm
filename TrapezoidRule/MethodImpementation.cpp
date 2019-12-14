#include <functional>
#include <iostream>
#include <vector>
#include <sstream>

#define OUT

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


void CalculateIntegralValueWithTrapezoidRule(double InLeftBoundary, double InRightBoundary, double InAccuracy, std::function<double(double)> InFunction)
{
	double LeftBoundary = InLeftBoundary;
	double RightBoundary = InRightBoundary;
	int32_t SectionNumber = 2; // Default start value
	double Accuracy = InAccuracy;
	double Result{};
	double PrevResult{};
	do
	{
		double Height = (RightBoundary - LeftBoundary) / SectionNumber;

		double MiddleSectionsSum{};
		for (double Step = LeftBoundary + Height; Step < RightBoundary; Step += Height)
		{
			MiddleSectionsSum += InFunction(Step);
		}

		PrevResult = Result;
		Result = (Height / 2) * (InFunction(LeftBoundary) + 2 * MiddleSectionsSum + InFunction(RightBoundary));
		SectionNumber *= 2;
	} while (abs(Result - PrevResult) > Accuracy);

	std::cout << "Given Accuracy is " << Accuracy << std::endl;
	std::cout << "Number of sections to achieve given Accuracy " << SectionNumber << std::endl;
	std::cout << "The Value of integral is  " << Result << std::endl;
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
	std::function<double(double)> GivenFunction = [&](double XValue) {return XValue * pow(3, -XValue); };
	std::function<bool(double)> LambdaCheck = [](double Param) {return abs(Param) < 1'000'000'000'000; };

	std::cout << "This is calculation of given task: " << std::endl << std::endl;
	CalculateIntegralValueWithTrapezoidRule(0, 2, 0.001, GivenFunction);

	do 
	{
		WaitAndCls();
		std::pair<double, double> Bounds;
		std::cout << "Now you can manually input boundaries...\n";
		std::cout << "Be careful, the upper bound should not be bigger then lower...\n\n";


		std::cout << "ATTENTION, if you will input garbage, the value automatically set's to Zero!!!" << std::endl;

		do
		{
			std::cout << "Input lower bound : " << std::endl;
			SafeInput(Bounds.first, LambdaCheck);

			std::cout << "Input upper bound : " << std::endl;
			SafeInput(Bounds.second, LambdaCheck);

			if (Bounds.first <= Bounds.second)
			{
				CalculateIntegralValueWithTrapezoidRule(Bounds.first, Bounds.second, 0.001, GivenFunction);
				break;
			}
			else
			{
				std::cout << "Incorrect values, reenter pls." << std::endl;
			}

		} while (true);


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
	} while (true);
}