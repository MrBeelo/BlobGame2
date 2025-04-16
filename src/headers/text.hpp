#ifndef TEXT_H
#define TEXT_H

#include "raylib.h"
#include <string>

class Text
{
    public:
    static Font OutfitBold;
    static void LoadContent();
    static void UnloadContent();
    static std::string Vector2ToString(Vector2 value);
    static void DrawOutfitBoldText(const char *text, Vector2 position, float fontSize, Color color);
};

#endif