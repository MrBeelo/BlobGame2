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
    Button(Vector2 pos, Vector2 size, const char *text);
    ~Button();
    void Update();
    void Draw();
    bool IsHovered();
    bool IsClicked();
    void UpdateDest();
    Color buttonColor = WHITE;
    Color textColor = BLACK;
};

#endif