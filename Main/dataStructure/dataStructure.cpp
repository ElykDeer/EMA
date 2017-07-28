#include "../dataStructure.h"
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

    //adjust the count
    ++entityCount;
}

//Delete an object
void Bin::remove(Entity* const entity)
{
    //remove from byLocal
    vector<unsigned int> cords = hexCords.hexOffsetCord(entity->getX(), entity->getY());
    hexes[cords[0]][cords[1]]->remove(entity);

    //remove from byType
    size_t classCode = typeid(*entity).hash_code();

    Enticap* enticapP = byTypeMap[classCode][entity];
    byTypeMap[classCode].erase(entity);
    delete enticapP; //Deletes the enticap and the entity

    //adjust the Count
    --entityCount;

    if (byTypeMap[classCode].size() == 0)
        byTypeMap.erase(classCode);
}

//Add to removal list
void Bin::markForRemoval(Entity* const entity)
{
  removalList.push_back(entity);
}

//remove all entities marked for removal and clear removal list
void Bin::removeAll()
{
  for (Entity* const entity : removalList)
  {
    remove(entity);
  }
  removalList.clear();
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
void Bin::updateEntities(unsigned int resolution)
{
  if (entityCount)
    for(Entity& entity : getAll())
        entity.update(resolution);
}

//Update All Hexes In The Structure
void Bin::updateHexes(unsigned int resolution)
{
  for(Hex& hex : getAllHexes())
    hex.update(resolution);
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

//A few simple getters
unsigned int Bin::getWidth() const
{
    return width;
}
unsigned int Bin::getHeight() const
{
    return height;
}
unsigned long int Bin::count() const
{
    return entityCount;
}

#include "Enticap.cpp"

#include "pixToHex.cpp"

#include "HexInternals.cpp"
