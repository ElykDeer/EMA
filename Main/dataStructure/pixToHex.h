#ifndef SIM_PIX2HEX
#define SIM_PIX2HEX 1

class pixToHex
{
public:
    pixToHex(const unsigned int, const unsigned int, const double);

    //See dataStructure.cpp for why this exists
      //Populate the guess grid
    void populate(const std::vector<std::vector<Hex*>>* const);

    std::vector<unsigned int> hexOffsetCord(const unsigned int x, const unsigned int y) const;

private:
    double guessBinWidth;
    double guessBinHeight;

    std::vector< std::vector< std::vector<Hex*> >> guessGrid;
};

#endif
