#include "datTestTypes.h"
#include <iostream>
using namespace std;

//The following three things are for const testing
void Flower::otherThingy()
{
  thingy2 = 11;
}

void Dog::bark() const
{
    cout << "Bark! ";
}
