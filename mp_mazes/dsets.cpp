/* Your code here! */
#include "dsets.h"
#include <iostream>
using namespace std;

void DisjointSets::addelements(int num) {
  for (int i = 0; i < num; i++)
    _elem.push_back(-1);
}

int DisjointSets::find(int elem) {
  if(_elem[elem] < 0)
    return elem;
  _elem[elem] = find(_elem[elem]);
  return find(_elem[elem]);
}

void DisjointSets::setunion(int a, int b) {
  int first = find(a);
  int second = find(b);

  if(first != second) {
    if(_elem[first]>_elem[second])
    {
      _elem[second] += _elem[first];
      _elem[first] = second;
    } else {
      _elem[first] += _elem[second];
      _elem[second] = first;
    }
  }
}

int DisjointSets::size(int elem) {
  return -_elem[find(elem)];
}

