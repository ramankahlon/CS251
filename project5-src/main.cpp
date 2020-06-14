#include <iostream>
#include <string>
#include "graph.h"
 
using namespace std;
Graph *tourGuide; 

 // Part 1 : Find the connected components and the bridge
void part1()
{
	int Vertices;
	int routes;
	cin >> Vertices;
	cin >> routes;
	tourGuide = new Graph(Vertices, routes);
	string start, end;
	double weight;
	for(int i=0; i < tourGuide -> getRouteCount(); i++)
	{
		cin >> start;
		cin >> end;
		cin >> weight;
		//cout << "start = " << start << endl;
		//cout << "end = " << end << endl;
		tourGuide -> addRoute(start,end,weight);
	}
	tourGuide -> analyseGraph();
}

 // Part 2 :  Find a ticket using Dijkstra	
void part2()
{
	int Vertices;
	int routes;
	cin >> Vertices;
	cin >> routes;
	tourGuide = new Graph(Vertices, routes);
	string start, end;
	double weight;
	for(int i=0; i < tourGuide -> getRouteCount(); i++)
	{
		cin >> start;
		cin >> end;
		cin >> weight;
		tourGuide -> addRoute(start, end, weight);
	}
	string start_new, end_new;
	while(true)
	{
		cin >> start_new;
		if(start_new.compare("END") == 0)
			return;
		cin >> end_new;
		tourGuide -> findCost(start_new, end_new);
	}
}

 // Part 3 :Try to do a tour of all cities 
void part3()
{
	int Vertices;
	int routes;
	cin >> Vertices;
	cin >> routes;
	tourGuide = new Graph(Vertices, routes);
	string start, end;
	double weight;
	for(int i=0; i < tourGuide -> getRouteCount(); i++)
	{
		cin >> start;
		cin >> end;
		cin >> weight;
		tourGuide -> addRoute(start, end, weight);
	}
	string root;
	cin >> root;
	tourGuide -> eulerianTour(root);
}
 
int main()
{
	double cmd;
	cin >> cmd;

	if(cmd == 1) part1();
	else if(cmd == 2) part2();
	else if(cmd == 3) part3();

	return 0;
}
