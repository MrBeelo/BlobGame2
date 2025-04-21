#include "../headers/screen/button.h"
#include "../headers/main/text.hpp"
#include "../headers/main/globals.hpp"

Button::Button(Vector2 pos, Vector2 size, const char *text)
{
    this->pos = pos;
    this->size = size;
    this->text = text;
}

Button::~Button() {}

void Button::Update()
{
    if(IsHovered()) buttonColor = BLACK; else buttonColor = WHITE;
    UpdateDest();
}

void Button::Draw()
{
    DrawRectangleRoundedLinesEx(dest, 0.5f, 2, 2, buttonColor);
    Text::DrawOutfitBoldText(text, {pos.x + size.x / 2 - Text::MeasureOutfitBoldText(text, 20).x / 2, pos.y + size.y / 2 - Text::MeasureOutfitBoldText(text, 20).y / 2}, 20, textColor);
}

bool Button::IsHovered()
{
    if(CheckCollisionPointRec(vMouse, dest)) return true;
    return false;
}

bool Button::IsClicked()
{
    if(IsHovered() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) return true;
    return false;
}

void Button::UpdateDest()
{
    dest = {pos.x, pos.y, size.x, size.y};
}

