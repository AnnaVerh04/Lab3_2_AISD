#include <iostream>
#include<math.h>
#include<vector>
#include<string>
#include<queue>
#include<map>
#include<set>



using namespace std;

template<typename Vertex = int, typename Dist = double>
class Graph
{
public:
	class Edge
	{
	public:
		Vertex from, to;
		Dist dist;
		Edge(const Vertex& _from, const Vertex& _to, const Dist& d)
		{
			from = _from;
			to = _to;
			dist = d;
		}

	};
};