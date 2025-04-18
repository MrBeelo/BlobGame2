#ifndef EXIT_SCREEN_H
#define EXIT_SCREEN_H

#include "../raylib/raylib.h"
#include "screen.h"

class ExitScreen : Screen
{
    public:
    ExitScreen();
    ~ExitScreen();
    void Update() override;
    void Draw() override;
    std::string GetTitleText() const override { return "EXIT?"; }
};

#endif