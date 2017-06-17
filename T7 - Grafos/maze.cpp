#include "maze.h"

#include <fstream>
#include <random>
#include <iostream>

#include "unionfind.h"


int randomInt( int from, int to )
{
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_int_distribution<int> distr(from, to);
    return distr(generator);
}


void createMaze( int m, int n, std::vector< bool >& maze )
{
    //Calculo do numero de paredes uteis.
    nElementsWall = (2*(m*n)) -1;

    //Criando o vetor de paredes uteis
    std::vector<int> walls = std::vector<int>(nElementsWall, 1);

    //Criando union que representas as celulas, com tamanho MxN
    _union = new UnionFind(m*n);

    int selectedWall = randomInt(0 , nElementsWall);

    if(selectedWall % 2 == 0){ // eh par
        if((selectedWall + 2) % m != 0){// nao eh borda
            if(_union->find((selectedWall/2)-1) != _union->find(selectedWall/2)+1) && maze[selectedWall] != true){
                maze[selectedWall] = !maze[selectedWall];
            }
        }
    } else{
        if (selectedWall <= ((m*n*2)-(m*2))){// nao eh borda
            if(_union->find((selectedWall/2)-1) != _union->find((selectedWall/2)+1) && maze[selectedWall] != true){
                maze[selectedWall] = !maze[selectedWall];
            }
        }
    }
}


void drawMaze( const std::vector< bool >& maze, int m, int n )
{
    //Linha de cima
    std::cout << "+";
    for( int j = 0; j < m; j++ )
        std::cout << "---+";

    for( int i = 0; i < n; i++ )
    {
        int pos = i*2*m;
        std::cout << std::endl << "|";
        for( int j = 0; j < m; j++ )
        {
            std::cout << "   ";
            std::cout << (maze[pos] ? "|" : " ");
            pos+=2;
        }
        std::cout << std::endl << "+";

        pos=i*2*m+1;
        for( int j = 0; j < m; j++ )
        {
            std::cout << (maze[pos] ? "---" : "   ") << "+";
            pos+=2;
        }
    }

    std::cout<< std::endl;
}


void printMaze( const std::vector< bool >& maze )
{
    if( !maze.empty() )
    {
        for( size_t i = 0; i < maze.size()-1; i+=2 )
        {
            std::cout << i/2 << " "
                      << (maze[i+0] ? 1 : 0) << " "
                      << (maze[i+1] ? 1 : 0) << std::endl;
        }
    }
}
