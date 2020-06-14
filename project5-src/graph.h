#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <vector>

using namespace std;

class Graph
{
	private:
		//Part 1
		int city_count;
		int route_count;
		string * cities;
		double weight;
		//bool * visit;
		vector<string> conversion;
		int stringToIndex(string s);
		string indexToString(int index);
		int indexCity;
		list<int> * adjacent_list;
		list<pair<int, double>> * adjacent;
		void connectedCities();
		void dfsHelp(int i, bool visit[]);
		int connected;
		vector<pair<int,int>> separation;
		void bridge();
		void bridgeHelp(int i, int low[], bool visit[], int parent[], int disc[]);
		int separated;
		
		//Part 2
		vector<pair<double, int>> dijkstra(int start, int end);
		vector<int> primMin();
		void dfsUtil(int i, bool visit[]);
		bool checkConnection();
		int checkEuler();
		void eulerDFS(int start);
		void eulerDFSHelp(int start, bool cities[]);
		int validNext(int start, int end);
		//int findMin(int code[], bool minSet[]);
		//int printMin(int i, int parent[], int graph[city_count][city_count]);
		//void primMin(int graph[city_count][city_count]);
	
	public:
		int getCityCount();
		int getRouteCount();

		Graph(int, int);
		// Create the graph
		void addRoute(string, string, double);	

		//part 1: Find the connected components and the bridges
		void analyseGraph();		
		
		
		// Part 2: Find a ticket using Dijkstra	
		void findCost(const string &source, const string &destination);         
		
		// Part 3: Try to do a tour of all cities
		//void remove(int, int);
		void eulerianTour(string);  // NOTE : If necessary, you can change the parameters to this function.
		//bool validNext(int, int);
};

#endif
