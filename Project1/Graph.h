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


	map<Vertex, vector<pair<Dist, Vertex>>> graph;
	set<Edge> edgeset;
	multiset < pair<Vertex, Vertex>> checkedge;

	bool has_vertex(const Vertex& v)const
	{
		return graph.find(v) != graph.end();
	}

	void add_vertex(const Vertex& v)
	{
		graph[v];
	}
	bool remove_vertex(const Vertex& v)
	{
		if (!has_vertex(v))
			return false;
		graph.erase(v);

		for (auto c : graph)
		{

			for (int i = 0; i < c.second.size(); i++)
			{
				if (c.second[i].second == v)
				{
					graph[c.first].erase(c.second.begin() + i);
					Edge ed(c.first, c.second[i].second, c.second[i].first);
					edgeset.erase(ed);
					checkedge.erase(checkedge.find({ ed.from, ed.to }));
					i--;

				}
			}

		}
		return true;

	}
	vector<Vertex> vertices()const
	{
		vector<Vertex> a;
		for (auto c : graph)
			a.push_back(c.first);
		return a;
	}

	void add_edge(const Vertex& from, const Vertex& to, const Dist& d)
	{
		if (!has_vertex(from) || !has_vertex(to))
			return;
		graph[from].push_back({ d, to });
		Edge ed(from, to, d);
		edgeset.insert(ed);
		checkedge.insert({ ed.from, ed.to });
	}
	void add_edge(const Edge& ed)
	{
		if (!has_vertex(ed.from) || !has_vertex(ed.to))
			return;
		graph[ed.from].push_back({ ed.dist, ed.to });
		edgeset.insert(ed);
		checkedge.insert({ ed.from, ed.to });
	}
	bool remove_edge(const Vertex& from, const Vertex& to)
	{
		if (!has_vertex(from) || !has_vertex(to))
			return false;
		for (int i = 0; i < graph[from].size(); i++)
		{
			if (graph[from][i].second == to)
			{
				Edge ed(from, to, graph[from][i].first);
				graph[from].erase(graph[from].begin() + i);
				edgeset.erase(ed);
				checkedge.erase(checkedge.find({ ed.from, ed.to }));
				return true;
			}
		}
		return false;
	}
	bool remove_edge(const Edge& ed)
	{
		if (!has_vertex(ed.from) || !has_vertex(ed.to))
			return false;
		for (int i = 0; i < graph[ed.from].size(); i++)
		{
			if (graph[ed.from][i].second == ed.to && graph[ed.from][i].first == ed.dist)
			{

				graph[ed.from].erase(graph[ed.from].begin() + i);
				edgeset.erase(ed);
				//checkedge.erase(checkedge.find({ ed.from, ed.to }));
				return true;
			}
		}
		return false;
	}
};