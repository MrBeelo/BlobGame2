#include "../headers/screen/paused_screen.h"
#include "../headers/main/globals.hpp"
#include "../headers/raylib/raygui.h"

PausedScreen::PausedScreen() {}
PausedScreen::~PausedScreen() {}

void PausedScreen::Update() {}

void PausedScreen::Draw()
{
    DrawCenteredTitle();

    if (DrawCenteredButton("CONTINUE")) gameState = PLAYING;
    if (DrawCenteredButton("BACK TO MAIN MENU", buttonSize.y + buffer)) gameState = MAIN_MENU;
}