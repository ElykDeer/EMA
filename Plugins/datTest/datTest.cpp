os << "INIT: Initializing Map...\n";

//Random number stuff
random_device seed;
mt19937 gen(seed());

//Make two generators for generating entities in random locations
uniform_real_distribution<double> randRangeWidth (0.0, bin.getWidth() );
uniform_real_distribution<double> randRangeHeight(0.0, bin.getHeight());

const unsigned int numFlowers = 5000;
os << "INIT: Generating " << numFlowers << " flowers\n";
for(unsigned int numOfNodes = 0; numOfNodes < numFlowers; ++numOfNodes)
{
    bin.insert(new Flower(randRangeWidth(gen), randRangeHeight(gen), &bin));
}
const unsigned int numBuns = 500;
os << "INIT: Generating " << numBuns << " bunnies\n";
for(unsigned int numOfNodes = 0; numOfNodes < numBuns; ++numOfNodes)
{
    bin.insert(new Bunny(randRangeWidth(gen), randRangeHeight(gen), &bin));
}

os << "INIT: Done!\n\n";
