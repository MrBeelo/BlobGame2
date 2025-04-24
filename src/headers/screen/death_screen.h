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
    Button button1 = {0, "RESTART"};
    Button button2 = {1, "LEAVE"};
};

#endif