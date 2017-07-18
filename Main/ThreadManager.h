#ifndef SIM_MANAGER
#define SIM_MANAGER 1

#include "dataStructure.h"

#include <chrono>  /*Timing*/
#include <thread>

class ThreadManager
{
public:
    std::chrono::duration<double> timeeee;
    std::chrono::duration<double> lasTimeeee;


    ThreadManager(Bin& bin);

    void startGraphics( void (*graphics)(const Bin* const, const ThreadManager* const) );
    void startUpdatingMap();

    void waitForThreadsEnd(); //Wait for the graphics and map threads to close

    void sleep(unsigned long long int nanosecs) const;

    void pause();
    void resume();

    void setSpeed(const unsigned int newSpeed);
    unsigned int getSpeed() const;
    unsigned int getResolution() const;
    unsigned int getTick() const;

private:
    //Helper functions to allow these to be seperate threads
    void continueUpdatingMap();
    void map();
    void entities();

    Bin* bin;
    unsigned int resolution = 1;  //how fine we is calculating
    unsigned long long int tick = 0; //the time, in seconds, of the game
    unsigned int speed = 1;  //The fast forwarding capability
    bool paused = false;
    std::chrono::system_clock::time_point t1, t2;

    //Lock stuff - for syncronization:
    bool ready = false;
    volatile bool mapBool = false;
    volatile bool entBool = false;

    std::thread* updateMapThread = nullptr;
    std::thread* graphicsThread = nullptr;
};

#endif
