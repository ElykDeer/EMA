// "Walk Of Life" Data Structure Test
//Only ever include the data structure - insures only registered plugins work
#include "dataStructure.h"
#include "ThreadManager.h"
#include "Graphics.h"
#include <random>
#include <iostream>
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

    const unsigned int numFlowers = 500;
    os << "INIT: Generating " << numFlowers << " flowers\n";
    vector<Flower>* flowerBucket = new vector<Flower>(numFlowers, Flower(randRangeWidth(gen), randRangeHeight(gen))); //Make space
    for(unsigned int numOfNodes = 0; numOfNodes < numFlowers; ++numOfNodes)
    {
        bin.insert(&(*flowerBucket)[numOfNodes]);
    }
    const unsigned int numDoggies = 500;
    os << "INIT: Generating " << numDoggies << " dogs\n";
    vector<Dog>* dogBucket = new vector<Dog>(numDoggies, Dog(randRangeWidth(gen), randRangeHeight(gen)));  //Make space
    for(unsigned int numOfNodes = 0; numOfNodes < numDoggies; ++numOfNodes)
    {
        bin.insert(&(*dogBucket)[numOfNodes]);
    }

    os << "INIT: Done!\n\n";
}

void graphics(const Bin* const bin, const ThreadManager* const manager)
{
    Graphics graphic(bin, manager);
    graphic.spin();
}
