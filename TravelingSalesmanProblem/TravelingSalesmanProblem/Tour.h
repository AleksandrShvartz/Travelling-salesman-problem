#pragma once
#include "AnnealingMethod.h"
#include <iostream>

/// <summary>
/// townsRatings - ������ ��������� �������
/// townsTimes - ������� ������� ����������� �� i ������ �� j ������
/// countTowns - ���������� �������
/// timeLimit - ����������� �� ������� �� �������
/// startTown - ��������� �����
/// AnnelingMethod - ����� �������� ������
/// </summary>
class Tour
{
private:
	unsigned int* townsRatings = nullptr;
	unsigned int** townsTimes = nullptr;

	unsigned int countTowns = 0;
	unsigned int timeLimit = 0;
	unsigned int startTown = 0;

	std::unique_ptr<AnnelingMethod> annelingMethod;

public:
	Tour(unsigned int countTowns, unsigned int* townsRating, unsigned int timeLimit, unsigned int startTown, unsigned int** townsTimes);

	~Tour();

	/// <summary>
	/// ������������� ���������� � ������ ��� ���� ������� ���������� ����������
	/// </summary>
	/// <param name="countTowns"> ���������� �������</param>
	/// <param name="townsRating"> ������ �������� �������</param>
	/// <param name="townsTimes"> ������� ������� �� ������ ������ �� �������</param>
	void setTownsInf(unsigned int countTowns, unsigned int* townsRatings, unsigned int timeLimit, unsigned int startTown, unsigned int** townsTimes);

	/// <summary>
	/// ���������� ������������ ��������� ������� ������� ����� ������ �����������
	/// </summary>
	/// <returns> maxRating �� annelingMethod</returns>
	unsigned int const& getMaxRating() const;

	/// <summary>
	/// ���������� ����, ��� ������ ����������� ����������� ��������� �������
	/// </summary>
	/// <returns> way �� annelingMethod</returns>
	unsigned int const* getWayMaxRating() const;

	/// <summary>
	/// ��������� ������������ ���������� � ������� � ��������� ����� ��������� ������
	/// </summary>
	/// <param name="temperature">��������� ������������</param>
	/// <param name="minTemperature">����������� ����������� ��� ������� ����� ���������� ������</param>
	/// <param name="coolingRate">�������� ����������</param>
	void run(double temperature, double minTemperature, double coolingRate);
};