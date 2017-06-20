#include "Entity.h"
using namespace std;

//Simple Constructor
Entity::Entity(const int x, const int y) : x(x), y(y) { }

//Deconstructor for derived classes
Entity::~Entity() { }

int Entity::getX() const
{
    return x;
}

int Entity::getY() const
{
    return y;
}
