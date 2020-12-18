
#include <iostream>
#include <cmath>
#include <cstdlib>

#include "StickerSheet.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

using namespace std;
using cs225::PNG;
using cs225::HSLAPixel;

void StickerSheet::helpCopy(const StickerSheet &other) {
    max = other.max;
    count = other.count;
    
    x = new int[max];
    y = new int[max];
    idx = other.idx;

    st = new Image*[max];
    pic = new Image(*(other.pic));

    for (unsigned i = 0; i < max; i++) {
	st[i] = new Image(*other.st[i]);
	x[i] = other.x[i];
	y[i] = other.y[i];
	
    }	
}

void StickerSheet::helpDelete() {

    delete[] st;
    delete[] x;
    delete[] y;
    delete[] idx;
    delete pic;

    st = NULL;
    x = NULL;
    y = NULL;
    idx = NULL;
    pic = NULL;

}

StickerSheet::StickerSheet(const Image &picture, unsigned Max) {
    pic = new Image();
    *pic = picture;
    max = Max;
    count = 0;

    st = new Image*[max];
    x = new int[max];
    y = new int[max];
    idx = new int[max];
    
    for (unsigned i = 0; i < max; i++) {
        st[i] = new Image();
        x[i] = 0;
        y[i] = 0;
	idx[i] = 0;
    }
}

StickerSheet::~StickerSheet() {
    helpDelete();   
}

StickerSheet::StickerSheet(const StickerSheet &other) {
    helpCopy(other);
}

const StickerSheet& StickerSheet::operator=(const StickerSheet &other) {
    if (this == &other)
	return *this;
 
    helpDelete();
    helpCopy(other);
    return *this;
    
}

void StickerSheet::changeMaxStickers(unsigned Max) {
    if(max == Max)
	return;
    else if(max > Max) {
	for(unsigned i = Max; i < max; i++) {
	    if(idx[i] != 0) {
		delete st[i];
		st[i] = NULL;
		idx[i]--;
	    }
	}
	max = Max;
    }

    Image* *tempSt = new Image*[Max];
    int* nx = new int[Max];
    int* ny = new int[Max];
    int* nc = new int[Max];
    
    unsigned countS = 0;
    Image* tempPic = new Image(*pic);
    if(Max>max) {
        for(unsigned i = 0; i<Max; i++) {
	    tempSt[i] = NULL;
	    nc[i] = 0;
        }
    }

    for(unsigned i = 0; i<max; i++) {
	if(idx == 0)
	    nc[i] = 0;
	else {
	    tempSt[i] = new Image(*st[i]);
	    nx[i] = x[i];
	    ny[i] = y[i];
	    nc[i] = idx[i];
	    countS++;
	}
    }

    max = Max;
    st = tempSt;
    x = nx;
    y = ny;
    idx = nc;

    count = countS;
    pic = tempPic;
    
}

int StickerSheet::addSticker(Image &sticker, unsigned nx, unsigned ny) {

    if (count < max) {
	for(unsigned i = 0; i<max; i++) {
	    if(idx[i] ==0) {
		st[i] = new Image(sticker);
		x[i] = nx;
		y[i] = ny;
	    
		count++;
		idx[i]++;
		return i;
	    }
	}
    }
    return -1;
}

bool StickerSheet::translate(unsigned index, unsigned nx, unsigned ny) {
    if (index < max && idx[index] != 0) {
	x[index] = nx;
	y[index] = ny;
	return true;
    }
    return false;
}

void StickerSheet::removeSticker(unsigned index) {
    if (index < max && idx[index] != 0) {
	delete st[index];
	st[index] = NULL;
	x[index] = 0;
	y[index] = 0;
	idx[index]--;
	count--;
    }	
}

Image* StickerSheet::getSticker(unsigned index) {
    if (index >= max || idx[index] == 0) 
	return NULL;
    return st[index];
}

Image StickerSheet::render() const {
    unsigned xx = pic->width();
    unsigned yy = pic->height();

    for (unsigned i = 0; i < max; i++) {
	if(idx[i] != 0) {
	    if (xx < x[i] + st[i]->width())
	        xx = x[i] + st[i]->width();
            if (yy < y[i] + st[i]->height())
                yy = y[i] + st[i]->height();
        }
    }
    Image *result = new Image(*pic);
    result->resize(xx,yy);


    for (unsigned i = 0; i < max; i++) {
	if(idx[i] != 0) {
	    Image s = *st[i];
	    for (unsigned j = 0; j < st[i]->width(); j++) {
	        for (unsigned k = 0; k < st[i]->height(); k++) {
		    HSLAPixel & ogPixel = st[i]->getPixel(j, k);
		    HSLAPixel & stPixel = result->getPixel(j+x[i],k+y[i]);
	            if (ogPixel.a != 0) 
	    	        stPixel = ogPixel;
		}
	    }
	}
    }
	
    Image temp = *result;
    delete result;
    result = NULL;
    return temp;
}
