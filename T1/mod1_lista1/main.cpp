#include "mod1_lista1.h"
#include <iostream>

int main (void){

	List l2 = List();
	l2.push_back(106);
	l2.push_back(105);
	l2.push_back(102);

	l2.sort();

	l2.print();


	return 0;
}