// "Walk Of Life" Data Structure Test
//Only ever include the data structure - insures only registered plugins work
#include "dataStructure.h"
#include <random>
#include <iostream>
#include <time.h>
using namespace std;

int main()
{
    //Timer stuff
    clock_t t1, t2; //Two timers

    //Random number stuff
    random_device seed;
    mt19937 gen(seed());
    uniform_real_distribution<double> randRange(0.0, 500.0);

    Bin bin(500, 500, 50);
    cout << "/////////////////////// Bin tests ///////////////////////\n";

    //Make 100 random dogs and flowers
    cout << "Insertion One (10 Entites Each); ";
    t1=clock();
    for(int numOfNodes = 0; numOfNodes < 10; ++numOfNodes)
    {
        bin.insert(new Flower(randRange(gen), randRange(gen)));
        bin.insert(new Dog(randRange(gen), randRange(gen)));
    }
    t2=clock();
    cout << "Time: " << ((double)t2-(double)t1) / CLOCKS_PER_SEC << endl;

    //Make every dog bark
    cout << "Doggie Chior:\n";
    for(const Dog& dog : bin.getAllOfType<Dog>())
        dog.bark();

    //Change somethings about every flower
    cout << "\nNon-Const Check (Flowers, 1;23):\n";
    for(Flower& flower : bin.getAllOfType<Flower>())
    {
        flower.thingy = 1;
        flower.otherThingy();
    }
    //Check all flowers
    for(const Flower& flower : bin.getAllOfType<Flower>())
        cout << flower.thingy << flower.thingy2 << " ";

    cout << "\n\nInsert myHeapFlower; ";
    Flower* myHeapFlower = new Flower(100, 100);
    t1=clock();
    bin.insert(myHeapFlower);
    t2=clock();
    cout << "Time: " << ((double)t2-(double)t1) / CLOCKS_PER_SEC << endl;
    //bin.remove(myHeapFlower);

    //Make more random dogs and flowers
    cout << "Insertion Two (2000 Entites Each); ";
    t1=clock();
    for(int numOfNodes = 0; numOfNodes < 2000; ++numOfNodes)
    {
        bin.insert(new Flower(randRange(gen), randRange(gen)));
        bin.insert(new Dog(randRange(gen), randRange(gen)));
    }
    t2=clock();
    cout << "Time: " << ((double)t2-(double)t1) / CLOCKS_PER_SEC << endl;

    cout << "\ngetAllNear(myHeapFlower, 0) test:\n";
    for(Entity& entity : bin.getAllNear(myHeapFlower, 0))
       cout << typeid(*&entity).name() << ' ';

    cout << "\ngetAllOfTypeNear<Flower>(myHeapFlower, 0) test (1;23):\n";
    for(Flower& flower : bin.getAllOfTypeNear<Flower>(myHeapFlower, 0))
        cerr << flower.thingy << flower.thingy2 << " ";

    /*
    cerr << endl;
    auto thingythingthing = bin.getAllOfTypeNear<Flower>(myHeapFlower, 0);
    cerr << (*thingythingthing).thingy << endl;
    */

    cout << "\n\ngetAll test: ";
    int entityCount = 0;
    t1=clock();
    for (Entity& thing : bin.getAll())
    {
        ++entityCount;
        thing.update();
    }
    t2=clock();
    cout << entityCount << " entities in the bin!; ";
    cout << "; Clocks: " << (t2-t1);
    cout << "; Time: " << ((double)t2-(double)t1) / CLOCKS_PER_SEC*1000 << "ms\n";

    cout << "###########################################################\n";
    cout << "# " << "Game Time vs Real Time:\n";
    cout << "# " << "Factor Acceleraton: " << 1.0 / (theTime / 1000.0) << "x" << endl;
    cout << "# " << "One Hour:   " << (theTime / 1000.0) * 60.0 << " minutes" << endl;
    cout << "# " << "One Day:    " << (theTime / 1000.0) * 60.0 * 24.0 << " minutes" << endl;
    cout << "# " << "One Year:   " << (theTime / 1000.0) * 24.0 * 365.0 << " hours (" << (theTime / 1000.0) * 365.0 << " days)" << endl;
    cout << "# " << "One Centry: " << (theTime / 1000.0) * 365.0 * 100.0 << " days (" << (theTime / 1000.0) * 100.0 << " years)" << endl;
    cout << "###########################################################\n";

    cout << "updateEntities() test: ";
    t1=clock();
    bin.updateEntities();
    t2=clock();
    cout << "; Time: " << ((double)t2-(double)t1) / CLOCKS_PER_SEC << endl;

    cout << "updateHexes() test: ";
    t1=clock();
    bin.updateHexes();
    t2=clock();
    cout << "; Time: " << ((double)t2-(double)t1) / CLOCKS_PER_SEC << endl;

    /* Hexes are only dealt with internally
    cout << "getAllHexes test: ";
    for (Hex& hex : bin.getAllHexes())
        cout << hex.getCol() << " ";*/

    cout << "\nAll done!\n";
}
