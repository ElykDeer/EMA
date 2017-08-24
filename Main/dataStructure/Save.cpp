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
        cerr << "Could not create file.\n" << saveFilename.str() << endl;
        return;
    }

    /* <Write Data> */

    //Super basic data
    file << "width: " << width << endl;
    file << "height: " << height << endl;
    file << "hexRadius: " << hexRadius <<endl;

    //Save hex data
    file << "Hexes:\n";
    for (vector<Hex*> hexV : hexes)
    {
        for (Hex* hexP : hexV)
        {
            auto hexSize = sizeof(*hexP);
            ostringstream byteStream;

            //Say which one it is
            file << hexP->getRow() << " x " << hexP->getCol() << " , " << hexSize << " : ";

            char* const byteP = reinterpret_cast<char*>(hexP);

            for (unsigned int byteCount = 0; byteCount <= hexSize; ++byteCount)
            {
                byteStream << *(byteCount + byteP);
            }
            file << byteStream.str() << endl;
        }
    }

    //Save entites
    file << "Entities:\n";
    for (Entity& entity : getAll())
    {
        Entity* entityP = &entity;
        auto entitySize = sizeof(*entityP);
        ostringstream byteStream;

        //Say which one it is
        file << entityP->getX() << " x " << entityP->getY() << " , " << entitySize << " : ";

        char* const byteP = reinterpret_cast<char*>(entityP);

        for (unsigned int byteCount = 0; byteCount <= entitySize; ++byteCount)
        {
            byteStream << *(byteCount + byteP);
        }
        file << byteStream.str() << endl;
    }

    /* </Write Data> */

    file.close();
}
//
// Bin Bin::load(string filename) : seed(), gen(seed()), chanceGen(0.0, 1.0)
// {
//     //For now, actually just use one default name:
//     ostringstream saveFilename;
//     saveFilename << "Saves/Turtle.dat";
//
//     //Open the save file
//     ifstream file(saveFilename.str());
//     if (!file)
//     {
//         cerr << "File failed to open.\n";
//         return;
//     }
//
//     /* <Load Data> */
//
//     //Super basics
//     string garbage;
//     const unsigned int width;
//     const unsigned int height;
//     const double hexRadius;
//     file >> garbage >> width >> garbage >> height >> garbage >> hexRadius;
//
//     //So now this is a copy of bin, except it doesn't have the entities it did
//     Bin workingBin(width, height, hexRadius);
//
//     //Load hex data
//
//     //Load/insert entites
//
//     /* </Load Data> */
//
//     file.close();
//     return workingBin;
// }
