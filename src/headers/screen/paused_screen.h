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
    Vector2 buttonSize1 = Button::CalculateSizeDefault(buttonText1);
    Vector2 buttonSize2 = Button::CalculateSizeDefault(buttonText2);
    Button button1 = {GetCenteredPosition(buttonSize1), buttonSize1, buttonText1};
    Button button2 = {GetCenteredPosition(buttonSize2, {0, buffer + buttonSize2.y}), buttonSize2, buttonText2};
};

#endif