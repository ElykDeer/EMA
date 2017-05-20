#ifndef SIM_ENTITY
#define SIM_ENTITY 1

class Entity
{
public:
    //Simple Constructor
    Entity(const int x, const int y);

    //Deconstructor for derived classes
    virtual ~Entity();

protected:
    // X/Y Locations
    int x;
    int y;
};

#endif
