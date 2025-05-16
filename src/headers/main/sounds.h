#ifndef SOUNDS_H
#define SOUNDS_H

#include "../raylib/raylib.h"
#include "../main/globals.hpp"

class Sounds
{
    public:
    Sounds();
    ~Sounds();
    static void LoadContent();
    static void UnloadContent();
    static Sound jump;
    static Sound success;
    static Sound lSwitch;
    static Sound fredBoop;
    static Music itsPizzaTime;
    static Music menuMusic;
    static Music tutorialMusic;
};

#endif
