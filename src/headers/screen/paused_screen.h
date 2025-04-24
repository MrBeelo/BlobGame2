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
    const char *buttonText1 = "CONTINUE";
    const char *buttonText2 = "BACK TO MAIN MENU";
    Button button1 = {0, "CONTINUE"};
    Button button2 = {1, "BACK TO MAIN MENU"};
};

#endif