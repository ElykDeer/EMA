#include "datTestTypes.h"
using namespace std;

Flower::Flower(unsigned int x, unsigned int y, Bin* const bin)
  : Entity::Entity(x, y, bin)
{
  //Random number stuff
  chance = bin->chanceGen(bin->gen);
}

void Flower::update(unsigned int resolution)
{
  age += resolution;

  auto gexChance = [=](int age)->double { return double(age-germinationMinAge) / double(germinationMaxAge-germinationMinAge);};
  auto distribution = [=](int age)->double { return pow( 2.0*(-0.1*gexChance(age) / (gexChance(age) - 1.0)), 3.0 ); };

  //If I can grow
  if (size < maxSize)
  {
    //If you're jumping over the grow period due to resolution
    if ((age-resolution <= germinationMinAge) && (age >= germinationMaxAge))
      size = maxSize;

    //If my grow start time has passed
    else if (chance < distribution(age))
    {
      //If this is the first time past my grow time
      if ( !(chance < distribution(age-resolution)) )
        size += (maxSize/(60.0*60.0*12.0))*(( chance-distribution(age) ) * (germinationMaxAge-germinationMinAge)); //How much the chance was missed by in world seconds
      else //If nothing else has happened - everything is normal
        size += (maxSize/(60.0*60.0*12.0))*resolution; //Grows to full size in 12 hours

      //safety
      if (size > maxSize)
        size = maxSize;
    }
  }

/////////////////// Death Stuff ///////////////////
  //death timer:
  if (age > maxAge)
  {
    //One flower generates two on death - will change later
    bin->insert(new Flower(getX()+(bin->chanceGen(bin->gen)*gatherRadius), getY()+(bin->chanceGen(bin->gen)*gatherRadius), bin));
    bin->insert(new Flower(getX()+(bin->chanceGen(bin->gen)*gatherRadius), getY()+(bin->chanceGen(bin->gen)*gatherRadius), bin));

    //Actually mark for death
    bin->markForRemoval(this);
  }

  // //If there are more than five flowers around me, I die
  // if (bin->getNearByCountOfType<Flower>(this, 10) > 10)
  // {
  //   bin->markForRemoval(this);
  // }
}

double Flower::getSize() const
{
  return size;
}

void Bunny::update(unsigned int resolution)
{
  age += resolution;
}
