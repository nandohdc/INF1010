#include "mod1_lista3.h"
#include <iostream>
using namespace std;

Avl::Avl()
	: _root(nullptr), _cursor(nullptr)
{
}


Avl::Avl(const int key) 
{
	this->_root = new AvlNode();
	this->_root->_key = key;
	this->_root->_left = this->_root->_right = this->_root->_up = nullptr;
	this->_root->_balance_factor = 0;
	this->_cursor = this->_root;
}


Avl::Avl(const Avl& orig)
	: _root(nullptr), _cursor(nullptr)
{
	cout << "The AVL Is Being Copied." << endl;
	this->_root = CopiaArvore(orig._root);
	this->_cursor = this->_root;
}


Avl::~Avl()
{
	cout << "The AVL Is Being Deleted." << endl;
	this->deleterec(this->_root);
}


int Avl::height()
{
	return heightrec(this->_root);
}


void Avl::insert(int key)
{
	int delta_h = 0;
	this->_root = this->insertrec(this->_root, key, delta_h);
	this->_root->_up = nullptr;
	this->_cursor = this->_root;
}


void Avl::show(const std::string& title)
{
	std::cout << title << std::endl;
	show_rec(_root);
	std::cout << std::endl;
}


bool Avl::first()
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


bool Avl::last()
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


bool Avl::next()
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


bool Avl::prev()
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


int Avl::value()
{
	return this->_cursor->_key;
}


void Avl::show_rec(AvlNode* node)
{
	if (node != nullptr)
	{
		std::cout << "<";
		std::cout << node->_key;
		show_rec(node->_left);
		show_rec(node->_right);
		std::cout << ">";
	}
	else 
	{
		std::cout << ".";
	}
}

AvlNode* Avl::CopiaArvore(AvlNode* oldRoot) {
	int delta_h = 0;
	if (oldRoot == nullptr) {
		return nullptr;
	}
	AvlNode* temp = insertrec(this->_root, oldRoot->_key, delta_h);
	temp->_left = CopiaArvore(oldRoot->_left);
	temp->_right = CopiaArvore(oldRoot->_right);
	return temp;
}

void Avl::deleterec(AvlNode* root)
{
	if (!root) {
		return;
	}

	deleterec(root->_left);
	deleterec(root->_right);
	delete root;
}

int Avl::Max(int a, int b) {
	return (a > b) ? a : b;
}

int Avl::heightrec(AvlNode* node) {
	if (node == nullptr) {
		return 0;
	}

	int leftHeight = heightrec(node->_left);
	int rightHeight = heightrec(node->_right);

	return (Max(leftHeight, rightHeight)) +1;

}

int Avl::getBalance(AvlNode* Node) {
	if (Node == nullptr) {
		return 0;
	}

	return heightrec(Node->_left) - heightrec(Node->_right);
}


AvlNode* Avl::rightRotate(AvlNode* Node) {
	AvlNode* father = Node->_up;
	AvlNode* t = Node->_left;
	AvlNode* a2 = t->_right;

	t->_right = Node;
	Node->_up = t;
	Node->_left = a2;
	if (a2) {
		a2->_up = Node;
	}

	if (father) {
		if (father->_right == Node) {
			father->_right = t;
		}
		else {
			father->_left = t;
		}
	}
	Node->_balance_factor = Max(heightrec(Node->_left), heightrec(Node->_right)) + 1;
	t->_balance_factor = Max(heightrec(t->_left), heightrec(t->_right)) + 1;
	return t;
}

AvlNode* Avl::leftRotate(AvlNode* Node) {
	AvlNode* father = Node->_up;
	AvlNode* t = Node->_right;
	AvlNode* a2 = t->_left;

	t->_left = Node;
	Node->_up = t;
	Node->_right = a2;

	if (a2) {
		a2->_up = Node;
	}

	if (father) {
		if (father->_right == Node) {
			father->_right = t;
		}
		else {
			father->_left = t;
		}
	}

	Node->_balance_factor = Max(heightrec(Node->_left), heightrec(Node->_right)) + 1;
	t->_balance_factor = Max(heightrec(t->_left), heightrec(t->_right)) + 1;
	return t;
}

AvlNode* Avl::insertrec(AvlNode* a, int key, int& delta_h) {
	if (a == nullptr) {
		AvlNode* p = new AvlNode();
		p->_key = key;
		p->_left = p->_right = p->_up = nullptr;
		p->_balance_factor = 0;
		delta_h = 1;
		return p;
	}
	else if (key > a->_key) {
		a->_right = insertrec(a->_right, key, delta_h);
		if (a->_right != nullptr) {
			a->_right->_up = a;
		}
	}
	else if (key < a->_key) {
		a->_left = insertrec(a->_left, key, delta_h);
		if (a->_left != nullptr) {
			a->_left->_up = a;
		}	
	}
	else { //Chaves iguais nada a fazer
		return a;
	}

	delta_h = 1 + Max(heightrec(a->_left), heightrec(a->_right));

	a->_balance_factor = getBalance(a);

	if (a->_balance_factor > 1 && key < a->_left->_key) {
		return rightRotate(a);
	}

	if (a->_balance_factor < -1 && key > a->_right->_key) {
		return leftRotate(a);
	}

	if (a->_balance_factor > 1 && key > a->_left->_key) {
		a->_left = leftRotate(a->_left);
		return rightRotate(a);
	}

	if (a->_balance_factor < -1 && key < a->_right->_key) {
		a->_right = rightRotate(a->_right);
		return leftRotate(a);
	}

	return a;
}






