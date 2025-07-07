#include "Clock.hpp"


void le::Clock::start()
{
    if (!running) 
    {
        startTime = ClockType::now();

        if (paused) 
        {
            pauseDuration += startTime - pauseStart;

            paused = false;
        }

        running = true;
    }
}

void le::Clock::stop()
{
    if (running) 
    {
        stopTime = ClockType::now();

        running = false;
    }
}


void le::Clock::pause()
{
    if (running && !paused) 
    {
        pauseStart = ClockType::now();

        paused = true;

        running = false;
    }
}

void le::Clock::reset()
{
    running = false;

    paused = false;

    pauseDuration = std::chrono::duration<double>::zero();

    startTime = ClockType::now();
}


float le::Clock::getTime() const
{
    if (running) 
    {
        return std::chrono::duration<float>(ClockType::now() - startTime - pauseDuration).count();
    }
    else if (paused) 
    {
        return std::chrono::duration<float>(pauseStart - startTime - pauseDuration).count();
    }
    else 
    {
        return std::chrono::duration<float>(stopTime - startTime - pauseDuration).count();
    }
}
