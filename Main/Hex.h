#ifndef SIM_HEX
#define SIM_HEX 1

class Hex
{
public:
    //Give it the matrix coordinates, and it will generate pixel coordinates
    Hex(const unsigned int x, const unsigned int y, const double hexRadius);

    void update();

    int getX();

    int getY();

private:
    // X/Y Locations
    const int x;
    const int y;
    const double hexRadius;
};

#endif
