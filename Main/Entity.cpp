#include "Entity.h"
using namespace std;

//Simple Constructor
Entity::Entity(const double x, const double y, Bin* const bin)
  : x(x), y(y), bin(bin) { }

//Deconstructor for derived classes
Entity::~Entity() { }

double Entity::getX() const
{
    return x;
}

double Entity::getY() const
{
    return y;
}
