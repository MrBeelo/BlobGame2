#include "../headers/screen/death_screen.h"
#include "../headers/main/globals.hpp"
#include "../headers/raylib/raygui.h"

DeathScreen::DeathScreen() {}
DeathScreen::~DeathScreen() {}

void DeathScreen::Update() {}

void DeathScreen::Draw()
{
    DrawCenteredTitle();

    if (DrawCenteredButton("RESTART")) {
        gameState = PLAYING;
    }
    if (DrawCenteredButton("LEAVE", buttonSize.y + buffer)) gameState = MAIN_MENU;
}