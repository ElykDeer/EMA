#include "dataStructure.h"
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
    vector<set<Entity*>>( ceil((height+hexRadius) / (sqrt(3)*hexRadius)) )), ////////////////////change to hex*

  guessBinWidth(hexRadius/4),
  guessBinHeight( (sqrt(3)*hexRadius) /4),
  guessGrid(width/guessBinWidth, vector<vector<Hex*>>( height/guessBinHeight ))
  {
      //Set up the guessGrid

      //for (int row = 0; row < guessGrid[0].size(); row++) {  }

      //guessGrid
  }

//How else do we put things in this monstrosity?
void Bin::insert(Entity* const entity)
{
    //First Convert coordinates
    vector<unsigned int> cords = hexOffsetCord(entity->getX(), entity->getX());

    //byLocal
    //structure: [col][row][Entity*]
    bins[cords[0]][cords[1]].insert(entity);

    //byType
    //structure: <typeid.HashCode: <pointerToEntity:pointerToEnticap> >
    byTypeMap[typeid(*entity).hash_code()][entity] = new Enticap(entity);
}

//Delete an object
void Bin::remove(Entity* const entity)
{
    //First Convert coordinates
    vector<unsigned int> cords = hexOffsetCord(entity->getX(), entity->getX());

    //remove from byLocal
    bins[cords[0]][cords[1]].erase(entity);

    //remove from byType
    Enticap* enticapP = byTypeMap[typeid(*entity).hash_code()][entity];
    byTypeMap[typeid(*entity).hash_code()].erase(entity);
    delete enticapP; //Deletes the enticap and the entity
}

//For right now this returns fomr the 3x3 bin area around/including our bin
vector<Entity*> Bin::getNear(Entity* entity)
{
    //First Convert coordinates
    vector<unsigned int> cords = hexOffsetCord(entity->getX(), entity->getX());

    //Our bin position - bins[col][row]
    size_t col = cords[0];
    size_t row = cords[1];

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

vector<unsigned int> Bin::hexOffsetCord(const unsigned int x, const unsigned int y) const
{
    //Generate the guess
    const unsigned int guessBinX = x/guessBinWidth;
    const unsigned int guessBinY = y/guessBinHeight;

    //Grab Guess
    const vector<Hex*>& guessBin = guessGrid[guessBinX][guessBinY];

    //71% chance for there to only be one thing to do..
    if (guessBin.size() == 1)
        return {guessBin[0]->getCol(), guessBin[0]->getRow()};

    //Calculate distances
    double dist1 =
    sqrt(pow((guessBin[0]->getX() - x), 2) + pow((guessBin[0]->getY() - y), 2));
    double dist2 =
    sqrt(pow((guessBin[1]->getX() - x), 2) + pow((guessBin[1]->getY() - y), 2));

    //If closer to one, return one
    if(dist1 < dist2)
        return {guessBin[0]->getCol(), guessBin[0]->getRow()};

    //Otherwise return the other
    return {guessBin[1]->getCol(), guessBin[1]->getRow()};
}

//Enticap
Bin::Enticap::Enticap(Entity* const newEntity) : entityP(newEntity) {}

Bin::Enticap::~Enticap()
{
    delete entityP;
}

/*
Entity* Bin::Enticap::UID() const //UDI for entity = mem addr on heap
{
    return entityP;
}

size_t Bin::Enticap::TUID() const //Type Identifier
{
    return typeid(*entityP).hash_code();
}*/
