#include "../headers/main_menu_screen.h"
#include "../headers/text.hpp"
#include "../headers/globals.hpp"
#include "../headers/raygui.h"

MainMenuScreen::MainMenuScreen() {}

void MainMenuScreen::Update() {}

void MainMenuScreen::Draw()
{
    Text::DrawOutfitBoldText(GetTitleText().c_str(), {windowSize.x / 2 - Text::MeasureOutfitBoldText(GetTitleText().c_str(), titleTextFontSize).x / 2, buffer}, titleTextFontSize, BLACK);
    
    Vector2 startButtonPos = {windowSize.x / 2 - buttonSize.x / 2, windowSize.y / 2 - buttonSize.y / 2};
    const char *startButtonText = "START GAME";
    if (GuiButton((Rectangle){startButtonPos.x, startButtonPos.y, buttonSize.x, buttonSize.y}, startButtonText)) gameState = PLAYING;
    
    Vector2 quitButtonPos = {windowSize.x / 2 - buttonSize.x / 2, windowSize.y / 2 - buttonSize.y / 2 + buttonSize.y + buffer};
    const char *quitButtonText = "EXIT";
    if (GuiButton((Rectangle){quitButtonPos.x, quitButtonPos.y, buttonSize.x, buttonSize.y}, quitButtonText)) gameState = EXIT;
}