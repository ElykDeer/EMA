class Hex : public HexInternals
{
public:
    //Give it the matrix coordinates, and it will generate pixel coordinates
    Hex(const unsigned int col, const unsigned int row, const double hexRadius);

    virtual void update(unsigned int resolution) override;
//private:

};
