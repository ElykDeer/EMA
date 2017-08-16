//These two are not really iters, but they fit best in this file I think
template<class C>
unsigned long int nearByCountOfType(const unsigned int distance, std::vector<std::vector<Hex*>>* hexes)
{
  {getAllOfTypeNear<C>(distance, hexes);} //Invoke this to build nearBy
  unsigned long int total = 0;
  for (auto map : nearBy[distance])
    total += (*map)[typeid(C).hash_code()].size();
  return total;
}

unsigned long int nearByCount(const unsigned int distance, std::vector<std::vector<Hex*>>* hexes)
{
  {getAllNear(distance, hexes);} //Invoke this to build nearBy
  unsigned long int total = 0;
  for (auto map : nearBy[distance])
    for (auto pair : *map)
      total += pair.second.size();
  return total;
}

////////////////////////////////////////////////////////////////////////////////
//Iterstuff - non-const - of one type near
    template<class C>
    byTypeIterNear<C> getAllOfTypeNear(const unsigned int distance, std::vector<std::vector<Hex*>>* hexes)
    {
        unsigned int hexDistance = floor(distance/hexRadius);
        if (nearBy.count(hexDistance) == 1)
            return byTypeIterNear<C>((*(*nearBy[hexDistance].begin()))[typeid(C).hash_code()].begin(), nearBy[hexDistance].begin(), &nearBy[hexDistance]);
        else
            nearBy[hexDistance] = buildNear(col, row, hexDistance, hexes);
        return byTypeIterNear<C>((*(*nearBy[hexDistance].begin()))[typeid(C).hash_code()].begin(), nearBy[hexDistance].begin(), &nearBy[hexDistance]);
    }

//Iterstuff - non-const - everything near
    //This returns an interatable object over a non-constant object
    globalIterNear getAllNear(const unsigned int distance, std::vector<std::vector<Hex*>>* hexes)
    {
        unsigned int hexDistance = floor(distance/hexRadius);
        if (nearBy.count(hexDistance) == 1)
            return globalIterNear((*nearBy[hexDistance].begin())->begin()->second.begin(), (*nearBy[hexDistance].begin())->begin(), nearBy[hexDistance].begin(), &nearBy[hexDistance]);
        else
            nearBy[hexDistance] = buildNear(col, row, hexDistance, hexes);
        return globalIterNear((*nearBy[hexDistance].begin())->begin()->second.begin(), (*nearBy[hexDistance].begin())->begin(), nearBy[hexDistance].begin(), &nearBy[hexDistance]);
    }
////////////////////////////////////////////////////////////////////////////////
