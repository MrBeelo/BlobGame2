#ifndef PAUSED_SCREEN_H
#define PAUSED_SCREEN_H

#include "../raylib/raylib.h"
#include "screen.h"

class PausedScreen : Screen
{
    public:
    PausedScreen();
    ~PausedScreen();
    void Update() override;
    void Draw() override;
    std::string GetTitleText() const override { return "PAUSED"; }
};

#endif