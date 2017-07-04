#include <iostream> //Temporary (for testing)

Bin::pixToHex::pixToHex(const unsigned int width,
                 const unsigned int height,
                 const double hexRadius)
:
  guessBinWidth(hexRadius/4),
  guessBinHeight( (sqrt(3)*hexRadius) /4),
  guessGrid(ceil(width/guessBinWidth), vector<vector<Hex*>>( ceil(height/guessBinHeight) )) {}

//Populate the guess grid
void Bin::pixToHex::populate(const vector<vector<Hex*>>* const binP)
{
    cerr << "#################################################\n";
    cerr << "# guessBinWidth: " << guessBinWidth << ",\tguessBinHeight:\t" << guessBinHeight << "\t#" << endl;
    cerr << "# guessBinsRows: " << guessGrid[0].size() << ",\tguessBinsCols:\t" << guessGrid.size() << "\t#" << endl;
    cerr << "# Bin's Rows:\t " << (*binP)[0].size() << ",\tBin's Cols:\t" << (*binP).size() << "\t#" << endl;
    cerr << "# max X:\t " << guessBinWidth*guessGrid.size() << ",\tmax Y:\t\t" << guessBinHeight*guessGrid[0].size() << "\t#" << endl;
    cerr << "#################################################\n";

    //Set up the guessGrid:
    //For each row
    int leftGridX = 0;
    int leftGridY = 0;

    int rightGridX = 1;
    int rightGridY = 0;

    for (size_t row = 0; row < guessGrid[0].size(); row++)
    {
       //For each collumn
       unsigned int nextDouble;
       if (row&1) //odd row
           nextDouble = 4;
       else //even rows
           nextDouble = 5;

       for (size_t col = 0; col < guessGrid.size(); col++)
       {
           if (col == nextDouble) //If an odd row
           {
               guessGrid[col][row].push_back((*binP)[leftGridX][leftGridY]);
               guessGrid[col][row].push_back((*binP)[rightGridX][rightGridY]);

               if (guessGrid[col][row].size()>2)
                     exit(1);
               if (guessGrid[col][row].size()==0)
                     exit(1);

               //set next double
               if (nextDouble&1) //if next double if odd
                   nextDouble += 5;
               else //is even
                   nextDouble += 7;

               //Set next pairing at that double
               leftGridX++;
               rightGridX++;
           }
           else
               guessGrid[col][row].push_back((*binP)[leftGridX][leftGridY]);
       }
       //reset x of the doubles
       leftGridX = 0;
       rightGridX = 1;

       //Adjust the y of the doubles
       if ((row+1) % 4 == 0)
           leftGridY++;
       else if ((row+1) % 2 == 0)
           rightGridY++;
    }
}

vector<unsigned int> Bin::pixToHex::hexOffsetCord(const unsigned int x, const unsigned int y) const
{

    //Generate the guess
    const unsigned int guessBinX = x/guessBinWidth;
    const unsigned int guessBinY = y/guessBinHeight;

    //Grab Guess
    const vector<Hex*>& guessBin = guessGrid[guessBinX][guessBinY];

    //71% chance for there to only be one thing to do..
    if (guessBin.size() == 1)
        return {guessBin[0]->getCol(), guessBin[0]->getRow()};

    //Calculate distances
    double dist1 =
    sqrt(pow((guessBin[0]->getX() - x), 2) + pow((guessBin[0]->getY() - y), 2));
    double dist2 =
    sqrt(pow((guessBin[1]->getX() - x), 2) + pow((guessBin[1]->getY() - y), 2));

    //If closer to one, return one
    if(dist1 < dist2)
        return {guessBin[0]->getCol(), guessBin[0]->getRow()};

    //Otherwise return the other
    return {guessBin[1]->getCol(), guessBin[1]->getRow()};
}
