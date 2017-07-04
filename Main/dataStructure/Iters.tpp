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

//Iterstuff - const
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
          return byTypeConstIter<C>(byTypeMapP->at(typeid(C).hash_code()).end(),
            byTypeMapP);
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

//Iterstuff - non-const - byType
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
        return *static_cast<C*>(iter->first);
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

////////////////////////////////////////////////////////////////////////////////
  //Iterstuff - non-const - everything
  class globalIter
  {
      //So the iterator can compare to beginning and end
      friend bool operator!=(
          const globalIter& lhs,
          const globalIter& rhs)
      {
          return lhs.innerIter != rhs.innerIter;
      }
  public:
      globalIter(const std::map<Entity* const, Enticap*>::iterator innerIter,
                 std::map<const std::size_t, std::map<Entity* const, Enticap*>>::iterator outerIter,
                 std::map<const std::size_t, std::map<Entity* const, Enticap*> >* const byTypeMapP)
                 :innerIter(innerIter), outerIter(outerIter),
                 byTypeMapP(byTypeMapP) {}

      Entity& operator*()
      {
        return *innerIter->first;
      }

      globalIter& operator++()
      {
          ++innerIter;

          //If at the end of the "byType", go to the next one
          if(innerIter == outerIter->second.end() &&
             innerIter != byTypeMapP->rbegin()->second.end())
          {
              ++outerIter;
              innerIter = outerIter->second.begin();
          }

          return *this;
      }

      globalIter begin() const
      {
          return globalIter(byTypeMapP->begin()->second.begin(), byTypeMapP->begin(), byTypeMapP);
      }

      globalIter end() const
      {
          return globalIter(byTypeMapP->rbegin()->second.end(), byTypeMapP->end(), byTypeMapP);
      }

  private:
      std::map<Entity* const, Enticap*>::iterator innerIter;
      std::map<const std::size_t, std::map<Entity* const, Enticap*>>::iterator
          outerIter;
      std::map< const std::size_t, std::map<Entity* const, Enticap*> >*
          const byTypeMapP;
  };

  //This returns an interatable object over all non-constant object
  globalIter getAll()
  {
      return globalIter(byTypeMap.begin()->second.begin(), byTypeMap.begin(),
          &byTypeMap);
  }



////////////////////////////////////////////////////////////////////////////////
  //Iterstuff - non-const - hexes
class globalHexIter
{
    //So the iterator can compare to beginning and end
    friend bool operator!=(
        const globalHexIter& lhs,
        const globalHexIter& rhs)
    {
        return lhs.innerIter != rhs.innerIter;
    }
public:
    globalHexIter(std::vector<Hex*>::iterator innerIter,
                  std::vector<std::vector<Hex*>>::iterator outerIter,
                  std::vector<std::vector<Hex*>>* hexesP)
     : innerIter(innerIter), outerIter(outerIter), hexesP(hexesP) {}

    Hex& operator*()
    {
      return **innerIter;
    }

    globalHexIter& operator++()
    {
        ++innerIter;

        //If at the end of the "byType", go to the next one
        if(innerIter == outerIter->end() &&
           innerIter != hexesP->rbegin()->end())
        {
            ++outerIter;
            innerIter = outerIter->begin();
        }

        return *this;
    }

    globalHexIter begin() const
    {
        return globalHexIter(hexesP->begin()->begin(), hexesP->begin(), hexesP);
    }

    globalHexIter end() const
    {
        return globalHexIter(hexesP->rbegin()->end(), hexesP->end(), hexesP);
    }

private:
    std::vector<Hex*>::iterator innerIter;
    std::vector<std::vector<Hex*>>::iterator outerIter;
    std::vector<std::vector<Hex*>>* hexesP;
};

globalHexIter getAllHexes()
{
    return globalHexIter(hexes.begin()->begin(), hexes.begin(), &hexes);
}

