// "Walk Of Life" Data Structure Test
//Only ever include the data structure - insures only registered plugins work
#include "dataStructure.h"
#include <random>
#include <iostream>
using namespace std;

int main()
{
    ////////////////////////////////////////////////////////////////////////////
    cout << "/////////////////////// byType tests ///////////////////////\n";
    byType bin;

    //Random number stuff
    random_device seed;
    mt19937 gen(seed());
    uniform_real_distribution<double> randRange(0.0, 500.0);

    //Make 100 random dogs and flowers
    for(int numOfNodes = 0; numOfNodes < 100; ++numOfNodes)
    {
        bin.insert(new Flower(randRange(gen), randRange(gen)));
        bin.insert(new Dog(randRange(gen), randRange(gen)));
    }

    //Make every dog bark
    cout << "\nDoggie Chior:\n";
    for(const Dog& dog : bin.getAllOfType<Dog>())
        dog.bark();

    //Change somethings about every flower
    for(Flower& flower : bin.getAllOfType<Flower>())
    {
        flower.thingy = 1;
        flower.otherThingy();
        bin.remove(&flower);
    }

    //Check all flowers
    cout << "\nFlower values:\n";
    for(const Flower& flower : bin.getAllOfType<Flower>())
    {
        cout << flower.thingy << " ";
        cout << flower.thingy2 << " ";
    }
    cout << endl;

    ////////////////////////////////////////////////////////////////////////////
    cout << "/////////////////////// byLocal tests ///////////////////////\n";
    byLocal binl(500, 500, 50);

    Flower* myHeapFlower = new Flower(100, 100);
    binl.insert(myHeapFlower);
    //binl.remove(myHeapFlower);

    //Make 100 random dogs and flowers
    for(int numOfNodes = 0; numOfNodes < 100; ++numOfNodes)
    {
        binl.insert(new Flower(randRange(gen), randRange(gen)));
        binl.insert(new Dog(randRange(gen), randRange(gen)));
    }

    auto thingything = binl.getNear(myHeapFlower);
    cout << "Nearby flowers: " << thingything.size() << endl;

    ////////////////////////////////////////////////////////////////////////////
    cout << "/////////////////////// Bin tests ///////////////////////\n";
    cout << "byType tests:\n";
    Bin theBin(500, 500, 50);
    //Make 100 random dogs and flowers
    for(int numOfNodes = 0; numOfNodes < 100; ++numOfNodes)
    {
        theBin.insert(new Flower(randRange(gen), randRange(gen)));
        theBin.insert(new Dog(randRange(gen), randRange(gen)));
    }

    //Make every dog bark
    cout << "Doggie Chior:\n";
    for(const Dog& dog : theBin.getAllOfType<Dog>())
        dog.bark();

    //Change somethings about every flower
    for(Flower& flower : theBin.getAllOfType<Flower>())
    {
        flower.thingy = 1;
        flower.otherThingy();
        //theBin.remove(&flower);
    }

    //Check all flowers
    cout << "\nFlower values:\n";
    for(const Flower& flower : theBin.getAllOfType<Flower>())
    {
        cout << flower.thingy << " ";
        cout << flower.thingy2 << " ";
    }
    cout << endl;

    cout << "\nbyLocal tests:\n";

    myHeapFlower = new Flower(100, 100);
    theBin.insert(myHeapFlower);
    //theBin.remove(myHeapFlower);

    //Make 100 random dogs and flowers
    for(int numOfNodes = 0; numOfNodes < 100; ++numOfNodes)
    {
        theBin.insert(new Flower(randRange(gen), randRange(gen)));
        theBin.insert(new Dog(randRange(gen), randRange(gen)));
    }

    thingything = theBin.getNear(myHeapFlower);
    cout << "Nearby flowers: " << thingything.size() << endl;
}
