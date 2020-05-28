
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.

  /*
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  */
  PNG square;
  square.readFromFile("png.png");
  FloodFilledImage image(square);
  square.writeToFile("myFloodFill.png");

  BFS change(square, Point(25, 25), 0.1);

  MyColorPicker red(square, Point(25, 25), 1);
  MyColorPicker yellow(square, Point(25, 25), 2);
  image.addFloodFill(change, red);
  image.addFloodFill(change, yellow);

  Animation animation = image.animate(50);
  PNG final = animation.getFrame(animation.frameCount() - 1);
  final.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  return 0;
}
