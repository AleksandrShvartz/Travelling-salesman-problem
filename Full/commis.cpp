#include <iostream>
#include <fstream>
#include <fstream>
struct Graph {
	int** adjMatrix; //матрица смежности
	int numVertices; // число городов
	int* townCoolness; // массив рейингов городов 
	int* incl; //1, если i-ая вершина включена в путь
	int* way;//Путь
public:

	int max; //Максимально возможное время
	int cLen = 1; //длина итогового маршрута
	int veryCool = -1; // максимум рейтинга
	Graph(int numVertices, int time) {
		max = time;
		this->numVertices = numVertices;
		adjMatrix = new int* [numVertices];

		for (int i = 0; i < numVertices; i++) {
			adjMatrix[i] = new int[numVertices];
			for (int j = 0; j < numVertices; j++)
				adjMatrix[i][j] = false;
		}

		incl = new int[numVertices]; //true, если i-ая вершина включена в путь
		way = new int[numVertices];
		townCoolness = new int[numVertices];

		for (int i = 0; i < numVertices; i++) {

			way[i] = -1;
			incl[i] = 0;
		}

	}



	bool isEdge(int i, int j) {
		return adjMatrix[i][j];
	}//Есть ли такое ребро
	void toString() {
		for (int i = 0; i < numVertices; i++) {
			std::cout << i << " : ";
			for (int j = 0; j < numVertices; j++)
				std::cout << adjMatrix[i][j] << " ";
			std::cout << "\n";
		}
	} //Вывод матрицы
	int calculate() {
		int locMax = -1;
		veryCool = townCoolness[0];
		for (int i = 1; i != numVertices; ++i) //Ищем все возможные пути из точки 0 во все другие, выбирая самый высокий по рейтингу
		{
			for (int t = 0; t < numVertices; t++) incl[t] = 0;
			step(0, i, 0, max, 0);
		}
		if (cLen > 1) { //Если путь вообще есть
			for (int i = 0; i != cLen; ++i)
				;	//std::cout << way[i] << " ";
		}
		else
			//std::cout << 0;
		std::cout << "\nCoolness: " << veryCool;
		return veryCool;
	}
	void step(int s, int f, int p, int time, int howCool) { //рекурсивный поиск шага пути. p - количество городов в пути
		incl[s] = 1;
		if (s == f) { //Если дошли из s в f
			howCool += townCoolness[s];
			if (howCool > this->veryCool) {
				this->veryCool = howCool;
				way[p] = f;
				cLen = p + 1;
			}

		}
		else { //Если не дошли, ищем дальше

			for (int i = 0; i != numVertices; ++i)
			{

				if (adjMatrix[s][i] && (time - adjMatrix[s][i]) >= 0 && !incl[i]) {

					way[p] = s;
					step(i, f, p + 1, (time - adjMatrix[s][i]), howCool + townCoolness[s]);
					incl[i] = 0;
				}
			}
		}

	}

	~Graph() {
		for (int i = 0; i < numVertices; i++) {
			delete[] adjMatrix[i];
		}
		delete[] adjMatrix;
		delete[] incl;
		delete[] way;
	}
};





int main() {
	std::ifstream fin("d:\Downloads\Telegram Desktop\file (4).txt");
	int count = fscanf(fid, '%*s\n%d\n', 1);
	int* times = new int[count];
	int* error = new int[count];
	int* iis = new int[count];
	for (int k = 0; k != count; k++) {











	}


	int m,t;
	std::cin >> m>>t;


	Graph g(m,t);

	for (int i = 0; i != m; ++i)
		std::cin >> g.townCoolness[i];
	for (int i = 0; i != m; ++i)
		for (int j = 0; j != m; ++j)
			std::cin >> g.adjMatrix[i][j];


	//g.toString();
	g.calculate();
}