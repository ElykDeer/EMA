#include "dataStructure.h"
#include <cmath>  //Because hexagons
#include <iostream> //- debug only
using namespace std;

//This is the data structure, where one can:
  //fetch entities by their type
  //insert entities
  //remove entities
  //get a list of elements with nearby x/y coordinates

//This data structure needs to know the level size in the game
//Width, height, hexRadius
Bin::Bin(const double width,
                 const double height,
                 const double hexRadius)
: width(width),
  height(height),
  hexRadius(hexRadius),
 //Initalize the x, then the y, of empty maps:
 bins(ceil( (width+(hexRadius*0.5)) / (1.5*hexRadius)),
    vector<set<Entity*>>( ceil((height+hexRadius) / (sqrt(3)*hexRadius)) )) {}

//How else do we put things in this monstrosity?
void Bin::insert(Entity* const entity)
{
    //byLocal
    //structure: [col][row][Entity*]
    bins[entity->getX()/hexRadius][entity->getY()/hexRadius].insert(entity);

    //byType
    //structure: <typeid.HashCode: <pointerToEntity:pointerToEnticap> >
    byTypeMap[typeid(*entity).hash_code()][entity] = new Enticap(entity);
}

//Delete an object
void Bin::remove(Entity* const entity)
{
    //remove from byLocal
    bins[entity->getX()/hexRadius][entity->getY()/hexRadius].erase(entity);

    //remove from byType
    Enticap* enticapP = byTypeMap[typeid(*entity).hash_code()][entity];
    byTypeMap[typeid(*entity).hash_code()].erase(entity);
    delete enticapP; //Deletes the enticap and the entity
}

//For right now this returns fomr the 3x3 bin area around/including our bin
vector<Entity*> Bin::getNear(Entity* entity)
{
    //Our bin position - bins[col][row]
    size_t col = entity->getX()/hexRadius;
    size_t row = entity->getY()/hexRadius;

    //Build the list of bins around us
    vector<Entity*> nearMes; //The vector of what's around us
    for(int colOffset = -1; colOffset < 2; ++colOffset)
        for(int rowOffset = -1; rowOffset < 2; ++rowOffset)
            for(auto& element : bins[col+colOffset][row+rowOffset])
                nearMes.push_back(element);

    //Return list
    return nearMes;
}

Bin::~Bin()
{
    //Cycle through all Entities/Enticaps and delete them
    for(auto& pair : byTypeMap) //Every Different type
        for(auto& thing : pair.second) //Every single element
            delete thing.second; //Delete enticaps, since they delete the entity

    //All heap elements are deleted, now the deconstructor will remove pointers
}

//Enticap
Bin::Enticap::Enticap(Entity* const newEntity) : entityP(newEntity) {}

Bin::Enticap::~Enticap()
{
    delete entityP;
}

Entity* Bin::Enticap::UID() const //UDI for entity = mem addr on heap
{
    return entityP;
}

size_t Bin::Enticap::TUID() const //Type Identifier
{
    return typeid(*entityP).hash_code();
}
