/* Your code here! */
#include "maze.h"
#include "cs225/PNG.h"
#include <iostream>
#include <stack>
#include <vector>
#include <map>

using namespace std;
using namespace cs225;

void SquareMaze::makeMaze(int width, int height) {
  // initializes variables and sizes of the maze
  mazeWidth_ = width;
  mazeHeight_ = height;
  mazeSize_ = (width * height);
  //reversed_ = false;

  visited_.resize(mazeSize_);
  for(auto square : visited_) {
    square = false;
  }
  maxLength = 0;

  DisjointSets squares;
  int squareNumber = mazeSize_;
  squares.addelements(mazeSize_);

  //clears the pre-existing mazes, if exists, and creates the new maze
  rightWalls_.clear();
  downWalls_.clear();
  rightWalls_.resize(mazeSize_);
  downWalls_.resize(mazeSize_);
  for(auto rightWallExists : rightWalls_) {
    rightWallExists = true;
  }
  for(auto downWallExists : downWalls_) {
    downWallExists = true;
  }

  // Randomizes the maze by selecting walls and destroying them
  while(squareNumber > 1) {
    int mazeW = rand() % width;
    int mazeH = rand() % height;
    int wallNeighbor = rand() % 2;
    int currSquare = ((mazeH * width) + mazeW);
    int nextSquareDown = (((mazeH + 1) * width) + mazeW);
    int nextSquareRight = ((mazeH * width) + mazeW + 1);

    // breaking down the right wall
    if(wallNeighbor == 0 && mazeW < (mazeWidth_ - 1)) {
      if(squares.find(currSquare) != squares.find(nextSquareRight)) {
        setWall(mazeW, mazeH, wallNeighbor, false);
        squares.setunion(currSquare, nextSquareRight);
        squareNumber--;
      }
    }
    // breaking down the down wall
    if(wallNeighbor == 1 && mazeH < (mazeHeight_ - 1)) {
      if(squares.find(currSquare) != squares.find(nextSquareDown)) {
        setWall(mazeW, mazeH, wallNeighbor, false);
        squares.setunion(currSquare, nextSquareDown);
        squareNumber--;
      }
    }
  }
}

