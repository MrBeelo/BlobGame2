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
    const char *buttonText1 = "NEXT LEVEL";
    Vector2 buttonSize1 = Button::CalculateSizeDefault(buttonText1);
    Button button1 = {GetCenteredPosition(buttonSize1), buttonSize1, buttonText1};
};

#endif