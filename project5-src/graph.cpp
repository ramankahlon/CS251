#include <iostream>
#include <string>
#include "graph.h"
#include <list>
#include <algorithm>
#include <vector>
#include <bits/stdc++.h>
#include <stdio.h>
#define INFI 1000000
/*
	Graph class for use in Project 5.
	
	This provided code does not include any specific data structure
	for storing a graph, only a list of methods that will be called 
	from main. Based on the project handout and the lecture slides,
	select a method for storing the graph and implement it here.

*/

using namespace std;
typedef pair<double,double> p;

// Constructor for Graph 
Graph::Graph(int Vertices, int routes)
{
	separated = 0;
	indexCity = 0;
	city_count = Vertices;
	route_count = routes;
	conversion.resize(city_count);
	connected = 0;
	adjacent = new list<pair<int, double>>[city_count];
	adjacent_list = new list<int>[city_count];
}

void Graph::analyseGraph()
{
	connectedCities();
	//cout << "Connected Components= " << connected << endl;
	cout << connected << endl;
	bridge();
	cout << separated << endl;
	sort(separation.begin(), separation.end());
	for(int i=0; i < separation.size(); i++)
	{
		if(indexToString(separation[i].second) > indexToString(separation[i].first))
			cout << indexToString(separation[i].first) << " " << indexToString(separation[i].second) << endl;
		else
			cout << indexToString(separation[i].second) << " " << indexToString(separation[i].first) << endl;
	}
}

void Graph::addRoute(string start, string end, double weight)
{
	int a = stringToIndex(start);
	int b = stringToIndex(end);
	adjacent[a].push_back(make_pair(b, weight));
	adjacent[b].push_back(make_pair(a, weight));
	//cout << "a = " << a << endl;
	//cout << "b = " << b << endl;
}

void Graph::bridge()
{
	int * low = new int[city_count];
	bool * visit = new bool[city_count];
	int * parent = new int[city_count];
	int * disc = new int[city_count];
	for(int x=0; x < city_count; x++)
	{
		parent[x] = -1;
		visit[x] = false;
	}
	for(int y=0; y < city_count; y++)
	{
		if(visit[y] == false)
			bridgeHelp(y, low, visit, parent, disc);
	}
}

void Graph::bridgeHelp(int i, int low[], bool visit[], int parent[], int disc[])
{
	static int t = 0;
	visit[i] = true;
	disc[i] = low[i] = ++t;
	list<pair<int, double>>::iterator it;
	for(it = adjacent[i].begin(); it != adjacent[i].end(); ++it)
	{
		int j = (*it).first;
		if(!visit[j])
		{
			parent[j] = i;
			bridgeHelp(j, low, visit, parent, disc);
			low[i] = min(low[i], low[j]);
			if(disc[i] < low[j])
			{
				separation.push_back(make_pair(i, j));
				separated++;
			}
		}
		else if(j != parent[i])
			low[i] = min(disc[j], low[i]);
	}
}

void Graph::dfsHelp(int i, bool visit[])
{
	list<pair<int, double>>::iterator it;
	visit[i] = true;
	//cout << "visited: " << visited;
	for(it = adjacent[i].begin(); it != adjacent[i].end(); ++it)
	{
		int j = (*it).first;
		if(!visit[j])
			dfsHelp(j, visit);
	}
}

void Graph::connectedCities()
{
	bool * visit = new bool[city_count];
	for(int i=0; i<city_count; i++)
	{
		visit[i] = false;
	}
	for(int i = 0; i < city_count; i++)
	{
		if(visit[i] == false)
		{
			connected++;
			dfsHelp(i, visit);
		}
	}
}

string Graph::indexToString(int index)
{
	return conversion[index];
}

int Graph::stringToIndex(string s)
{
	int b;
	for(int a=0; a < indexCity; a++)
	{
		if(conversion[a].compare(s) == 0)
			return a;
	}
	b = indexCity;
	conversion[indexCity] = s;
	indexCity++;
	return b;
}

