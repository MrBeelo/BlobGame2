#include "../headers/screen/win_screen.h"
#include "../headers/main/globals.hpp"
#include "../headers/raylib/raygui.h"

WinScreen::WinScreen() {}
WinScreen::~WinScreen() {}

void WinScreen::Update() {}

void WinScreen::Draw() {
    DrawCenteredTitle();

    if (DrawCenteredButton("BACK TO MAIN MENU")) gameState = MAIN_MENU;
    if (DrawCenteredButton("PLAY AGAIN", buttonSize.y + buffer)) gameState = PLAYING;
}