#ifndef MAZE_H
#define MAZE_H

#include <vector>

int randomInt( int from, int to );
void createMaze( int m, int n, std::vector< bool >& maze );
void drawMaze( const std::vector< bool >& maze, int m, int n );
void printMaze( const std::vector< bool >& maze );

#endif // MAZE_H

