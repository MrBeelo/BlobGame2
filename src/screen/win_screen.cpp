#include "../headers/screen/win_screen.h"
#include "../headers/main/globals.hpp"

WinScreen::WinScreen() {}
WinScreen::~WinScreen() {}

void WinScreen::Update() 
{
    button1.Update();
    button2.Update(); 
    
    if (button1.IsClicked()) gameState = MAIN_MENU;
    if (button2.IsClicked()) {
        gameState = PLAYING;
        speedrunTimer.Start();
    }
}

void WinScreen::Draw() {
    DrawCenteredTitle(0, GOLD);
    
    button1.Draw();
    button2.Draw();
    
    Text::DrawOutfitBoldText(winText, {Text::GetCenteredOutfitBoldXPos(winText, 32), 100}, 32, WHITE);
    Text::DrawOutfitBoldText(modReminderText, {Text::GetCenteredOutfitBoldXPos(modReminderText, 32), 140}, 32, WHITE);
}