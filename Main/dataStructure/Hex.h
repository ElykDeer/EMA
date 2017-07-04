#ifndef SIM_HEX
#define SIM_HEX 1

#include "../Entity.h"
#include <map>
#include <cmath> //Because hexagons

class Hex;

class HexInternals
{
public:
    //Give it the matrix coordinates, and it will generate pixel coordinates
    HexInternals(const unsigned int col, const unsigned int row, const double hexRadius);

    //Fake destructor because inheritance
    virtual ~HexInternals();

    virtual void update() = 0;

    void insert(Entity* const entity, Enticap* enticap);

    void remove(Entity* const entity);

    unsigned int getX() const;

    unsigned int getY() const;

    unsigned int getCol() const;

    unsigned int getRow() const;

////////////////////////////////////////////////////////////////////////////////
//Iterstuff - non-const - of one type near
    template<class C>
    byTypeIterNear<C> getAllOfTypeNear(const unsigned int col, const unsigned int row, const unsigned int distance, std::vector<std::vector<Hex*>>* hexes)
    {
        unsigned int hexDistance = distance;//floor((distance-(hexRadiusSmall))/(2*hexRadiusSmall));
        if (nearBy.count(hexDistance) == 1)
            return byTypeIterNear<C>((*(*nearBy[hexDistance].begin()))[typeid(C).hash_code()].begin(), nearBy[hexDistance].begin(), &nearBy[hexDistance]);
        else
            nearBy[hexDistance] = buildNear(col, row, hexDistance, hexes);
        return byTypeIterNear<C>((*(*nearBy[hexDistance].begin()))[typeid(C).hash_code()].begin(), nearBy[hexDistance].begin(), &nearBy[hexDistance]);
    }

//Iterstuff - non-const - everything near
    //This returns an interatable object over a non-constant object
    globalIterNear getAllNear(const unsigned int col, const unsigned int row, const unsigned int distance, std::vector<std::vector<Hex*>>* hexes)
    {
        unsigned int hexDistance = distance;//floor((distance-(hexRadiusSmall/2))/hexRadiusSmall);
        if (nearBy.count(hexDistance) == 1)
            return globalIterNear((*nearBy[hexDistance].begin())->begin()->second.begin(), (*nearBy[hexDistance].begin())->begin(), nearBy[hexDistance].begin(), &nearBy[hexDistance]);
        else
            nearBy[hexDistance] = buildNear(col, row, hexDistance, hexes);
        return globalIterNear((*nearBy[hexDistance].begin())->begin()->second.begin(), (*nearBy[hexDistance].begin())->begin(), nearBy[hexDistance].begin(), &nearBy[hexDistance]);
    }
////////////////////////////////////////////////////////////////////////////////

private:
    //std::vector< std::map< const std::size_t, std::map<Entity* const, Enticap*>>* > buildNear(const unsigned int distance)
    std::vector< std::map< const std::size_t, std::map<Entity* const, Enticap*>>* > buildNear(const unsigned int col, const unsigned int row, const unsigned int distance, std::vector<std::vector<Hex*>>* hexes) const
    {
        //Create Storage Space
        std::vector< std::map< const std::size_t, std::map<Entity* const, Enticap*>>* > nearVec;

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

    // X/Y Locations
    const unsigned int x;
    const unsigned int y;
    const double hexRadius;
    const double hexRadiusSmall;

    //Where in the grid that it is located
    const unsigned int col;
    const unsigned int row;

    //Setup: <typeid.HashCode: <pointerToEntity:pointerToEnticap> >
    std::map< const std::size_t, std::map<Entity* const, Enticap*> > byTypeMap;

    //Keep track of who's near me
    //Setup: <hex distance, vector<pointers to my neighbors' byTypeMaps>>
    std::map<const unsigned int, std::vector<
     std::map< const std::size_t, std::map<Entity* const, Enticap*>>* >> nearBy;
};

class Hex : public HexInternals
{
public:
    //Give it the matrix coordinates, and it will generate pixel coordinates
    Hex(const unsigned int col, const unsigned int row, const double hexRadius);

    virtual void update() override;
//private:

};

#endif
