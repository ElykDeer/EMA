#ifndef SIM_HEX
#define SIM_HEX 1

#include "../Entity.h"
#include <map>
#include <cmath> //Because hexagons

class Hex;

class HexInternals
{
public:
    //Give it the matrix coordinates, and it will generate pixel coordinates
    HexInternals(const unsigned int col, const unsigned int row, const double hexRadius);

    //Fake destructor because inheritance
    virtual ~HexInternals();

    virtual void update(unsigned int resolution) = 0;

    void insert(Entity* const entity, Enticap* enticap);
    void remove(Entity* const entity);

    //Map Positoin Getters
    double getX() const;
    double getY() const;

    //Storage Position Getters
    unsigned int getCol() const;
    unsigned int getRow() const;

    //Radius Getter
    double getRadius() const;

    //Returns the count of how many entities are in this hex
    unsigned long int count() const;

    #include "HexIters.tpp"

private:
    //This function creates a list of all entities within a certian pix distance
    std::vector< std::map< const std::size_t, std::map<Entity* const, Enticap*>>* >
      buildNear(const unsigned int col, const unsigned int row,
      const unsigned int distance, std::vector<std::vector<Hex*>>* hexes) const;

    // X/Y Locations
    const double x;
    const double y;
    const double hexRadius;
    const double hexRadiusSmall;

    //Where in the grid that it is located
    const unsigned int col;
    const unsigned int row;

    unsigned int entityCount = 0;

    //Setup: <typeid.HashCode: <pointerToEntity:pointerToEnticap> >
    std::map< const std::size_t, std::map<Entity* const, Enticap*> > byTypeMap;

    //Keep track of who's near me
    //Setup: <hex distance, vector<pointers to my neighbors' byTypeMaps>>
    std::map<const unsigned int, std::vector<
     std::map< const std::size_t, std::map<Entity* const, Enticap*>>* >> nearBy;
};

#include "../../Plugins/Enviornment/Hex.h"

#endif
