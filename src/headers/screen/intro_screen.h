#ifndef INTRO_SCREEN_H
#define INTRO_SCREEN_H

#include "../raylib/raylib.h"
#include "../main/timer.h"
#include "screen.h"

class IntroScreen : Screen
{
    public:
    IntroScreen();
    ~IntroScreen();
    void Update() override;
    void Draw() override;
    std::string GetTitleText() const override { return ""; }
    static void Start();
    static void AddText();
    static int textCounter;
    static Timer textTimer;
    const char *text1 = "And here begins a thrilling journey,";
    const char *text2 = "with a stupid colorful cube with legs,";
    const char *text3 = "looking for the 'win block',";
    const char *text4 = "and so, the blob goes forth.";
    const int fontsize = 48;
};

#endif