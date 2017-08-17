#include "pausedFloatersTypes.h"
using namespace std;

void Floater::update(unsigned int resolution)
{
  if (resolution)
    bin->move(this, getX()+(bin->chanceGen(bin->gen)-0.5), getY()+(bin->chanceGen(bin->gen)-0.5));
}
