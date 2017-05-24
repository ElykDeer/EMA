#include "dataStructure.h"
#include <iostream>
using namespace std;

//This is the map that is based on type, where one can:
  //fetch entities by their type
  //insert entities
  //remove entities

void byType::insert(Entity* const entity)
{
    //Insert into our map structure:
      //<typeid.HashCode: <pointerToEntity:pointerToEnticap> >
    byTypeMap[typeid(*entity).hash_code()][entity] = new Enticap(entity);
}

void byType::remove(Entity* const entity)
{
    //Save where the enticap is
    Enticap* enticapP = byTypeMap[typeid(*entity).hash_code()][entity];
    byTypeMap[typeid(*entity).hash_code()].erase(entity); //Calls enticap destuc
    delete enticapP; //Deletes the enticap
}

byType::~byType()
{
    //Delete all entities
    for(auto& pair : byTypeMap) //Every Different type
        for(auto& thing : pair.second) //Every single element
            delete thing.second; //Delete enticaps, since they delete the entity

    //Alernative way, without auto:
    //for(std::pair< const std::size_t, std::map<const Entity*, Enticap*> >& pair : byTypeMap) //Different type
        //for(const std::pair<const Entity*, Enticap*>& thing : pair.second) //Every single element
}

byType::Enticap::Enticap(Entity* const newEntity) : entityP(newEntity) {}

byType::Enticap::~Enticap()
{
    delete entityP;
}

const Entity* byType::Enticap::UID() const //UDI for entity = mem addr on heap
{
    return entityP;
}

const size_t byType::Enticap::TUID() const //Type Identifier
{
    return typeid(*entityP).hash_code();
}

////////////////////////////////////////////////////////////////////////////////
byLocal::byLocal(const unsigned int width,
                 const unsigned int height,
                 const unsigned int binSize)
: width(width),
  height(height),
  binSize(binSize),
 //Initalize the x, then the y, of empty maps:
 bins(width/binSize, vector<map<Entity*, Enticap*>>(height/binSize)) {}

void byLocal::insert(Entity* const entity)
{
    bins[entity->getX()/binSize][entity->getY()/binSize][entity] = 
        new Enticap(entity);
}

void byLocal::remove(Entity* const entity)
{
    //Save where the enticap is
    Enticap* enticapP
        = bins[entity->getX()/binSize][entity->getY()/binSize][entity];
    //Calls enticap destuctor
    bins[entity->getX()/binSize][entity->getY()/binSize].erase(entity);
    delete enticapP; //Deletes the enticap
}

//For right now this returns fomr the 3x3 bin area around/including our bin
vector<Entity*> byLocal::getNear(Entity* entity)
{
    //Our bin position - bins[col][row]
    size_t col = entity->getX()/binSize;
    size_t row = entity->getY()/binSize;

    //Build the list of bins around us
    vector<Entity*> nearMes; //The vector of what's around us
    for(int colOffset = -1; colOffset < 2; ++colOffset)
        for(int rowOffset = -1; rowOffset < 2; ++rowOffset)
            for(auto& pair : bins[col+colOffset][row+rowOffset])
                nearMes.push_back(pair.first);

    //Return list
    return nearMes;
}

byLocal::~byLocal()
{
    //Delete all entities
    for(auto& col : bins)
        for(auto& row : col)
            for(auto& pair : row)
                delete pair.second; //Delete enticaps, they delete the entity
}

//Duplicate:
byLocal::Enticap::Enticap(Entity* const newEntity) : entityP(newEntity) {}

byLocal::Enticap::~Enticap()
{
    delete entityP;
}

const Entity* byLocal::Enticap::UID() const //UDI for entity = mem addr on heap
{
    return entityP;
}

const size_t byLocal::Enticap::TUID() const //Type Identifier
{
    return typeid(*entityP).hash_code();
}
