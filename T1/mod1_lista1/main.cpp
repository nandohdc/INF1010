#include "mod1_lista1.h"
#include <iostream>

int main (void){

	List l2 = List();
	l2.push_back(106);
	l2.push_back(105);
	l2.push_back(102);

	l2.sort();
	l2.pop_back();
	l2.size();
	l2.print();
	l2.sort();
	l2.print();

	l2.remove(105);
	l2.print();
	
	
	List* L3 = new List(l2);

	L3->print();

	L3->push_front(105);
	L3->pop_back();
	L3->push_back(101);

	

	L3->print();

	L3->sort();

	L3->print();

	L3->~List();
	return 0;
}