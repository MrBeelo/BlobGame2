#ifndef DEATH_SCREEN_H
#define DEATH_SCREEN_H

#include "../raylib/raylib.h"
#include "screen.h"

class DeathScreen : Screen
{
    public:
    DeathScreen();
    ~DeathScreen();
    void Update() override;
    void Draw() override;
    std::string GetTitleText() const override { return "YOU DIED"; }
    const char *buttonText1 = "RESTART";
    const char *buttonText2 = "LEAVE";
    Vector2 buttonSize1 = Button::CalculateSizeDefault(buttonText1);
    Vector2 buttonSize2 = Button::CalculateSizeDefault(buttonText2);
    Button button1 = {GetCenteredPosition(buttonSize1), buttonSize1, buttonText1};
    Button button2 = {GetCenteredPosition(buttonSize2, {0, buffer + buttonSize2.y}), buttonSize2, buttonText2};
};

#endif