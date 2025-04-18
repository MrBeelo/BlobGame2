#include "../headers/screen/main_menu_screen.h"
#include "../headers/main/globals.hpp"
#include "../headers/raylib/raygui.h"

MainMenuScreen::MainMenuScreen() {}
MainMenuScreen::~MainMenuScreen() {}

void MainMenuScreen::Update() {}

void MainMenuScreen::Draw() {
    DrawCenteredTitle();

    if (DrawCenteredButton("START GAME")) gameState = PLAYING;
    if (DrawCenteredButton("EXIT", buttonSize.y + buffer)) gameState = EXIT;
}