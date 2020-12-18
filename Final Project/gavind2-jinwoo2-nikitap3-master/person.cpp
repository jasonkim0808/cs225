#include "person.h"

#include <string>
#include <iostream>
#include <math.h>

using namespace std;

/**
 * person class constructor
 */
person::person() {
  currentRate = 0.001;
  ageRate = 0;
}

/**
 * person class constructor
 * int nodeN: # of nodes in starting airport
 * int age: age of user
 */
person::person(int nodeN, int age) {
  ageRate = age/1000;
  currentRate = exp((-1)*1/nodeN) + ageRate;
}

/**
 * method for adding rate per destination
 * int nodeN: # of nodes in new destination
 */
void person::rate(int nodeN) {
  currentRate = currentRate*(1.0+exp((-1)*1/nodeN)) + ageRate;
  if(currentRate >= 1.0)
    currentRate = 1.0;
}

/**
 * getter function for rate
 * returns rate
 */
double person::getRate() {
  return currentRate;
}

/**
* Sets the age of the person
* @param age - age of the person
*/
void person::setAge(float age) {
  ageRate = age/1000;
}
