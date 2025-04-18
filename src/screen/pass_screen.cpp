#include "../headers/screen/pass_screen.h"
#include "../headers/main/globals.hpp"
#include "../headers/raylib/raygui.h"

PassScreen::PassScreen() {}
PassScreen::~PassScreen() {}

void PassScreen::Update() {}

void PassScreen::Draw() {
    DrawCenteredTitle();

    if (DrawCenteredButton("NEXT LEVEL")) gameState = PLAYING;
}