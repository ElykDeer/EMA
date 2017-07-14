// "Walk Of Life" Data Structure Test
//Only ever include the data structure - insures only registered plugins work
#include "dataStructure.h"
#include "ThreadManager.h"
#include <random>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

void init(Bin& bin, ostream& os = cout);
void graphics(const Bin* const bin, const ThreadManager* const manager);

int main()
{
    //Create Bin
    Bin bin(500, 500, 5);

    init(bin); //Initialize the content of the bin

    //This is the multithreading a thread for each for
     //updating the hexes
     //updating the entities
     //Timing the update cycle and adjusting resolution
    ThreadManager manager(bin);

    //Start drawing the screen, in a seperate thread
    manager.startGraphics(&graphics);

    //Will "endlessly" update the map (spawns and updates the described threads)
    manager.startUpdatingMap();

    manager.wait();
}


void init(Bin& bin, ostream& os)
{
    os << "INIT: Initializing Map...\n";

    //Random number stuff
    random_device seed;
    mt19937 gen(seed());

    //Make two generators for generating entities in random locations
    uniform_real_distribution<double> randRangeWidth (0.0, bin.getWidth() );
    uniform_real_distribution<double> randRangeHeight(0.0, bin.getHeight());

    int numFlowers = 100000;
    os << "INIT: Generating " << numFlowers << " flowers\n";
    for(int numOfNodes = 0; numOfNodes < numFlowers; ++numOfNodes)
    {
        bin.insert(new Flower(randRangeWidth(gen), randRangeHeight(gen)));
    }
    int numDoggies = 100000;
    os << "INIT: Generating " << numDoggies << " dogs\n";
    for(int numOfNodes = 0; numOfNodes < numDoggies; ++numOfNodes)
    {
        bin.insert(new Dog(randRangeWidth(gen), randRangeHeight(gen)));
    }

    os << "INIT: Done!\n\n";
}

void graphics(const Bin* const bin, const ThreadManager* const manager)
{
    string spin = "|\\-/";
    while (1)
        for (int i = 0; i < 4; ++i)
        {
            //Build print statement
            ostringstream output;
            output << "Resolution: " << manager->getResolution();
            output << "; Speed: " << manager->getSpeed();
            output << "; Tick Count: " << manager->getTick();
            output << "; entityCount: " << bin->count() << " " << spin[i];

            //Print it
            cout << output.str();
            cout.flush();

            //Delay for the spinner
            manager->sleep(75000000);  //Spin lock hovered around 30%

            //Refreash/clear screen
            for (size_t t = 0; t < output.str().size(); ++t)
                cout << "\b"; //clear last character
        }
}
