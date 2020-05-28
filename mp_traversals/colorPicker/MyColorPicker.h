#pragma once

#include "../cs225/PNG.h"
#include "ColorPicker.h"
#include "../cs225/HSLAPixel.h"
#include "../Point.h"

using namespace cs225;

/**
 * A color picker class using your own color picking algorithm
 */
class MyColorPicker : public ColorPicker {
public:
  HSLAPixel getColor(unsigned x, unsigned y);
  MyColorPicker(PNG &png, Point center, int picker);
private:
  PNG png_;
  Point center_;
  HSLAPixel red_;
  HSLAPixel yellow_;
  int colorSelect_;
};
