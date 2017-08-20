#include "pausedFloatersTypes.h"
using namespace std;

Floater::Floater(const double x, const double y, Bin* const bin)
: Entity::Entity(x, y, bin), moveX((bin->chanceGen(bin->gen)*3)-1.5),
moveY((bin->chanceGen(bin->gen)*3)-1.5) {}

void Floater::update(unsigned int resolution)
{
  if (resolution)
  {
    double newX;
    double newY;

    if ( moveX+getX() < 0 )
      newX = getX() + (moveX + double(bin->getWidth()));
    else
      newX = getX() + moveX;

    if ( moveY+getY() < 0 )
      newY = getY() + (moveY + double(bin->getWidth()));
    else
      newY = getY() + moveY;

    bin->move(this, newX, newY);
  }
}
