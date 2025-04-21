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
    Button button1 = {GetCenteredPosition(buttonSize), buttonSize, "CONTINUE"};
    Button button2 = {GetCenteredPosition(buttonSize, {0, buffer + buttonSize.y}), buttonSize, "BACK TO MAIN MENU"};
};

#endif