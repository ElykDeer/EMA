#ifndef SIM_ENTITY
#define SIM_ENTITY 1

class Bin; //Forward dec for derived entities

class Entity
{
    friend class Bin;
public:
    //Simple Constructor
    Entity(const double x, const double y, Bin* const bin);

    virtual void update(unsigned int resolution) = 0;

    //Deconstructor for derived classes
    virtual ~Entity();

    double getX() const;

    double getY() const;

protected:
    // X/Y Locations
    double x;
    double y;

    Bin* const bin;
};

#endif
