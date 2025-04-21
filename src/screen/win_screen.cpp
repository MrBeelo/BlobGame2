#include "../headers/screen/win_screen.h"
#include "../headers/main/globals.hpp"

WinScreen::WinScreen() {}
WinScreen::~WinScreen() {}

void WinScreen::Update() 
{
    button1.Update();
    button2.Update(); 
    
    if (button1.IsClicked()) gameState = MAIN_MENU;
    if (button2.IsClicked()) gameState = PLAYING;
}

void WinScreen::Draw() {
    DrawCenteredTitle();
    
    button1.Draw();
    button2.Draw();
}