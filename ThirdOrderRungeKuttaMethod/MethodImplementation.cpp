#include <vector>
#include <iostream>
#include <functional>
#include <sstream>

#include "gnuplot_i.hpp"

template <typename T>
void SafeInput(T& CheckParam, std::function<bool(T)> Predicate)
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

double_t EntryY = 0.7;
double_t EntryX = 0.0;
constexpr int32_t KuttaOrder = 3;

std::vector<double_t> XValues;
std::vector<double_t> YValues;

Gnuplot gp;
void draw(std::vector<double_t> x, std::vector<double_t> y)
{
	gp.set_style("lines");
	gp.plot_xy(x, y, "Graph");

	gp.set_style("points");
	gp.plot_xy(x, y, "Points");
}


double_t Derivative(double_t x, double_t y)
{
	return pow(x, 2) + pow(y, 2);
}

std::vector<double_t> C{ 0.0, 0.5, 1.0 };
std::vector<double_t> B{ 1.0/6.0, 2.0/3.0, 1.0/6.0 };
std::vector<std::vector<double_t>> A
{
	{0.0, 0.0, 0.0},
	{0.5, 0.0, 0.0},
	{-1.0, 2.0, 0.0} 
};

std::vector<double_t> K(3, 0);

int main()
{
	int32_t N;
	std::cout << "Input number of intervals in range [1; 10.000] : \n";
	std::function<bool(int32_t)> Lambda1 = [](int32_t Size) {return Size > 1 && Size < 10'000; };
	SafeInput(N, Lambda1);

	double_t InputX;
	std::cout << "Input X point in range [0.001; 1.0]\n";
	std::function<bool(double_t)> Lambda2 = [](double_t Var) {return Var > 0.000'001 && Var < 1.000'000; };
	SafeInput(InputX, Lambda2);

	std::cin >> InputX;

	double_t H = (InputX - EntryX) / N;

	double_t Yn = EntryY;
	double_t DesiredY{};

	for (double_t Xn = EntryX; Xn <= InputX; Xn += H)
	{
		K[0] = 0;
		K[1] = 0;
		K[2] = 0;

		double_t KiBiSum{};
		for (int32_t it2 = 0; it2 < KuttaOrder; it2++)
		{
			double_t KiSum{};
			for (int32_t it3 = 0; it3 < it2; it3++)
			{
				KiSum += A[it2][it3] * K[it3];
			}

			K[it2] = Derivative(Xn + C[it2] * H, Yn + H * KiSum);
			KiBiSum += B[it2] * K[it2];
		}

		DesiredY = Yn + H * KiBiSum;
		Yn = DesiredY;
		XValues.push_back(Xn);
		YValues.push_back(Yn);
	}

	std::cout << "Result " << DesiredY;

	draw(XValues, YValues);
	std::cin.clear();
	std::cin.get();
	std::cin.get();
}