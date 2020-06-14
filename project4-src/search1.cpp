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


struct sort_pred {
        bool operator()(const std::pair<string,int>  &a,const  std::pair<string,int>  &b){    
                if (a.second == b.second){
			a.first < b.first;
		} else { 
			return (a.second > b.second);
		}
        }
};

  
vector<pair<string,int>> intersection(vector<pair<string,int>>& finalvec,vector<pair<string,int>>& newvec) {
  	
  	vector<pair<string,int>> temp;
  	pair<string,int> add;

  	std::sort(finalvec.begin(),finalvec.end(),sort_pred());
  	std::sort(newvec.begin(),newvec.end(),sort_pred());
  	for(int i = 0; i < finalvec.size(); i++){
      		for(int j = 0; j < newvec.size(); j++) {
          		if(finalvec.at(i).first.compare(newvec.at(j).first) == 0){
              			add.first = finalvec.at(i).first;
              			add.second = finalvec.at(i).second + newvec.at(j).second;
              			temp.push_back(add);
            		}
        	}
    	}
  	return temp;
}

int main(int argc, char** argv) {
 	
  	if(argc > 2 && argc < 8){
      		ifstream inFile;
      		inFile.open(argv[1]);
      		if(inFile.fail()) {
          		return 1;
        	}
      		RBTree<string,vector<pair<string,int>>> rbt ;
      		inFile  >>  rbt;
      		vector<vector<pair<string,int>>> listElements;
      		Node<string,vector<pair <string,int>>> * tempNodes;
      		for(int i = 1; i <= argc-2;i++){
          		string word = argv[i+1];
          		transform(word.begin(), word.end(), word.begin(), :: tolower);
          		if(tempNodes = rbt.search(word)){
              			if(tempNodes != NULL){
              				listElements.push_back(tempNodes->getElement());
              			}
            		} else {
              			cout<<"Not found"<<endl;
              			return 1;
            		}
        	}		

      		if(argc-2 == 1) {
         		vector<pair<string,int>> sorter = listElements.at(0);
	   		std::sort(sorter.begin(),sorter.end(), sort_pred());
			for(int i = 0; i< sorter.size();i++){
        			cout<<sorter.at(i).first<<" "<<sorter.at(i).second<<endl;
      			}
        	} else if(argc-2 == 2) {
          		vector<pair<string,int>> inter = intersection(listElements.at(0),listElements.at(1));
          		std::sort(inter.begin(),inter.end(),sort_pred());
			for(int i = 0; i< inter.size();i++){
        			cout<< inter.at(i).first<<" "<< inter.at(i).second<<endl;
      			}
		} else if(argc-2 > 2) {
          		vector<pair<string,int>> inter = intersection(listElements.at(0),listElements.at(1));
          		int i = 2;
			while(i < argc-2){
				inter = intersection(inter,listElements.at(i));
				i++;
			}
			std::sort(inter.begin(),inter.end(),sort_pred());
			for(int i = 0; i< inter.size();i++){
        			cout<< inter.at(i).first << " " << inter.at(i).second << endl;
      			}
		}

	} else {
		cout<<"Usage: ./search.org RBTree phrase"<<endl<<"Phrase must be between 1 and 5 words"<<endl;
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
