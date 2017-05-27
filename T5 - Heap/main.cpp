#include "mod2_lista5.h"
#include <iostream>
using namespace std;

int main(void) {
	int array[] = { 10, 4, 5, 30, 3, 300, 15, 2 };
	float array2[] = {0.124f, 0.34242f, 11.32432f, 23.2321f, 3.424f, 1.34276f};
	double array3[] = { 10.99999999999996, 4.99999999999996, 5.99999999999996, 30.99999999999996, 3.99999999999996, 300.99999999999996 };

	//Heap<int> minHeap(array, 8);
	//Heap<float> minHeap2(array2, 6);
	//Heap<double> minHeap3(array3, 6);

	Heap<int> minHeap4(array, 8);
	cout << minHeap4.size() << endl;
	minHeap4.push(11);
	minHeap4.push(1);
	minHeap4.push(6);
	minHeap4.push(33);
	minHeap4.push(7);
	minHeap4.push(310);
	minHeap4.push(16);
	minHeap4.push(8);

	//minHeap.show("Min Heap:");
	//minHeap2.show("Min Heap2:");
	//minHeap3.show("Min Heap3:");
	minHeap4.show("Min Heap4: ");

	return 0;

}