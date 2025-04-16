#pragma once

#include "raylib.h"
#include <string>
#include <vector>

extern float buffer;
extern Vector2 windowSize;
extern float simDT;
extern bool f3On;
extern int currentLevel;

enum GameState
{
    PLAYING,
    MAIN_MENU
};

extern GameState gameState;

extern void LeaveGame();

struct Vector2Hash {
    std::size_t operator()(const Vector2& v) const {
        std::hash<float> hasher;
        return hasher(v.x) ^ (hasher(v.y) << 1); // simple hash combiner
    }
};

struct Vector2Equal {
    bool operator()(const Vector2& a, const Vector2& b) const {
        return std::abs(a.x - b.x) < 0.001f && std::abs(a.y - b.y) < 0.001f;
    }
};
