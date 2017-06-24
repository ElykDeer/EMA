#include "../dataStructure.h"
#include <cmath>
#include <iostream> //- debug only
using namespace std;

//This is the data structure, where one can:
  //fetch entities by their type
  //insert entities
  //remove entities
  //get a list of elements with nearby x/y coordinates

//This data structure needs to know the level size in the game
//Width, height, hexRadius
Bin::Bin(const unsigned int width,
                 const unsigned int height,
                 const double hexRadius)
: width(width),
  height(height),
  hexRadius(hexRadius),

  //Initalize the x, then the y, of empty maps:
  bins(ceil( (width+(hexRadius*0.5)) / (1.5*hexRadius)),
    vector<Hex*>( ceil((height+hexRadius) / (sqrt(3)*hexRadius)), nullptr )),
  hexCords(width, height, hexRadius)
  {
      //Populate hex grid:
      for (size_t col = 0; col < bins.size(); col++)
        for (size_t row = 0; row < bins[col].size(); row++)
            bins[col][row] = new Hex(col, row, hexRadius);

      //Can only now initialize the hexCords with bins, since hexes now exist
      hexCords.populate(&bins);
  }

//How else do we put things in this monstrosity?
void Bin::insert(Entity* const entity)
{
    if (entity->getX() >= width)
        entity->x = entity->x % width;

    if (entity->getY() >= height)
        entity->y = entity->y % height;

    //First Convert coordinates
    vector<unsigned int> cords = hexCords.hexOffsetCord(entity->getX(), entity->getY());

    Enticap* enticap = new Enticap(entity, bins[cords[0]][cords[1]]);

    //byLocal (which in turn stores by type)
    //structure: [col][row][Hex*]
    bins[cords[0]][cords[1]]->insert(entity, enticap);

    //byType
    //structure: <typeid.HashCode: <pointerToEntity:pointerToEnticap> >
    byTypeMap[typeid(*entity).hash_code()][entity] = enticap;
}

//Delete an object
void Bin::remove(Entity* const entity)
{
    //First Convert coordinates
    vector<unsigned int> cords = hexCords.hexOffsetCord(entity->getX(), entity->getY());

    //remove from byLocal
    bins[cords[0]][cords[1]]->remove(entity);

    //remove from byType
    Enticap* enticapP = byTypeMap[typeid(*entity).hash_code()][entity];
    byTypeMap[typeid(*entity).hash_code()].erase(entity);
    delete enticapP; //Deletes the enticap and the entity
}

//Update All Entities In The Structure
void Bin::updateEntities()
{
    for(Entity* entity : getAll())
        entity->update();
}

Bin::~Bin()
{
    //Cycle through all Entities/Enticaps and delete them
    for(auto& pair : byTypeMap) //Every Different type
        for(auto& thing : pair.second) //Every single element
            delete thing.second; //Delete enticaps, since they delete the entity

    //All heap elements are deleted, now the deconstructor will remove pointers
}

#include "Enticap.cpp"

#include "pixToHex.cpp"

#include "Hex.cpp"
