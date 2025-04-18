// screen.hpp
#pragma once

#include "../main/text.hpp"
#include "../main/globals.hpp"
#include "../raylib/raygui.h"

class Screen {
public:
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual std::string GetTitleText() const { return "Screen"; }
    virtual ~Screen() = default;
    int titleTextFontSize = 32;
    Vector2 buttonSize = {180, 50};

protected:
    void DrawCenteredTitle(float yOffset = 0) const {
        const std::string title = GetTitleText();
        Vector2 size = Text::MeasureOutfitBoldText(title.c_str(), titleTextFontSize);
        Vector2 pos = { windowSize.x / 2 - size.x / 2, buffer + yOffset };
        Text::DrawOutfitBoldText(title.c_str(), pos, titleTextFontSize, BLACK);
    }

    Vector2 GetCenteredPosition(Vector2 size, float yOffset = 0) const {
        return {
            windowSize.x / 2 - size.x / 2,
            windowSize.y / 2 - size.y / 2 + yOffset
        };
    }

    bool DrawCenteredButton(const char* text, float yOffset = 0) const {
        Vector2 pos = GetCenteredPosition(buttonSize, yOffset);
        return GuiButton({pos.x, pos.y, buttonSize.x, buttonSize.y}, text);
    }
};
