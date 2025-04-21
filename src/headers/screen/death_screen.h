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
    Button button1 = {GetCenteredPosition(buttonSize), buttonSize, "RESTART"};
    Button button2 = {GetCenteredPosition(buttonSize, {0, buffer + buttonSize.y}), buttonSize, "LEAVE"};
};

#endif