#include <iostream>
#include <string>
using namespace std;

class person
{
  private:
    double currentRate;
    double ageRate;

  public:
    /**
     * person class constructor
     */
    person();

    /**
     * person class constructor
     * int nodeN: # of nodes in starting airport
     * int age: age of user
     */
    person(int nodeN, int age);

    /**
     * Sets the age of the person
     * @param age - age of the person
     */
    void setAge(float age);

    /**
     * method for adding rate per destination
     * int nodeN: # of nodes in new destination
     */
    void rate(int nodeN);

    /**
     * getter function for rate
     * returns rate
     */
    double getRate();
};
