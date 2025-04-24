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
    const char *buttonText1 = "YES";
    const char *buttonText2 = "NO";
    Vector2 buttonSize1 = Button::CalculateSizeDefault(buttonText1);
    Vector2 buttonSize2 = Button::CalculateSizeDefault(buttonText2);
    Button button1 = {GetCenteredPosition(buttonSize1), buttonSize1, buttonText1};
    Button button2 = {GetCenteredPosition(buttonSize2, {0, buffer + buttonSize2.y}), buttonSize2, buttonText2};
};

#endif