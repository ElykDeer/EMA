#include "HexInternals.h"
using namespace std;

//Give it the matrix coordinates, and it will generate pixel coordinates
Bin::HexInternals::HexInternals(const unsigned int col, const unsigned int row, const double hexRadius) :
  x(hexRadius * 1.5 * col),
  y(hexRadius * sqrt(3.0) * (row - (0.5*(col&1))) ),
  hexRadius(hexRadius),
  hexRadiusSmall((sqrt(3)*hexRadius)/2),
  col(col),
  row(row) {}

Bin::HexInternals::~HexInternals()
{
//     std::cerr << " 1";
//     std::cerr << " count: " << count() << " ";
//
//     for (std::pair< const std::size_t, std::map<Entity* const, Enticap*> > typePair : byTypeMap)
//         //{std::cerr << typePair.second.begin() << '\n'; std::cerr << typePair.second.end(); ++entiPair);}
//         //for (std::pair<Entity* const, Enticap*> entiPair : typePair.second)
//         for (auto entiPair = typePair.second.begin(); entiPair != typePair.second.end(); ++entiPair)
//         {std::cerr << " begin: " << &*typePair.second.begin() << " end: " << &*typePair.second.end() << " current: " << &*entiPair << std::endl; }
// //{           /*entMap.second = nullptr;*/ std::cerr << &*entiPair << " ";}
//             //for (auto pair : entMap.second)
//             //    pair.second = nullptr;
//             std::cerr << "2 ";
//     byTypeMap.clear();
//     std::cerr << "3 ";
//     nearBy.clear();
}

void Bin::HexInternals::insert(Entity* const entity, Enticap* enticap)
{
    //Insert into our map structure:
      //<typeid.HashCode: <pointerToEntity:pointerToEnticap> >
    //This died: std::cerr << "adding: " << typeid(*entity).hash_code() << std::endl;
    std::cerr << "adding: " << entity << std::endl;
    byTypeMap[typeid(*entity).hash_code()][entity] = enticap;
    std::cerr << "added\n";

    ++entityCount;
}

void Bin::HexInternals::remove(Entity* const entity)
{
    byTypeMap[typeid(*entity).hash_code()].erase(entity);
    --entityCount;
}

//Map Positoin Getters
double Bin::HexInternals::getX() const
{
    return x;
}
double Bin::HexInternals::getY() const
{
    return y;
}


//Storage Position Getters
unsigned int Bin::HexInternals::getCol() const
{
    return col;
}
unsigned int Bin::HexInternals::getRow() const
{
    return row;
}

//Radius Getter
double Bin::HexInternals::getRadius() const
{
    return hexRadius;
}


//Returns the count of how many entities are in this hex
unsigned long int Bin::HexInternals::count() const
{
    return entityCount;
}


//This function creates a list of all entities within a certian pix distance
vector< map< const size_t, map<Entity* const, Bin::Enticap*>>* >
  Bin::HexInternals::buildNear(const unsigned int col,
                               const unsigned int row,
                               const unsigned int distance,
                               vector<vector<Hex*>>* hexes) const
{
    //Create Storage Space
    vector< map< const size_t, map<Entity* const, Enticap*>>* > nearVec;

    //Left-most collumn
    unsigned int colMin;
    if (col < distance)
        colMin = 0;
    else
        colMin = col-distance;
    //right-most collumn
    unsigned int colMax;
    if (col+distance >= hexes->size())
        colMax = hexes->size()-1;
    else
        colMax = col+distance;

    //Where to start building
    unsigned int rowStart;
    if (col&1) //odd col
    {
        if (row < floor(distance+1/2.0))
            rowStart = 0;
        else
            rowStart = row-floor(distance+1/2.0);
    }
    else //even col
    {
        if (row < floor(distance+1/2.0))
            rowStart = 0;
        else
            rowStart = row-floor(distance+1/2.0);
    }

    //Where to stop building
    unsigned int rowEnd;
    if (col&1) //odd col
    {
        if (row+floor(distance/2.0) >= (*hexes)[col].size())
            rowEnd = (*hexes)[col].size()-1;
        else
            rowEnd = row+floor(distance/2.0);
    }
    else //even col
    {
        if (row+floor(distance/2.0) >= (*hexes)[col].size())
            rowEnd = (*hexes)[col].size()-1;
        else
            rowEnd = row+floor(distance/2.0);
    }

    //-1 for left side, 1 for right side
    int sideOfStart = -1;
    for (unsigned int colCur = colMin; colCur <= colMax; ++colCur)
    {
        for (unsigned int rowCur = rowStart; rowCur <= rowEnd; ++rowCur)
        {
            nearVec.push_back( &(*hexes)[colCur][rowCur]->byTypeMap ); //Append all in a col
        }

        //Based on the side of the center, and cur pos, adjust next col height
        if (colCur == col)
            sideOfStart = 1;

        if (colCur&1) //if odd
        {
            if (rowStart > 0)
                rowStart += sideOfStart;
        }
        else //even cols
        {
            if (rowEnd < hexes[col].size()-1)
                rowEnd -= sideOfStart;
        }
    }
    return nearVec;
}

#include "../../Plugins/Environment/Hex.cpp"
