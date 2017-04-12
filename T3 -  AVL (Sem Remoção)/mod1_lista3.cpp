#include "mod1_lista3.h"
#include <iostream>

Avl::Avl()
	: _root(nullptr), _cursor(nullptr)
{
}


Avl::Avl(const int key) 
{
}


Avl::Avl(const Avl& orig)
	: _root(nullptr), _cursor(nullptr)
{
}


Avl::~Avl()
{
}


int Avl::height()
{
	return 0;
}


void Avl::insert(int key)
{
}


void Avl::show(const std::string& title)
{
	std::cout << title << std::endl;
	show_rec(_root);
	std::cout << std::endl;
}


bool first()
{
	return false;
}


bool last()
{
	return false;
}


bool next()
{
	return false;
}


bool prev()
{
	return false;
}


int value()
{
	return 0;
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

