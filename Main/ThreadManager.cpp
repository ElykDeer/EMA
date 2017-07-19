#include "ThreadManager.h"

using namespace std;
using namespace std::chrono;
typedef std::chrono::high_resolution_clock Clock;

ThreadManager::ThreadManager(Bin& bin) : bin(&bin) {}

void ThreadManager::startGraphics( void (*graphics)(Bin* const, ThreadManager* const) )
{
    //Just let the graphics do their thing
    graphicsThread = new thread(graphics, bin, this);
}

void ThreadManager::startUpdatingMap()
{
    //continueUpdatingMap(); // - private function
    //Alternativly, if I want more in main:
    //Start thread, let it go, get back to main
    updateMapThread = new thread(&ThreadManager::continueUpdatingMap, this);
}

void ThreadManager::waitForThreadsEnd()
{
    if (updateMapThread)
        updateMapThread->join();
    if (graphicsThread)
        graphicsThread->join();
}

void ThreadManager::sleep(unsigned long long int nanosecs) const
{
    this_thread::sleep_for(nanoseconds(nanosecs));
}

void ThreadManager::pause()
{
    paused = true;
}

void ThreadManager::resume()
{
    paused = false;
}

void ThreadManager::setSpeed(const unsigned int newSpeed)
{
    if (newSpeed > 0)
        speed = newSpeed;
}

unsigned int ThreadManager::getSpeed() const
{
    return speed;
}

unsigned int ThreadManager::getResolution() const
{
    return resolution;
}

unsigned int ThreadManager::getTick() const
{
    return tick;
}

void ThreadManager::continueUpdatingMap()
{
    //Spawn two threads for maps and entities
    thread mapThread(&ThreadManager::map, this);
    thread entThread(&ThreadManager::entities, this);

    while (running)
    {
        //Sleep == 0; means paused. Sleep for 1/20th a second and try again
        if (paused)
        {
            sleep(50000000);
            continue;
        }

        //Start Threads
        nextLoop = true;

        //Start timing
        t1 = Clock::now();
        while (!mapBool || !entBool)
        {
            if (!running) //If while we were waiting, the game closes...
            {
                mapThread.join();
                entThread.join();

                return;
            }
        }
        t2 = Clock::now();

        //Reset things
        mapBool = entBool = false;
        nextLoop = false;

        lasTimeeee = timeeee;
        timeeee = duration_cast<duration<double>>(t2 - t1);

        //if (duration_cast<duration<double>>(t2 - t1) >= seconds(1))
        if ((t2 - t1).count() >= system_clock::to_time_t(t1 + nanoseconds(1000000000/speed)))
            //If this has taken one second or more, double the resolution
            resolution *= 2;
        else
            //timeout the rest of the second
            this_thread::sleep_for(nanoseconds(1000000000/speed) - (t2 - t1));

        //If the resolution can be reduced, do it
          //Resolution greater than one,
          //runtime less than 1/3 a period - wiggle room
        if (resolution > 1 && (t2 - t1).count() < system_clock::to_time_t(t1 + nanoseconds((1000000000/speed)/3)))
            resolution /= 2;

            //Uses about 2x more CPU time:
              //while ((t2 - t1) < nanoseconds(1000000000/speed))
              //    t2 = Clock::now();

        tick += resolution; //The tick has completed, simulating "res" # O ticks
    }

    mapThread.join();
    entThread.join();
}


void ThreadManager::map()
{
    while(running)
    {
        //Wait to be notified to continue
        while (!nextLoop || mapBool)
            if (!running)
                return;

        bin->updateHexes(resolution);

        //Notify controling thread
        mapBool = true;
    }
}

void ThreadManager::entities()
{
    while(running)
    {
        //Wait to be notified to continue
        while (!nextLoop || entBool)
            if (!running)
                return;

        bin->updateEntities(resolution);

        //Notify controling thread
        entBool = true;
    }
}

void ThreadManager::kill()
{
  running = false;
}
