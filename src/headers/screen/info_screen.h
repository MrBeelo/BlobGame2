#ifndef INFO_SCREEN_H
#define INFO_SCREEN_H

#include "../raylib/raylib.h"
#include "screen.h"

class InfoScreen : Screen
{
    public:
    InfoScreen();
    ~InfoScreen();
    void Update() override;
    void Draw() override;
    std::string GetTitleText() const override { return "INFO / CREDITS"; }
    Button button1 = {8,  "BACK"};
};

#endif