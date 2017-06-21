#include "Entity.h"
using namespace std;

//Simple Constructor
Entity::Entity(const unsigned int x, const unsigned int y) : x(x), y(y) { }

//Deconstructor for derived classes
Entity::~Entity() { }

unsigned int Entity::getX() const
{
    return x;
}

unsigned int Entity::getY() const
{
    return y;
}
