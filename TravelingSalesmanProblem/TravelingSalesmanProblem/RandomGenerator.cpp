#include "RandomGenerator.h"
#include <random>
#include <algorithm>
#include <iostream>

bool comp(unsigned int a, unsigned int b)
{ 
	return (a > b); 
}

void RandomGenerator::generateRandomRating(unsigned int minRating, unsigned int maxRaiting)
{
	std::random_device random_device;
	std::mt19937 generator(random_device());

	std::uniform_int_distribution<> distribution(minRating, maxRaiting);

	ratingVector = new unsigned int[size];

	for (int i = 0; i < size; i++)
		ratingVector[i] = distribution(generator);
}

void RandomGenerator::generateRandomWay()
{
	std::vector<unsigned int> tmpWay;
	for (unsigned int i = 0; i < size; i++)
	{
		tmpWay.push_back(i);
	}
	std::vector<unsigned int> tmpRatings(ratingVector, ratingVector + size);

	for (int i = 2; i < size; i++)
		for (int j = i; j > 1 && tmpRatings[j - 1] < tmpRatings[j]; j--)
		{
			std::swap(tmpRatings[j - 1], tmpRatings[j]);
			std::swap(tmpWay[j - 1], tmpWay[j]);
		}
	
	maxRaitingWay = new unsigned int[size];
	std::copy(tmpWay.begin(), tmpWay.end(), maxRaitingWay);
}

// timeLimit должен быть меньше maxTime
void RandomGenerator::generateTimeMatrix(unsigned int minTime, unsigned int maxTime, unsigned int timeLimit)
{
	this->timeLimit = timeLimit;

	std::random_device random_device;
	std::mt19937 generator(random_device());

	std::uniform_int_distribution<> distribution1(minTime, (unsigned int) maxTime / 2);
	std::uniform_int_distribution<> distribution2(maxTime / 2, maxTime);

	timeMatrix = new unsigned int*[size];
	int tmpIndex = maxRaitingWay[0];
	for (int i = 0; i < size; i++)
	{
		timeMatrix[i] = new unsigned int[size];
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = i; j < size; j++)
		{
			if (i == j)
			{
				timeMatrix[i][j] = 0;
				continue;
			}

			timeMatrix[i][j] = distribution2(generator);
			timeMatrix[j][i] = timeMatrix[i][j];
		}
	}

	for (int i = 0; i < size; i++)
	{
		if (i != size - 1)
		{
			timeMatrix[maxRaitingWay[i]][maxRaitingWay[i + 1]] = distribution1(generator);
			timeMatrix[maxRaitingWay[i + 1]][maxRaitingWay[i]] = timeMatrix[maxRaitingWay[i]][maxRaitingWay[i + 1]];
		}
		else
		{
			timeMatrix[maxRaitingWay[i]][0] = distribution1(generator);
			timeMatrix[0][maxRaitingWay[i]] = timeMatrix[maxRaitingWay[i]][0];
		}
	}

	maxRaiting += ratingVector[0];
	int tmpTimeSum = 0;
	int tmp = 0;
	for (int i = 0; i < size - 1 && tmpTimeSum <= timeLimit; i++)
	{
		tmp = tmpTimeSum;
		tmpTimeSum += timeMatrix[maxRaitingWay[i]][maxRaitingWay[i + 1]];
		if (tmpTimeSum > timeLimit)
		{
			this->timeLimit = tmp;
			break;
		}
		maxRaiting += ratingVector[maxRaitingWay[i + 1]];
	}
}

void RandomGenerator::generate(unsigned int minRating, unsigned int maxRaiting, unsigned int minTime, unsigned int maxTime, unsigned int timeLimit)
{
	generateRandomRating(minRating, maxRaiting);
	generateRandomWay();
	generateTimeMatrix(minTime, maxTime, timeLimit);
}

void RandomGenerator::writeInFile(std::ostream& stream)
{
	stream << "Size:\n" << size << std::endl;

	stream << "Time limit:\n" << timeLimit << std::endl;

	stream << "Raitings:" << std::endl;
	for (int i = 0; i < size; i++)
	{
		if (i != size - 1)
			stream << ratingVector[i] << " ";
		else
			stream << ratingVector[i] << std::endl;
	}

	stream << "Times:" << std::endl;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (j != size - 1)
				stream << timeMatrix[i][j] << " ";
			else
				stream << timeMatrix[i][j];
		}
		stream << std::endl;
	}

	stream << "Max raiting:\n" << maxRaiting << std::endl;

	stream << "Way:" << std::endl;
	for (int i = 0; i < size; i++)
	{
		if (i != size - 1)
			stream << maxRaitingWay[i] << " ";
		else
			stream << maxRaitingWay[i] << std::endl;
	}
}

/*
* Записать количество городов
* Записать ограничение по времени
* Записать рейтинги
* Записать матрицу времени
* Записать максимальный суммарный рейтинг
* Записать путь макисмального суммарного рейтинга
*/

/*
* Замечания:
* 1. Стартовый город 0
* 2. Он не учитывается в максимальноьм рейтинге
* 3. Если в конце пути стоит 0, это значит, что коммивояжер вернулся в исходный пункт, обойдя все города. 
		В этом случае рейтинг нулевого города прибавляется к максимальному рейтингу
*/