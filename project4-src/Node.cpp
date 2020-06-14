#include <iostream>
#include "Node.h"
#include <string>
#include <fstream>
#include <bitset>
#include <cstring>
#include <cstddef>
#include <vector>

using namespace std;

Node::Node(Key k, Element e)
{
	//put constructor stuff in here
	this ->k = k;
	this ->e = e;
	left = NULL;
	right = NULL;
}

const Key& Node::getKey()
{
	Key k;
	return k;
}

const Element& Node::getElement()
{
	Element e;
	return e;
}

Element& Node::getElement()
{
	Element e;
	return e;
}

color Node::getColor()
{
	return c;
}

Node* Node::getParent()
{
	return this->parent;
}

Node* Node::getLeft()
{
	return this->left;
}

Node* Node::getRight()
{
	return this->right;
}

void Node::setKey(const Key& k)
{

}

void Node::setElement(const Element& e)
{

}

void Node::setColor(color c)
{

}

Node::~Node()
{
}
