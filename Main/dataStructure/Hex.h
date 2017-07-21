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

    double getX() const;

    double getY() const;

    unsigned int getCol() const;

    unsigned int getRow() const;

    unsigned long int count() const;

    double getRadius() const;

////////////////////////////////////////////////////////////////////////////////
//Iterstuff - non-const - of one type near
    template<class C>
    byTypeIterNear<C> getAllOfTypeNear(const unsigned int col, const unsigned int row, const unsigned int distance, std::vector<std::vector<Hex*>>* hexes)
    {
        unsigned int hexDistance = floor(distance/hexRadius);
        if (nearBy.count(hexDistance) == 1)
            return byTypeIterNear<C>((*(*nearBy[hexDistance].begin()))[typeid(C).hash_code()].begin(), nearBy[hexDistance].begin(), &nearBy[hexDistance]);
        else
            nearBy[hexDistance] = buildNear(col, row, hexDistance, hexes);
        return byTypeIterNear<C>((*(*nearBy[hexDistance].begin()))[typeid(C).hash_code()].begin(), nearBy[hexDistance].begin(), &nearBy[hexDistance]);
    }

//Iterstuff - non-const - everything near
    //This returns an interatable object over a non-constant object
    globalIterNear getAllNear(const unsigned int col, const unsigned int row, const unsigned int distance, std::vector<std::vector<Hex*>>* hexes)
    {
        unsigned int hexDistance = floor(distance/hexRadius);
        if (nearBy.count(hexDistance) == 1)
            return globalIterNear((*nearBy[hexDistance].begin())->begin()->second.begin(), (*nearBy[hexDistance].begin())->begin(), nearBy[hexDistance].begin(), &nearBy[hexDistance]);
        else
            nearBy[hexDistance] = buildNear(col, row, hexDistance, hexes);
        return globalIterNear((*nearBy[hexDistance].begin())->begin()->second.begin(), (*nearBy[hexDistance].begin())->begin(), nearBy[hexDistance].begin(), &nearBy[hexDistance]);
    }
////////////////////////////////////////////////////////////////////////////////

private:
    std::vector< std::map< const std::size_t, std::map<Entity* const, Enticap*>>* > buildNear(const unsigned int col, const unsigned int row, const unsigned int distance, std::vector<std::vector<Hex*>>* hexes) const;

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
