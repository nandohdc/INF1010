#include "mod1_lista2.h"
#include <iostream>
using namespace std;

int main(void) {
	int min = -2;

	Abb b3 = Abb();

	b3.insert(8);
	b3.insert(5);
	b3.insert(6);
	b3.insert(10);
	b3.insert(9);
	b3.insert(10);
	b3.insert(12);
	b3.insert(4);
	b3.show("Arvore B3");

	b3.first();
	int value = b3.value();
	cout << value << endl;

	Abb* b2 = new Abb(b3);
	b2->show("Arvore B2");
	b2->last();
	value = b2->value();
	cout << value << endl;

	return 0;
}