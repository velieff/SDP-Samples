#include<iostream>
#include"Graph.h"

// 1. Find vertexes, which has no successors.
void task1(Graph g, int v)
{
	for (int i = 0; i < v; i++)
	{
		bool flag = true;
		for (int j = 0; j < v; j++)
		{
			if (g.a[i][j] == 1)
				flag = false;
		}
		if (flag)
			std::cout << i + 1 << ' ';
	}
	std::cout << '\n';
}

// 2. Find vertexes which have edges to 'u' (vertex).
void task2(int u, Graph g, int v)
{
	for (int i = 0; i < v; i++)
	{
		if(g.a[u-1][i] == 1)
			std::cout << i + 1 << ' ';
	}
	std::cout << '\n';
}

// 3. Check if the graph is symetric.
bool task3(Graph g, int v)
{
	for (int i = 0; i < v; i++)
	{
		for (int j = i + 1; j < v; j++)
		{
			if (g.a[i][j] != g.a[j][i])
				return false;
		}
	}
	return true;
}


int main()
{
	Graph g;
	g.a[0][1] = 1;
	g.a[0][2] = 1;
	g.a[0][3] = 1;
	g.a[0][4] = 1;
	g.a[1][3] = 1;
	g.a[2][3] = 1;
	g.a[2][4] = 1;

	task1(g, 5);
	task2(1, g, 5);
	std::cout << task3(g, 5) << '\n';

	return 0;
}