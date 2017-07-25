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

  double gexChance = ((germinationMaxAge-germinationMinAge)-(germinationMaxAge-age)) / (germinationMaxAge-germinationMinAge);

  if (size <= maxSize)
    if ((age <= germinationMaxAge) && (age >= germinationMinAge))
      if (chance < pow(((-0.1*gexChance) / (gexChance - 1.0)), 4.0))
        size += 0.1;
  }

double Flower::getSize() const
{
  return size;
}

void Bunny::update(unsigned int resolution)
{
  age += resolution;
}
