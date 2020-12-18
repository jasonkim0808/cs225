/* Your code here! */
#pragma once
#include "dsets.h"
#include <vector>
#include <queue>
#include "cs225/PNG.h"

using std::vector;
using cs225::PNG;
class SquareMaze{
  public:
    SquareMaze();
    void makeMaze(int width, int height);
    bool canTravel(int x, int y, int dir) const;
    void setWall(int x, int y, int dir, bool exists);
    vector<int> solveMaze();
    PNG* drawMaze() const;
    PNG* drawMazeWithSolution();
    
  private:
    int w;
    int h;
    vector<int> box;
    DisjointSets dj;
    int maxN;
};
