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
  
  PNG shibal;
  shibal.readFromFile("lantern-rainbow-bfs.png");
  Animation gaesaeki;
  FloodFilledImage byungshin(shibal);
  MyColorPicker hogu;

  BFS jotbab(shibal, Point(58, 54), 0.5);
  DFS ojim(shibal, Point(58, 54), 0.5);

  byungshin.addFloodFill(jotbab, hogu);
  byungshin.addFloodFill(ojim, hogu);

  gaesaeki = byungshin.animate(69);

  PNG lastFrame = gaesaeki.getFrame( gaesaeki.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  gaesaeki.write("myFloodFill.gif");
  


  return 0;
}
