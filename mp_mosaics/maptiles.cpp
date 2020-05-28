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

    vector<Point<3>> points;
    Point<3> tempCoord;
    map<Point<3>, TileImage*> tileMapper;
    unsigned long count = 0;
    int row = 0;
    int col = 0;
    int numRows = theSource.getRows();
    int numCols = theSource.getColumns();
    size_t tileSize = theTiles.size();

    if(theTiles.empty() == true || numRows == 0 || numCols == 0) {
      return NULL;
    }
    else {
      MosaicCanvas* newCanvas = new MosaicCanvas(numRows, numCols);
      for(const TileImage& t : theTiles) {
        tempCoord = convertToXYZ(t.getAverageColor());
        points.push_back(tempCoord);
      }
      KDTree<3> tree(points);

      while(count < tileSize) {
        tileMapper[points[count]] = & theTiles[count];
        count++;
      }

      while(row < numRows) {
        while(col < numCols) {
          Point<3> coordinate = convertToXYZ(theSource.getRegionColor(row, col));
          newCanvas->setTile(row, col, tileMapper[tree.findNearestNeighbor(coordinate)]);
          col++;
        }
        col = 0;
        row++;
      }
      return newCanvas;
    }
}
