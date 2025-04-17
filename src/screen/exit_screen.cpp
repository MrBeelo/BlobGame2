#include "../headers/exit_screen.h"
#include "../headers/text.hpp"
#include "../headers/globals.hpp"
#include "../headers/raygui.h"

ExitScreen::ExitScreen() {}

void ExitScreen::Update() {}

void ExitScreen::Draw()
{
    Text::DrawOutfitBoldText(GetTitleText().c_str(), {windowSize.x / 2 - Text::MeasureOutfitBoldText(GetTitleText().c_str(), titleTextFontSize).x / 2, buffer}, titleTextFontSize, BLACK);
    
    Vector2 yesButtonPos = {windowSize.x / 2 - buttonSize.x / 2, windowSize.y / 2 - buttonSize.y / 2};
    const char *yesButtonText = "YES";
    if (GuiButton((Rectangle){yesButtonPos.x, yesButtonPos.y, buttonSize.x, buttonSize.y}, yesButtonText)) LeaveGame();
    
    Vector2 noButtonPos = {windowSize.x / 2 - buttonSize.x / 2, windowSize.y / 2 - buttonSize.y / 2 + buttonSize.y + buffer};
    const char *noButtonText = "NO";
    if (GuiButton((Rectangle){noButtonPos.x, noButtonPos.y, buttonSize.x, buttonSize.y}, noButtonText)) gameState = MAIN_MENU;
}