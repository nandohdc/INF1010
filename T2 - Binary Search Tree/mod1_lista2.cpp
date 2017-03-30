#include "mod1_lista2.h"
#include <iostream>
using namespace std;

Abb::Abb()
{
	this->_root = nullptr;
	this->_cursor = nullptr;
}


Abb::Abb(int key)
{
	this->_root = new Node();
	this->_root->_key = key;
	this->_root->_left = this->_root->_right = this->_root->_up = nullptr;
}


Abb::Abb(const Abb& orig)
{
}


Abb::~Abb()
{
	this->deleterec(this->_root);
}


void Abb::insert(int key)
{
	this->insertrec(this->_root, key);
}


bool Abb::remove(int key)
{
	return false;
}


void Abb::show(const std::string& title)
{
	cout << title << endl;
	this->showrec(this->_root);
}


void Abb::order(const std::string& title)
{
	cout << title << endl;
	this->orderrec(this->_root);
}


int Abb::min()
{
	if (!this->_root) {
		return -1;
	}

	Node* temp = this->_root;

	while (!temp->_left)
		temp = temp->_left;

	return temp->_key;
}


bool Abb::first()
{
	return false;
}


bool Abb::last()
{
	return false;
}


bool Abb::next()
{
	if (!this->_cursor)
		return false;
	if (!this->_cursor->_right) {
		this->_cursor = this->_cursor->_right;
		while (!this->_cursor->_left)
			this->_cursor = this->_cursor->_left;
		return true;
	}
	else {
		while (!this->_cursor) {
			if (!this->_cursor->_up && this->_cursor->_up->_key > this->_cursor->_key) {
				this->_cursor = this->_cursor->_up;
				return true;
			}
			this->_cursor = this->_cursor->_up;
		}
		return false;
	}
}


bool Abb::prev()
{
	return false;
}


int Abb::value()
{
	return this->_cursor->_key;
}


Node* Abb::search(int key)
{
	return searchrec(this->_root, key);
}


Node* Abb::searchrec(Node* node, int key)
{
	if (!node) {
		return nullptr;
	}
	if (node->_key == key) {
		return node;
	}
	if (node->_key > key) {
		return searchrec(node->_left, key);
	}
	else
	{
		return searchrec(node->_right, key);
	}
}


void Abb::deleterec(Node* root)
{
	if (!root) {
		return;
	}

	deleterec(root->_left);
	deleterec(root->_right);
	delete root;
}


Node* Abb::insertrec(Node* a, int key)
{
	if (!a) {
		Node* p = new Node();
		p->_key = key;
		p->_left = p->_right = p->_up = nullptr;
		return p;
	}
	else if (key > a->_key) {
		a->_right = insertrec(a->_right, key);
		a->_right->_up = a;
	}
	else if (key < a->_key) {
		a->_left = insertrec(a->_left, key);
		a->_left->_up = a;
	}

	return a;
}


void Abb::showrec(Node* a)
{
	if (!a) {
		cout << ".";
		return;
	}

	cout << "<" << a->_key;
	showrec(a->_left);
	showrec(a->_right);
	cout << ">";
}


void Abb::orderrec(Node* a)
{
	if (!a) {
		return;
	}
	cout << "<";
	orderrec(a->_left);
	cout << a->_key << ",";
	orderrec(a->_right);
	cout << ">";
}


void Abb::removesimplenode(Node* node)
{
}
