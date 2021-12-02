#pragma once
#include <string>
#include <fstream>

class RandomGenerator
{
private:
	unsigned int size;
	unsigned int* ratingVector;
	unsigned int** timeMatrix;
	unsigned int* maxRaitingWay;
	unsigned int maxRaiting;
	unsigned int timeLimit;

	void generateRandomRating(unsigned int minRating, unsigned int maxRaiting);

	void generateRandomWay();

	void generateTimeMatrix(unsigned int minTime, unsigned int maxTime, unsigned int timeLimit);

public:
	RandomGenerator(unsigned int size)
		: size(size), ratingVector(nullptr), timeMatrix(nullptr), maxRaiting(0), maxRaitingWay(nullptr), timeLimit(0) {}
	void generate(unsigned int minRating, unsigned int maxRaiting, unsigned int minTime, unsigned int maxTime, unsigned int timeLimit);
	void writeInFile(std::ostream& stream);

	int getSize() { return size; }
	unsigned int* getRatingVector() { return ratingVector; }
	unsigned int** getTimeMatrix() { return timeMatrix; }
	unsigned int* getMaxRatingWay() { return maxRaitingWay; }
	unsigned int getMaxRating() { return maxRaiting; }
	unsigned int getTimeLimit() { return timeLimit; }

	~RandomGenerator()
	{
		delete[] ratingVector;
		delete[] maxRaitingWay;
		for (int i = 0; i < size; i++)
		{
			delete[] timeMatrix[i];
		}
		delete[] timeMatrix;
	}
};