////////////////////////////////////////////////////////////////////////////////
///Iterstuff - non-const - byType - distance
template<class C>
class byTypeIterNear
{
    //So the iterator can compare to beginning and end
    friend bool operator!=(
        const byTypeIterNear& lhs,
        const byTypeIterNear& rhs)
    {
        return lhs.innerIter != rhs.innerIter;
    }
public:
    byTypeIterNear(std::map<Entity* const, Enticap*>::iterator innerIter,
               std::vector<std::map< const std::size_t, std::map<Entity* const, Enticap*> >*>::iterator outerIter,
               std::vector<std::map< const std::size_t, std::map<Entity* const, Enticap*> >* >* const byTypeMapsP)
               : innerIter(innerIter), outerIter(outerIter),
               byTypeMapsP(byTypeMapsP) {}

    C& operator*()
    {
      return *static_cast<C*>(innerIter->first);;
    }

    byTypeIterNear<C>& operator++()
    {
        ++innerIter;

        //If at the end of the "byType" part, go to the next part
        if (innerIter == (**outerIter)[typeid(C).hash_code()].end())
        {
            if (innerIter != (**byTypeMapsP->rbegin())[typeid(C).hash_code()].end())
            {
                ++outerIter;
                innerIter = (*outerIter)[typeid(C).hash_code()].begin()->second.begin();
            }
        }

        return *this;
    }

    byTypeIterNear<C> begin() const
    {
        return byTypeIterNear<C>((*(*byTypeMapsP->begin()))[typeid(C).hash_code()].begin(), byTypeMapsP->begin(), byTypeMapsP);
    }

    byTypeIterNear<C> end() const
    {
        return byTypeIterNear<C>((*(*byTypeMapsP->rbegin()))[typeid(C).hash_code()].end(), byTypeMapsP->end(), byTypeMapsP);
    }

private:
    std::map<Entity* const, Enticap*>::iterator innerIter;
    std::vector<std::map< const std::size_t, std::map<Entity* const, Enticap*> >*>::iterator
        outerIter;
    std::vector<std::map< const std::size_t, std::map<Entity* const, Enticap*> >* >* const
        byTypeMapsP;

};

//Iterstuff - non-const - everything - distance
class globalIterNear
{
    //So the iterator can compare to beginning and end
    friend bool operator!=(
        const globalIterNear& lhs,
        const globalIterNear& rhs)
    {
        return lhs.innerIter != rhs.innerIter;
    }
public:
    globalIterNear(const std::map<Entity* const, Enticap*>::iterator innerIter,
               std::map<const std::size_t, std::map<Entity* const, Enticap*>>::iterator middleIter,
               std::vector<std::map< const std::size_t, std::map<Entity* const, Enticap*> >*>::iterator outerIter,
               std::vector<std::map< const std::size_t, std::map<Entity* const, Enticap*> >* >* const byTypeMapsP)
               :innerIter(innerIter), middleIter(middleIter), outerIter(outerIter),
               byTypeMapsP(byTypeMapsP) {}

    Entity& operator*()
    {
      return *innerIter->first;
    }

    globalIterNear& operator++()
    {
        ++innerIter;

        //If at the end of the "byType" part, go to the next part
        if(innerIter == middleIter->second.end() &&
           innerIter != (*byTypeMapsP->rbegin())->rbegin()->second.end())
        {
            //if at the end of this byType map, go to the next map
            if(innerIter == (*outerIter)->rbegin()->second.end())
            {
                ++outerIter;
                middleIter = (*outerIter)->begin();
            }

            ++middleIter;
            innerIter = middleIter->second.begin();
        }

        return *this;
    }

    globalIterNear begin() const
    {
        return globalIterNear((*byTypeMapsP->begin())->begin()->second.begin(), (*byTypeMapsP->begin())->begin(), byTypeMapsP->begin(), byTypeMapsP);
    }

    globalIterNear end() const
    {
        return globalIterNear((*byTypeMapsP->rbegin())->rbegin()->second.end(), (*byTypeMapsP->rbegin())->end(), byTypeMapsP->end(), byTypeMapsP);
    }

private:
    std::map<Entity* const, Enticap*>::iterator innerIter;
    std::map<const std::size_t, std::map<Entity* const, Enticap*>>::iterator
        middleIter;
    std::vector<std::map< const std::size_t, std::map<Entity* const, Enticap*> >*>::iterator
        outerIter;
    std::vector<std::map< const std::size_t, std::map<Entity* const, Enticap*> >* >* const
        byTypeMapsP;
};