bool SquareMaze::canTravel(int x, int y, int dir) const {
  // initializes local variables for cleaner code
  int index = ((mazeWidth_ * y) + x);
  int index2 = ((mazeWidth_ * (y - 1)) + x);
  int checkWidth = (mazeWidth_ - 1);
  int checkHeight = (mazeHeight_ - 1);

  // checks a wall, depending on the input, to determine if travel in that way is possible
  if(dir == 0 && x < checkWidth && rightWalls_[index] == false) {
    return true;
  }
  if(dir == 1 && y < checkHeight && downWalls_[index] == false) {
    return true;
  }
  if(dir == 2 &&  x != 0 && rightWalls_[index - 1] == false) {
    return true;
  }
  if(dir == 3 && y != 0 && downWalls_[index2] == false) {
    return true;
  }
  return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {
  // initializes local variables for cleaner code
  int index = ((mazeWidth_ * y) + x);

  // breaks down either the down or right wall depending on the input
  if(dir == 1) {
    downWalls_[index] = exists;
    return;
  }
  if(dir == 0) {
    rightWalls_[index] = exists;
    return;
  }
}

vector<int> SquareMaze::solveMaze() {
  visited_[0] = true;
  nextSquare.push(0);

  while(!nextSquare.empty()) {
    int x, y, index, index2, index3;
    int currSquare = solveMazeInitializer(x, y, index, index2, index3);

    if(canTravel(x, y, 0)) {
      if(!visited_[index + 1]) {
        solveMazeHelper(index + 1, currSquare);
      }
    }
    if(canTravel(x, y, 1)) {
      if(!visited_[index2]) {
        solveMazeHelper(index2, currSquare);
      }
    }
    if(canTravel(x, y, 2)) {
      if(!visited_[index - 1]) {
        solveMazeHelper(index - 1, currSquare);
      }
    }
    if(canTravel(x, y, 3)) {
      if(!visited_[index3]) {
        solveMazeHelper(index3, currSquare);
      }
    }
  }

  findLongestPath();
  return longestPath;
}

void SquareMaze::solveMazeHelper(int index, int currSquare) {
  nextSquare.push(index);
  solution[index] = currSquare;
  visited_[index] = true;
}

int SquareMaze::solveMazeInitializer(int & x, int & y, int & index, int & index2, int & index3) {
  int currSquare = nextSquare.top();
  nextSquare.pop();
  x = currSquare % mazeWidth_;
  y = currSquare / mazeWidth_;
  index = (mazeWidth_ * y) + x;
  index2 = ((mazeWidth_ * (y + 1)) + x);
  index3 = ((mazeWidth_ * (y - 1)) + x);
  return currSquare;
}

void SquareMaze::findLongestPath() {
  vector<int> currentPath;
  int count = 0;
  int squareChecker = mazeWidth_;

  while(count < mazeWidth_) {
    currentPath.clear();
    int pathLength = 0;
    int square = ((mazeWidth_ * (mazeHeight_ - 1)) + count);

    while(square != 0) {
      int checkSquare = square - solution[square];
      if(checkSquare == 1) {
        findLongestPathHelper(currentPath, square, pathLength, 0);
        continue;
      }
      if(checkSquare == squareChecker) {
        findLongestPathHelper(currentPath, square, pathLength, 1);
        continue;
      }
      if(checkSquare == -1) {
        findLongestPathHelper(currentPath, square, pathLength, 2);
        continue;
      }
      if(checkSquare == -squareChecker) {
        findLongestPathHelper(currentPath, square, pathLength, 3);
        continue;
      }
    }

    checkLongerPath(currentPath, pathLength);
    count++;
  }

  int tempIndex = (longestPath.size() - 1);
  vector<int> temp = longestPath;
  for(int i = tempIndex; i >= 0; i--) {
    longestPath[tempIndex - i] = temp[i];
  }
  reversed_ = false;
}

void SquareMaze::findLongestPathHelper(vector<int> & currentPath, int & currSquare, int & currLength, int index) {
  currentPath.push_back(index);
  currSquare = solution[currSquare];
  currLength = currLength + 1;
}

void SquareMaze::checkLongerPath(vector<int> & currentPath, int currentPathLength) {
  if(maxLength >= currentPathLength) {
    return;
  }
  longestPath = currentPath;
  maxLength = currentPathLength;
}

PNG * SquareMaze::drawMaze() const {
  int count = 0;
  HSLAPixel blankPixel = HSLAPixel(0, 0, 0);
  int newWidth = ((mazeWidth_ * 10) + 1);
  int newHeight = ((mazeHeight_ * 10) + 1);
  PNG * drawing = new PNG(newWidth, newHeight);

  while(count < newHeight) {
    drawing->getPixel(0, count) = blankPixel;
    count++;
  }

  count = 10;
  while(count < newWidth) {
    drawing->getPixel(count, 0) = blankPixel;
    count++;
  }

  for(int width = 0; width < mazeWidth_; width++) {
    for(int height = 0; height < mazeHeight_; height++) {
      int newCount = 0;
      int index = ((mazeWidth_ * height) + width);
      if(downWalls_[index] == true) {
        while(newCount < 11) {
          HSLAPixel & square = drawing->getPixel(((width * 10) + newCount), ((height + 1) * 10));
          square = blankPixel;
          newCount++;
        }
      }
      newCount = 0;
      if(rightWalls_[index]) {
        while(newCount < 11) {
          HSLAPixel & square = drawing->getPixel(((width + 1) * 10), ((height * 10) + newCount));
          square = blankPixel;
          newCount++;
        }
      }
    }
  }
  return drawing;
}

PNG * SquareMaze::drawMazeWithSolution() {
  int startX = 5;
  int startY = 5;
  HSLAPixel redSquare = HSLAPixel(0, 1, 0.5, 1);
  HSLAPixel whiteSquare = HSLAPixel(0, 0, 1);

  PNG * drawing = drawMaze();
  vector<int> answers = solveMaze();

  if(reversed_ == false) {
    int tempIndex = (answers.size() - 1);
    vector<int> temp = answers;
    for(int i = tempIndex; i >= 0; i--) {
      answers[tempIndex - i] = temp[i];
    }
    reversed_ = true;
  }

  int step = 0;
  int totalSteps = answers.size();
  while(step < totalSteps) {
    if(answers[step] == 0) {
      for(int k = 0; k < 11; k++) {
        drawing->getPixel(startX + k, startY) = redSquare;
      }
      startX += 10;
    }
    if(answers[step] == 1) {
      for(int k = 0; k < 11; k++) {
        drawing->getPixel(startX, startY + k) = redSquare;
      }
      startY += 10;
    }
    if(answers[step] == 2) {
      for(int k = 0; k < 11; k++) {
        drawing->getPixel(startX - k, startY) = redSquare;
      }
      startX -= 10;
    }
    if(answers[step] == 3) {
      for(int k = 0; k < 11; k++) {
        drawing->getPixel(startX, startY - k) = redSquare;
      }
      startY -=10;
    }
    step++;
  }

  step = 1;
  while(step < 10) {
    drawing->getPixel(((startX / 10) * 10) + step, (mazeHeight_ * 10)) = whiteSquare;
    step++;
  }

  return drawing;
}

PNG * SquareMaze::drawCreativeMaze() {
  int count = 0;
  HSLAPixel yellowSquare = HSLAPixel(45, 100, 50, 1);
  HSLAPixel blueSquare = HSLAPixel(248, 100, 50, 1);
  int newWidth = ((mazeWidth_ * 10) + 1);
  int newHeight = ((mazeHeight_ * 10) + 1);
  PNG * creativeMaze = new PNG(newWidth, newHeight);

  while(count < newHeight) {
    creativeMaze->getPixel(0, count) = yellowSquare;
    count++;
  }

  count = 10;
  while(count < newWidth) {
    creativeMaze->getPixel(count, 0) = yellowSquare;
    count++;
  }

  for(int width = 0; width < mazeWidth_; width++) {
    for(int height = 0; height < mazeHeight_; height++) {
      int newCount = 0;
      int index = ((mazeWidth_ * height) + width);
      if(downWalls_[index] == true) {
        while(newCount < 11) {
          HSLAPixel & square = creativeMaze->getPixel(((width * 10) + newCount), ((height + 1) * 10));
          square = blueSquare;
          newCount++;
        }
      }
      newCount = 0;
      if(rightWalls_[index]) {
        while(newCount < 11) {
          HSLAPixel & square = creativeMaze->getPixel(((width + 1) * 10), ((height * 10) + newCount));
          square = blueSquare;
          newCount++;
        }
      }
    }
  }
  return creativeMaze;
}

PNG * SquareMaze::drawCreativeMazeWithSolution() {

  PNG * creativeMaze = drawCreativeMaze();
  int startX = 5;
  int startY = 5;
  HSLAPixel redSquare = HSLAPixel(0, 1, 0.5, 1);
  HSLAPixel whiteSquare = HSLAPixel(0, 0, 1);

  vector<int> answers = solveMaze();

  int step = 0;
  int totalSteps = answers.size();
  while(step < totalSteps) {
    if(answers[step] == 0) {
      for(int k = 0; k < 11; k++) {
        creativeMaze->getPixel(startX + k, startY) = redSquare;
      }
      startX += 10;
    }
    if(answers[step] == 1) {
      for(int k = 0; k < 11; k++) {
        creativeMaze->getPixel(startX, startY + k) = redSquare;
      }
      startY += 10;
    }
    if(answers[step] == 2) {
      for(int k = 0; k < 11; k++) {
        creativeMaze->getPixel(startX - k, startY) = redSquare;
      }
      startX -= 10;
    }
    if(answers[step] == 3) {
      for(int k = 0; k < 11; k++) {
        creativeMaze->getPixel(startX, startY - k) = redSquare;
      }
      startY -=10;
    }
    step++;
  }

  step = 1;
  while(step < 10) {
    creativeMaze->getPixel(((startX / 10) * 10) + step, (mazeHeight_ * 10)) = whiteSquare;
    step++;
  }

  return creativeMaze;
}
