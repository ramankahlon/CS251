#include <iostream>
#include <climits>
#include <cstring>
#include <cstdint>
#include "MinHeap.h"
#define ARRAYMAX 1000;
using namespace std;


//implement the methods in MinHeap.h

MinHeap::MinHeap()
{
	size = 0;
}	

void MinHeap::insert(TreeNode * val)
{
	vec.push_back(val);
	size++;
	this->siftUp(size -1);
}

MinHeap::~MinHeap()
{
	for(int i =0; i < vec.size(); i++)
	{
		delete vec[i];
	}
}

int MinHeap::getSize()
{
	return this->size;
}

TreeNode * MinHeap::removeMin()
{
	if(size == 0)
		return NULL;
	TreeNode * temp = vec[0];
	vec[0] = vec[size-1];
	vec.erase(vec.end()-1);
	siftDown(0);
	size--;
	return temp;
//	return NULL;

}

void MinHeap::siftDown(int index)
{
	int left = this->leftChild(index);
	int right = this->rightChild(index);
	int min = index;
	if(left < size)
	{
		if(vec[left]->getFrequency() < vec[index]->getFrequency())
			min = left;
	}
	if(right < size)
	{
		if( vec[right]->getFrequency() < vec[min]->getFrequency())
			min = right;
	} 
	if(min != index)
	{
		//	TreeNode * temp = vec[minIndex];
		//	vec[minIndex] = vec[index];
		//	vec[index] = temp;
			swap(min, index);
			siftDown(min);
	}
}
void MinHeap::siftUp(int index)
{
	int child = size -1;
	int parent = this->parent(index);
	while(child > 0)
	{
		if(vec[child]->getFrequency() >= vec[parent]->getFrequency() )
			break;
	//	TreeNode * temp = vec[child];
	//	vec[child] = vec[parent];
	//	vec[parent] = temp;
		swap(child, parent);
		child = parent;
		parent = this->parent(child);		
	}
}

void MinHeap::swap(int child, int parent)
{
	TreeNode * temp = vec[child];
	vec[child] = vec[parent];
	vec[parent] = temp;
}

int MinHeap::parent(int child)
{ 
	return (child-1)/2; 
}

int MinHeap::rightChild(int parent)
{ 
	return 2*parent +2; 
}

int MinHeap::leftChild(int parent)
{ 
	return 2*parent +1; 
}

