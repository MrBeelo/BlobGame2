#pragma once

#include "raylib.h"

extern float buffer;
extern Vector2 windowSize;
extern float simDT;
extern bool f3On;

enum GameState
{
    PLAYING,
    MAIN_MENU
};

extern GameState gameState;

extern void LeaveGame();
