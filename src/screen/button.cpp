#include "../headers/screen/button.h"
#include "../headers/main/text.hpp"
#include "../headers/main/globals.hpp"
#include "../headers/screen/screen.h"

Button::Button(Vector2 pos, Vector2 size, const char *text, Color hovColor, Color defColor, Color textColor)
{
    this->size = size;
    this->text = text;
    this->pos = pos;
    this->hovColor = hovColor;
    this->defColor = defColor;
    this->textColor = textColor;
}

Button::Button(Vector2 pos, const char *text, Color hovColor, Color defColor, Color textColor)
{
    this->size = CalculateSizeDefault(text);
    this->text = text;
    this->pos = pos;
    this->hovColor = hovColor;
    this->defColor = defColor;
    this->textColor = textColor;
}

Button::Button(float yIndex, const char *text, Color hovColor, Color defColor, Color textColor)
{
    this->size = CalculateSizeDefault(text);
    this->text = text;
    this->pos = Screen::GetCenteredPosition(size, {0, (buffer + size.y) * yIndex});
    this->hovColor = hovColor;
    this->defColor = defColor;
    this->textColor = textColor;
}

Button::~Button() {}

void Button::Update()
{
    if(IsHovered()) buttonColor = hovColor; else buttonColor = defColor;
    UpdateDest();
}

void Button::Draw()
{
    DrawRectangleRoundedLinesEx(dest, 0.5f, 2, 2, buttonColor);
    Text::DrawOutfitBoldText(text, {pos.x + size.x / 2 - Text::MeasureOutfitBoldText(text, textFontSize).x / 2, pos.y + size.y / 2 - Text::MeasureOutfitBoldText(text, textFontSize).y / 2}, textFontSize, textColor);
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

Vector2 Button::CalculateSize(const char *text, float fontSize)
{ return {Text::MeasureOutfitBoldText(text, fontSize).x + buffer * 2, Text::MeasureOutfitBoldText(text, fontSize).y + buffer * 2}; }

Vector2 Button::CalculateSizeDefault(const char *text)
{ return {CalculateSize(text, textFontSize)}; }

