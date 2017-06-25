#include <iostream>

#include "graph.h"
#include "maze.h"

/* BFS. Saida esperada: (1000000: valor representando infinito)
s = 3
3 1 4 2 0
distances: 2 1 1 0 1 1000000 1000000 1000000 1000000
s = 8
8 6 7 5
distances: 1000000 1000000 1000000 1000000 1000000 2 1 1 0
Conecta as duas componentes do grafo
s = 8
8 6 7 5 1 0 2 3 4
distances: 4 3 4 4 5 2 1 1 0
*/
void bfsTest()
{
	Graph graph1(9);
	graph1.insertEdge(0, 1);
	graph1.insertEdge(1, 2);
	graph1.insertEdge(2, 4);
	graph1.insertEdge(1, 3);
	graph1.insertEdge(5, 6);
	graph1.insertEdge(6, 7);
	graph1.insertEdge(6, 8);
	graph1.insertEdge(4, 3);
	graph1.insertEdge(7, 8);
	graph1.insertEdge(2, 3);

	std::cout << "s = 3" << std::endl;
	graph1.bfs(3);
	std::cout << "distances: ";
	for (int d : graph1.distances)
	{
		std::cout << d << " ";
	}
	std::cout << std::endl;

	std::cout << "s = 8" << std::endl;
	graph1.bfs(8);
	std::cout << "distances: ";
	for (int d : graph1.distances)
	{
		std::cout << d << " ";
	}
	std::cout << std::endl;

	std::cout << "Conecta as duas componentes do grafo" << std::endl;
	graph1.insertEdge(1, 5);
	std::cout << "s = 8" << std::endl;
	graph1.bfs(8);
	std::cout << "distances: ";
	for (int d : graph1.distances)
	{
		std::cout << d << " ";
	}
	std::cout << std::endl;
}

/* DFS. Saida esperada:
s = 3
3 1 0 2 4
s = 8
8 6 5 7
Conecta as duas componentes do grafo
s = 8
8 6 5 1 0 2 4 3 7
*/
void dfsTest()
{
	Graph graph1(9);
	graph1.insertEdge(0, 1);
	graph1.insertEdge(1, 2);
	graph1.insertEdge(2, 4);
	graph1.insertEdge(1, 3);
	graph1.insertEdge(5, 6);
	graph1.insertEdge(6, 7);
	graph1.insertEdge(6, 8);
	graph1.insertEdge(4, 3);
	graph1.insertEdge(7, 8);
	graph1.insertEdge(2, 3);

	std::cout << "s = 3" << std::endl;
	graph1.dfs(3);

	std::cout << "s = 8" << std::endl;
	graph1.dfs(8);

	std::cout << "Conecta as duas componentes do grafo..." << std::endl;
	graph1.insertEdge(1, 5);

	std::cout << "s = 8" << std::endl;
	graph1.dfs(8);
}

/* Bicolored. Saida esperada:
Sim
Sim
Nao
Nao
*/
void bicoloredTest()
{
	Graph graph1(9);
	graph1.insertEdge(0, 1, 10);
	graph1.insertEdge(1, 2, 2);
	graph1.insertEdge(2, 4, 3);
	graph1.insertEdge(1, 3, 14);
	graph1.insertEdge(5, 6, 9);
	graph1.insertEdge(6, 7, 1);
	graph1.insertEdge(6, 8, 4);

	std::cout <<
		(graph1.isBicolored() ? "Sim" : "Nao")
		<< std::endl;

	//Fecha um ciclo par em uma das componentes
	graph1.insertEdge(4, 3, 2);
	std::cout <<
		(graph1.isBicolored() ? "Sim" : "Nao")
		<< std::endl;

	//Fecha um ciclo impar em uma das componentes
	graph1.insertEdge(7, 8, 8);
	std::cout <<
		(graph1.isBicolored() ? "Sim" : "Nao")
		<< std::endl;

	//Fecha um ciclo impar na outra componente
	graph1.insertEdge(2, 3, 9);
	std::cout <<
		(graph1.isBicolored() ? "Sim" : "Nao")
		<< std::endl;
}

/* Djikstra. Saida esperada: (1000000: valor representando infinito)
A partir do no 7: 1000000 1000000 1000000 1000000 1000000 10 1 0 5
A partir do no 3: 17 7 5 0 2 1000000 1000000 1000000 1000000
Conecta as duas componentes do grafo...
A partir do no 3: 17 7 5 0 2 15 24 25 28
*/
void djikstraTest()
{
	Graph graph1(9);
	graph1.insertEdge(0, 1, 10);
	graph1.insertEdge(1, 2, 2);
	graph1.insertEdge(2, 4, 3);
	graph1.insertEdge(1, 3, 14);
	graph1.insertEdge(5, 6, 9);
	graph1.insertEdge(6, 7, 1);
	graph1.insertEdge(6, 8, 4);
	graph1.insertEdge(4, 3, 2);
	graph1.insertEdge(7, 8, 8);
	graph1.insertEdge(2, 3, 9);

	graph1.djikstra(7);
	std::cout << "A partir do no 7: ";
	for (int d : graph1.distances)
	{
		std::cout << d << " ";
	}
	std::cout << std::endl;

	graph1.djikstra(3);
	std::cout << "A partir do no 3: ";
	for (int d : graph1.distances)
	{
		std::cout << d << " ";
	}
	std::cout << std::endl;

	//Unindo as duas componentes conexas:
	std::cout << "Conecta as duas componentes do grafo..." << std::endl;
	graph1.insertEdge(1, 5, 8);

	graph1.djikstra(3);
	std::cout << "A partir do no 3: ";
	for (int d : graph1.distances)
	{
		std::cout << d << " ";
	}
	std::cout << std::endl;
}

/* Kruskal. Saida esperada:
0: 1(10), 3(5)
1: 0(10), 2(2), 3(14)
2: 1(2), 4(3), 3(9)
3: 0(5), 1(14), 2(9)
4: 2(3)
MST:
0: 3(5)
1: 2(2)
2: 1(2), 4(3), 3(9)
3: 0(5), 2(9)
4: 2(3)
*/
void kruskalTest()
{
	Graph graph1(5);
	graph1.insertEdge(0, 1, 10);
	graph1.insertEdge(0, 3, 5);
	graph1.insertEdge(1, 2, 2);
	graph1.insertEdge(2, 4, 3);
	graph1.insertEdge(1, 3, 14);
	graph1.insertEdge(2, 3, 9);

	graph1.print();

	std::cout << "MST:\n";
	Graph mst = graph1.kruskal();
	mst.print();
}

/* Maze start e end. Saida esperada:
+---+---+---+---+---+
|       |           |
+   +---+   +---+   +
|       |       |   |
+---+   +   +---+   +
|       |   |   |   |
+---+   +   +   +   +
|           |       |
+---+---+---+---+---+
start: 13
end: 1
*/
void mazeTest()
{
	int m = 5;
	int n = 4;

	std::vector<bool> maze =
	{
		false, false, true, true, false, false, false, true, true, false,
		false, true, true, false, false, false, true, true, true, false,
		false, true, true, false, true, false, true, false, true, false,
		false, true, false, true, true, true, false, true, true, true
	};

	drawMaze(maze, m, n);

	int start, end;
	findStartEnd(maze, m, n, start, end);

	std::cout << "start: " << start;
	std::cout << "\nend: " << end << std::endl;
}

int main()
{
	// Descomente o teste desejado:

	bfsTest();
	//dfsTest();
	//bicoloredTest();
	//djikstraTest();
	//kruskalTest();
	//mazeTest();

	return 0;
}