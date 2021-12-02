#include "Tour.h"

Tour::Tour(unsigned int countTowns, unsigned int* townsRating, unsigned int timeLimit, unsigned int startTown, unsigned int** townsTimes)
{
	this->countTowns = countTowns;
	this->startTown = startTown;
	this->townsRatings = townsRating;
	this->townsTimes = townsTimes;
	this->timeLimit = timeLimit;
}

Tour::~Tour()
{
	if (townsTimes != nullptr)
	{
		for (int i = 0; i < countTowns; i++)
		{
			delete[] townsTimes[i];
		}
		delete townsTimes;
		townsTimes = nullptr;
	}
	if (townsRatings != nullptr)
	{
		delete townsRatings;
		townsRatings = nullptr;
	}
}

void Tour::setTownsInf(unsigned int countTowns, unsigned int* townsRatings, unsigned int timeLimit, unsigned int startTown, unsigned int** townsTimes)
{
	if (townsTimes != nullptr)
	{
		for (int i = 0; i < countTowns; i++)
		{
			delete[] townsTimes[i];
		}
		delete townsTimes;
		townsTimes = nullptr;
	}
	if (townsRatings != nullptr)
	{
		delete townsRatings;
		townsRatings = nullptr;
	}

	this->countTowns = countTowns;
	this->startTown = startTown;
	this->townsRatings = townsRatings;
	this->townsTimes = townsTimes;
	this->timeLimit = timeLimit;
}

unsigned int const& Tour::getMaxRating() const
{
	return annelingMethod->getMaxRating();
}

unsigned int const* Tour::getWayMaxRating() const
{
	return annelingMethod->getWay();
}

void Tour::run(double temperature, double minTemperature, double coolingRate)
{
	this->annelingMethod = std::make_unique<AnnelingMethod>(temperature, coolingRate, minTemperature);

	annelingMethod->run(townsRatings, townsTimes, startTown, countTowns, timeLimit);
}
