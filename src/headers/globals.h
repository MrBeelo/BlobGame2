#pragma once

#include "raylib.h"

extern float buffer;
extern Vector2 windowSize;
extern float simDT;

enum GameState
{
    PLAYING,
    MAIN_MENU
};

extern GameState gameState;

extern void LeaveGame();
