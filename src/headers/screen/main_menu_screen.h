#ifndef MAIN_MENU_SCREEN_H
#define MAIN_MENU_SCREEN_H

#include "../raylib/raylib.h"
#include "screen.h"

class MainMenuScreen : Screen
{
    public:
    MainMenuScreen();
    ~MainMenuScreen();
    void Update() override;
    void Draw() override;
    std::string GetTitleText() const override { return "BLOB GAME 2"; }
    Button button1 = {0, "START GAME"};
    Button button2 = {1, "INFO/CREDITS"};
    Button button3 = {2, "EXIT"};
};

#endif