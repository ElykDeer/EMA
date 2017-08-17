#include "pausedFloatersTypes.h"
using namespace std;

void Floater::update(unsigned int resolution)
{
  if (resolution)
  {
    unsigned int newX;
    unsigned int newY;

    double moveX = (bin->chanceGen(bin->gen)-0.5)*2;
    double moveY = (bin->chanceGen(bin->gen)-0.5)*2;

    if ( moveX+getX() < 0 )
      newX = getX() + (moveX + bin->getWidth());
    else
      newX = getX() + moveX;

    if ( moveY+getY() < 0 )
      newY = getY() + (moveY + bin->getWidth());
    else
      newY = getY() + moveY;

    bin->move(this, newX, newY);
  }
}
