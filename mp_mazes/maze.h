/* Your code here! */
#pragma once
#include "cs225/PNG.h"
#include "dsets.h"
#include <map>
#include <stack>
#include <vector>

using namespace std;
using namespace cs225;

class SquareMaze {
  public:
    void makeMaze(int width, int height);
    bool canTravel(int x, int y, int dir) const;
    void setWall(int x, int y, int dir, bool exists);
    vector<int> solveMaze();
    int solveMazeInitializer(int & x, int & y, int & index, int & index2, int & index3);
    void solveMazeHelper(int index, int currSquare);
    void findLongestPath();
    void findLongestPathHelper(vector<int> & currentPath, int & currSquare, int & currLength, int index);
    void checkLongerPath(vector<int> & currentPath, int currentPathLength);
    PNG * drawMaze() const;
    PNG * drawMazeWithSolution();
    PNG * drawCreativeMaze();
    PNG * drawCreativeMazeWithSolution();
  private:
    int mazeWidth_;
    int mazeHeight_;
    int mazeSize_;
    int maxLength;
    bool reversed_;
    stack<int> nextSquare;
    map<int, int> solution;
    vector<int> longestPath;
    vector<bool> visited_;
    vector<bool> rightWalls_;
    vector<bool> downWalls_;
};
