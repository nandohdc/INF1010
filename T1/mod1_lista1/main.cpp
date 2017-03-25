#include "mod1_lista1.h"
#include <iostream>

int main (void){

	List* l2 = new List();
	l2->push_back(106);
	l2->push_back(100);
	l2->push_back(101);
	l2->push_back(104);
	l2->push_back(103);
	l2->push_back(105);
	//l2->print();

	//l2->remove(102);

	l2->sort();

	l2->print();

	//l3->print();
	//l2->print();

	//delete(l2);
	//delete(l3);

	return 0;
}