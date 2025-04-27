#ifndef BUTTON_H
#define BUTTON_H

#include "../raylib/raylib.h"

class Button
{
    public:
    Vector2 pos;
    Vector2 size;
    Rectangle dest;
    const char *text;
    Color hovColor;
    Color defColor;
    Button(float yIndex, const char *text, Color hovColor = WHITE, Color defColor = BLACK, Color textColor = BLACK);
    Button(Vector2 pos, const char *text, Color hovColor = WHITE, Color defColor = BLACK, Color textColor = BLACK);
    Button(Vector2 pos, Vector2 size, const char *text, Color hovColor = WHITE, Color defColor = BLACK, Color textColor = BLACK);
    ~Button();
    void Update();
    void Draw();
    bool IsHovered();
    bool IsClicked();
    void UpdateDest();
    Color buttonColor = WHITE;
    Color textColor = BLACK;
    static Vector2 CalculateSize(const char *text, float fontSize);
    static Vector2 CalculateSizeDefault(const char *text);
    const static int textFontSize = 20;
};

#endif