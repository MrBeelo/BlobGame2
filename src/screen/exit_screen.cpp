#include "../headers/screen/exit_screen.h"
#include "../headers/main/globals.hpp"
#include "../headers/raylib/raygui.h"

ExitScreen::ExitScreen() {}
ExitScreen::~ExitScreen() {}

void ExitScreen::Update() {}

void ExitScreen::Draw()
{
    DrawCenteredTitle();

    if (DrawCenteredButton("YES")) LeaveGame();
    if (DrawCenteredButton("NO", buttonSize.y + buffer)) gameState = MAIN_MENU;
}