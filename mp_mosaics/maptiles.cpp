/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"


using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */

    int row = theSource.getRows();
    int column = theSource.getColumns();


    if(theTiles.size() == 0 || !row || !column)
      return NULL;

    vector<Point<3>> points(theTiles.size());
    map<Point<3>, int> m;

    for (size_t i = 0; i < theTiles.size(); i++) {
      points[i] = convertToXYZ(theTiles[i].getAverageColor());
      m[points[i]] = i;
    }

    KDTree<3> sourceTree(points);

    MosaicCanvas *temp = new MosaicCanvas(row, column);
    for(int i = 0; i < row; i++) {
      for(int j = 0; j < column; j++)
	temp->setTile(row, column, &theTiles[m[sourceTree.findNearestNeighbor(convertToXYZ(theSource.getRegionColor(row, column)))]]);
    }
    return temp;
}

