#include "Graph.h"

using namespace std;

int main()
{
	Graph<int, double> g;
	for (int i = 0; i < 10; i++)
	{
		int v = i;
		g.add_vertex(v);
	}
	int v1, v2;
	double d;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> v1 >> v2 >> d;
		g.add_edge(v1, v2, d);
	}
	vector<int> ver = g.vertices();
	int vertex = -1;
	double dist = INF;
	for (int i = 0; i < ver.size(); i++)
	{
		d = g.shortest_longest_path(ver[i]);
		if (dist > d)
		{
			dist = d;
			vertex = ver[i];
		}
	}
	cout << vertex << endl;
}