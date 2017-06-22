#ifndef SIM_BINS
#define SIM_BINS 1

#include "Entity.h"

//All Active Plugins need to be registered in this file
#include "../Compiler/pluginTypes.h"

#include <map>
#include <set>
#include <functional>
#include <vector>

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

    //Update All Entities In The Structure
    void updateEntities();

    ~Bin();
private:
    class Hex;

    #include "dataStructure/Enticap.h"

    std::vector<unsigned int> hexOffsetCord(const unsigned int x, const unsigned int y) const;

    //For the bins:
    const unsigned int width;
    const unsigned int height;
    const double hexRadius;
    std::vector<std::vector<Hex*>> bins;

    //Setup: <typeid.HashCode: <pointerToEntity:pointerToEnticap> >
    std::map< const std::size_t, std::map<Entity* const, Enticap*> > byTypeMap;

    // vector<Entity* const> allEntities; - have another list of everything?

    //For converting from pixel-hex:
    double guessBinWidth;
    double guessBinHeight;

    std::vector< std::vector< std::vector<Hex*> >> guessGrid;

public:
    #include "dataStructure/Iters.h"

private:
    #include "dataStructure/Hex.h"
};

#endif
