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
    vector<Hex*>( ceil((height+hexRadius) / (sqrt(3)*hexRadius)), nullptr )), ////////////////////change to hex*

  guessBinWidth(hexRadius/4),
  guessBinHeight( (sqrt(3)*hexRadius) /4),
  guessGrid(ceil(width/guessBinWidth), vector<vector<Hex*>>( ceil(height/guessBinHeight) ))
  {
      cerr << "################################################\n";
      cerr << "guessBinWidth: " << guessBinWidth << " guessBinHeight: " << guessBinHeight << endl;
      cerr << "guessBinsRow: " << guessGrid[0].size() << ", guessBinsCol: " << guessGrid.size() << endl;
      cerr << "BinsRow: " << bins[0].size() << ", BinsCol: " << bins.size() << endl;
      cerr << "max X: " << guessBinWidth*guessGrid.size() << ", max Y: " << guessBinHeight*guessGrid[0].size() << endl;
      cerr << "################################################\n";

      //Populate hex grid:
      for (size_t col = 0; col < bins.size(); col++)
        for (size_t row = 0; row < bins[col].size(); row++)
            bins[col][row] = new Hex(col, row, hexRadius);


      //Set up the guessGrid:
      //For each row
      int leftGridX = 0;
      int leftGridY = 0;

      int rightGridX = 1;
      int rightGridY = 0;

      for (size_t row = 0; row < guessGrid[0].size(); row++)
      {
          //For each collumn
          unsigned int nextDouble;
          if (row&1) //odd row
              nextDouble = 4;
          else //even rows
              nextDouble = 5;

          for (size_t col = 0; col < guessGrid.size(); col++)
          {
              if (col == nextDouble) //If an odd row
              {
                  guessGrid[col][row].push_back(bins[leftGridX][leftGridY]);
                  guessGrid[col][row].push_back(bins[rightGridX][rightGridY]);

                  if (guessGrid[col][row].size()>2)
                        exit(1);
                  if (guessGrid[col][row].size()==0)
                        exit(1);

                  //set next double
                  if (nextDouble&1) //if next double if odd
                      nextDouble += 5;
                  else //is even
                      nextDouble += 7;

                  //Set next pairing at that double
                  leftGridX++;
                  rightGridX++;
              }
              else
                  guessGrid[col][row].push_back(bins[leftGridX][leftGridY]);
          }
          //reset x of the doubles
          leftGridX = 0;
          rightGridX = 1;

          //Adjust the y of the doubles
          if ((row+1) % 4 == 0)
              leftGridY++;
          else if ((row+1) % 2 == 0)
              rightGridY++;
      }
  }

//How else do we put things in this monstrosity?
void Bin::insert(Entity* const entity)
{
    //First Convert coordinates
    vector<unsigned int> cords = hexOffsetCord(entity->getX(), entity->getY());

    //byLocal
    //structure: [col][row][Entity*]
    bins[cords[0]][cords[1]]->insert(entity);

    //byType
    //structure: <typeid.HashCode: <pointerToEntity:pointerToEnticap> >
    byTypeMap[typeid(*entity).hash_code()][entity] = new Enticap(entity);
}

//Delete an object
void Bin::remove(Entity* const entity)
{
    //First Convert coordinates
    vector<unsigned int> cords = hexOffsetCord(entity->getX(), entity->getY());

    //remove from byLocal
    bins[cords[0]][cords[1]]->erase(entity);

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

    if (0)
        cerr << col << row;

    //Build the list of bins around us
    vector<Entity*> nearMes; //The vector of what's around us
/*    for(int colOffset = -1; colOffset < 2; ++colOffset)
        for(int rowOffset = -1; rowOffset < 2; ++rowOffset)
            for(auto& element : bins[col+colOffset][row+rowOffset])
                nearMes.push_back(element);
*/
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
