#include "../headers/main/text.hpp"
#include "../headers/raylib/raylib.h"
#include <string>


Font Text::OutfitBold;

void Text::LoadContent()
{
    OutfitBold = LoadFont("res/assets/font/outfit_bold.ttf");
}

void Text::UnloadContent()
{
    UnloadFont(OutfitBold);
}

std::string Text::Vector2ToString(Vector2 value)
{
    return "{" + std::to_string(value.x) + ", " + std::to_string(value.y) + "}";
}

void Text::DrawOutfitBoldText(const char *text, Vector2 position, float fontSize, Color color)
{
    DrawTextPro(OutfitBold, text, position, {0, 0}, 0.0f, fontSize, 0.5f, color);
}

Vector2 Text::MeasureOutfitBoldText(const char *text, float fontSize)
{
    return MeasureTextEx(OutfitBold, text, fontSize, 0.5f);
}