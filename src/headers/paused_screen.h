#ifndef PAUSED_SCREEN_H
#define PAUSED_SCREEN_H

#include "raylib.h"
#include "screen.h"

class PausedScreen : Screen
{
    public:
    PausedScreen();
    ~PausedScreen();
    static void Update();
    static void Draw();
    const static std::string GetTitleText() { return "PAUSED"; }
};

#endif