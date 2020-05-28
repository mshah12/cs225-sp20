#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>


void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
  cs225::PNG png, pngOutput;
  png.readFromFile(inputFile);
  pngOutput.readFromFile(inputFile);
  double pngWidth = png.width() - 1;
  double pngHeight = png.height() - 1;
  for (unsigned x = 0; x < png.width(); x++) {
    for (unsigned y = 0; y < png.height(); y++) {
      cs225::HSLAPixel & pixel = png.getPixel(x, y);
      cs225::HSLAPixel & pixel2 = pngOutput.getPixel(pngWidth - x, pngHeight - y);
      pixel2.h = pixel.h;
      pixel2.s = pixel.s;
      pixel2.l = pixel.l;
      pixel2.a = pixel.a;
    }
  }
  pngOutput.writeToFile(outputFile);
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  // TODO: Part 3
  for (unsigned x = 0; x < png.width(); x++) {
    for (unsigned y = 0; y < png.height(); y++) {
      cs225::HSLAPixel & pixel = png.getPixel(x, y);
      pixel.s = 0.75;
      pixel.l = 0.50;
      pixel.a = 1.0;
      if (y < 265) {
        pixel.h = 20.0;
      }
      else if (y >= 265 && y < 530) {
        pixel.l  = 1.0;
      }
      else {
        pixel.h = 110;
      }
    }
  }
  return png;
}
