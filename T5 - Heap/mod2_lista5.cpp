#include "mod2_lista5.h"
#include <iostream>
using namespace std;

template <class T>
Heap<T>::Heap()
	: _vector(0)
{

}

template <class T>
Heap<T>::Heap(T* values, unsigned int size) : _vector(size)
{
	for (int i = 0; i < size; ++i) {
		this->_vector[i] = values[i];
	}

	Heapify();
}

template <class T>
Heap<T>::Heap(const vector<T>& other) : _vector(other)
{
	Heapify();
}

template <class T>
Heap<T>::~Heap()
{
	cout << "The Heap has been deleted." << endl;
	int size = this->_vector.size();
	this->_vector.erase(this->_vector.begin(), this->_vector.begin() + size);
}

template <class T>
unsigned int Heap<T>::size()
{
	return this->_vector.size();
}

template <class T>
void Heap<T>::push(int value)
{
	int size = this->_vector.size();
	this->_vector[size] = value;
	BubbleUp(size);
}

template <class T>
T Heap<T>::top()
{
	return this->_vector[0];
}

template <class T>
void Heap<T>::pop()
{
	int size = this->_vector.size();

	if (size == 0) {
		return;
	}

	this->_vector[0] = this->_vector[size - 1];
	this->_vector.pop_back();

	BubbleDown(0);
}

template <class T>
void Heap<T>::show(const std::string& title)
{
	cout.precision(20);
	std::cout << title << " ";

	if (this->_vector.size() > 0)
	{
		std::cout << this->_vector[0];
	}

	for (unsigned int i = 1; i < this->_vector.size(); i++)
	{
		std::cout << " " << this->_vector[i];
	}

	std::cout << std::endl;
}

template <class T>
void Heap<T>::BubbleDown(int pos) {
	int size = this->_vector.size();
	int leftChildPos = 2 * pos + 1;
	int rightChildPos = 2 * pos + 2;

	if (leftChildPos >= size) {
		return; //essa posicao eh uma folha
	}

	int minPos = pos;

	if ((this->_vector[pos] > this->_vector[leftChildPos])) {
		minPos = leftChildPos;
	}

	if ((rightChildPos < size) && (this->_vector[minPos] > this->_vector[rightChildPos])) {
		minPos = rightChildPos;
	}

	if (minPos != pos) {
		//precisa realizar a troca
		T temp = this->_vector[pos];
		this->_vector[pos] = this->_vector[minPos];
		this->_vector[minPos] = temp;
		BubbleDown(minPos);
	}
}

template <class T>
void Heap<T>::BubbleUp(int pos) {
	if (pos == 0) {
		return;
	}

	int parentPos = (pos - 1) / 2;

	if(this->_vector[parentPos] > this->_vector[pos]) {
		T temp = this->_vector[parentPos];
		this->_vector[parentPos] = this->_vector[pos];
		this->_vector[pos] = temp;
		BubbleUp(parentPos);
	}
}

template <class T>
void Heap<T>::Heapify() {
	int size = this->_vector.size();

	for (int i = size - 1; i >= 0; --i) {
		BubbleDown(i);
	}
}

template Heap <int>;
template Heap <float>;
template Heap <double>;