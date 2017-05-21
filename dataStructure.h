#ifndef SIM_BINS
#define SIM_BINS 1

#include "Entity.h"

//All Active Plugins need to be registered in this file
#include "pluginTypes.h"

#include <map>
#include <functional>
#include <vector>

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
    //Wrapper for an entity..adds
      //a "unique identifier" and
      //list of all things near me - not yet implimented
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
    std::map< const std::size_t, std::map<Entity* const, Enticap*> > byTypeMap;

//Iterstuff - const ////////////////////////////////////////////////////////////
public:
    /*
    This was removed as to force the user to use our provided iterators, which
      hide the internals of this data structure
    template<class C>
    const auto& getAllOfTyp() const
    {
        return byTypeMap.at(typeid(C).hash_code());
    }

    This would have been used as such:
    for(auto& flo : bin.getAllOfTyp<Flower>())
        static_cast<Flower*>(flo.first)->thingy = 1;
    for(auto& flo : bin.getAllOfTyp<Flower>())
        cout << static_cast<Flower*>(flo.first)->thingy << " ";
    */

    //If this is deleted it still works... Consider deleting this in the future
    template<class C>
    class byTypeConstIter
    {
        //So the iterator can compare to beginning and end
        friend bool operator!=(
            const byTypeConstIter<C>& lhs,
            const byTypeConstIter<C>& rhs)
        {
            return lhs.iter != rhs.iter;
        }
    public:
        byTypeConstIter(
            const std::map<Entity* const, Enticap*>::const_iterator& iter,
            const std::map< const std::size_t,
            std::map<Entity* const, Enticap*> >* const byTypeMapP)
            :iter(iter), byTypeMapP(byTypeMapP) {}

        const C& operator*() const //I don't like casting, but I know no alt.
        {
            return *static_cast<const C*>(iter->first);
        }

        byTypeConstIter<C>& operator++()
        {
            ++iter;
            return *this;
        }

        byTypeConstIter<C> begin() const
        {
            return byTypeConstIter<C>(
                byTypeMapP->at(typeid(C).hash_code()).begin(), byTypeMapP);
        }

        byTypeConstIter<C> end() const
        {
            return byTypeConstIter<C>(
                byTypeMapP->at(typeid(C).hash_code()).end(), byTypeMapP);
        }

    private:
        std::map<Entity* const, Enticap*>::const_iterator iter;
        const std::map< const std::size_t, std::map<Entity* const, Enticap*> >*
            const byTypeMapP;
    };

    //This returns a const interatable object over a const object
    template<class C>
    byTypeConstIter<C> getAllOfType() const
    {
        return byTypeConstIter<C>(byTypeMap.at( typeid(C).hash_code() ).begin(),
            &byTypeMap);
    }

//Iterstuff - non-const ////////////////////////////////////////////////////////
    template<class C>
    class byTypeIter
    {
        //So the iterator can compare to beginning and end
        friend bool operator!=(
            const byTypeIter<C>& lhs,
            const byTypeIter<C>& rhs)
        {
            return lhs.iter != rhs.iter;
        }
    public:
        byTypeIter(const std::map<Entity* const, Enticap*>::iterator iter,
                   std::map<const std::size_t,
                    std::map<Entity* const, Enticap*> >* const byTypeMapP)
                   :iter(iter), byTypeMapP(byTypeMapP) {}

        C& operator*() //I don't like casting, but I know no alternative
        {
          return *static_cast<C*>((iter)->first);
        }

        byTypeIter<C>& operator++()
        {
            ++iter;
            return *this;
        }

        byTypeIter<C> begin() const
        {
            return byTypeIter<C>(byTypeMapP->at(typeid(C).hash_code()).begin(),
                byTypeMapP);
        }

        byTypeIter<C> end() const
        {
            return byTypeIter<C>(byTypeMapP->at(typeid(C).hash_code()).end(),
                byTypeMapP);
        }

    private:
        std::map<Entity* const, Enticap*>::iterator iter;
        std::map< const std::size_t, std::map<Entity* const, Enticap*> >*
            const byTypeMapP;
    };

    //This returns an interatable object over a non-constant object
    template<class C>
    byTypeIter<C> getAllOfType()
    {
        return byTypeIter<C>(byTypeMap[typeid(C).hash_code()].begin(),
            &byTypeMap);
    }
};

//This is the map that is based on position, where one can:
  //insert entities
  //remove entities
  //get a list of nearby entities in constant time
class byLocal
{
public:
    //This data structure is closely bound inn deffinition with the size of the map
    byLocal(const unsigned int, const unsigned int, const unsigned int);

    void insert(Entity* const entity);

    void remove(Entity* const entity);

    //Get a list of something to all objects near me
    std::vector<Entity*> getNear(Entity* object);

    ~byLocal();

private:
    //Wrapper for an entity..adds
      //a "unique identifier" and
      //list of all things near me - not yet implimented
    class Enticap
    {
    public:
        Enticap(Entity* const newEntity);

        ~Enticap();

        const Entity* UID() const;

        const std::size_t TUID() const;

    private:
        Entity* const entityP;
        std::vector<Enticap*> nearMe; //For the other one
    };

    const unsigned int width;
    const unsigned int height;
    const unsigned int binSize;
    std::vector<std::vector<std::map<Entity*, Enticap*>>> bins;
    //std::vector< std::vector< std::vector< Entity* const >>> binsies;
};

/*
class Bin// : public byType, public byLocal
{
public:
    Bin()
    {

    }

    //How else do we put things in this monstrosity?
    void insert(Entity* const entity);

    //Delete an object
    void remove(Entity* const entity);

    //Get a list of something to all objects near me
    std::vector<Entity> getNear(Entity& object)
    {
        return {};
    }
private:
    vector<Entity* const> allEntities;
    byType allEntitesByType;
    byLocal allEntitesByLocal;

};*/

#endif
