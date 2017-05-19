#ifndef SIM_BINS
#define SIM_BINS 1

#include "Entity.h"
//#include <vector>
#include <map>
#include <string>
#include <functional>

//This is the map that is based on type, where one can:
  //insert entities
  //remove entities
  //fetch entities by their type
class byType
{
public:
    void insert(Entity* const entity);

    void remove(Entity* const entity);

    ~byType();

private:
    //Wrapper for an entity..adds a "unique identifier" and list of all things near me
    class Enticap
    {
    public:
        Enticap(Entity* const newEntity);

        ~Enticap();

        const Entity* UID() const;

        const std::size_t TUID() const;

    private:
        Entity* const entityP;
        //vector<Enticap*> nearMe; //For the other one
    };

    //Setup: <typeid.HashCode: <pointerToEntity:pointerToEnticap> >
    std::map< const std::size_t, std::map<const Entity*, Enticap*> > byTypeMap;

//Iterstuff
public:
    //This should probably return a interatable object
    template<class C>
    const auto& getAllOfTyp() const
    {
        return byTypeMap.at(typeid(C).hash_code()); //at = const op[] for maps
    }

    template<class C> //Fuckin shit this is going to make the binary massive
    class byTypeIter
    {
    public:
        byTypeIter(std::map<const Entity*, Enticap*>::const_iterator iter) : iter(iter) {}

        C& operator*()
        {
            return (*iter).first;
        }

        C& operator++()
        {
            return ++iter;
        }

        C operator++(int)
        {
            return iter++;
        }

    private:
        std::map<const Entity*, Enticap*>::const_iterator iter;
    };

    /*template<class C>
    auto begin(byTypeIter<C>&)
    {
        return byTypeMap.at( typeid(C).hash_code() ).begin();
    }

    template<class C>
    auto end(byTypeIter<C>&)
    {
        return byTypeMap.at( typeid(C).hash_code() ).end();
    }*/

    auto begin(byTypeIter<Dog>&)
    {
        return byTypeMap.at( typeid(Dog).hash_code() ).begin();
    }

    auto end(byTypeIter<Dog>&)
    {
        return byTypeMap.at( typeid(Dog).hash_code() ).end();
    }

    //This returna an interatable object
    template<class C>
    byTypeIter<C> getAllOfType() const
    {
        return byTypeIter<C>(byTypeMap.at( typeid(C).hash_code() ).begin());
    }
};

/*
class byLocal
{
public:

private:

};


class Bin : public byType, public byLocal
{
public:
    Bin()
    {

    }

    //How else do we put things in this monstrosity?
    void insert(Entity& newObject)
    {

    }

    //Delete an object
    void remove(Entity& oldObject)
    {

    }

    //Get a list of something to all objects near me
    std::vector<Entity> getNear(Entity& object)
    {
        return {};
    }
private:

};*/

#endif
