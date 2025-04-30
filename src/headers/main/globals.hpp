#pragma once

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif

#include "../raylib/raylib.h"
#include "../main/stopwatch.h"
#include <cstdlib>
#include <functional>

extern float buffer;
extern Vector2 windowSize;
const extern Vector2 simulationSize;
extern float simDT;
extern bool f3On;
extern int currentLevel;
extern RenderTexture2D target;
extern float scale;
extern Vector2 vMouse;
extern const char *version;
extern Texture2D raylibLogo;
extern const char *credits;
extern Stopwatch speedrunTimer;
extern Color backgroundColor;
extern Image windowIcon;
extern bool isTerminalOpen;
extern float timeLimit;
extern std::string ToStringWithDecimalPoints(float value, int decimalPoints);

enum GameState
{
    PLAYING,
    MAIN_MENU,
    PAUSED,
    EXIT,
    DIED,
    PASS,
    WIN,
    INFO
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
