#include "AnnealingMethod.h"
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>
#include <cmath>
#include <iostream>

AnnelingMethod::AnnelingMethod(const double temperature, const double coolingRate, const double minTemperature)
{
	if (coolingRate <= 0)
		throw std::exception("CoolingRate can't be less then 0");
	if (coolingRate >= 1)
		throw std::exception("CoolingRate can't be more then 1");
	if (temperature <= 0)
		throw std::exception("Temperature can't be less then 0");
	if (minTemperature <= 0)
		throw std::exception("minTemperature can't be less then 0");

	this->coolingRate = coolingRate;
	this->temperature = temperature;
	this->minTemperature = minTemperature;
}

AnnelingMethod::~AnnelingMethod()
{
	if (way != nullptr)
	{
		delete[] way;
	}
}

void AnnelingMethod::setTemperature(double temperature)
{
	this->temperature = temperature;
}

void AnnelingMethod::setCoolingRate(double coolingRate)
{
	this->coolingRate = coolingRate;
}

unsigned int const* AnnelingMethod::getWay() const
{
	return way;
}

unsigned int const& AnnelingMethod::getMaxRating() const
{
	return maxRating;
}

int myrandom(int i) { return std::rand() % i; }

void AnnelingMethod::run(unsigned int* townsRatings, unsigned int** townsTimes, unsigned int startTown, unsigned int countTowns, unsigned int timeLimit)
{
	std::srand(unsigned(std::time(0)));
	std::vector<unsigned int> curWay;
	unsigned int curMax = 0;

	for(int i = 0; i < countTowns; i++)
	{
		curWay.push_back(i);
	}
	std::swap(curWay[0], curWay[startTown]);

	std::random_shuffle(curWay.begin() + 1, curWay.end(), myrandom);

	curMax += townsRatings[startTown];
	unsigned int time = 0;
	for (int i = 0; i < countTowns - 1; i++)
	{
		time += townsTimes[curWay[i]][curWay[i + 1]];
		if (time > timeLimit)
		{
			break;
		}
		curMax += townsRatings[curWay[i + 1]];

		/*if (i != countTowns - 1)
		{
			time += townsTimes[curWay[i]][curWay[i + 1]];
			if (time > timeLimit)
			{
				break;
			}
			curMax += townsRatings[curWay[i + 1]];
		}
		else
		{
			time += townsTimes[curWay[i]][curWay[0]];
			if (time > timeLimit)
			{
				break;
			}
			curMax += townsRatings[curWay[0]];
		}*/
	}

	double tmpTemperature = temperature;

	std::random_device random_device;
	std::mt19937 generator(random_device()); 

	while (tmpTemperature > minTemperature)
	{
		std::vector<unsigned int> tmpWay(curWay);

		std::uniform_int_distribution<> distribution(1, countTowns - 1);
		std::uniform_int_distribution<> distributionY(1, countTowns - 1);

		int x = distribution(generator);
		int y = distributionY(generator);
		std::swap(tmpWay[x], tmpWay[y]);

		unsigned int tmpMax = townsRatings[startTown];
		unsigned int tmpTime = 0;
		for (int i = 0; i < countTowns - 1; i++)
		{
			tmpTime += townsTimes[tmpWay[i]][tmpWay[i + 1]];
			if (tmpTime > timeLimit)
			{
				break;
			}
			tmpMax += townsRatings[tmpWay[i + 1]];

			/*if (i != countTowns - 1)
			{
				tmpTime += townsTimes[tmpWay[i]][tmpWay[i + 1]];
				if (tmpTime > timeLimit)
				{
					break;
				}
				tmpMax += townsRatings[tmpWay[i + 1]];
			}
			else
			{
				tmpTime += townsTimes[tmpWay[i]][tmpWay[0]];
				if (tmpTime > timeLimit)
				{
					break;
				}
				tmpMax += townsRatings[tmpWay[0]];
			}*/
		}

		int delta = tmpMax - curMax;

		if (delta >= 0)
		{
			curMax = tmpMax;
			curWay = tmpWay;
		}
		else
		{
			double a = exp(delta / tmpTemperature);

			double b = ((double)rand() / (double)RAND_MAX);
			if (a > b)
			{
				delta += 1;
				curMax = tmpMax;
				curWay = tmpWay;
			}
		}

		tmpTemperature = coolingRate*tmpTemperature;
	}
	
	maxRating = curMax;

	if (way != nullptr)
		delete[] way;

	way = new unsigned int[countTowns];
	for (int i = 0; i < countTowns; i++)
		way[i] = curWay[i];
}
