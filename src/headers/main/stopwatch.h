#ifndef STOPWATCH_H
#define STOPWATCH_H

#include "../raylib/raylib.h"
#include <functional>
#include <string>

class Stopwatch
{
    public:
    Stopwatch(bool autoStart = false);
    ~Stopwatch();
    float startTime;
    bool active;
    float stopwatchTime;
    void Start();
    void Stop();
    void Update();
    float GetStopwatchTime();
};

#endif