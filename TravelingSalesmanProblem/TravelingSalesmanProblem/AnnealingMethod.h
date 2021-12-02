#pragma once

/// <summary>
/// way - массив состоящий из последовательности городов, которая составляет путь
/// maxRating - максимальный рейтинг городов, кторый может пройти за определенное время
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
	/// Устанавливает температуру
	/// </summary>
	/// <param name="temperature">Новая температура</param>
	void setTemperature(double temperature);

	/// <summary>
	/// Устанавливает скорость охлождения
	/// </summary>
	/// <param name="coolingRate">Новая скорость охлождения</param>
	void setCoolingRate(double coolingRate);

	/// <summary>
	/// Возвращает путь, при котором достигается максимальный суммарный рейтинг
	/// </summary>
	/// <returns>way</returns>
	unsigned int const* getWay() const;

	/// <summary>
	/// Возвращает максимальный рейтинг
	/// </summary>
	/// <returns>maxRating</returns>
	unsigned int const& getMaxRating() const;

	/// <summary>
	/// Запускает алгоритм иммитации отжига
	/// </summary>
	/// <param name="townsRatings">Рейтинги городов</param>
	/// <param name="townsTimes">Время прохождеиня от одного города до другого</param>
	/// <param name="countTowns">Количество городов</param>
	/// <param name="timeLimits">Ограничение по времени</param>
	void run(unsigned int* townsRatings, unsigned int** townsTimes, unsigned int startTown, unsigned int countTowns, unsigned int timeLimits);
};