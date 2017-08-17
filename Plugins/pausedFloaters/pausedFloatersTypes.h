#ifndef PAUSED_FLOATER_TYPE
#define PAUSED_FLOATER_TYPE 1
#include "../../Main/Entity.h"
#include "../../Main/dataStructure.h"
#include <cmath>

class Floater : public Entity
{
public:
    using Entity::Entity;
    void update(unsigned int resolution) override;

private:
};

#endif
