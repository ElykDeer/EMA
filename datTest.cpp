// "Walk Of Life" Data Structure Test
#include "dataStructure.h" // no need to include our testTypes since the main on needs ours
#include <random>
#include <iostream>
using namespace std;

int main()
{
    //Bin bin;
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
    }

    //Check all flowers
    cout << "\nFlower values:\n";
    for(const Flower& flower : bin.getAllOfType<Flower>())
    {
        cout << flower.thingy << " ";
        cout << flower.thingy2 << " ";
    }
    cout << endl;
}
