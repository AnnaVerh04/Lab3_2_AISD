#include <iostream>
#include<math.h>
#include<vector>
#include<string>
#include<queue>
#include<map>
#include<set>





using namespace std;
const int INF = 1e9;

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

		bool  operator < (const Edge& a)const
		{
			if (dist < a.dist)
				return true;
			else
			{
				if (a.dist < dist)
					return false;
				else
					return false;
			}
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
	bool has_edge(const Vertex& from, const Vertex& to)const
	{
		return checkedge.find({ from, to }) != checkedge.end();
	}

	bool has_edge(const Edge& ed)const
	{
		return edgeset.find(ed) != edgeset.end();
	}

	vector<Edge> edges(const Vertex& v)
	{
		vector<Edge> a;
		if (!has_vertex(v))
			return a;
		for (auto c : graph[v])
		{
			Edge ed(v, c.second, c.first);
			a.push_back(ed);
		}
		return a;
	}
	size_t order()
	{
		return graph.size();
	}
	size_t degre(const Vertex& v)
	{
		return graph[v].size();
	}

	vector<Vertex> walk(const Vertex& start_v)const
	{
		vector<Vertex> an;
		if (!has_vertex(start_v))
			return an;
		map<Vertex, bool> us;

		us[start_v] = true;
		queue<Vertex> q;
		q.push(start_v);
		while (!q.empty())
		{
			Vertex x = q.front();
			q.pop();
			an.push_back(x);
			for (int i = 0; i < graph.at(x).size(); i++)
			{
				Vertex y = graph.at(x)[i].second;
				if (!us[y])
				{
					us[y] = true;
					q.push(y);
				}

			}
		}
		return an;
	}

	vector<Vertex> shortest_path(const Vertex& from, const Vertex& to)const
	{
		map<Vertex, pair<Dist, Vertex>> dist_pred;
		vector<Vertex> an;
		if (!has_vertex(from) || !has_vertex(to))
			return an;
		for (auto c : graph)
			dist_pred[c.first] = { INF, -1 };
		dist_pred[from] = { 0, from };
		set<pair<Dist, Vertex>> q;
		q.insert(dist_pred[from]);
		while (!q.empty())//пока есть непосещенные вершины
		{
			Vertex x = (*q.begin()).second;
			q.erase(*q.begin());
			for (int i = 0; i < graph.at(x).size(); i++)//перебераем ребра из вершины x
			{
				Vertex y = graph.at(x)[i].second;
				Dist d = graph.at(x)[i].first;
				if (dist_pred[y].first > d + dist_pred[x].first)//если найден путь в у короче чем тот который был найден до этого
				{
					if (q.find({ dist_pred[y].first ,y }) != q.end())// надо ли удалять ребро стоящие в прошлом лучшем пути
					{
						q.erase({ dist_pred[y].first ,y });
					}
					dist_pred[y].first = d + dist_pred[x].first;
					dist_pred[y].second = x;
					q.insert({ dist_pred[y].first ,y });// добавляем ребро
				}

			}
		}
		if (dist_pred[to].first == INF)
		{
			return an;
		}
		Vertex v = to;
		an.push_back(v);
		while (dist_pred[v].second != v)
		{
			v = dist_pred[v].second;
			an.push_back(v);
		}
		reverse(an.begin(), an.end());
		return an;
	}

	Dist shortest_longest_path(const Vertex& from)const
	{
		map<Vertex, pair<Dist, Vertex>> dist_pred;

		if (!has_vertex(from))
			return -1;
		for (auto c : graph)
			dist_pred[c.first] = { INF, -1 };
		dist_pred[from] = { 0, from };
		set<pair<Dist, Vertex>> q;
		q.insert(dist_pred[from]);
		while (!q.empty())//пока есть непосещенные вершины
		{
			Vertex x = (*q.begin()).second;
			q.erase(*q.begin());
			for (int i = 0; i < graph.at(x).size(); i++)//перебераем ребра из вершины x
			{
				Vertex y = graph.at(x)[i].second;
				Dist d = graph.at(x)[i].first;
				if (dist_pred[y].first > d + dist_pred[x].first)//если найден путь в у короче чем тот который был найден до этого
				{
					if (q.find({ dist_pred[y].first ,y }) != q.end())// надо ли удалять ребро стоящие в прошлом лучшем пути
					{
						q.erase({ dist_pred[y].first ,y });
					}
					dist_pred[y].first = d + dist_pred[x].first;
					dist_pred[y].second = x;
					q.insert({ dist_pred[y].first ,y });// добавляем ребро
				}

			}
		}
		Dist an = 0;
		for (auto c : dist_pred)
			an = max(an, c.second.first);
		return an;
	}


};

