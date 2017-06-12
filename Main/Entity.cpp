#include "Entity.h"
using namespace std;

//Simple Constructor
Entity::Entity(const int x, const int y) : x(x), y(y) { }

//Deconstructor for derived classes
Entity::~Entity() { }

int Entity::getX()
{
    return x;
}

int Entity::getY()
{
    return y;
}
