#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image baseImage, corn, ramchip, computer;
  baseImage.readFromFile("illinois.png");
  computer.readFromFile("computer.png");
  ramchip.readFromFile("ramchip.png");
  corn.readFromFile("corn.png");
  StickerSheet sheet(baseImage, 4);
  sheet.addSticker(computer, 200, 300);
  sheet.addSticker(ramchip, 1200, 300);
  sheet.addSticker(corn, 1900, 300);
  Image final = sheet.render();
  final.writeToFile("myImage.png");
  return 0;
}
