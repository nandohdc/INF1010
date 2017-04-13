#include "mod1_lista3.h"
#include <iostream>

using namespace std;

int main(void) {

	Avl a;
	a.insert(5);
	a.show(" A r v o r e A : ");
	a.insert(8);
	a.show(" A r v o r e A : ");
	a.insert(10);
	a.show(" A r v o r e A : ");
	a.insert(4);
	a.show(" A r v o r e A : ");
	a.insert(3);
	a.show(" A r v o r e A : ");
	a.insert(6);
	a.show(" A r v o r e A : ");
	a.insert(12);
	a.show(" A r v o r e A : ");
	a.insert(11);
	a.show(" A r v o r e A : ");
	std::cout << " A l t u r a de A : "
		<< a.height() << std::endl;
	Avl b(a);
	a.show(" A r v o r e B : ");

	return 0;

}