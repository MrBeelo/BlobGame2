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
    Button button1 = {0, introDone ? "CONTINUE GAME" : "START GAME"};
    Button button2 = {1, "MODIFIERS"};
    Button button3 = {2, "INFO/CREDITS"};
    Button button4 = {3, "EXIT"};
};

#endif