#ifndef SIM_BINS
#define SIM_BINS 1

#include "Entity.h"

//All Active Plugins need to be registered in this file
#include "../Compiler/pluginTypes.h"

#include <map>
#include <set>
#include <functional>
#include <vector>
#include <cmath> //because hexagons

//Ability to:
    //insert
    //remove
    //get near
    //iterate over each specific type
class Bin// : public byType, public byLocal
{
public:
    //This data structure needs to know the level size in the game
    //Width, height, hexRadius
    Bin(const unsigned int, const unsigned int, const double);

    //How else do we put things in this monstrosity?
    void insert(Entity* const entity);

    //Delete an object
    void remove(Entity* const entity);

    //How to move an object in the dataStructure
    void move(Entity* entity, unsigned int newX, unsigned int newY);

    //Update All Entities In The Structure
    void updateEntities();

    //Update All Hexes In The Data Structure
    void updateHexes();

    ~Bin();
private:
    class Hex;

    #include "dataStructure/Enticap.h"

    //For the bins:
    const unsigned int width;
    const unsigned int height;
    const double hexRadius;
    std::vector<std::vector<Hex*>> hexes;

    //Setup: <typeid.HashCode: <pointerToEntity:pointerToEnticap> >
    std::map< const std::size_t, std::map<Entity* const, Enticap*> > byTypeMap;

    #include "dataStructure/pixToHex.h"
    pixToHex hexCords;

public:
    #include "dataStructure/Iters.tpp"

private:
    #include "dataStructure/Hex.h"

public:
////////////////////////////////////////////////////////////////////////////////
    ///Iterstuff - non-const - byType - distance
    template<class C>
    byTypeIterNear<C> getAllOfTypeNear(Entity* entity, const unsigned int distance)
    {
        Hex* hexP = byTypeMap[typeid(C).hash_code()][entity]->getHexP();
        return hexP->getAllOfTypeNear<C>(hexP->getCol(), hexP->getRow(), distance, &hexes);
    }

////////////////////////////////////////////////////////////////////////////////
    //Iterstuff - non-const - everything - distance
    globalIterNear getAllNear(Entity* entity, const unsigned int distance)
    {
        Hex* hexP = byTypeMap[typeid(*entity).hash_code()][entity]->getHexP();
        return hexP->getAllNear(hexP->getCol(), hexP->getRow(), distance, &hexes);
    }
};

#endif
