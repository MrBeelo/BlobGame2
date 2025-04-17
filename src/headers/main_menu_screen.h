#ifndef MAIN_MENU_SCREEN_H
#define MAIN_MENU_SCREEN_H

#include "raylib.h"
#include "screen.h"

class MainMenuScreen : Screen
{
    public:
    MainMenuScreen();
    ~MainMenuScreen();
    static void Update();
    static void Draw();
    const static std::string GetTitleText() { return "BLOB GAME 2"; }
};

#endif