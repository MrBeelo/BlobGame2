#include "../headers/screen/paused_screen.h"
#include "../headers/main/globals.hpp"

PausedScreen::PausedScreen() {}
PausedScreen::~PausedScreen() {}

void PausedScreen::Update() 
{
    button1.Update();
    button2.Update(); 
    
    if (button1.IsClicked()) gameState = PLAYING;
    if (button2.IsClicked()) gameState = MAIN_MENU;
}

void PausedScreen::Draw()
{
    DrawCenteredTitle();
    
    button1.Draw();
    button2.Draw();
}