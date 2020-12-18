#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image alma;     alma.readFromFile("tests/alma.png");
  Image i;        i.readFromFile("tests/i.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 10, 200);
  sheet.addSticker(i, 350, 0);
  sheet.addSticker(i, 600, 200);
  
  Image result = sheet.render();

  result.writeToFile("myImage.png");
  return 0;
}
