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
  iT = NULL;
  psv.resize(p.width(), std::vector<bool>(p.height()));
  for(unsigned i = 0; i < p.width(); i++) {
    for(unsigned j = 0; j < p.height(); j++) {
      psv[i][j] = false;
    }
  }
}

ImageTraversal::Iterator::Iterator(PNG png, Point start, double tolerance, ImageTraversal * IT) {

  /** @todo [Part 1] */
  p = png;
  s = start;
  pos = start;
  t = tolerance;
  iT = IT;
  
  if (iT->empty())
    iT->pop();

  int pw = p.width();
  int ph = p.height();

  psv.resize(p.width(), std::vector<bool>(ph));
  for(unsigned int i = 0; i < p.width(); i++) {
    for(unsigned int j = 0; j < p.height(); j++) {
      psv[i][j] = false;
    }
  }
 
  if(check(pos))
    psv[pos.x][pos.y] = true;
}

bool ImageTraversal::Iterator::check(Point point) {
  if(point.x >= p.width() || point.y >= p.height())
    return false;
  if(point.y<p.height() && point.x<p.width()){
    HSLAPixel & pStart = p.getPixel(s.x,s.y);
    HSLAPixel & pPos = p.getPixel(point.x,point.y);
    if(calculateDelta(pStart, pPos) < t) {
      if (psv[point.x][point.y]==false)
        return true;
    }
  }
  return false;
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  psv[pos.x][pos.y] = true;

  Point up = Point(pos.x, pos.y-1);
  Point down = Point(pos.x, pos.y+1);
  Point right = Point(pos.x+1, pos.y);
  Point left = Point(pos.x-1, pos.y);

  if(check(right))
    iT->add(right);
  if(check(down))
    iT->add(down);
  if(check(left))
    iT->add(left);
  if(check(up))
    iT->add(up);

  while(!(iT->empty()) && !(check(iT->peek()))) {
    iT->pop();
    if(iT->empty())
      return *this;
  }
  if(!(iT->empty())) {
    pos = iT->peek();
    return *this;
  } else {
    iT = NULL;
    return *this;
  }
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return pos;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  bool temp1 = false;
  bool temp2 = false;

  if (this->iT == NULL)
    temp1 = true;
  if (other.iT == NULL)
    temp2 = true;
  if(!temp1)
    temp1 = iT->empty();
  if(!temp2)
    temp2 = other.iT->empty();
  if(!temp1 && !temp2)
    return iT != other.iT;
  else if(temp1 && temp2)
    return false;
  else
    return true;
}

