#include "../headers/main/stopwatch.h"

Stopwatch::Stopwatch(bool autoStart) {
    stopwatchTime = 0;
    if(autoStart) Start();
}

Stopwatch::~Stopwatch() {}

void Stopwatch::Start()
{
    this->active = true;
    this->startTime = GetTime();
}

void Stopwatch::Stop()
{
    this->active = false;
    this->startTime = 0;
}

void Stopwatch::Update()
{
    if(active) stopwatchTime = GetTime() - startTime;
}

float Stopwatch::GetStopwatchTime()
{
    return stopwatchTime;
}

