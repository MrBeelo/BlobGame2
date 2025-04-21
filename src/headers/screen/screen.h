// screen.hpp
#pragma once

#include "../main/text.hpp"
#include "../main/globals.hpp"
#include "button.h"

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
        Vector2 pos = { simulationSize.x / 2 - size.x / 2, buffer + yOffset };
        Text::DrawOutfitBoldText(title.c_str(), pos, titleTextFontSize, BLACK);
    }

    Vector2 GetCenteredPosition(Vector2 size, Vector2 offset = {0, 0}) const {
        return {
            simulationSize.x / 2 - size.x / 2 + offset.x,
            simulationSize.y / 2 - size.y / 2 + offset.y
        };
    }
};
