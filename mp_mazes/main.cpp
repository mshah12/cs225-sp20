#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;
using namespace cs225;

int main()
{
    // Write your own main here
    // cout << "Add your own tests here! Modify main.cpp" << endl;
    SquareMaze myMaze;
    PNG * createdMaze;
    myMaze.makeMaze(92, 92);
    createdMaze = myMaze.drawCreativeMazeWithSolution();
    createdMaze->writeToFile("creative.png");
    delete createdMaze;
    return 0;
}
