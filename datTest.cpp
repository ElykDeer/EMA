// "Walk Of Life" Data Structure Test

#include "datTestTypes.h"
#include "dataStructure.h"
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

    for(int numOfNodes = 0; numOfNodes < 100; ++numOfNodes)
    {
        bin.insert(new Flower(randRange(gen), randRange(gen)));
        bin.insert(new Dog(randRange(gen), randRange(gen)));
    }

    for(const auto& dog : bin.getAllOfTyp<Dog>())
        static_cast<const Dog*>(dog.first)->bark();

    //auto thing = bin.getAllOfType<Dog>();

    for(const auto& dog : bin.getAllOfType<Dog>())
        dog.bark();
}
