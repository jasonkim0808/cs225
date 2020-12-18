#include "safecovid.h"
#include <iostream>
int main() {
  std::cout << "Getting data....This may take a couple minutes." << std::endl;
  safeCovid s ("data/edges.txt");

  std::cout << "Welcome to SAFECOVID, a patent-pending tool for safe international travel!" << std::endl;

  std::cout << "Please enter your age." << std::endl;
  string age;
  std::cin >> age;
  float numAge = stof(age);
  s.setPerson(numAge);
  std::cout << std::endl;

  std::cout << "Please select one of the following: \n 1. Travel with a landmark. \n 2. Travel without a landmark. \n 3. End program. " << std::endl;

  std::cout << "Type the number of the operation you would like: ";
  int selection;

  string start;
  string dest;
  string maybeLandmark;
  string landmark;

  std::cin >> selection;

  while (selection != 3) {
    switch(selection) {
      case 1:
        std::cout << "Please enter the three-letter IATA code of your starting airport." << std::endl;
        std::cin >> start;
        std::cout << "Please enter the three-letter IATA code of your destination airport." << std::endl;
        std::cin >> dest;

        std::cout << "Please enter the three-letter IATA code of the landmark's airport." << std::endl;
        std::cin >> landmark;

        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "This is the quickest landmark route from " << start << " to " << dest << ":" << std::endl;
        s.printLandmarkPathBFS(start, landmark, dest);
        std::cout << std::endl;
        std::cout << "This is the safest landmark route from " << start << " to " << dest << ":" << std::endl;
        s.printLandmarkPathDijkstra(start, landmark, dest);

        std::cout << "Please select one of the following: \n 1. Travel with a landmark. \n 2. Travel without a landmark. \n 3. End program. " << std::endl;

        std::cout << "Type the number of the operation you would like: ";

        std::cin >> selection;
  	    break;
      case 2:
        std::cout << "Please enter the three-letter IATA code of your starting airport." << std::endl;
        std::cin >> start;
        std::cout << "Please enter the three-letter IATA code of your destination airport." << std::endl;
        std::cin >> dest;

        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "This is the quickest route from " << start << " to " << dest << ":" << std::endl;
        s.printPathBFS(start, dest);
        std::cout << std::endl;
        std::cout << "This is the safest route from " << start << " to " << dest << ":" << std::endl;
        s.printPathDijkstra(start, dest);

        std::cout << "Please select one of the following: \n 1. Travel with a landmark. \n 2. Travel without a landmark. \n 3. End program. " << std::endl;

        std::cout << "Type the number of the operation you would like: ";

        std::cin >> selection;
	      break;
      case 3:
        std::cout << "Thank you for using SAFECOVID." << std::endl;
        break;
      default:
        std::cout << "Please select one of the following: \n 1. Travel with a landmark. \n 2. Travel without a landmark. \n 3. End program. " << std::endl;

        std::cout << "Type the number of the operation you would like: ";

        std::cin >> selection;
  	    break;
    }
  }
  std::cout << "Thank you for using SAFECOVID." << std::endl;
}
