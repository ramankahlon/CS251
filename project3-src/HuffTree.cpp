#include <iostream>
#include "HuffTree.h"
#include "TreeNode.h"
#include "MinHeap.h"

using namespace std;

HuffTree::HuffTree()
{
}

TreeNode * HuffTree::getRoot()
{ 
	return this->root; 
}

void HuffTree::buildTree(MinHeap * mh)
{
	TreeNode * right;
	TreeNode * left;
	TreeNode * parent;	
	for(int i = mh->getSize(); i > 1; i = mh->getSize())
	{
		left = mh->removeMin();
		right = mh->removeMin();
		parent = new TreeNode((char)(0), left->getFrequency() + right->getFrequency());
		parent->join(left,right);
		mh->insert(parent);
	}
	mh->removeMin();
	this->root = parent;
}

void HuffTree::generateCodes()
{
	this->genCodes(this->getRoot(),"");
}

int HuffTree::getSize()
{
	return this->vec.size();
}

void HuffTree::deleteNode(TreeNode *n)
{
	if(n->isLeafNode()){
		delete n;
	}	
	else{
		deleteNode(n->getLeft());
		deleteNode(n->getRight());
		delete n;
	}
}

void HuffTree::genCodes(TreeNode * root, string bitCode){

	if(root->isLeafNode() == true)
	{
		bit.push_back(bitCode);
		vec.push_back(root->getVal());
		return;
	}
	this->genCodes(root->getLeft(), bitCode + "1" );
	this->genCodes(root->getRight(),bitCode + "0");
}

string HuffTree::getCharCode(int ascii)
{
	int s = this -> getSize();
	for(int x = 0; x < s; x++)
	{
		if((int)ascii == (vec[x]))
			return bit[x];	
	}
	return NULL;
}

HuffTree::~HuffTree()
{
	deleteNode(getRoot());
}

