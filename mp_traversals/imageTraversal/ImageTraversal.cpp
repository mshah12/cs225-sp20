#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  traversal_ = NULL;
}


ImageTraversal::Iterator::Iterator(PNG currPNG, Point startPoint, double currTolerance, ImageTraversal* currTraversal) {
  traversalPNG_ = currPNG;
  startPoint_ = startPoint;
  currPoint_ = startPoint;
  traversalTolerance_ = currTolerance;
  traversal_ = currTraversal;

  vistable_.resize(traversalPNG_.width());
  for(vector<bool>& v : vistable_) {
    v.resize(traversalPNG_.height());
  }
  for(unsigned int width = 0; width < traversalPNG_.width(); width++) {
    for(unsigned int height = 0; height < traversalPNG_.height(); height++) {
      vistable_[width][height] = true;
    }
  }
}

bool ImageTraversal::Iterator::isVistable(Point curr) {
  if(curr.x >= traversalPNG_.width() || curr.y >= traversalPNG_.height()) {
    return false;
  }
  if(0 > curr.x || 0 > curr.y) {
    return false;
  }
  HSLAPixel& temp1 = traversalPNG_.getPixel(startPoint_.x, startPoint_.y);
  HSLAPixel& temp2 = traversalPNG_.getPixel(curr.x, curr.y);
  if(calculateDelta(temp1, temp2) >= traversalTolerance_) {
    return false;
  }
  return true;
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  Point temp = traversal_->pop();
  vistable_[temp.x][temp.y] = false;

  Point right = Point(temp.x + 1, temp.y);
  Point down = Point(temp.x, temp.y + 1);
  Point left = Point(temp.x - 1, temp.y);
  Point up = Point(temp.x, temp.y - 1);

  if(isVistable(right)) {
    traversal_->add(right);
  }
  if(isVistable(down)) {
    traversal_->add(down);
  }
  if(isVistable(left)) {
    traversal_->add(left);
  }
  if(isVistable(up)) {
    traversal_->add(up);
  }

  while(!traversal_->empty() && !(vistable_[traversal_->peek().x][traversal_->peek().y])) {
    traversal_->pop();
  }
  if(traversal_->empty()) {
    traversal_ = NULL;
    return *this;
  }
  currPoint_ = traversal_->peek();
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return currPoint_;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  return (traversal_ != other.traversal_);
}
