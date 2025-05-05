#include "../headers/screen/death_screen.h"
#include "../headers/main/globals.hpp"
#include <string>

DeathScreen::DeathScreen() {}
DeathScreen::~DeathScreen() {}

std::string DeathScreen::deathMessage;

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
    
    Text::DrawOutfitBoldShakyText(deathMessage.c_str(), 
        {simulationSize.x / 2 - Text::MeasureOutfitBoldText(deathMessage.c_str(), 42).x / 2,
            simulationSize.y / 4}, 
        42, WHITE);
}