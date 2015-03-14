#ifndef MAZESOLVER_H
#define MAZESOLVER_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include "FileException.h"
#include "ArrayStack.h"



using std::fstream;
using std::ifstream;

    struct Cell
    {
      int row;
      int col;
    };

    const char visited = 'X';
    const char pathMarker = '#';
    const char emptyPath = ' ';

    
class MazeSolver
{
public:
  
    MazeSolver(char * fileName, char * outFileName);
    ~MazeSolver();
       
private:
  
  int rows;
  int cols;
  char ** maze;
  
  int getRows(char * fileName);
  int getCols(char * fileName);
  void loadMaze(char * fileName);
  void writeMaze();
  void showTruePath();
  void setTruePathMarker();
  
  void solve();
  void print();
  
  char * outFile = "Solved.txt";
  ArrayStack<Cell> path;
  
};

#endif // MAZESOLVER_H
