#include "Tour.h"
#include <fstream>
#include <random>
#include <chrono>
#include "RandomGenerator.h"
#include <sstream>
#include <cmath>

void parse()
{
	std::ifstream file("file.txt");
	std::ofstream workingHoursFromSize("workingHoursFromSize.txt");
	std::ofstream solutionAccuracy("solutionAccuracy.txt");

	unsigned int size = 0;
	unsigned int timeLimit = 0;
	unsigned int* ratings = nullptr;
	unsigned int** times = nullptr;

	std::string line;

	int index = 0;
	int p = 5;

	std::getline(file, line);
	std::getline(file, line);
	while (std::getline(file, line))
	{
		if (line == "Size:")
		{
			std::getline(file, line);
			size = std::stoi(line);
		}

		std::getline(file, line);
		if (line == "Time limit:")
		{
			std::getline(file, line);
			timeLimit = std::stoi(line);
		}

		std::getline(file, line);
		if (line == "Raitings:")
		{
			std::getline(file, line);
			std::stringstream ss;
			ss << line;
			std::string num;
			ratings = new unsigned int[size];
			for (int i = 0; i < size; i++)
			{
				ss >> num;
				ratings[i] = std::stoi(num);
			}
		}

		std::getline(file, line);
		if (line == "Times:")
		{
			times = new unsigned int* [size];
			for (int i = 0; i < size; i++)
			{
				std::getline(file, line);
				std::stringstream ss;
				ss << line;
				std::string num;
				times[i] = new unsigned int[size];
				for (int j = 0; j < size; j++)
				{
					ss >> num;
					times[i][j] = std::stoi(num);
				}
			}
		}

		unsigned int max = 0;
		std::getline(file, line);
		if (line == "Max raiting:")
		{
			std::getline(file, line);
			max = std::stoi(line);
		}
		std::getline(file, line);
		std::getline(file, line);

		/*if (index % 5 == 0)
			p++;*/

		auto begin = std::chrono::steady_clock::now();
		Tour tour(size, ratings, timeLimit, 0, times);
		tour.run(10000, pow(0.1, p), 0.99999);
		auto end = std::chrono::steady_clock::now();
		auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
		workingHoursFromSize << elapsed_ms.count()/*(int)max - (int)tour.getMaxRating()*/ << " ";
		solutionAccuracy << (double)((int)max - (int)tour.getMaxRating()) / (double)max << " ";
		//std::cout << (int)max - (int)tour.getMaxRating() << " ";
		std::cout << index++ << std::endl;
	}

	file.close();
	workingHoursFromSize.close();
	solutionAccuracy.close();
}

int main()
{

	/*std::ofstream file("file.txt");
	file << "Iterations:\n" << 497 << std::endl;
	for (int i = 3; i < 501; i += 1)
	{
		std::cout << i << std::endl;
		RandomGenerator randomGenerator(i);
		randomGenerator.generate(1, i, 10, 100, i * 10);
		randomGenerator.writeInFile(file);
	}
	file.close();*/


	//while (1)
	//parse();

	return 0;
}


/* Графики
* Время от количества городов
* Память от количества городов
* Точность найденного решения от количества городов
* Время от температуры
* Точность от температуры
* Максимальная температура от итерации
*/

/*
* 1. Создать вектор рейтингов
* 2. Построить для него путь
* 3. Создать ограничения чтобы этот путь был максимальным
* 4. Создать матрицу времени, чтобы максимальный путь сохранился
*/

/*
* 1. Берем решенную задачу коммивояжера
* 2. Делаем максимальный рейтинг для какой-то часит пути
* 3. Устанавливаем ограничение в качестве этого максимума
*/



//struct Graph {
//	int** adjMatrix; //матрица смежности
//	int numVertices; // число городов
//	int* townCoolness; // массив рейингов городов 
//	int* incl; //1, если i-ая вершина включена в путь
//	int* way;//Путь
//public:
//
//	int max; //Максимально возможное время
//	int cLen = 1; //длина итогового маршрута
//	int veryCool = -1; // максимум рейтинга
//	Graph(int numVertices) {
//
//		std::cin >> max;
//		this->numVertices = numVertices;
//		adjMatrix = new int* [numVertices];
//
//		for (int i = 0; i < numVertices; i++) {
//			adjMatrix[i] = new int[numVertices];
//			for (int j = 0; j < numVertices; j++)
//				adjMatrix[i][j] = false;
//		}
//
//		incl = new int[numVertices]; //true, если i-ая вершина включена в путь
//		way = new int[numVertices];
//		townCoolness = new int[numVertices];
//
//		for (int i = 0; i < numVertices; i++) {
//
//			way[i] = -1;
//			incl[i] = 0;
//		}
//
//	}
//
//
//
//	bool isEdge(int i, int j) {
//		return adjMatrix[i][j];
//	}//Есть ли такое ребро
//	void toString() {
//		for (int i = 0; i < numVertices; i++) {
//			std::cout << i << " : ";
//			for (int j = 0; j < numVertices; j++)
//				std::cout << adjMatrix[i][j] << " ";
//			std::cout << "\n";
//		}
//	} //Вывод матрицы
//	int calculate() {
//		int locMax = -1;
//		veryCool = townCoolness[0];
//		for (int i = 1; i != numVertices; ++i) //Ищем все возможные пути из точки 0 во все другие, выбирая самый высокий по рейтингу
//		{
//			for (int t = 0; t < numVertices; t++) incl[t] = 0;
//			step(0, i, 0, max, 0);
//		}
//		if (cLen > 1) { //Если путь вообще есть
//			for (int i = 0; i != cLen; ++i)
//				std::cout << way[i] << " ";
//		}
//		else
//			std::cout << 0;
//		std::cout << "\nCoolness: " << veryCool;
//		return veryCool;
//	}
//	void step(int s, int f, int p, int time, int howCool) { //рекурсивный поиск шага пути. p - количество городов в пути
//		incl[s] = 1;
//		if (s == f) { //Если дошли из s в f
//			howCool += townCoolness[s];
//			if (howCool > this->veryCool) {
//				this->veryCool = howCool;
//				way[p] = f;
//				cLen = p + 1;
//			}
//			incl[s] = 0;
//		}
//		else { //Если не дошли, ищем дальше
//
//			for (int i = 0; i != numVertices; ++i)
//			{
//				if (adjMatrix[s][i] != 0 && (time - adjMatrix[s][i]) >= 0 && incl[i] == 0) {
//					way[p] = s;
//					step(i, f, p + 1, (time - adjMatrix[s][i]), howCool + townCoolness[s]);
//					incl[i] = 0;
//				}
//			}
//		}
//
//	}
//
//	~Graph() {
//		for (int i = 0; i < numVertices; i++) {
//			delete[] adjMatrix[i];
//		}
//		delete[] adjMatrix;
//		delete[] incl;
//		delete[] way;
//	}
//};
//
//int main() {
//	int m;
//	std::cin >> m;
//
//
//	Graph g(m);
//
//	for (int i = 0; i < m; ++i)
//		std::cin >> g.townCoolness[i];
//	for (int i = 0; i != m; ++i)
//		for (int j = 0; j != m; ++j)
//			std::cin >> g.adjMatrix[i][j];
//
//
//	//g.toString();
//	g.calculate();
//}