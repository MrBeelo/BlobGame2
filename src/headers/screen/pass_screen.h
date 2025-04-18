#ifndef PASS_SCREEN_H
#define PASS_SCREEN_H

#include "../raylib/raylib.h"
#include "screen.h"

class PassScreen : Screen
{
    public:
    PassScreen();
    ~PassScreen();
    void Update() override;
    void Draw() override;
    std::string GetTitleText() const override { return "LEVEL COMPLETE"; }
};

#endif