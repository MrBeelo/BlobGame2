#ifndef EXIT_SCREEN_H
#define EXIT_SCREEN_H

#include "raylib.h"
#include "screen.h"

class ExitScreen : Screen
{
    public:
    ExitScreen();
    ~ExitScreen();
    static void Update();
    static void Draw();
    const static std::string GetTitleText() { return "EXIT?"; }
};

#endif