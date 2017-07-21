////////////////////////////////////////////////////////////////////////////////
//Iterstuff - non-const - of one type near
    template<class C>
    byTypeIterNear<C> getAllOfTypeNear(const unsigned int col, const unsigned int row, const unsigned int distance, std::vector<std::vector<Hex*>>* hexes)
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
    globalIterNear getAllNear(const unsigned int col, const unsigned int row, const unsigned int distance, std::vector<std::vector<Hex*>>* hexes)
    {
        unsigned int hexDistance = floor(distance/hexRadius);
        if (nearBy.count(hexDistance) == 1)
            return globalIterNear((*nearBy[hexDistance].begin())->begin()->second.begin(), (*nearBy[hexDistance].begin())->begin(), nearBy[hexDistance].begin(), &nearBy[hexDistance]);
        else
            nearBy[hexDistance] = buildNear(col, row, hexDistance, hexes);
        return globalIterNear((*nearBy[hexDistance].begin())->begin()->second.begin(), (*nearBy[hexDistance].begin())->begin(), nearBy[hexDistance].begin(), &nearBy[hexDistance]);
    }
////////////////////////////////////////////////////////////////////////////////
