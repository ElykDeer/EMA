#include "datTestTypes.h"
#include <random>
#include <cmath>
using namespace std;

Flower::Flower(unsigned int x, unsigned int y, Bin* const bin)
  : Entity::Entity(x, y, bin)
{
  //Random number stuff
  random_device seed;
  mt19937 gen(seed());
  uniform_real_distribution<double> chanceGen (0.0, 1.0);
  chance = chanceGen(gen);
}

void Flower::update(unsigned int resolution)
{
  age += resolution;

  auto gexChance = [=](int age)->double { return double(age-germinationMinAge) / double(germinationMaxAge-germinationMinAge);};
  auto distribution = [=](int age)->double { return pow( 2.0*(-0.1*gexChance(age) / (gexChance(age) - 1.0)), 3.0 ); };

  //If I can grow
  if (size <= maxSize)
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
    }
  }
  else
    size = maxSize; //safty net, incase the above has a bug

  //Out-competed calculation


  //death timer:
  if (age > maxAge)
  {
    //One flower generates two on death
    random_device seed;
    mt19937 gen(seed());
    uniform_real_distribution<double> randChange (0.0, gatherRadius );
    bin->insert(new Flower(getX()+randChange(gen), getY()+randChange(gen), bin));
    bin->insert(new Flower(getX()+randChange(gen), getY()+randChange(gen), bin));

    //Actually mark for death
    bin->markForRemoval(this);
  }
}

double Flower::getSize() const
{
  return size;
}

void Bunny::update(unsigned int resolution)
{
  age += resolution;
}
