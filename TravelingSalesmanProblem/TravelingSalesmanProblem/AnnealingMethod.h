#pragma once

/// <summary>
/// way - ������ ��������� �� ������������������ �������, ������� ���������� ����
/// maxRating - ������������ ������� �������, ������ ����� ������ �� ������������ �����
/// temperature - 
/// </summary>
class AnnelingMethod
{
private:
	unsigned int* way = nullptr;
	unsigned int maxRating = 0;

	double temperature = 0;
	double coolingRate = 0;
	double minTemperature = 0;
public:
	AnnelingMethod() {};
	AnnelingMethod(const double temperature, const double coolingRate, const double minTemperature);

	~AnnelingMethod();

	/// <summary>
	/// ������������� �����������
	/// </summary>
	/// <param name="temperature">����� �����������</param>
	void setTemperature(double temperature);

	/// <summary>
	/// ������������� �������� ����������
	/// </summary>
	/// <param name="coolingRate">����� �������� ����������</param>
	void setCoolingRate(double coolingRate);

	/// <summary>
	/// ���������� ����, ��� ������� ����������� ������������ ��������� �������
	/// </summary>
	/// <returns>way</returns>
	unsigned int const* getWay() const;

	/// <summary>
	/// ���������� ������������ �������
	/// </summary>
	/// <returns>maxRating</returns>
	unsigned int const& getMaxRating() const;

	/// <summary>
	/// ��������� �������� ��������� ������
	/// </summary>
	/// <param name="townsRatings">�������� �������</param>
	/// <param name="townsTimes">����� ����������� �� ������ ������ �� �������</param>
	/// <param name="countTowns">���������� �������</param>
	/// <param name="timeLimits">����������� �� �������</param>
	void run(unsigned int* townsRatings, unsigned int** townsTimes, unsigned int startTown, unsigned int countTowns, unsigned int timeLimits);
};