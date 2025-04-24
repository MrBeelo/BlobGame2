#include "../headers/main/timer.h"

Timer::Timer(float duration, bool repeat, bool autoStart, std::function<void()> method)
{
    this->duration = duration;
    this->startTime = 0;
    this->active = false;
    this->repeat = repeat;
    this->method = method;
    if(autoStart) Activate();
}

Timer::~Timer() {}

void Timer::Activate()
{
    this->active = true;
    this->startTime = GetTime();
}

void Timer::Deactivate()
{
    ForceDeactivate();
    if(this->repeat) Activate();
}

void Timer::ForceDeactivate()
{
    this->active = false;
    this->startTime = 0;
}

void Timer::Update()
{
    if(this->active)
    {
        if(GetTime() - this->startTime >= this->duration)
        {
            if(this->method != nullptr)
            {
                method();
            }
            
            Deactivate();
        }
    }
}