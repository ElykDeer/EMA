#ifndef TESTTYPES
#define TESTTYPES 1
#include "Entity.h"

//Just two basic derived types to serve testing purposes
class Flower : public Entity
{
public:
    using Entity::Entity;

    //The following three things are for const testing
    void otherThingy()
    {
      thingy2 = 11;
    }
    int thingy = 0;
    int thingy2 = 10;
};

class Dog : public Entity
{
public:
    using Entity::Entity;
    void bark() const;
};

#endif
