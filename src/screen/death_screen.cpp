#include "../headers/screen/death_screen.h"
#include "../headers/main/globals.hpp"

DeathScreen::DeathScreen() {}
DeathScreen::~DeathScreen() {}

void DeathScreen::Update() 
{
    button1.Update();
    button2.Update(); 
    
    if(button1.IsClicked()) {
        gameState = PLAYING;
        speedrunTimer.Start();
    }
    
    if(button2.IsClicked()) gameState = MAIN_MENU;
}

void DeathScreen::Draw()
{
    DrawCenteredTitle();
    
    button1.Draw();
    button2.Draw();
}