int Graph::getCityCount()
{
	return city_count;
}

int Graph::getRouteCount()
{
	return route_count;
}

int Graph::validNext(int start, int end)
{
	bool * visited = new bool[city_count];
	for(int i=0; i<city_count; i++)
	{
		visited[i] = false;
	}
	dfsHelp(start, visited);
	if(visited[end] == false)
		return 0;
	return 1;
}

void Graph::findCost(const string &source, const string &destination)
{
	int a = stringToIndex(source);
	int b = stringToIndex(destination);
	if(validNext(a, b) == 0)
	{
		cout << "not possible" << endl;
		return;
	}
	vector<pair<double, int>> vec = dijkstra(a, b);
	double route = vec[b].first;
	string out = destination;
	int vert = b;
	while(vec[vert].second != a)
	{
		out = indexToString(vec[vert].second) + " " + out;
		vert = vec[vert].second;
	}
	out = source + " " + out;
	cout << out << " ";
	printf("%.2f\n", route);
}

vector<pair<double, int>> Graph::dijkstra(int start, int end)
{
	set<pair<int, int>> s;
	vector<pair<double, int>> len;
	len.resize(city_count);
	for(int i=0; i<city_count; i++)
	{
		len[i].first = 1000000;
		len[i].second = -1;
	}
	s.insert(make_pair(0, start));
	len[start].first = 0;
	len[start].second = start;
	
	while(!s.empty())
	{
		pair<int, int> p = *(s.begin());
		s.erase(s.begin());
		int i = p.second;
		list<pair<int, double>>::iterator it;
		for(it = adjacent[i].begin(); it != adjacent[i].end(); ++it)
		{
			int j = (*it).first;
			double weight = (*it).second;
			if((len[i].first + weight) < len[j].first)
			{
				if(len[j].first != 1000000)
					s.erase(s.find(make_pair(len[j].first, j)));
				len[j].first = len[i].first + weight;
				len[j].second = i;
				s.insert(make_pair(len[j].first, j));
			}
		}
	}
	return len;
}
/*
int findMin(int code[], bool minSet[])
{
	int min = INT_MAX;
	int min_count;
	for(int i = 0; i < city_count; i++)
	{
		if(min > code[i] && minSet[i] == false)
			min = code[i];
			min_count = i;
	}
	return min_count;
}

int printMin(int i, int parent[], int graph[city_count][city_count])
{
	printf("Edge   Weight\n");
	for(int i=1; i < city_count; i++)
		printf("%d - %d    %d \n", parent[i], i, graph[i][parent[i]]);
}
*/
vector<int> Graph::primMin()
{
	priority_queue<pair<double,double>, vector<pair<double,double>>, greater<pair<double,double>>> queue;
	int start = 0;
	vector<int> key(city_count, 1000000);
	vector<int> parent(city_count, -1);
	vector<bool> inMin(city_count, false);
	queue.push(make_pair(0,start));
	key[start] = 0;
	while(!queue.empty())
	{
		int a = queue.top().second;
		queue.pop();
		inMin[a] = true;
		list<pair<int,double>>::iterator it;
		for(it = adjacent[a].begin(); it!=adjacent[a].end(); it++)
		{
			int b = (*it).first;
			double weight = (*it).second;
			if(inMin[b] == false && key[b] > weight)
			{
				key[b] = weight;
				queue.push(make_pair(key[b], b));
				parent[b] = a;
			}
		}
	}
	return parent;
/*
	int code[city_count];
	bool minSet[city_count];
	int parent[city_count];

	for(int i=0; i < city_count; i++)
		code[i] = INT_MAX, minSet[i] = false;

	parent[0] = -1;
	code[0] = 0;
	for(int i=0; i < city_count-1; i++)
	{
		int j = findMin(code, minSet);
		minSet[j] = true;
		for(int k=0; k < city_count; k++)
		{
			if(key[k] > graph[j][k] && graph[j][k] && minSet[k] == false)
			{
				parent[k] = j;
				code[k] = graph[j][k];
			}
		}
	}
	printMin(city_count, parent, graph);
*/
}

