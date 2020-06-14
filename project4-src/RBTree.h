#ifndef PROJ4_RBTREE_H
#define PROJ4_RBTREE_H
#include <queue>
#include "Node.h"
#include <iostream>
#include <cstdlib>
#include <stdexcept>
using namespace std;

template <typename Key, typename Element>
class RBTree {
 private:
  	size_t sizeT;
  	//Node<Key,Element>* root;
  	void rotateLeft(Node<Key,Element> *);
  	void rotateRight(Node<Key,Element> *);
 public:
	Node <Key, Element>* root;  
	void inorderHelp(Node<Key,Element> *,ostream& out);
  	void levelOrderHelp(ostream& out, Node<Key,Element> *, int) const;

  // Implement each of these methods                                                               
	RBTree() { 
		sizeT = 0; root = NULL;  	
	}
    	void insert(const Key& k, const Element& e);
    	Node<Key, Element>* search(const Key& k);
    	void del(const Key& k);
    	void inorder(ostream& out);
    	void levelOrder(ostream& out) const;
        size_t size() const;
        Node<Key, Element>* getRoot();
};


// Function to insert a new node with given data                                                   
template <typename Key, typename Element>
void RBTree<Key, Element>::insert(const Key& key, const Element& element){
	Node<Key, Element> *node;
	Node<Key, Element> *parent;
	Node<Key, Element> *tempNode;
	parent = NULL;
	node = root;
	while(node){
		parent = node;
		if(key < node->getKey()){
			node = node->getLeft();
		} else {
			node = node->getRight();
		}
	}

	if(!parent){
		tempNode = root = new Node<Key,Element>;
		tempNode->setKey(key);
		tempNode->setElement(element);
		tempNode->setColor(BLACK);
		tempNode->setParent(NULL);
		tempNode->setLeft(NULL);
		tempNode->setRight(NULL);
	} else {
		tempNode = new Node<Key, Element>;
		tempNode->setKey(key);
		tempNode->setElement(element);
		tempNode->setColor(RED);
		tempNode->setParent(parent);
		tempNode->setLeft(NULL);
		tempNode->setRight(NULL);

		if(parent->getKey() > tempNode->getKey()){
			parent->setLeft(tempNode);
		} else {
			parent->setRight(tempNode);
        	}
	}

	Node<Key,Element> * uncle;
 	bool side;
	while (tempNode->getParent() && tempNode->getParent()->getColor() == RED){
		if((side = (tempNode->getParent() == tempNode->getParent()->getParent()->getLeft()))){
			uncle = tempNode->getParent()->getParent()->getRight();
        	} else {
          		uncle = tempNode->getParent()->getParent()->getLeft();
        	}

      		if (uncle && uncle->getColor() == RED){
          		tempNode->getParent()->setColor(BLACK);
          		uncle->setColor(BLACK);
          		tempNode->getParent()->getParent()->setColor(RED);
          		tempNode = tempNode->getParent()->getParent();
        	} else {
          		if (side){
				if (tempNode == tempNode->getParent()->getRight()){
					tempNode = tempNode->getParent();
					rotateLeft(tempNode);
				}
            		} else {
				if(tempNode == tempNode->getParent()->getLeft()){
					tempNode = tempNode->getParent();
					rotateRight(tempNode);
				}	
			}
          		tempNode->getParent()->setColor(BLACK);
          		tempNode->getParent()->getParent()->setColor(RED);
			if (side){
				rotateRight(tempNode->getParent()->getParent());
			} else {
				rotateLeft(tempNode->getParent()->getParent());
			}
        	}
    	}
  	root->setColor(BLACK);
  	sizeT++;
}

//Function to rotate left                                                                                       
template <typename Key, typename Element>
void RBTree<Key, Element>::rotateLeft(Node<Key,Element> *x){
	Node<Key, Element> *y;

  	y = x->getRight();
	x->setRight(y->getLeft());

  	if(y->getLeft()){
      		y->getLeft()->setParent(x);
    	}
	y->setParent(x->getParent());
  	y->setLeft(x);

  	if (!x->getParent()){
      		root = y;
    	} else if (x == x->getParent()->getLeft()){
      		x->getParent()->setLeft(y);
    	} else {
      		x->getParent()->setRight(y);
    	}
  	x->setParent(y);
}

//Function to rotate right                                                                                      
template <typename Key, typename Element>
void RBTree<Key, Element>::rotateRight(Node<Key,Element> *y){
  	Node<Key,Element> *x;
  	x = y->getLeft();
  	y->setLeft(x->getRight());
  	if (x->getRight()){
      		x->getRight()->setParent(y);
    	}
  	x->setParent(y->getParent());
 	x->setRight(y);

  	if (!y->getParent()){
      		root = x;
    	} else if ( y == y->getParent()->getLeft()){
      		y->getParent()->setLeft(x);
    	} else {
      		y->getParent()->setRight(x);
    	}
  	y->setParent(x);

}

// Function to search a node with given data                                                                    
template <typename Key, typename Element>
Node<Key, Element>* RBTree<Key, Element>::search(const Key& k) {
  	Node<Key,Element> *node = root;
  	while(node){
      		if (node->getKey() > k){
          		node = node->getLeft();
        	} else if (node->getKey() < k){
          		node = node->getRight();
        	} else {
          		return node;
        	}
    	}
  	return NULL;
}

// Function to delete a node with given data                                                                    
template <typename Key, typename Element>
void del(const Key& key) {}


// Function to do inorder traversal                                                                             
template <typename Key, typename Element>
void RBTree<Key, Element>::inorder(ostream& out){
  	if (root == NULL){
      		return;
   	}                                                                    
  	inorderHelp(this->root,out);
}

template <typename Key, typename Element>
void RBTree<Key, Element>::inorderHelp(Node<Key,Element> * root, ostream& out){
  	if (root == NULL){
      		return;
    	}
  	inorderHelp(root->getLeft(),out);
   	out<< *root<< endl;
  	inorderHelp(root->getRight(),out);

}
// Function to perform level-order traversal                                                                    
template <typename Key, typename Element>
void RBTree<Key, Element>::levelOrder(ostream& out)const {
	for (int i = 1; i < sizeT; i++){
		levelOrderHelp(out, root, i);
	}
}

template <typename Key, typename Element>
void RBTree<Key, Element>::levelOrderHelp(ostream & out, Node<Key,Element> * root, int level)const {
	if (root == NULL){
		return ;
	} else if (level ==1){
		out << *root << "\n";
	} else {
		levelOrderHelp(out, root->getLeft(), level - 1);
		levelOrderHelp(out, root->getRight(), level - 1);
	}
}

template <typename Key, typename Element>
size_t RBTree<Key, Element>::size() const {
	return sizeT;
}

// Function to return a pointer to the root of the RBTree
template <typename Key, typename Element>
Node<Key, Element>* RBTree<Key, Element>::getRoot() { 	
	return root;
}

template <typename Key, typename Element>
ostream& operator<<(ostream& out, const RBTree<Key, Element>& rbtree) {
	out << rbtree.size() << endl;
	rbtree.inorder(out);
	return out;
}

template <typename Key, typename Element>
istream& operator>>(istream& in, RBTree<Key, Element>& rbtree) {
	rbtree = RBTree<Key, Element>();
	size_t size;
	in >> size;
	for (size_t i = 0; i < size; i++) {
		Node<Key, Element> n;
		in >> n;
		rbtree.insert(n.getKey(), n.getElement());
	}
	return in;
}

#endif //PROJ4_RBTREE_H
