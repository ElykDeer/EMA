#ifndef SIM_HEX
#define SIM_HEX 1

class Hex
{
public:
    //Give it the matrix coordinates, and it will generate pixel coordinates
    Hex(const unsigned int x, const unsigned int y, const double hexRadius);

    void update();

    unsigned int getX() const;

    unsigned int getY() const;

    unsigned int getCol() const;

    unsigned int getRow() const;

private:
    // X/Y Locations
    const unsigned int x;
    const unsigned int y;
    const double hexRadius;

    //Where in the grid that it is located
    const unsigned int col;
    const unsigned int row;
};

#endif
