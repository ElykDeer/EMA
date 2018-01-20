#include <string>
#include <iostream>
using namespace std;

class Foo
{
public:
    Foo() {}

    void doNothing() {}
    virtual void doNoMore() {}
private:
    int a;
    string b;
};



void Bin::save()
{


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

int main()
{

}
if (typeid(*&entity).hash_code() == typeid(Flower).hash_code())
{
    file << " datTestFlower ";
    file.write((char *)(&entity), sizeof(Flower));
}
else if (typeid(*&entity).hash_code() == typeid(Bunny).hash_code())
{
    file << " datTestBunny ";
    file.write((char *)(&entity), sizeof(Bunny));
}

#endif



#ifdef LOADHEADERS

//Read in identifier
string entityType = "";
while (file >> entityType)
{
    //cerr << '.';

    //read the space seperator
    file.read(&byte, 1);

    if (entityType == "datTestFlower")
    {
        cerr << "1\n";
        Flower* entityP = new Flower(0,0,this);
        cerr << "2\n";
        auto* stuff = &typeid(*entityP);
        std::cerr << stuff << std::endl;
        file.read((char *)entityP, sizeof(Flower));
        cerr << "3\n";
        // std::cerr << &typeid(*entityP) << std::endl;
        entityP->bin = this;
        cerr << "4\n";
        insert(entityP);
        cerr << "5\n";
    }
    else if (entityType == "datTestBunny")
    {
        Bunny* entityP = new Bunny(0,0,this);
        file.read((char *)entityP, sizeof(Bunny));
        entityP->bin = this;
        insert(entityP);
    }
    else
    {
        cerr << "Something went very wrong: " << entityType << ".\n";
    }
}


#endif
