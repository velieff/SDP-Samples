#ifndef _GRAPH_HEADER_
#define _GRAPH_HEADER_

const int MAX = 100;

class Graph
{
public:
	int a[MAX][MAX];
	Graph()
	{
		for (int i = 0; i < MAX; i++)
		{
			for (int j = 0; j < MAX; j++)
			{
				a[i][j] = 0;
			}
		}
	}
	~Graph() {}
};

#endif
