#include "Hex.h"
using namespace std;

//Give it the matrix coordinates, and it will generate pixel coordinates
Bin::HexInternals::HexInternals(const unsigned int col, const unsigned int row, const double hexRadius) :
  x(hexRadius * 1.5 * col),
  y(hexRadius * sqrt(3.0) * (row - (0.5*(col&1))) ),
  hexRadius(hexRadius),
  hexRadiusSmall((sqrt(3)*hexRadius)/2),
  col(col),
  row(row) {}

Bin::HexInternals::~HexInternals() {}

void Bin::HexInternals::insert(Entity* const entity, Enticap* enticap)
{
    //Insert into our map structure:
      //<typeid.HashCode: <pointerToEntity:pointerToEnticap> >
    byTypeMap[typeid(*entity).hash_code()][entity] = enticap;

    ++entityCount;
}

void Bin::HexInternals::remove(Entity* const entity)
{
    byTypeMap[typeid(*entity).hash_code()].erase(entity);
    --entityCount;
}

double Bin::HexInternals::getX() const
{
    return x;
}

double Bin::HexInternals::getY() const
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

unsigned long int Bin::HexInternals::count() const
{
    return entityCount;
}

double Bin::HexInternals::getRadius() const
{
    return hexRadius;
}

//std::vector< std::map< const std::size_t, std::map<Entity* const, Enticap*>>* > buildNear(const unsigned int distance)
//vector<map< const size_t, map<Entity* const, Enticap*>>* > Bin::HexInternals::buildNear(const unsigned int col, const unsigned int row, const unsigned int distance, vector<vector<Hex*>>* hexes) const

#include "../../Plugins/Enviornment/Hex.cpp"
