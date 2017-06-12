#ifndef SIM_ENTITY
#define SIM_ENTITY 1

class Entity
{
public:
    //Simple Constructor
    Entity(const int x, const int y);

    virtual void update() = 0;

    //Deconstructor for derived classes
    virtual ~Entity();

    int getX();

    int getY();

protected:
    // X/Y Locations
    int x;
    int y;
};

#endif
