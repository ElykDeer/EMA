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
  hexes(ceil( (width+(hexRadius*0.5)) / (1.5*hexRadius)),
    vector<Hex*>( ceil((height+hexRadius) / (sqrt(3)*hexRadius)), nullptr )),
  hexCords(width, height, hexRadius)
  {
      //Populate hex grid:
      for (size_t col = 0; col < hexes.size(); col++)
        for (size_t row = 0; row < hexes[col].size(); row++)
            hexes[col][row] = new Hex(col, row, hexRadius);

      //Can only now initialize the hexCords with bins, since hexes now exist
      hexCords.populate(&hexes);
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

    Enticap* enticap = new Enticap(entity, hexes[cords[0]][cords[1]]);

    //byLocal (which in turn stores by type)
    //structure: [col][row][Hex*]
    hexes[cords[0]][cords[1]]->insert(entity, enticap);

    //byType
    //structure: <typeid.HashCode: <pointerToEntity:pointerToEnticap> >
    byTypeMap[typeid(*entity).hash_code()][entity] = enticap;
}

//Delete an object
void Bin::remove(Entity* const entity)
{
    //First Convert Coordinates
    vector<unsigned int> cords = hexCords.hexOffsetCord(entity->getX(), entity->getY());

    //remove from byLocal
    hexes[cords[0]][cords[1]]->remove(entity);

    //remove from byType
    Enticap* enticapP = byTypeMap[typeid(*entity).hash_code()][entity];
    byTypeMap[typeid(*entity).hash_code()].erase(entity);
    delete enticapP; //Deletes the enticap and the entity
}

//How to move an object in the dataStructure
void Bin::move(Entity* entity, unsigned int newX, unsigned int newY)
{
    //Adjust coordinates if needed
    if (newX >= width)
        newX = newX % width;

    if (newY >= height)
        newY = newY % height;

    //First Convert Coordinates
    vector<unsigned int> oldCords = hexCords.hexOffsetCord(entity->getX(), entity->getY());
    vector<unsigned int> newCords = hexCords.hexOffsetCord(newX, newY);

    //Switch Hexes
    hexes[oldCords[0]][oldCords[1]]->remove(entity);
    hexes[newCords[0]][newCords[1]]->insert(entity, byTypeMap[typeid(*entity).hash_code()][entity]);

    //Let the entity know it's been moved
    entity->x = newX;
    entity->y = newY;
}

//Update All Entities In The Structure
void Bin::updateEntities()
{
    for(Entity& entity : getAll())
        entity.update();
}

//Update All Hexes In The Structure
void Bin::updateHexes()
{
    for(Hex& hex : getAllHexes())
        hex.update();
}

Bin::~Bin()
{
    //Cycle through all Entities/Enticaps and delete them
    for(auto& outerPair : byTypeMap) //Every Different type
        for(auto& innerPair : outerPair.second) //Every single element
            delete innerPair.second; //Delete enticaps, since they delete the entity

    for(auto& col : hexes) //Every Different type
        for(Hex* hex : col) //Every single element
            delete hex;
    //All heap elements are deleted, now the deconstructor will remove pointers
}

#include "Enticap.cpp"

#include "pixToHex.cpp"

#include "Hex.cpp"
