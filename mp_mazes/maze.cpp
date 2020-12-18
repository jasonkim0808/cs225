/* Your code here! */

#include "maze.h"
#include <iostream>
using namespace cs225;
SquareMaze::SquareMaze() {
  w = 0;
  h = 0;
}

void SquareMaze::makeMaze(int width, int height) {

  this->w = width;
  this->h = height;
  maxN = w*h;
  box.resize(maxN,3);
  dj.addelements(maxN);
  
  while(dj.size(0) != maxN) {
    int r = rand()%2;
    int xy = rand()%maxN;
    if(r == 0) {
      if((xy+1)%w != 0 && dj.find(xy) !=dj.find(xy+1)) {
	setWall(xy%w, xy/w, 0, false);
	dj.setunion(xy, xy+1);
      }
    } else {
      if(xy+w < maxN && dj.find(xy) != dj.find(xy+w)) {
	setWall(xy%w, xy/w, 1, false);
        dj.setunion(xy, xy+w);
      }
    }
  }
}

bool SquareMaze::canTravel(int x, int y, int dir) const {
  if(dir == 0 && x < w - 1 && box.at(y*w+x) != 1 && box.at(y*w+x) != 3) 
    return true;
  else if(dir == 1 && y < h - 1 && box.at(y*w+x) != 2 && box.at(y*w+x) != 3)
    return true;
  else if(dir == 2 && x != 0 && box.at(y*w+(x-1)) != 1 && box.at(y*w+(x-1)) != 3)
    return true;
  else if(dir == 3 && y != 0 && box.at((y-1)*w+x) != 2 && box.at((y-1)*w+x) != 3)
    return true;    
  else
    return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {

  if(dir == 0) {
    if(exists) {
      if(box.at(y*w+x) == 0)
	box.at(y*w+x) = 1;
      else if(box.at(y*w+x) == 2)
	box.at(y*w+x) = 3;
    } else {
      if(box.at(y*w+x) == 1)
        box.at(y*w+x) = 0;
      else if(box.at(y*w+x) == 3)
        box.at(y*w+x) = 2;
    }
  } else if(dir == 1) {
    if(exists) {
      if(box.at(y*w+x) == 0)
        box.at(y*w+x) = 2;
      else if(box.at(y*w+x) == 2)
        box.at(y*w+x) = 3;
    } else {
      if(box.at(y*w+x) == 1)
        box.at(y*w+x) = 0;
      else if(box.at(y*w+x) == 3)
        box.at(y*w+x) = 1;
    }

  }
    
}


vector<int> SquareMaze::solveMaze() {
  
  std::queue<int> q;
  q.push(0);

  vector<int> temp1(maxN, -1);
  vector<int> temp2(maxN, -1);
  vector<int> temp3(maxN, -1);

  while(!q.empty()) {
    int temp = q.front();
    int x = temp % w;
    int y = temp / w;

    if(canTravel(x, y, 0) && temp1[temp + 1] < 0) {
      q.push(temp+1);
      temp1[temp+1] = temp1[temp] +1;
      temp2[temp+1] = 0;
      temp3[temp+1] = temp;
    } else if(canTravel(x, y, 1) && temp1[temp + w] < 0) {
      q.push(temp+w);
      temp1[temp+w] = temp1[temp] +1;
      temp2[temp+w] = 1;
      temp3[temp+w] = temp;
    } else if(canTravel(x, y, 2) && temp1[temp - 1] < 0) {
      q.push(temp-1);
      temp1[temp-1] = temp1[temp] +1;
      temp2[temp-1] = 2;
      temp3[temp-1] = temp;
    } else if(canTravel(x, y, 3) && temp1[temp - w] < 0) {
      q.push(temp-w);
      temp1[temp-w] = temp1[temp] +1;
      temp2[temp-w] = 3;
      temp3[temp-w] = temp;
    }

  q.pop();
  }

  int maxI = 0;
  int maxL = 0;
  for(int i = (h-1)*w; i<maxN; i++) {
    if(temp1[i] > maxL) {
      maxI = i;
      maxL = temp1[i];
    }
  }

  vector<int> result;
  while(maxI>0){
    result.push_back(temp2[maxI]);
    maxI = temp3[maxI];
  }

  reverse(result.begin(), result.end());
  return result;
}

PNG* SquareMaze::drawMaze() const {
  PNG* maze = new PNG(w*10 + 1, h*10 + 1);
  maze->getPixel(0,0) = HSLAPixel(0,0,0);
  for(int i = 10; i < w*10 + 1; i++) {
    maze->getPixel(i,0) = HSLAPixel(0,0,0);
  }
  for( int i = 0; i < h*10 + 1; i++) {
    maze->getPixel(0,i) = HSLAPixel(0,0,0);
  }

  for(int i = 0; i<w; i++) {
    for(int j = 0; j<h; j++) {
      if(box.at(j*w+i) == 1 || box.at(j*w+i) == 3) {
	for(int k = 0; k <= 10; k++) {
	  HSLAPixel & pixel = maze->getPixel((i+1)*10, j*10+k);
	  pixel.l = 0;
	}
      }
      if(box.at(j*w+i) == 2 || box.at(j*w+i) == 3) {
        for(unsigned k = 0; k <= 10; k++) {
          HSLAPixel & pixel = maze->getPixel(i*10+k, (j+1)*10);
          pixel.l = 0;
        }
      }
    }
  }
  return maze;


    
}
PNG* SquareMaze::drawMazeWithSolution() {
  PNG* maze = drawMaze();
  vector<int> answer = solveMaze();
  
  int x_val = 5;
  int y_val = 5;

  for(size_t i = 0; i < answer.size(); i++) {
    for(unsigned j = 0; j < 10; j++) {
      maze->getPixel(x_val, y_val) = HSLAPixel(0,1,0.5,1);
      if(answer[i] == 0)
	x_val++;
      if(answer[i] == 1)
        y_val++;
      if(answer[i] == 2)
        x_val--;
      if(answer[i] == 3)
        y_val--;
    } 
  }
  return maze;
}

