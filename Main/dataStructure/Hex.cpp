#include "Hex.h"
#include <cmath>  //Because hexagons
using namespace std;

//Give it the matrix coordinates, and it will generate pixel coordinates
Bin::HexInternals::HexInternals(const unsigned int col, const unsigned int row, const double hexRadius) :
  x(hexRadius * 1.5 * col),
  y(hexRadius * sqrt(3) * (row - (0.5*(col&1))) ),
  hexRadius(hexRadius),
  col(col),
  row(row) {}

Bin::HexInternals::~HexInternals() {}

void Bin::HexInternals::insert(Entity* const entity, Enticap* enticap)
{
    //Insert into our map structure:
      //<typeid.HashCode: <pointerToEntity:pointerToEnticap> >
    byTypeMap[typeid(*entity).hash_code()][entity] = enticap;
}

void Bin::HexInternals::remove(Entity* const entity)
{
    byTypeMap[typeid(*entity).hash_code()].erase(entity);
}

unsigned int Bin::HexInternals::getX() const
{
    return x;
}

unsigned int Bin::HexInternals::getY() const
{
    return y;
}

unsigned int Bin::HexInternals::getCol() const
{
    return col;
}

unsigned int Bin::HexInternals::getRow() const
{
    return row;
}

//Give it the matrix coordinates, and it will generate pixel coordinates
Bin::Hex::Hex(const unsigned int row, const unsigned int col, const double hexRadius)
: HexInternals(row, col, hexRadius) {}

void Bin::Hex::update() {}
