#ifndef TESTTYPES
#define TESTTYPES 1
#include "../../Main/Entity.h"
#include "../../Main/dataStructure.h"
#include <cmath>

#define TICKSINADAY 60*60*24 //Ticks in one day

//Just two basic derived types to serve testing purposes
class Flower : public Entity
{

public:
  Flower(unsigned int x, unsigned int y, Bin* const bin);
  void update(unsigned int resolution) override;

  double getSize() const;

private:
  //Age, in ticks, of the flower
  unsigned long long int age = 0;

  //Growth of the flower over time
  double size = 0.0; //0 at birth
  double maxSize = 3.0; //Flowers cannot be bigger than this, ever ever

  //When it flowers and seeds
  unsigned int minSeedAge = 23;
  unsigned int maxSeedAge = 35;

  //Germinates between 10 and 20 days
  unsigned int germinationMinAge = 10*TICKSINADAY;
  unsigned int germinationMaxAge = 22*TICKSINADAY;

  //The area over which a flower gathers its nutrients
  double gatherRadius = 20.0;

  //No flower can live longer than 60 days
  unsigned long long int maxAge = 60*TICKSINADAY;
  double chanceOfRandomDeath = 0.0005; //0.05% chance of dying at any point

  double chance;

};

class Bunny : public Entity
{
public:
    using Entity::Entity;
    void update(unsigned int resolution) override;

private:
  unsigned long long int age;
};

#undef TICKSINADAY
#endif
