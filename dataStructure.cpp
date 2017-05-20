#include "dataStructure.h"
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
    delete byTypeMap[typeid(*entity).hash_code()][entity];
}

byType::~byType()
{
    //Delete all entities
    for(auto& pair : byTypeMap) //Different type
        for(const auto& thing : pair.second) //Every single element
            delete thing.second; //Delete all enticaps, since they in turn delete their entities

    //Alernative way, without auto:
    //for(std::pair< const std::size_t, std::map<const Entity*, Enticap*> >& pair : byTypeMap) //Different type
        //for(const std::pair<const Entity*, Enticap*>& thing : pair.second) //Every single element
}

byType::Enticap::Enticap(Entity* const newEntity) : entityP(newEntity) {}

byType::Enticap::~Enticap()
{
    delete entityP;
}

const Entity* byType::Enticap::UID() const //UDI for this entity = mem addr on heap
{
    return entityP;
}

const size_t byType::Enticap::TUID() const //Type Identifier
{
    return typeid(*entityP).hash_code();
}
