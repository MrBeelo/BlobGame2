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
    Button button1 = {0, "BACK TO MAIN MENU"};
    Button button2 = {1, "PLAY AGAIN"};
    const char *winText = "That was it. Now play again or get out.";
    const char *modReminderText = "Oh yeah there are also some modifiers if you wanna check them out.";
};

#endif