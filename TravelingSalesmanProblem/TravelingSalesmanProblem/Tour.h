#pragma once
#include "AnnealingMethod.h"
#include <iostream>

/// <summary>
/// townsRatings - массив рейтингов городов
/// townsTimes - матрица времени прохождения от i городо до j города
/// countTowns - количество городов
/// timeLimit - ограничение по времени на решение
/// startTown - стартовый город
/// AnnelingMethod - метод имитации отжига
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
	/// Устанавливает информацию о городе при этом затирая предыдущую информацию
	/// </summary>
	/// <param name="countTowns"> Количество городов</param>
	/// <param name="townsRating"> Массив рейтинга городов</param>
	/// <param name="townsTimes"> Матрица прохода от одного города до другого</param>
	void setTownsInf(unsigned int countTowns, unsigned int* townsRatings, unsigned int timeLimit, unsigned int startTown, unsigned int** townsTimes);

	/// <summary>
	/// Возвращает максимальный суммарный рейтинг который может пройти коммивояжер
	/// </summary>
	/// <returns> maxRating из annelingMethod</returns>
	unsigned int const& getMaxRating() const;

	/// <summary>
	/// Возвращает путь, при котром достигается макимальный суммарный рейтинг
	/// </summary>
	/// <returns> way из annelingMethod</returns>
	unsigned int const* getWayMaxRating() const;

	/// <summary>
	/// Проверяет корректность информации о городах и запускает метод иммитации отжига
	/// </summary>
	/// <param name="temperature">стартовая темепература</param>
	/// <param name="minTemperature">минимальная температура при которой метод прекращает работу</param>
	/// <param name="coolingRate">скорость охлождения</param>
	void run(double temperature, double minTemperature, double coolingRate);
};