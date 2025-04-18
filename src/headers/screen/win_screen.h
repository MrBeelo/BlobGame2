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
};

#endif