#ifndef WIN_SCREEN_H
#define WIN_SCREEN_H

#include "../raylib/raylib.h"
#include "screen.h"

class WinScreen : Screen
{
    public:
    WinScreen();
    ~WinScreen();
    void Update() override;
    void Draw() override;
    std::string GetTitleText() const override { return "YOU WIN"; }
    Button button1 = {GetCenteredPosition(buttonSize), buttonSize, "BACK TO MAIN MENU"};
    Button button2 = {GetCenteredPosition(buttonSize, {0, buffer + buttonSize.y}), buttonSize, "PLAY AGAIN"};
};

#endif