#include <iostream>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <cmath>
#include <string>

using namespace cs225;

void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2

  PNG* original = new PNG();

  original -> readFromFile(inputFile);
  unsigned width = original -> width();
  unsigned height = original -> height();

  PNG* output = new PNG(width, height);

  for (unsigned x = 0; x < (original->width()); x++) {
    for (unsigned y = 0; y < (original->height()); y++) {
      HSLAPixel & pixel = original -> getPixel(x, y);
      HSLAPixel & result = output -> getPixel(output->width()-x-1, output->height()-y-1); 
      result = pixel;
    }
  }
  output -> writeToFile(outputFile);
}

PNG myArt(unsigned int width, unsigned int height) {
  PNG png(width, height);
  // TODO: Part 3
  for (unsigned x = 0; x < width; x++) {
    for (unsigned y = 0; y < height; y++) {
      if (x*y < 360) {
	HSLAPixel p(x*y, 1, 0.5);
	HSLAPixel &pixel = png.getPixel(x,y);
	pixel = p;
      }
    }
  }
  
  return png;
}

