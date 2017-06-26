#include "graph.h"
#include "unionfind.h"
#include <iostream>
#include <functional>
#include <queue>
#include <utility>
#include <stack>

Graph::Graph( int N )
    : G(std::vector< std::vector<Edge> >(N))
{
	this->sizeG = N;
	this->distances = std::vector<int>(N);
}


void Graph::insertEdge( int from, int to, int weight, bool undirected )
{
	struct Edge e;
	e.v = to;
	e.w = weight;

    G[from].push_back(e);

    if( undirected )
    {
		e.v = from;
		e.w = weight;
        G[to].push_back(e);
    }
}


void Graph::print()
{
    for( unsigned int u = 0; u < G.size(); u++ )
    {
        std::cout << u << ": ";

        if( !G[u].empty() )
        {
            std::cout << G[u][0].v << '(' << G[u][0].w << ')';
        }

        for( unsigned int e = 1; e < G[u].size(); e++ )
        {
            std::cout << ", " << G[u][e].v << '(' << G[u][e].w << ')';
        }

        std::cout << std::endl;
    }
}


void Graph::bfs( int s )
{
	std::vector<int> _distance;
	std::deque<int> _queue;
	std::vector<Color> _colors;

	for (int index = 0; index < this->sizeG; index++) {
		_colors.push_back(this->WHITE);
		_distance.push_back(INT_MAX);
	}
	_queue.push_front(s);
	_distance[s] = 0;

	while (!_queue.empty()) {
		int popped = _queue.front();
		_queue.pop_front();
		for (int index = 0; index < this->G[popped].size(); index++) {
			if (_colors[index] == this->WHITE) {
				if (_distance[index] > _distance[popped]) {
					_distance[index] = _distance[popped] + 1;
				}
				_colors[index] = this->GRAY;
				_queue.push_front(this->G[popped][index].v);
			}
		}
		_colors[popped] = this->BLACK;
	}

	for (int index = 0; index < _distance.size(); index++) {
		this->distances[index] = _distance[index];
	}
}


void Graph::dfs(int s)
{
	std::vector<int> _distance;
	std::stack<int> _stack;
	std::vector<Color> _colors;
	for (int index = 0; index < this->sizeG; index++) {
		_colors.push_back(this->WHITE);
		_distance.push_back(INT_MAX);
	}
		_stack.push(s);
		_distance[s] = 0;

		while (!_stack.empty()) {
			int popped = _stack.top();
			_stack.pop();
			if (_colors[popped] == this->WHITE) {
				_colors[popped] = this->GRAY;
				for (int index = 0; index < this->G[popped].size(); index++) {
					if (_distance[index] > _distance[popped]) {
						_distance[index] = _distance[popped] + 1;
					}
					_stack.push(this->G[popped][index].v);
				}
			}
			_colors[popped] = this->BLACK;
		}

		for (int index = 0; index < _distance.size(); index++) {
			this->distances[index] = _distance[index];
		}
}


void Graph::djikstra( int s )
{
	std::vector<int> _distance;
	std::vector<int> _previous;
	std::priority_queue < std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>> > minheap;
	std::vector<Color> _colors;
	
	for (int index = 0; index < this->sizeG; index++) {
		_colors.push_back(this->WHITE);
		_distance.push_back(INT_MAX);
		_previous.push_back(-1);
	}

	minheap.push(std::make_pair(_distance[s], s));
	_distance[s] = 0;

	while (!minheap.empty()) {
		int popped = minheap.top().second;
		minheap.pop();
		for (int index = 0; index < this->G[popped].size(); index++) {
			if (_colors[this->G[popped][index].v] == this->WHITE) {
				if (_distance[this->G[popped][index].v] > _distance[popped] + this->G[popped][index].w) {
					_distance[this->G[popped][index].v] = _distance[popped] + this->G[popped][index].w;
					minheap.push(std::make_pair(_distance[this->G[popped][index].v], this->G[popped][index].v));
				}
			}
		}
		_colors[popped] = this->BLACK;
	}

	for (int index = 0; index < _distance.size(); index++) {
		this->distances[index] = _distance[index];
	}
}


Graph Graph::kruskal()
{
	Graph *T =  new Graph(this->sizeG);
	UnionFind *U = new UnionFind(this->sizeG);
	std::priority_queue < std::tuple<int, int, int>, std::vector<std::tuple<int, int, int>>, std::greater<std::tuple<int, int, int>>> minheap;

	for (int index = 0; index < this->sizeG; index++) {
		for (int index2 = 0; index2 < this->G[index].size(); index2++) {
			minheap.push(std::make_tuple(this->G[index][index2].w, this->G[index][index2].v, index));
		}
	}

	while (U->getNumSets() > 1 && !minheap.empty()) {
		if (U->find(std::get<2>(minheap.top())) != U->find(std::get<1>(minheap.top()))) {
			T->insertEdge(std::get<2>(minheap.top()), std::get<1>(minheap.top()), std::get<0>(minheap.top()));
			U->makeUnion(std::get<2>(minheap.top()), std::get<1>(minheap.top()));
			minheap.pop();
		}
		minheap.pop();
	}

    return (*T);
}


bool Graph::isBicolored()
{
	std::vector<int> _colors;
	std::deque<int> _queue;
	int src = 0;
	for (int index = 0; index < this->sizeG; index++) {
		_colors.push_back(-1);
	}

	_colors[src] = 1;
	_queue.push_back(src);

	while (!_queue.empty()) {
		int popped = _queue.front();
		_queue.pop_front();

		for (int index = 0; index < this->G[popped].size(); index++) {
			if (_colors[index] == -1) {
				_colors[index] = 1 - _colors[popped];
				_queue.push_back(this->G[popped][index].v);
			}
			else if (_colors[index] == _colors[popped]) {
				return false;
			}
		}
	}
    return true;
}

