#ifndef SIM_BINS
#define SIM_BINS 1

#include "Entity.h"

//All Active Plugins need to be registered in this file
#include "../Compiler/pluginTypes.h"

#include <map>
#include <set>
#include <functional>
#include <vector>
#include <random>
#include <cmath> //because hexagons

#include <iostream>

//Ability to:
    //insert
    //remove
    //get near
    //iterate over each specific type
    //get width/height
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

    //Add to removal list
    void markForRemoval(Entity* const entity);
    //remove all entities marked for removal and clear removal list
    void removeAll();

    //How to move an object in the dataStructure
    void move(Entity* entity, unsigned int newX, unsigned int newY);

    //Update All Entities In The Structure
    void updateEntities(unsigned int resolution);

    //Update All Hexes In The Data Structure
    void updateHexes(unsigned int resolution);

    //A few simple getters
    unsigned int getWidth() const;
    unsigned int getHeight() const;
    unsigned long int count() const;

    ~Bin();

    //Random Number Stuff
    std::random_device seed;
    std::mt19937 gen;
    std::uniform_real_distribution<double> chanceGen;

    class Hex;//Now needs to be public - so the graphics can mess with it
  private:
    #include "dataStructure/Enticap.h"

    //For the bins:
    const unsigned int width;
    const unsigned int height;
    const double hexRadius;
    std::vector<std::vector<Hex*>> hexes;

    //Setup: <typeid.HashCode: <pointerToEntity:pointerToEnticap> >
    std::map< const std::size_t, std::map<Entity* const, Enticap*> > byTypeMap;
    unsigned long int entityCount = 0;

    #include "dataStructure/pixToHex.h"
    pixToHex hexCords;

    std::vector<Entity*> removalList;

public:
    #include "dataStructure/Iters.tpp"

    #include "dataStructure/HexInternals.h"

////////////////////////////////////////////////////////////////////////////////
    ///Iterstuff - non-const - byType - distance
    template<class C>
    byTypeIterNear<C> getAllOfTypeNear(Entity* entity, const unsigned int distance)
    {
        Hex* hexP = byTypeMap[typeid(C).hash_code()][entity]->getHexP();
        return hexP->getAllOfTypeNear<C>(distance, &hexes);
    }

    //Iterstuff - non-const - everything - distance
    globalIterNear getAllNear(Entity* entity, const unsigned int distance)
    {
        Hex* hexP = byTypeMap[typeid(*entity).hash_code()][entity]->getHexP();
        return hexP->getAllNear(distance, &hexes);
    }

    ///Count - non-const - byType - distance
    template<class C>
    unsigned long int getNearByCountOfType(Entity* entity, const unsigned int distance)
    {
        Hex* hexP = byTypeMap[typeid(C).hash_code()][entity]->getHexP();
        return hexP->nearByCountOfType<C>(distance, &hexes);
    }

    //Count - non-const - everything - distance
    unsigned long int getNearByCount(Entity* entity, const unsigned int distance)
    {
        Hex* hexP = byTypeMap[typeid(*entity).hash_code()][entity]->getHexP();
        return hexP->nearByCount(distance, &hexes);
    }
////////////////////////////////////////////////////////////////////////////////
};

#endif
