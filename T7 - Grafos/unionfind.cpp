#include "unionfind.h"


UnionFind::UnionFind(int n)
    : parent( std::vector<int>(n, -1) )
    , size( std::vector<int>(n, 1) )
    , numSets(n)
{
}


UnionFind::~UnionFind()
{
	parent.clear();
	size.clear();
}


int UnionFind::find(int u)
{
	int element = -2;
	if(element > this.parent.size()/2 ){
		element = findLoop(u);
	} else{
		element = findRec(u);
	}

	return element;
}


void UnionFind::makeUnion(int u, int v)
{
	x = this->find(u);
	y = this->find(v);

	if(x != y){
		if(this.size[x] > this.size[y]){
			parent[y] = x;
			this.size[x] = this.size[x] + 1;
			this.size[y] = this.size[y] - 1;
			if(this.size[y] == 0){
				this.numSets = this.numSets -1;
			}
		} else{
			parent[x] = y;
			this.size[y] = this.size[y] + 1;
			this.size[x] = this.size[x] - 1;
			if(this.size[x] == 0){
				this.numSets = this.numSets -1;
			}
		}
	} else{
		parent[y] = -1;
	}
}


int UnionFind::getNumSets()
{
    return numSets;
}

int UnionFind::findLoop(int u){
	while(parent[u] != -1){
		u = parent[u];
	}

	return u;
}

int UnionFind::findRec(int u){
	return (parent[u] == -1)? U : findRec(parent[u]);
}