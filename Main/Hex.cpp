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

//Update enviornment stuff only, do not update entities inside
void Hex::update() {}

void Hex::insert(Entity* const entity, Enticap* enticap)
{
    //Insert into our map structure:
      //<typeid.HashCode: <pointerToEntity:pointerToEnticap> >
    byTypeMap[typeid(*entity).hash_code()][entity] = enticap;
}

void Hex::remove(Entity* const entity)
{
    byTypeMap[typeid(*entity).hash_code()].erase(entity);
}

unsigned int Hex::getX() const
{
    return x;
}

unsigned int Hex::getY() const
{
    return y;
}

unsigned int Hex::getCol() const
{
    return col;
}

unsigned int Hex::getRow() const
{
    return row;
}
