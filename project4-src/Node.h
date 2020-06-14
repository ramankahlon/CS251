#ifndef NODE_H
#define NODE_H

#include <iostream>
using namespace std;

enum color {RED, BLACK};

template <typename Key, typename Element>
class Node {
private:
	color c;
	Node<Key, Element> * parent;	
	Node<Key, Element> * left;
	Node<Key, Element> * right;
	Element e;
	Key k;
	// Add class members here

public:
	// Implement each of these methods
	Node() {
		this->left = NULL;
//		this->right = NULL;
		this->parent = NULL;
		c = RED;
	}

	// These implementations are only to get the skeleton
	// code to compile. Ignore the warnings they generate
	// until you replace their implementations with your own
	const Key& getKey() const {
		return this->k;
	}

	const Element& getElement() const {
		return this->e;
	}

	Element& getElement(){
		return this->e;
	}

	color getColor() const {
		return this->c;
	}

	Node* getParent() {
		return this->parent;
	}

	Node* getLeft() {
		return this->left;
	}

	Node* getRight() {
		return this->right;
	}

	void setKey(const Key& k) {
		this->k = k;
	}

	void setElement(const Element& e) {
		this->e = e;
	}
	void setColor(color c) {
		this->c = c;
	}
	void setParent(Node<Key, Element> * n){
		this->parent = n;
	}
	void setLeft(Node<Key, Element> *n){
		this->left = n;
	}
	void setRight(Node<Key, Element> *n){
		this->right = n;
	}
	void Recolor(){
		if (c==RED){
			c = BLACK;
		}
	}
};



// The following functions have been provided for you, and do not
// need to be modified:


// Output stream operator overload -- writes the contents of a
// Node to the specified output stream. Note that there must be
// a similar operator overload for Key and Element types in
// order for this to compile.
// Example usage:
//		Node<K,E> n;
//		cout << n << endl;
template <typename Key, typename Element>
ostream& operator<<(ostream& out, const Node<Key, Element>& n) {
	out << n.getKey() << endl;
	out << n.getElement() << endl;
	return out;
}

// Input stream operator overload -- reads the contents of a
// Node from the specified input stream. Note that there must be
// a similar operator overload for Key and Element types in order
// for this to compile.
// Example usage:
//		Node<K,E> n;
//		cin >> n;
template <typename Key, typename Element>
istream& operator>>(istream& in, Node<Key, Element>& n) {
	// Clear existing contents, if any
	n = Node<Key, Element>();

	Key k;
	in >> k;
	Element e;
	in >> e;
	n.setKey(k);
	n.setElement(e);

	return in;
}

#endif

