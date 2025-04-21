#include "../headers/screen/pass_screen.h"
#include "../headers/main/globals.hpp"

PassScreen::PassScreen() {}
PassScreen::~PassScreen() {}

void PassScreen::Update() 
{
    button1.Update();
    
    if (button1.IsClicked()) gameState = PLAYING;
}

void PassScreen::Draw() {
    DrawCenteredTitle();
    
    button1.Draw();
}