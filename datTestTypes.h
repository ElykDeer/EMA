#ifndef TESTTYPES
#define TESTTYPES 1
#include "Entity.h"

class Flower : public Entity
{
public:
    using Entity::Entity;
};

class Dog : public Entity
{
public:
    using Entity::Entity;
    void bark() const;
};

#endif
