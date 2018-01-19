#ifndef PAUSED_FLOATER_TYPE
#define PAUSED_FLOATER_TYPE 1
#include "../../Main/Entity.h"
#include "../../Main/dataStructure.h"
#include <cmath>

class Floater : public Entity
{
public:
    Floater(const double x, const double y, Bin* const bin);
    void update(unsigned int resolution) override;

private:
    const double moveX;
    const double moveY;
};

#endif
