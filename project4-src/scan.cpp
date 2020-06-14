#include <iostream>
#include <vector>
#include "RBTree.h"
#include "SimpleHTMLParser.h"
#include "Node.h"
#include <stdio.h>
#include <sstream>
#include <string>
#include <fstream>
using namespace std;

// Output stream operator overload for node elements
ostream& operator<<(ostream& out, const vector<pair<string, int>>& e);

int counter = 0;

int main(int argc, char ** argv)
{
	string infile;
	string ofile;
	if(argc == 3)
	{
		infile = argv[1];
		ofile = argv[2];
	}
	ifstream read;
	read.open(infile);
	if(!read)
		return 0;
	int linkCount;
	read >> linkCount;
	string url;
	SimpleHTMLParser * html = new SimpleHTMLParser();
	RBTree<string,vector<pair<string,int>>> * rbt = new RBTree<string,vector<pair<string,int>>>();
	for(int i=0;i<linkCount;i++)
	{
		read >> url;
		if(html -> parse(url))
		{
			string word;
			istringstream iss(html -> getText());
			while(iss >> word)
			{
				Node<string,vector<pair<string,int>>> * node;
				node = rbt -> search(word);
				if(node)
				{
					vector<pair<string,int>> e = node -> getElement();
					int index = -1;
					pair<string,int> temp;
					if(url.empty())
						index = -1;
					for(int x=0; x < e.size(); x++)
					{
						temp = e[x];
						if(temp.first.compare(url)==0)
						{
							index = x;
							break;
						}
					}
					if(index == -1)
					{
						temp.first = url;
						temp.second = 1;
						e.push_back(temp);
						node -> setElement(e);
					}
					else
					{
						temp = e[index];
						temp.second++;
						e[index] = temp;
						node -> setElement(e);
					}
				}
				else
				{
					vector<pair<string,int>> e;
					pair<string,int> vec;
					vec.first = url;
					vec.second = 1;
					e.insert(e.begin(),vec);
					rbt -> insert(word,e);
					counter++;		
				}
			}
		}
	}
	ofstream write;
	write.open(ofile);
	if(!write)
		return 1;
	write << counter << endl;
	rbt -> inorder(write);
	write << endl;
	write.close();
	read.close();
	return 0;
}

// This function overloads the output stream operator for Node
// elements. It has been provided to you and does not need to be
// altered.
ostream& operator<<(ostream& out, const vector<pair<string, int>>& e) {
    // Write the number of elements in the vector
    out << e.size() << endl;
    for (auto& uf : e)
        // Write each member of each pair the vector stores
        out << uf.first << " " << uf.second << endl;
    return out;
}
