#ifndef SIM_HEX
#define SIM_HEX 1

#include "../Entity.h"
#include <map>

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

    //Iterators:
    //This returns an interatable object over a non-constant object
    template<class C>
    byTypeIter<C> getAllOfType()
    {
        return byTypeIter<C>(byTypeMap[typeid(C).hash_code()].begin(),
            &byTypeMap);
    }
    //This returns an interatable object over a non-constant object
    globalIter getAll()
    {
        return globalIter(byTypeMap.begin()->second.begin(), byTypeMap.begin(),
            &byTypeMap);
    }


private:
    // X/Y Locations
    const unsigned int x;
    const unsigned int y;
    const double hexRadius;

    //Where in the grid that it is located
    const unsigned int col;
    const unsigned int row;

    //Setup: <typeid.HashCode: <pointerToEntity:pointerToEnticap> >
    std::map< const std::size_t, std::map<Entity* const, Enticap*> > byTypeMap;
};

class Hex : public HexInternals
{
public:
    //Give it the matrix coordinates, and it will generate pixel coordinates
    Hex(const unsigned int row, const unsigned int col, const double hexRadius);

    virtual void update() override;
private:

};

#endif
