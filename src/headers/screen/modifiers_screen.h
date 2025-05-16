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
    std::string label4;
    std::string label5;
    
    Button button1 = {0, "NEED MORE SPEED"};
    Button button2 = {1, "INVERSE"};
    Button button3 = {2, "TICK TOCK"};
    Button button4 = {3, "LIGHTS OUT"};
    Button button5 = {4, "FRED"};
    Button button6 = {5, "BACK"};
};

#endif