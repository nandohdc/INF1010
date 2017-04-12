#include "mod1_lista2.h"
#include <iostream>
using namespace std;

Abb::Abb()
{
	this->_root = nullptr;
	this->_cursor = this->_root;
}


Abb::Abb(int key)
{
	this->_root = new Node();
	this->_root->_key = key;
	this->_root->_left = this->_root->_right = this->_root->_up = nullptr;
	this->_cursor = this->_root;
}


Abb::Abb(const Abb& orig)
{
	cout << "The Binary Search Tree Is Being Copied." << endl;
	this->_root = CopiaArvore(orig._root);
	this->_cursor = this->_root;
}

Abb::~Abb()
{
	cout << "The Binary Search Tree Is Being Deleted." << endl;
	this->deleterec(this->_root);
}


void Abb::insert(int key)
{
	//cout << "Key Is Being Inserted On Binary Search Tree." << endl;
	this->_root = this->insertrec(this->_root, key);
	this->_root->_up = nullptr;
	this->_cursor = this->_root;
}


bool Abb::remove(int key)
{
	Node* temp = nullptr;
	temp = search(key);

	if (temp != nullptr) {
		removesimplenode(temp);
		return true;
	}

	return false;
}


void Abb::show(const std::string& title)
{
	cout << title << endl;
	this->showrec(this->_root);
	cout << endl;
}


void Abb::order(const std::string& title)
{
	cout << endl;
	cout << title << endl;
	this->orderrec(this->_root);
	cout << endl;
}


int Abb::min()
{
	if (this->_root == nullptr) {
		return -1;
	}

	this->_cursor = this->_root;

	while (this->_cursor->_left !=nullptr)
		this->_cursor = this->_cursor->_left;

	return this->_cursor->_key;
}


bool Abb::first()
{
	if (this->_cursor == nullptr) {
		return false;
	}

	while (this->_cursor->_up != nullptr) {
		this->_cursor = this->_cursor->_up;
	}

	while (this->_cursor->_left != nullptr) {
		this->_cursor = this->_cursor->_left;
	}

	return true;
}


bool Abb::last()
{
	if (this->_cursor == nullptr) {
		return false;
	}

	while (this->_cursor->_up != nullptr) {
		this->_cursor = this->_cursor->_up;
	}

	while (this->_cursor->_right != nullptr) {
		this->_cursor = this->_cursor->_right;
	}

	return true;
}


bool Abb::next()
{
	if (this->_cursor == nullptr)
		return false;
	if (this->_cursor->_right != nullptr) {
		this->_cursor = this->_cursor->_right;
		while (this->_cursor->_left != nullptr)
			this->_cursor = this->_cursor->_left;
		return true;
	}
	else {
		while (this->_cursor != nullptr) {
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
	if (this->_cursor == nullptr)
		return false;
	if (this->_cursor->_left != nullptr) {
		this->_cursor = this->_cursor->_left;
		while (this->_cursor->_right != nullptr)
			this->_cursor = this->_cursor->_right;
		return true;
	}
	else {
		while (this->_cursor != nullptr) {
			if (!this->_cursor->_up && this->_cursor->_up->_key < this->_cursor->_key) {
				this->_cursor = this->_cursor->_up;
				return true;
			}
			this->_cursor = this->_cursor->_up;
		}
		return false;
	}
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
	if (node == nullptr) {
		return nullptr;
	}
	if (node->_key == key) {
		return node;
	}
	else if (node->_key > key) {
		return searchrec(node->_left, key);
	}
	else if (node->_key < key)
	{
		return searchrec(node->_right, key);
	}
	else {
		return nullptr;
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
	if (a == nullptr) {
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
	if (a == nullptr) {
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
	if (a == nullptr) {
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
	if (node->_left == nullptr && node->_right == nullptr) {
		node->_up->_right = NULL;
		node->_up->_left = NULL;
		free(node);
		node = NULL;
	}
	else if (node->_left == nullptr) {
		Node* temp = node;
		node = temp->_right;
		free(temp);
	}
	else if (node->_right == nullptr) {
		Node* temp = node;
		node = temp->_left;
		free(temp);
	}
}

Node* Abb::CopiaArvore(Node* oldRoot) {
	if (oldRoot == nullptr) {
		return nullptr;
	}
	Node* temp = insertrec(this->_root, oldRoot->_key);
	temp->_left = CopiaArvore(oldRoot->_left);
	temp->_right = CopiaArvore(oldRoot->_right);
	return temp;
}