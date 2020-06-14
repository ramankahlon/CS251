#include <iostream>
#include "TreeNode.h"

#include <string>


TreeNode::TreeNode(unsigned char val, unsigned int frequency)
{
	this ->val = val;
	this ->frequency = frequency;
	left = NULL;
	right = NULL;
}

bool TreeNode::isLeafNode()
{
	if(this->left == NULL && this->right == NULL)
		return true;
	else
		return false;
}

void TreeNode::join(TreeNode * left, TreeNode * right)
{
	if(left != NULL)
		this->left = left;
	if (right != NULL)
		this->right = right;
}
TreeNode * TreeNode::getLeft()
{
	return this->left;
}
TreeNode * TreeNode::getRight()
{
	return this->right;
}
unsigned TreeNode::getFrequency()
{
	return this->frequency;
}
unsigned TreeNode::getVal()
{
	return this->val;
}

