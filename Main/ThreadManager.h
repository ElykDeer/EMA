#ifndef SIM_MANAGER
#define SIM_MANAGER 1

#include "dataStructure.h"

#include <chrono>  /*Timing*/
#include <thread>
#include <cmath>

class ThreadManager
{
public:
    std::chrono::duration<double> timeeee;
    std::chrono::duration<double> lasTimeeee;

    ThreadManager(Bin& bin);

    void startGraphics( void (*graphics)(Bin* const, ThreadManager* const) );
    void startUpdatingMap();

    //Template to start any thread, detached
    template <typename... Args, typename F>
    void startDetachedThread(const F& func, Args &&... args)
    {
        std::thread newThread(func, args...);
        newThread.detach();
    }

    void waitForThreadsEnd(); //Wait for the graphics and map threads to close

    void sleep(unsigned long long int nanosecs) const;

    void pause();
    void resume();
    bool getPauseState() const;

    void setSpeed(const unsigned int newSpeed);
    unsigned int getSpeed() const;
    unsigned int getResolution() const;
    unsigned int getTick() const;

    void kill();

private:
    //Helper functions to allow these to be seperate threads
    void continueUpdatingMap();
    void map();
    void entities();

    Bin* bin;
    volatile double resolution = 1;  //how fine we is calculating
    volatile unsigned long long int tick = 0; //the time, in seconds, of the game
    volatile double speed = 0;  //The fast forwarding capability
    std::chrono::system_clock::time_point t1, t2;
    //pasuing
    volatile double lastSpeed = 1;
    volatile bool paused = true;

    //Lock stuff - for syncronization:
    volatile bool nextLoop = false;
    volatile bool mapBool = false;
    volatile bool entBool = false;

    std::thread* updateMapThread = nullptr;
    std::thread* graphicsThread = nullptr;

    volatile bool running = true; //Whether the game is running
};

#endif
