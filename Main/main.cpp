// "Walk Of Life" Data Structure Test

#include "dataStructure.h"
#include "ThreadManager.h"
#include "Graphics.h"
#include <random>
#include <iostream>
using namespace std;

//Define the init function, built by the compiler:
#include "../Compiler/init.cpp"

void graphics(Bin* const bin, ThreadManager* const manager);

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

    manager.waitForThreadsEnd();

    cout << endl; //For neatness
}

void graphics(Bin* const bin, ThreadManager* const manager)
{
    Graphics graphic(bin, manager);
    graphic.eventLoop();
}
