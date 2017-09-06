#include <iostream> /* For debug output */
#include <fstream>  /* For saving */
#include <sstream>  /* For building strings */
#include <iomanip>  /* For time/date */
#include <chrono>  /*Timing*/


void Bin::save()
{
    /*//Create new save file:
    time_t now = chrono::system_clock::to_time_t(chrono::system_clock::now());
    ostringstream saveFilename;
    ostringstream dateRaw;
    dateRaw << put_time(localtime(&now), "%F %T");
    ostringstream dateProc;

    for (char character : dateRaw.str())
    {
        if (character == ':')
            dateProc << '-';

        else if (character == ' ')
            dateProc << '-';

        else
            dateProc << character;
    }
    saveFilename << "Saves/";
    saveFilename << dateProc.str(); //Current time as string
    saveFilename << ".dat";*/

    //For now, actually just use one default name:
    ostringstream saveFilename;
    saveFilename << "Saves/Turtle.dat";

    //Open the save file
    ofstream file(saveFilename.str());
    if (!file)
    {
        cerr << "Could not create file: \"" << saveFilename.str() << "\"." << endl;
        return;
    }

    /* <Write Data> */

    //Super basic data
    file << width << ' ' << height << ' ' << hexRadius << ' ';

    //Save hex data
    for (vector<Hex*>& hexV : hexes)
        for (Hex* hexP : hexV)
            file.write((char *)hexP, sizeof(Hex));

    //Save entites
    for (Entity& entity : getAll())
    {
        #define SAVEHEADERS 1
        #include "../../Compiler/EntityHeaders.cpp"
        #undef SAVEHEADERS
    }

    /* </Write Data> */

    file.close();
}

void Bin::load(string filename)
{
    //For now, actually just use one default name:
    filename = "Saves/Turtle.dat";

    //Open the save file
    ifstream file(filename);
    if (!file)
    {
        cerr << "File failed to open.\n";
        return;
    }

    /* <Delete old map and entites> */
    //clear all data, deconstructor:
    //Cycle through all Entities/Enticaps and delete them
    for(auto& outerPair : byTypeMap) //Every Different type
        for(auto& innerPair : outerPair.second) //Every single element
            delete innerPair.second; //Delete enticaps, since they delete the entity

    for(auto& col : hexes)
        for(Hex* hex : col)
            delete hex;

    byTypeMap.clear();
    hexes.clear();
    //All heap elements are deleted
    /* </Delete old map and entites> */

    /* <Load Data> */

    //Super basics
    file >> width >> height >> hexRadius;

    //Generate new map
    hexes = std::move(vector<vector<Hex*>>(ceil( (width+(hexRadius*0.5)) / (1.5*hexRadius)), vector<Hex*>( ceil((height+hexRadius) / (sqrt(3)*hexRadius)), nullptr )));

    //Populate hex grid:
    for (size_t col = 0; col < hexes.size(); col++)
      for (size_t row = 0; row < hexes[col].size(); row++)
          hexes[col][row] = new Hex(col, row, hexRadius);

    //read the space seperator
    char byte = ' ';
    file.read(&byte, 1);

    //Load hex data into those new hexes
    for (vector<Hex*>& hexV : hexes)
        for (Hex* hexP : hexV)
        {
            file.read((char *)hexP, sizeof(Hex));

            //cout << hexP->byTypeMap.size() << endl;
            //cout << hexP->nearBy.size() << endl;

            //Reset old variables
            auto* newByTypeMap = new std::map< const std::size_t, std::map<Entity* const, Enticap*> >;
            auto* newByNear = new std::map<const unsigned int, std::vector<std::map< const std::size_t, std::map<Entity* const, Enticap*>>* >>;

            for (size_t byteCount = 0; byteCount < sizeof(*newByTypeMap); ++byteCount)
            {
                *((char *)&hexP->nearBy + byteCount) = *( (char*)newByTypeMap + byteCount);
            }
            for (size_t byteCount = 0; byteCount < sizeof(*newByNear); ++byteCount)
            {
                *((char *)&hexP->nearBy + byteCount) = *( (char*)newByNear + byteCount);
            }

        }

    //Now that hexes are loaded, the  hex cords can be set properly
    hexCords.postInit(width, height, hexRadius);
    hexCords.populate(&hexes);

    //Load/insert entites
    #define LOADHEADERS 1
    #include "../../Compiler/EntityHeaders.cpp"
    #undef LOADHEADERS


    /* </Load Data> */

    file.close();

}