/*
void remove(int u, int v)
{
	list<pair<int,double>>::iterator it1 = find(adjacent[u].begin(),adjacent[u].end(),v);
	*it1 = make_pair(-1,-1.0);
	list<pair<int,double>>::iterator it2 = find(adjacent[v].begin(),adjacent[v].end(),u);
	*it2 = make_pair(-1,-1.0);
}
*/

void Graph::eulerianTour(string root)
{
	if(checkEuler() == 0)
	{
		cout << "not possible" << endl;
		return;
	}
	vector<int> edge = primMin();
	for(int i=1; i<city_count; i++)
	{
		adjacent_list[i].push_back(edge[i]);
		adjacent_list[edge[i]].push_back(i);
	}
	int a = stringToIndex(root);
	eulerDFS(a);
/*
	list<pair<int,double>>::iterator it;
	int u = stringToIndex(root);
	for(it = adjacent[u].begin(); i!=adjacent[u].end(); ++i)
	{
		pair<int,double> * v = *it;
		if(v.first != -1 && v.second != -1.0 && validNext(u,v))
		{
			cout << indexToString(u);
			remove(u,v);
			eulerianTour(v);
		}
	}
*/
}

void Graph::dfsUtil(int i, bool visit[])
{
	visit[i] = true;
	list<pair<int,double>>::iterator it;
	for(it = adjacent[i].begin(); it!=adjacent[i].end(); ++it)
	{
		if(!visit[(*it).first])
			dfsUtil((*it).first, visit);
	}
}

void Graph::eulerDFS(int start)
{
	bool * visited_cities = new bool[city_count];
	for(int i=0; i<city_count; i++)
		visited_cities[i] = false;
	eulerDFSHelp(start, visited_cities);
}

void Graph::eulerDFSHelp(int start, bool cities[])
{
	cities[start] = true;
	cout << indexToString(start) << endl;
	vector<int> vec;
	list<int>::iterator it;
	for(it = adjacent_list[start].begin(); it!=adjacent_list[start].end();it++)
		vec.push_back(*it);
	for(int a=0; a<vec.size()-1;a++)
	{
		for(int b=0; b<vec.size()-1;b++)
		{
			if(indexToString(vec[b+1]).compare(indexToString(vec[b])) < 0)
			{
				int temp = vec[b];
				vec[b] = vec[b+1];
				vec[b+1] = temp;
			}
		}
	}
	for(int a=0; a<vec.size(); a++)
	{
		if(!cities[vec[a]])
			eulerDFSHelp(vec[a], cities);
	}
}

int Graph::checkEuler()
{
	int a;
	bool * visit = new bool[city_count];
	for(a=0; a<city_count; a++)
		visit[a] = false;
	for(a=0; a<city_count; a++)
	{
		if(adjacent[a].size() != 0)
			break;
	}
	if(a == city_count)
		return 1;
	dfsHelp(a, visit);
	for(a=0; a<city_count; a++)
	{
		if(adjacent[a].size() > 0 && visit[a] == false)
			return 0;
	}
	return 1;
}
/*
bool validNext(int u, int v)
{
	int num = 0;
	list<pair<int,double>>::iterator it;
	for(it = adjacent[u].begin(); it != adjacent[u].end(); ++it)
	{
		if(*it.first != -1 && *it.second != -1.0)
			num++;
	}
	if(num == 1)
		return true;
	vertices = getCityCount();
	
	bool visited[vertices];
	memset(visited,false,vertices);
	int num1 = dfsCount(u, visited);

	remove(u, v);
	memset(visited,false,vertices);
	int num2 = dfsCount(u, visited);
	addRoute(u, v);
	if(num1 > num2)
		return false;
	else
		return true;
}
*/
