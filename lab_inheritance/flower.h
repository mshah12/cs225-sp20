/**
 * @file flower.h
 * Declaration of the Flower class.
 */

#pragma once

#include "shape.h"

/**
 * A subclass of Drawable that can draw a flower
 */
class Flower : public Drawable
{
  private:
    Shape * my_stem;
    Shape * my_pistil; // center piece of flower
    Shape * my_leaf;

    void drawPetals(cs225::PNG* canvas, const Vector2& center, int x, int y) const;

  public:
    ~Flower();
    Flower(const Vector2& center);
    void draw(cs225::PNG* canvas) const;
};
