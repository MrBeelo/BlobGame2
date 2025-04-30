#ifndef MODIFIERS_SCREEN_H
#define MODIFIERS_SCREEN_H

#include "../raylib/raylib.h"
#include "screen.h"

class ModifiersScreen : Screen
{
    public:
    ModifiersScreen();
    ~ModifiersScreen();
    void Update() override;
    void Draw() override;
    std::string GetTitleText() const override { return "MODIFIERS"; }
    
    std::string label1;
    std::string label2;
    std::string label3;
    
    Button button1 = {0, "NEED MORE SPEED", GOLD, WHITE, WHITE};
    Button button2 = {1, "INVERSE", GOLD, WHITE, WHITE};
    Button button3 = {2, "TICK TOCK", GOLD, WHITE, WHITE};
    Button button4 = {3, "BACK", GOLD, WHITE, WHITE};
};

#endif