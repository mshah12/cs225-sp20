#include "Image.h"

void Image::lighten() {
  for(unsigned x = 0; x < this->width(); x++) {
    for(unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x,y);
      if((pixel.l + 0.1) > 1.0) {
        pixel.l = 1.0;
      }
      else {
        pixel.l = pixel.l + 0.1;
      }
    }
  }
}

void Image::lighten(double amount) {
  for(unsigned x = 0; x < this->width(); x++) {
    for(unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x,y);
      if((pixel.l + amount) > 1.0) {
        pixel.l = 1.0;
      }
      else {
        pixel.l = pixel.l + amount;
      }
    }
  }
}

void Image::darken() {
  for(unsigned x = 0; x < this->width(); x++) {
    for(unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x,y);
      if((pixel.l - 0.1) < 0.0) {
        pixel.l = 0.0;
      }
      else {
        pixel.l = pixel.l - 0.1;
      }
    }
  }
}

void Image::darken(double amount) {
  for(unsigned x = 0; x < this->width(); x++) {
    for(unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x,y);
      if((pixel.l - amount) < 0.0) {
        pixel.l = 0.0;
      }
      else {
        pixel.l = pixel.l - amount;
      }
    }
  }
}

void Image::saturate() {
  for(unsigned x = 0; x < this->width(); x++) {
    for(unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x,y);
      if((pixel.s + 0.1) > 1.0) {
        pixel.s = 1.0;
      }
      else {
        pixel.s = pixel.s + 0.1;
      }
    }
  }
}

void Image::saturate(double amount) {
  for(unsigned x = 0; x < this->width(); x++) {
    for(unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x,y);
      if((pixel.s + amount) > 1.0) {
        pixel.s = 1.0;
      }
      else {
        pixel.s = pixel.s + amount;
      }
    }
  }
}

void Image::desaturate() {
  for(unsigned x = 0; x < this->width(); x++) {
    for(unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x,y);
      if((pixel.s - 0.1) < 0.0) {
        pixel.s = 0.0;
      }
      else {
        pixel.s = pixel.s - 0.1;
      }
    }
  }
}

void Image::desaturate(double amount) {
  for(unsigned x = 0; x < this->width(); x++) {
    for(unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x,y);
      if((pixel.s - amount) < 0.0) {
        pixel.s = 0.0;
      }
      else {
        pixel.s = pixel.s - amount;
      }
    }
  }
}

void Image::grayscale() {
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);
      pixel.s = 0;
    }
  }
}

void Image::illinify() {
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);
      if (pixel.h > 293.5 || pixel.h < 113.5) {
        pixel.h = 11;
      }
      else {
        pixel.h = 216;
      }
    }
  }
}

void Image::rotateColor(double degrees) {
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);
    pixel.h = pixel.h + degrees;
    if(pixel.h > 360.0) {
      pixel.h = pixel.h - 360.0;
    }
    else {
      while(pixel.h < 0) {
        pixel.h = pixel.h + 360.0;
      }
    }
    }
  }
}

void Image::scale(double factor) {
  PNG *new_PNG = new PNG(*this);
  unsigned widthNew = this->width() * factor;
  unsigned heightNew = this->height() * factor;
  new_PNG->resize(widthNew, heightNew);
  for (unsigned i = 0; i < widthNew; i++) {
    for (unsigned j = 0; j < heightNew; j++) {
      HSLAPixel & pixelOrig = this->getPixel((i / factor), (j / factor));
      HSLAPixel & pixelNew = new_PNG->getPixel(i, j);
      pixelNew = pixelOrig;
    }
  }
  this->resize(widthNew, heightNew);
  for(unsigned i = 0; i < widthNew; i++) {
    for(unsigned j = 0; j < heightNew; j++) {
      this->getPixel(i,j) = new_PNG->getPixel(i,j);
    }
  }
  delete new_PNG;
}

void Image::scale(unsigned w, unsigned h) {
  double doublew = double(w);
  double doubleh = double(h);
  double doublewOrig = double(this->width());
  double doublehOrig = double(this->height());
  double widthRatioNew = (doublew / doublewOrig);
  double heightRatioNew = (doubleh / doublehOrig);
  if(widthRatioNew > heightRatioNew) {
    scale(heightRatioNew);
  }
  else {
    scale(widthRatioNew);
  }
}
