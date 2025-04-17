#include "../headers/paused_screen.h"
#include "../headers/text.hpp"
#include "../headers/globals.hpp"
#include "../headers/raygui.h"

PausedScreen::PausedScreen() {}

void PausedScreen::Update() {}

void PausedScreen::Draw()
{
    Text::DrawOutfitBoldText(GetTitleText().c_str(), {windowSize.x / 2 - Text::MeasureOutfitBoldText(GetTitleText().c_str(), titleTextFontSize).x / 2, buffer}, titleTextFontSize, BLACK);
    
    Vector2 continueButtonPos = {windowSize.x / 2 - buttonSize.x / 2, windowSize.y / 2 - buttonSize.y / 2};
    const char *continueButtonText = "CONTINUE";
    if (GuiButton((Rectangle){continueButtonPos.x, continueButtonPos.y, buttonSize.x, buttonSize.y}, continueButtonText)) gameState = PLAYING;
    
    Vector2 backButtonPos = {windowSize.x / 2 - buttonSize.x / 2, windowSize.y / 2 - buttonSize.y / 2 + buttonSize.y + buffer};
    const char *backButtonText = "BACK TO MAIN MENU";
    if (GuiButton((Rectangle){backButtonPos.x, backButtonPos.y, buttonSize.x, buttonSize.y}, backButtonText)) gameState = MAIN_MENU;
}