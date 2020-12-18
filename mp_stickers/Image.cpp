 /**
 * @file Image.cpp
 * Contains your interface for the Image class.
 */

#include <iostream>
#include <cmath>
#include <cstdlib>

#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

using cs225::HSLAPixel;
using cs225::PNG;
using namespace std;

void Image::lighten() {  
  unsigned int w = width();
  unsigned int h = height();

  for (unsigned int iw = 0; iw < w; iw++) {
    for (unsigned int ih = 0; ih < h; ih++) {
      HSLAPixel & p = getPixel(iw,ih);
      p.l += 0.1;
      if (p.l < 0)
	p.l = 0;
      else if (p.l > 1)
	p.l = 1;
    }
  }
}

void Image::lighten(double amount) { 
  unsigned int w = width();
  unsigned int h = height();

  for (unsigned int iw = 0; iw < w; iw++) {
    for (unsigned int ih = 0; ih < h; ih++) {
      HSLAPixel & p = getPixel(iw,ih);
      p.l += amount;
      if (p.l < 0)
        p.l = 0;
      else if (p.l > 1)
        p.l = 1;
    }
  }
}

void Image::darken() {

  unsigned int w = width();
  unsigned int h = height();

  for (unsigned int iw = 0; iw < w; iw++) {
    for (unsigned int ih = 0; ih < h; ih++) {
      HSLAPixel & p = getPixel(iw,ih);
      p.l -= 0.1;
      if (p.l < 0)
        p.l = 0;
      else if (p.l > 1)
        p.l = 1;
    }
  }
}

void Image::darken(double amount) {
  unsigned int w = width();
  unsigned int h = height();

  for (unsigned int iw = 0; iw < w; iw++) {
    for (unsigned int ih = 0; ih < h; ih++) {
      HSLAPixel & p = getPixel(iw,ih);
      p.l -= amount;
      if (p.l < 0)
        p.l = 0;
      else if (p.l > 1)
        p.l = 1;
    }
  }
}

void Image::saturate() {

  unsigned int w = width();
  unsigned int h = height();

  for (unsigned int iw = 0; iw < w; iw++) {
    for (unsigned int ih = 0; ih < h; ih++) {
      HSLAPixel & p = getPixel(iw,ih);
      p.s += 0.1;
      if (p.s < 0)
        p.s = 0;
      else if (p.s > 1)
        p.s = 1;
    }
  }
}

void Image::saturate(double amount) {
  unsigned int w = width();
  unsigned int h = height();

  for (unsigned int iw = 0; iw < w; iw++) {
    for (unsigned int ih = 0; ih < h; ih++) {
      HSLAPixel & p = getPixel(iw,ih);
      p.s += amount;
      if (p.s < 0)
        p.s = 0;
      else if (p.s > 1)
        p.s = 1;
    }
  }
}

void Image::desaturate() {
  unsigned int w = width();
  unsigned int h = height();

  for (unsigned int iw = 0; iw < w; iw++) {
    for (unsigned int ih = 0; ih < h; ih++) {
      HSLAPixel & p = getPixel(iw,ih);
      p.s -= 0.1;
      if (p.s < 0)
        p.s = 0;
      else if (p.s > 1)
        p.s = 1;
    }
  }
}

void Image::desaturate(double amount) {
  unsigned int w = width();
  unsigned int h = height();

  for (unsigned int iw = 0; iw < w; iw++) {
    for (unsigned int ih = 0; ih < h; ih++) {
      HSLAPixel & p = getPixel(iw,ih);
      p.s -= amount;
      if (p.s < 0)
        p.s = 0;
      else if (p.s > 1)
        p.s = 1;
    }
  }
}

void Image::grayscale() {
  unsigned int w = width();
  unsigned int h = height();

  for (unsigned int iw = 0; iw < w; iw++) {
    for (unsigned int ih = 0; ih < h; ih++) {
      HSLAPixel & p = getPixel(iw,ih);
      p.s = 0;
    }
  }
}

void Image::rotateColor(double degrees) {
  unsigned int w = width();
  unsigned int h = height();

  for (unsigned int iw = 0; iw < w; iw++) {
    for (unsigned int ih = 0; ih < h; ih++) {
      HSLAPixel & p = getPixel(iw,ih);
      p.h += degrees;
      if (p.h > 360) {
	p.h -=360;
      } else if (p.h < 0) {
	p.h += 360;
      }
    }
  }
}



void Image::illinify() {
  unsigned int w = width();
  unsigned int h = height();
  for (unsigned x = 0; x < w; x++) {
    for (unsigned y = 0; y < h; y++) {
      HSLAPixel & p = getPixel(x,y);
      if (114 <= p.h && 293 >= p.h){
        p.h = 216;
      } else {
        p.h = 11;
      }
    }
  }
}

void Image::scale(double factor) {
  unsigned int w = width() * factor;
  unsigned int h = height() * factor;
  
  Image *result = new Image();
  *result = *this;
  resize(w,h);

  for (unsigned x = 0; x < w; x++) {
    for (unsigned y = 0; y < h; y++) {
      HSLAPixel & p = getPixel(x,y);
      HSLAPixel & r = result->getPixel(x/factor, y/factor);
      p = r;
    }
  }
  delete result;
}

void Image::scale(unsigned wi, unsigned he) {
  unsigned int w = wi/width();
  unsigned int h = he/height();

  Image *result = new Image();
  *result = *this;
  resize(wi,he);

  for (unsigned x = 0; x < wi; x++) {
    for (unsigned y = 0; y < he; y++) {
      HSLAPixel & p = getPixel(x,y);
      HSLAPixel & r = result->getPixel(x/w, y/h);
      p = r;
    }
  }
  delete result;
}


