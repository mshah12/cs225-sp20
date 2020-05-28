#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"
#include <cmath>

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
MyColorPicker::MyColorPicker(PNG &png, Point center, int picker) {
  png_ = png;
  center_ = center;
  red_ = HSLAPixel(359, 1, 0.5, 1);
  yellow_ = HSLAPixel(38, 1, 0.5, 1);
  colorSelect_ = picker;
}

HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  HSLAPixel &pixel = png_.getPixel(x, y);
  if(colorSelect_ == 1) {
    pixel = red_;
    return pixel;
  }
  pixel = yellow_;
  return pixel;
}
