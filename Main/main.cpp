// "Walk Of Life" Data Structure Test
//Only ever include the data structure - insures only registered plugins work
#include "dataStructure.h"
#include <random>
#include <iostream>
using namespace std;

int main()
{
    //Random number stuff
    random_device seed;
    mt19937 gen(seed());
    uniform_real_distribution<double> randRange(0.0, 500.0);

    cout << "/////////////////////// Bin tests ///////////////////////\n";
    Bin bin(500, 500, 50);
    cout << "byType tests:\n";

    //Make 100 random dogs and flowers
    for(int numOfNodes = 0; numOfNodes < 100; ++numOfNodes)
    {
        bin.insert(new Flower(randRange(gen), randRange(gen)));
        bin.insert(new Dog(randRange(gen), randRange(gen)));
    }

    //Make every dog bark
    cout << "Doggie Chior:\n";
    for(const Dog& dog : bin.getAllOfType<Dog>())
        dog.bark();

    //Change somethings about every flower
    for(Flower& flower : bin.getAllOfType<Flower>())
    {
        flower.thingy = 1;
        flower.otherThingy();
        //bin.remove(&flower);
    }

    //Check all flowers
    cout << "\nFlower values:\n";
    for(const Flower& flower : bin.getAllOfType<Flower>())
    {
        cout << flower.thingy << " ";
        cout << flower.thingy2 << " ";
    }
    cout << endl;

    cout << "\nbyLocal tests:\n";

    Flower* myHeapFlower = new Flower(100, 100);
    bin.insert(myHeapFlower);
    //bin.remove(myHeapFlower);

    //Make more random dogs and flowers
    for(int numOfNodes = 0; numOfNodes < 1000; ++numOfNodes)
    {
        bin.insert(new Flower(randRange(gen), randRange(gen)));
        bin.insert(new Dog(randRange(gen), randRange(gen)));
    }

    auto thingything = bin.getNear(myHeapFlower);
    cout << "Nearby flowers: " << thingything.size() << endl;

    cout << "/////////////////////// Everything tests ///////////////////////\n";
    int entityCount = 0;
    for (auto& thing : bin.getAll())
        ++entityCount;
    cout << "There are " << entityCount << " entities in the bin!\n";
    cout << "Call updateEntities():\n";
    bin.updateEntities();

    cout << "All done!\n";
}
