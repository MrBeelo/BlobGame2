#include "../headers/main_menu_screen.h"
#include "../headers/text.hpp"
#include "../headers/globals.h"
#include "../headers/raygui.h"

MainMenuScreen::MainMenuScreen() {}

void MainMenuScreen::Update() {}

void MainMenuScreen::Draw()
{
    const char *titleText = "BLOB GAME 2";
    const int titleTextFontSize = 32;
    
    Text::DrawOutfitBoldText(titleText, {windowSize.x / 2 - Text::MeasureOutfitBoldText(titleText, titleTextFontSize).x / 2, buffer}, titleTextFontSize, BLACK);
    
    const Vector2 startButtonSize = {120, 30};
    Vector2 startButtonPos = {windowSize.x / 2 - startButtonSize.x / 2, windowSize.y / 2 - startButtonSize.y / 2};
    const char *startButtonText = "START GAME";
    
    if (GuiButton((Rectangle){startButtonPos.x, startButtonPos.y, startButtonSize.x, startButtonSize.y}, startButtonText)) 
    {
        gameState = PLAYING;
    }
    
    const Vector2 quitButtonSize = {120, 30};
    Vector2 quitButtonPos = {windowSize.x / 2 - quitButtonSize.x / 2, windowSize.y / 2 - quitButtonSize.y / 2 + startButtonSize.y + buffer};
    const char *quitButtonText = "EXIT";
    
    if (GuiButton((Rectangle){quitButtonPos.x, quitButtonPos.y, quitButtonSize.x, quitButtonSize.y}, quitButtonText)) 
    {
        LeaveGame();
    }
}