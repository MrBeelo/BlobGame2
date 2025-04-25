#ifndef TIMER_H
#define TIMER_H

#include "../raylib/raylib.h"
#include <functional>
#include <string>

class Timer
{
    public:
    Timer(float duration, bool repeat = false, bool autoStart = false, std::function<void()> method = nullptr);
    ~Timer();
    float duration;
    float startTime;
    bool active;
    bool repeat;
    std::function<void()> method;
    void Activate();
    void ActivateImmediately();
    void Deactivate();
    void ForceDeactivate();
    void Update();
};

#endif