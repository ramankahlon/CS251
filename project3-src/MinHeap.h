#ifndef MINHEAP_H
#define MINHEAP_H

#include "TreeNode.h"
#include <vector>

#define ARRAYMAX 1000;
using namespace std;

class MinHeap
{
	private:
		vector<TreeNode*> vec;
		int size;
	public:
		MinHeap();
		void swap(int child, int parent);
		TreeNode * removeMin(); //returns root of heap
		void insert(TreeNode * val); //adds element to heap
		int getSize(); //returns size of heap
		void siftUp(int index);
		void siftDown(int index);
		int parent(int index);
		int rightChild(int index);
		int leftChild(int index);
		~MinHeap();
};
#endif

