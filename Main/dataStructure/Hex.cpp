#include "Hex.h"
#include <cmath>  //Because hexagons
using namespace std;

//Give it the matrix coordinates, and it will generate pixel coordinates
Bin::Hex::Hex(const unsigned int x, const unsigned int y, const double hexRadius) :
  x(hexRadius * 1.5 * x),
  y(hexRadius * sqrt(3) * (y - (0.5*(x&1))) ),
  hexRadius(hexRadius),
  col(x),
  row(y) {}

//Update enviornment stuff only, do not update entities inside
void Bin::Hex::update() {}

void Bin::Hex::insert(Entity* const entity, Enticap* enticap)
{
    //Insert into our map structure:
      //<typeid.HashCode: <pointerToEntity:pointerToEnticap> >
    byTypeMap[typeid(*entity).hash_code()][entity] = enticap;
}

void Bin::Hex::remove(Entity* const entity)
{
    byTypeMap[typeid(*entity).hash_code()].erase(entity);
}

unsigned int Bin::Hex::getX() const
{
    return x;
}

unsigned int Bin::Hex::getY() const
{
    return y;
}

unsigned int Bin::Hex::getCol() const
{
    return col;
}

unsigned int Bin::Hex::getRow() const
{
    return row;
}
