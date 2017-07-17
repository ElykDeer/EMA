#ifndef SIM_ENTITY
#define SIM_ENTITY 1

class Entity
{
    friend class Bin;
public:
    //Simple Constructor
    Entity(const unsigned int x, const unsigned int y);

    virtual void update(unsigned int resolution) = 0;

    //Deconstructor for derived classes
    virtual ~Entity();

    unsigned int getX() const;

    unsigned int getY() const;

protected:
    // X/Y Locations
    unsigned int x;
    unsigned int y;
};

#endif
