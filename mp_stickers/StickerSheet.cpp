#include "StickerSheet.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <iostream>

using namespace cs225;

StickerSheet::StickerSheet(const Image &picture, unsigned max) {
  curr_index_ = 0;
  max_index_ = max;
  base_picture_ = new Image(picture);
  x_ = new unsigned[max_index_];
  y_ = new unsigned[max_index_];
  sheet = new Image*[max_index_];
  for(unsigned i = 0; i < max_index_; i++) {
    x_[i] = 0;
    y_[i] = 0;
    sheet[i] = NULL;
  }
}

StickerSheet::~StickerSheet() {
  destroy_();
}

StickerSheet::StickerSheet(const StickerSheet &other) {
  copy_(other);
}

const StickerSheet & StickerSheet::operator=(const StickerSheet &other) {
  if(this != &other) {
    destroy_();
    copy_(other);
  }
  return *this;
}

void StickerSheet::changeMaxStickers(unsigned max) {
  unsigned maxOrig = max_index_;
  max_index_ = max;
  if(max_index_ == maxOrig) {
    return;
  }
  unsigned * x_New = new unsigned[max_index_];
  unsigned * y_New = new unsigned[max_index_];
  Image ** sheetNew = new Image *[max_index_];
  if(max_index_ < maxOrig) {
    for(unsigned i = 0; i < max_index_; i++) {
      if(sheet[i] != NULL) {
        x_New[i] = x_[i];
        y_New[i] = y_[i];
        sheetNew[i] = new Image(*sheet[i]);
      }
      else {
        x_New[i] = 0;
        y_New[i] = 0;
        sheetNew[i] = NULL;
      }
    }
    if(curr_index_ > max_index_) {
      curr_index_ = max_index_ - 1;
    }
  }
  else if(max_index_ > maxOrig) {
    for(unsigned i = 0; i < max_index_; i++) {
      x_New[i] = 0;
      y_New[i] = 0;
      sheetNew[i] = NULL;
    }
    for(unsigned i = 0; i < maxOrig; i++) {
      if(sheet[i] != NULL) {
        x_New[i] = x_[i];
        y_New[i] = y_[i];
        sheetNew[i] = new Image (*sheet[i]);
      }
    }
  }
  for(unsigned i = 0; i < maxOrig; i++) {
    delete sheet[i];
    sheet[i] = NULL;
  }
  delete[] x_;
  delete[] y_;
  delete[] sheet;
  x_ = x_New;
  y_ = y_New;
  sheet = sheetNew;
}

int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y) {
  if(curr_index_ == max_index_) {
    return -1;
  }
  for(unsigned i = 0; i < max_index_; i++) {
    if(sheet[i] == NULL) {
      sheet[i] = new Image(sticker);
      x_[i] = x;
      y_[i] = y;
      curr_index_ = curr_index_ + 1;
      return curr_index_;
    }
  }
  return -1;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
  for(unsigned i = 0; i < max_index_; i++) {
    if(sheet[i] != NULL && index >= 0 && index < max_index_ && index == i) {
      x_[i] = x;
      y_[i] = y;
      return true;
    }
  }
  return false;
}

void StickerSheet::removeSticker(unsigned index) {
  for(unsigned i = 0; i < max_index_; i++) {
    if(index >= 0 && index < max_index_ && index == i) {
      x_[i] = 0;
      y_[i] = 0;
      delete sheet[i];
      sheet[i] = NULL;
    }
  }
}

Image * StickerSheet::getSticker(unsigned index) {
  for(unsigned i = 0; i < max_index_; i++) {
    if(index >= 0 && index < max_index_ && index == i) {
      return sheet[index];
    }
  }
  return NULL;
}

Image StickerSheet::render() const {
  unsigned maxWidth = base_picture_->width();
  unsigned maxHeight = base_picture_->height();
  for(unsigned i = 0; i < max_index_; i++) {
    if(sheet[i] != NULL) {
       if(maxWidth < (x_[i] + sheet[i]->width())) {
         maxWidth = (x_[i] + sheet[i]->width());
       }
       if(maxHeight < (y_[i] + sheet[i]->height())) {
         maxHeight = (y_[i] + sheet[i]->height());
        }
     }
   }
  Image finalImage(*base_picture_);
  finalImage.resize(maxWidth, maxHeight);
  for(unsigned i = 0; i < max_index_; i++) {
    if(sheet[i] != NULL) {
      for(unsigned w = x_[i]; w < (x_[i] + sheet[i]->width()); w++) {
        for(unsigned h = y_[i]; h < (y_[i] + sheet[i]->height()); h++) {
          HSLAPixel & newPixel = finalImage.getPixel(w,h);
          HSLAPixel & stickerPixel = sheet[i]->getPixel(w - x_[i], h - y_[i]);
          if(stickerPixel.a > 0) {
            newPixel = stickerPixel;
          }
        }
      }
    }
  }
  return finalImage;
}

void StickerSheet::copy_(const StickerSheet &other) {
  max_index_ = other.max_index_;
  x_ = new unsigned[max_index_];
  y_ = new unsigned[max_index_];
  sheet = new Image*[max_index_];
  base_picture_ = new Image(*(other.base_picture_));
  curr_index_ = other.curr_index_;
  for(unsigned i = 0; i < max_index_; i++) {
    if(other.sheet[i] != NULL) {
      x_[i] = other.x_[i];
      y_[i] = other.y_[i];
      sheet[i] = new Image(*other.sheet[i]);
    }
    else {
      x_[i] = 0;
      y_[i] = 0;
      sheet[i] = NULL;
    }
  }
 }

void StickerSheet::destroy_() {
  for(unsigned i = 0; i < max_index_; i++) {
    delete sheet[i];
    sheet[i] = NULL;
  }
  delete base_picture_;
  delete[] x_;
  delete[] y_;
  delete[] sheet;
  x_ = NULL;
  y_ = NULL;
  sheet = NULL;
}
