#pragma once
#ifndef MOD2_LISTA5_H
#define MOD2_LISTA5_H

#include <string>
#include <vector>
#include "mod2_lista5.h"
using namespace std;

//#define MAX_ELEMENTS 50

template <class T>
class Heap /* Min-Heap */
{
public:
	//Construtor vazio
	Heap();

	//Constroi o heap a partir de um vetor de elementos
	Heap(T* values, unsigned int size);

	//Constroi o heap a partir de outro heap
	Heap(const vector<T>& other);

	//Destroi o heap
	~Heap();

	//Retorna o numero de elementos atualmente no heap
	unsigned int size();

	//Insere um novo elemento
	void push(int value);

	//Retorna o elemento do topo
	T top();

	//Remove o elemento do topo
	void pop();

	//Exibe os elementos do heap
	void show(const std::string& title);

private:
	vector<T> _vector;
	void BubbleDown(int pos);
	void BubbleUp(int pos);
	void Heapify();
	/* Funcoes privadas que julgar necessarias */

private:
	//Contem os elementos do heap
	//int _container[MAX_ELEMENTS];

	//Tamanho atual do heap
	//unsigned int _size;
};
#endif
