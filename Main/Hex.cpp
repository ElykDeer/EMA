#include "Hex.h"
#include <cmath>  //Because hexagons
using namespace std;

//Give it the matrix coordinates, and it will generate pixel coordinates
Hex::Hex(const unsigned int x, const unsigned int y, const double hexRadius) :
  x(hexRadius * 1.5 * x),
  y(hexRadius * sqrt(3) * (y - (0.5*(x&1))) ),
  hexRadius(hexRadius),
  col(x),
  row(y) {}

int Hex::getX()
{
    return x;
}

int Hex::getY()
{
    return y;
}

int Hex::getCol()
{
    return col;
}

int Hex::getRow()
{
    return row;
}
