#include <iostream>
#include <cstring>
#include <memory>
#include <vector>
#include "Node.h"
#include "RBTree.h"
#include <sstream>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

// Input stream operator overload for node elements
istream& operator>>(istream& in, vector<pair<string, int>>& e);


struct sortP {
        bool operator()(const std::pair<string,int>  &p1,const  std::pair<string,int>  &p2){    
                if (p1.second == p2.second)
			p1.first < p2.first;
		else
			return (p1.second > p2.second);
        }
};

  
vector<pair<string,int>> intersection(vector<pair<string,int>>& finvec,vector<pair<string,int>>& newvec) {
  	
  	vector<pair<string,int>> temp;
  	pair<string,int> a;

  	std::sort(finvec.begin(),finvec.end(),sortP());
  	std::sort(newvec.begin(),newvec.end(),sortP());
  	for(int i = 0; i < finvec.size(); i++){
      		for(int j = 0; j < newvec.size(); j++) {
          		if(finvec.at(i).first.compare(newvec.at(j).first) == 0){
              			a.first = finvec.at(i).first;
              			a.second = newvec.at(j).second + finvec.at(i).second;
              			temp.push_back(a);
            		}
        	}
    	}
  	return temp;
}

int main(int argc, char** argv) {
 	
	if(argc <= 2 || argc >= 8)
		cout<<"Usage: ./search.org RBTree phrase"<<endl<<"Phrase must be between 1 and 5 words"<<endl;
	else
	{
      		ifstream inFile;
      		inFile.open(argv[1]);
      		if(inFile.fail()) {
          		return 1;
        	}
      		RBTree<string,vector<pair<string,int>>> rbt ;
      		inFile >> rbt;
      		vector<vector<pair<string,int>>> list;
      		Node<string,vector<pair <string,int>>> * nodes;
      		for(int i = 1; i <= argc-2;i++){
          		string word = argv[i+1];
          		transform(word.begin(), word.end(), word.begin(), :: tolower);
          		if(nodes = rbt.search(word)){
              			if(nodes != NULL){
              				list.push_back(nodes->getElement());
              			}
            		} else {
              			cout<<"Not found"<<endl;
              			return 1;
            		}
        	}		

		if(argc-2 > 2) {
          		vector<pair<string,int>> inter = intersection(list.at(0),list.at(1));
          		int i = 2;
			while(i < argc-2){
				inter = intersection(inter,list.at(i));
				i++;
			}
			std::sort(inter.begin(),inter.end(),sortP());
			for(int i = 0; i< inter.size();i++)
        			cout<< inter.at(i).first << " " << inter.at(i).second << endl;
      		}
		
        	else if(argc-2 == 2) {
          		vector<pair<string,int>> inter = intersection(list.at(0),list.at(1));
          		std::sort(inter.begin(),inter.end(),sortP());
			for(int i = 0; i< inter.size();i++)
        			cout<< inter.at(i).first<<" "<< inter.at(i).second<<endl;
		}
		else if(argc-2 == 1) {
         		vector<pair<string,int>> s = list.at(0);
	   		std::sort(s.begin(),s.end(), sortP());
			for(int i = 0; i< s.size();i++)
        			cout<<s.at(i).first<<" "<<s.at(i).second<<endl;
        	}

	}
        return 0;
}


// This function overloads the input stream operator for Node
// elements. It has been provided to you and does not need to be
// altered.
istream& operator>>(istream& in, vector<pair<string, int>>& e) {
	// Clear any existing contents
	e.clear();

	// Read the number of elements
	size_t n;
	in >> n;
	for (int i = 0; i < n; i++) {
		// Readleach member of each pair the vector stores
		string u;
		in >> u;
		int f;
		in >> f;
		// Add to vector
		e.push_back(make_pair(u, f));
	}

	return in;
}
