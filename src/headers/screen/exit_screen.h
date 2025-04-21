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
    Button button1 = {GetCenteredPosition(buttonSize), buttonSize, "YES"};
    Button button2 = {GetCenteredPosition(buttonSize, {0, buffer + buttonSize.y}), buttonSize, "NO"};
};

#endif