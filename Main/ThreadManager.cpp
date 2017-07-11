#include "ThreadManager.h"

#include <iostream>

using namespace std;
using namespace std::chrono;

typedef std::chrono::high_resolution_clock Clock;

ThreadManager::ThreadManager(Bin& bin) : bin(&bin), resolution(1) {}

void ThreadManager::startGraphics( void (*graphics)(const Bin* const, const ThreadManager* const) ) const
{
    //Just let the graphics do their thing
    thread graphicsThread(graphics, bin, this);
    graphicsThread.detach();
}

unsigned int ThreadManager::getResolution() const
{
    return resolution;
}

unsigned int ThreadManager::getTick() const
{
    return tick;
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

void ThreadManager::startUpdatingMap()
{
    //continueUpdatingMap(); // - private function
    //Alternativly, if I want more in main:
    //Start thread, let it go, get back to main
    thread updateMapThread(&ThreadManager::continueUpdatingMap, this);
    updateMapThread.detach();
}

void ThreadManager::continueUpdatingMap()
{
    //lock my lock - own it - doesn't actually matter?
    originalLock.lock();

    //Spawn two threads for maps and entities
    thread mapThread(&ThreadManager::map, this);
    thread entThread(&ThreadManager::entities, this);

    while (1)
    {
        //Start Threads
        ready = true;
        sync.notify_all();
        originalLock.unlock();

        //Start timing
        t1 = Clock::now();
        while (!mapBool || !entBool) {}
        t2 = Clock::now();

        //Reset things
        mapBool = entBool = false;
        ready = false;
        originalLock.lock();

        //if (duration_cast<duration<double>>(t2 - t1) >= seconds(1))
        if ((t2 - t1).count() >= system_clock::to_time_t(t1 + nanoseconds(1000000000/speed)))
            //If this has taken one second or more, double the resolution
            resolution *= 2;
        else
            //timeout the rest of the second
            while ((t2 - t1) < nanoseconds(1000000000/speed))
                t2 = Clock::now();

        ++tick; //The tick has completed

        //Test, need to see what this is so I don't have to cast
        //cerr << "TIMER: " << duration_cast<duration<double>>t2 - t1).count() << endl<< endl<< endl<< endl<< endl;
    }
}


void ThreadManager::map()
{
    while(1)
    {
        //Wait to be notified to continue
        unique_lock<std::mutex> lock(originalLock);
        while (!ready)
            sync.wait(lock);
        sync.notify_all(); //Just incase

        bin->updateHexes(resolution);

        //Notify controling thread
        mapBool = true;
    }
}

void ThreadManager::entities()
{
    while(1)
    {
        //Wait to be notified to continue
        unique_lock<std::mutex> lock(originalLock);
        while (!ready)
            sync.wait(lock);
        sync.notify_all(); //Just incase

        bin->updateEntities(resolution);

        //Notify controling thread
        entBool = true;
    }
}
